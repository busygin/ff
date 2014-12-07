/*
 * fast_fields.h
 *
 *  Created on: Jul 18, 2014
 *      Author: busygin
 */

#ifndef FAST_FIELDS_H_
#define FAST_FIELDS_H_

#include <cstring>
#include <string>
#include <utility>
#include <type_traits>
#include "optional.h"
#include "pmap.h"
#include "utils.h"


namespace FIX {


template<typename T>
inline void unsigned_fast_scan_without_null(T& value, const char* &buf, const char* end) {
	value = 0;
	while ((*buf & '\x80') == 0) {
		value = (value << 7) + static_cast<uint8_t>(*buf);
		++buf;
#ifdef BUFFER_RANGE_CHECK
		if (buf >= end)
			throw UnexpectedEndOfMessageBuffer();
#endif
	}
	value = (value << 7) + static_cast<uint8_t>(*buf++ ^ '\x80');
}

template<typename T>
inline void unsigned_fast_encode_without_null(const T& value, char* &buf, char* end) {
	char* p(buf);
	T x(value);
	do {
#ifdef BUFFER_RANGE_CHECK
		if (buf >= end)
			throw UnexpectedEndOfMessageBuffer();
#endif
		char byte = static_cast<char>(x & '\x7F');
		x >>= 7;
		*buf++ = byte;
	} while(x);
	*p |= '\x80';
	char* p1(buf-1);
	while (p<p1) std::swap(*p++, *p1--);
}

template<typename T>
inline void signed_fast_scan_without_null(T& value, const char* &buf, const char* end) {
	char byte(*buf);
	bool sign_bit( (byte&'\x40') != 0 );
	byte &= '\xBF';
	value = (sign_bit ? T(-1)<<6 : 0);
	while( (byte&'\x80') == 0 ) {
		value = (value + byte) << 7;
		++buf;
#ifdef BUFFER_RANGE_CHECK
		if (buf>=end)
			throw UnexpectedEndOfMessageBuffer();
#endif
		byte = *buf;
	}
	value += byte^'\x80';
	++buf;
}

template<typename T>
inline void signed_fast_encode_without_null(const T& value, char* &buf, char* end) {
	char* p(buf);
	T x(value);
	bool sign_bit = (value<0);
	char byte;
	if (sign_bit) {
		x = ~x;
		do {
#ifdef BUFFER_RANGE_CHECK
			if (buf >= end)
				throw UnexpectedEndOfMessageBuffer();
#endif
			byte = static_cast<char>(x & '\x7F') ^ '\x7F';
			x >>= 7;
			*buf++ = byte;
		} while(x);
		if (!(byte & '\x40')) {
#ifdef BUFFER_RANGE_CHECK
			if (buf >= end)
				throw UnexpectedEndOfMessageBuffer();
#endif
			*buf++ = '\x7F';
		}
	} else {
		do {
#ifdef BUFFER_RANGE_CHECK
			if (buf >= end)
				throw UnexpectedEndOfMessageBuffer();
#endif
			byte = static_cast<char>(x & '\x7F');
			x >>= 7;
			*buf++ = byte;
		} while(x);
		if (byte & '\x40') {
#ifdef BUFFER_RANGE_CHECK
			if (buf >= end)
				throw UnexpectedEndOfMessageBuffer();
#endif
			*buf++ = 0;
		}
	}
	*p |= '\x80';
	char* p1(buf-1);
	while (p<p1) std::swap(*p++, *p1--);
}

template<typename T>
inline void unsigned_fast_scan_with_null(Optional<T>& value, const char* &buf, const char* end) {
	value = 0;
	unsigned_fast_scan_without_null(*value, buf, end);
	if (*value==0) value.disable();
	else if (*value>0) --(*value);
}

template<typename T>
inline void unsigned_fast_encode_with_null(const Optional<T>& value, char* &buf, char* end) {
	if (value) {
		T x(*value + 1);
		unsigned_fast_encode_without_null(x, buf, end);
	} else {
#ifdef BUFFER_RANGE_CHECK
		if (buf >= end)
			throw UnexpectedEndOfMessageBuffer();
#endif
		*buf++ = '\x80';
	}
}

template<typename T>
inline void signed_fast_scan_with_null(Optional<T>& value, const char* &buf, const char* end) {
	value = 0;
	signed_fast_scan_without_null(*value, buf, end);
	if (*value==0) value.disable();
	else if (*value>0) --(*value);
}

template<typename T>
inline void signed_fast_encode_with_null(const Optional<T>& value, char* &buf, char* end) {
	if (value) {
		T x(*value);
		if (x>=0) ++x;
		signed_fast_encode_without_null(x, buf, end);
	} else {
#ifdef BUFFER_RANGE_CHECK
		if (buf >= end)
			throw UnexpectedEndOfMessageBuffer();
#endif
		*buf++ = '\x80';
	}
}

template<typename T>
void fast_scan_without_null(T& value, const char* &buf, const char* end) {
	if (std::is_unsigned<T>::value) unsigned_fast_scan_without_null(value, buf, end);
	else signed_fast_scan_without_null(value, buf, end);
}

template<typename T>
void fast_encode_without_null(const T& value, char* &buf, char* end) {
	if (std::is_unsigned<T>::value) unsigned_fast_encode_without_null(value, buf, end);
	else signed_fast_encode_without_null(value, buf, end);
}

template<typename T>
void fast_scan_with_null(Optional<T>& value, const char* &buf, const char* end) {
	if (std::is_unsigned<T>::value) unsigned_fast_scan_with_null(value, buf, end);
	else signed_fast_scan_with_null(value, buf, end);
}

template<typename T>
void fast_encode_with_null(const Optional<T>& value, char* &buf, char* end) {
	if (std::is_unsigned<T>::value) unsigned_fast_encode_with_null(value, buf, end);
	else signed_fast_encode_with_null(value, buf, end);
}

template<>
inline void fast_scan_without_null<std::string>(std::string& value, const char* &buf, const char* end) {
	const char* p(buf);
	while( (*p&'\x80') == 0 ) {
		++p;
#ifdef BUFFER_RANGE_CHECK
		if (p>=end)
			throw UnexpectedEndOfMessageBuffer();
#endif
	}
	++p;
	value.assign(buf, p);
	value.back() ^= '\x80';
	buf = p;
	if (value[0]=='\0') value.clear();
}

template<>
inline void fast_encode_without_null<std::string>(const std::string& value, char* &buf, char* end) {
	size_t len = value.length();
	if (len) {
#ifdef BUFFER_RANGE_CHECK
		if (end < buf+len)
			throw UnexpectedEndOfMessageBuffer();
#endif
		memcpy(buf, &value[0], len);
		buf += len-1;
		*buf++ |= '\x80';
	} else {
#ifdef BUFFER_RANGE_CHECK
		if (buf >= end)
			throw UnexpectedEndOfMessageBuffer();
#endif
		*buf++ = '\x80';
	}
}

template<>
void fast_scan_with_null<std::string>(Optional<std::string>& value, const char* &buf, const char* end) {
	const char* p(buf);
	while ((*p & '\x80') == 0) {
		++p;
#ifdef BUFFER_RANGE_CHECK
		if (p >= end)
			throw UnexpectedEndOfMessageBuffer();
#endif
	}
	++p;
	value = "";
	value->assign(buf, p);
	value->back() ^= '\x80';
	buf = p;
	bool is_empty = ((*value)[0]=='\0');
	if (is_empty) {
		if (value->size()<=1) value.disable();
		else value->clear();
	}
}

template<>
void fast_encode_with_null<std::string>(const Optional<std::string>& value, char* &buf, char* end) {
	if (value) {
		size_t len = value->length();
		if (len) {
#ifdef BUFFER_RANGE_CHECK
			if (end < buf+len)
				throw UnexpectedEndOfMessageBuffer();
#endif
			memcpy(buf, &(*value)[0], len);
			buf += len-1;
			*buf++ |= '\x80';
		} else {
#ifdef BUFFER_RANGE_CHECK
			if (buf+1 >= end)
				throw UnexpectedEndOfMessageBuffer();
#endif
			*buf++ = 0;
			*buf++ = '\x80';
		}
	} else {
#ifdef BUFFER_RANGE_CHECK
		if (buf >= end)
			throw UnexpectedEndOfMessageBuffer();
#endif
		*buf++ = '\x80';
	}
}


template<>
void fast_scan_without_null<PMap>(PMap& value, const char* &buf, const char* end) {
	value.clear();
	while(true) {
		char mask = *buf++;
		for (char b='\x40'; b; b>>=1)
			value.push_back(mask&b);
		if ((mask&'\x80') != 0) break;
#ifdef BUFFER_RANGE_CHECK
		if (buf>=end)
			throw UnexpectedEndOfMessageBuffer();
#endif
	}
	value.reset();
}

template<>
void fast_encode_without_null<PMap>(const PMap& value, char* &buf, char* end) {
#ifdef BUFFER_RANGE_CHECK
	if (buf>=end)
		throw UnexpectedEndOfMessageBuffer();
#endif
	if (!value.empty()) {
		PMap pm(value);
		*buf = 0;
		char mask = '\x40';
		while (true) {
			if (*pm) *buf |= mask;
			pm.clear_bit();
			if (pm.empty())
				break;
			mask >>= 1;
			if (!mask) {
				++buf;
#ifdef BUFFER_RANGE_CHECK
				if (buf>=end)
					throw UnexpectedEndOfMessageBuffer();
#endif
				*buf = 0;
				mask = '\x40';
			}
		}
		*buf++ |= '\x80';
	} else *buf++ = '\x80';
}


template<typename T, size_t NUMBER>
class FastField {
	Optional<T> value_;

public:
	FastField() { }
	FastField(const T& val) : value_(val) { }

	bool defined() const { return bool(value_); }

	const T& value() const { return *value_; }
	T& value() { return *value_; }

	void assign(const T& val) {	value_ = val; }

	void clear() { value_.disable(); }

	static constexpr size_t number() { return NUMBER; }

	template<typename FieldOp>
	bool scan(const char* &buf, const char* end, FieldOp& op, PMap& pmap) {
		op.scan(value_, buf, end, pmap);
		return defined();
	}

	template<typename FieldOp>
	void encode(char* &buf, char* end, FieldOp& op, PMap& pmap) {
		op.encode(value_, buf, end, pmap);
	}
};

template<size_t NUMBER>
class FastField<Decimal, NUMBER> {
	Decimal value_;
	Optional<int64_t> mant_value_;
	Optional<int32_t> exp_value_;

public:
	FastField() { }
	FastField(const Decimal& val) : value_(val), mant_value_(val.exponent), exp_value_(val.mantissa) { }

	bool defined() const { return bool(mant_value_); }

	const Decimal& value() const { return value_; }
	Decimal& value() { return value_; }

	void assign(const Decimal& val) {
		value_ = val;
		mant_value_ = val.mantissa;
		exp_value_ = val.exponent;
	}

	void clear() {
		mant_value_.disable();
		exp_value_.disable();
	}

	static constexpr size_t number() { return NUMBER; }

	template<typename FieldOpMant, typename FieldOpExp>
	bool scan(const char* &buf, const char* end, FieldOpMant& op_mant, FieldOpExp& op_exp, PMap& pmap) {
		op_mant.scan(mant_value_, buf, end, pmap);
		op_exp.scan(exp_value_, buf, end, pmap);
		value_.mantissa = *mant_value_;
		value_.exponent = *exp_value_;
		return defined();
	}

	template<typename FieldOpMant, typename FieldOpExp>
	void encode(char* &buf, char* end, FieldOpMant& op_mant, FieldOpExp& op_exp, PMap& pmap) {
		op_mant.encode(mant_value_, buf, end, pmap);
		op_exp.encode(exp_value_, buf, end, pmap);
	}
};


template<typename T, size_t NUMBER>
class NoOperatorMandatoryField {
public:
	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		fast_scan_without_null(*value, buf, end);
		value.enable();
	}

	void encode(const Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		fast_encode_without_null(*value, buf, end);
	}

	void reset() { }
};

template<typename T, size_t NUMBER>
class NoOperatorOptionalField {
public:
	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		fast_scan_with_null(value, buf, end);
	}

	void encode(const Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		fast_encode_with_null(value, buf, end);
	}

	void reset() { }
};

template<typename T, size_t NUMBER>
class ConstantMandatoryField {
	T value_;

public:
	ConstantMandatoryField() { }
	ConstantMandatoryField(const T& val) : value_(val) { }

	const T& const_value() const { return value_; }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		if (!bool(value))
			value = value_;
	}

	void encode(const Optional<T>& value, char* &buf, char* end, PMap& pmap) { }

	void reset() { }
};

template<typename T, size_t NUMBER>
class ConstantOptionalField {
	T value_;

public:
	ConstantOptionalField() { }
	ConstantOptionalField(const T& val) : value_(val) { }

	const T& const_value() const { return value_; }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		if (pmap.fetch_bit())
			value = value_;
		else
			value.disable();
	}

	void encode(const Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		pmap.push_back(bool(value));
	}

	void reset() { }
};

template<typename T, size_t NUMBER>
class CopyMandatoryField {
	Optional<T> init_value_;
	Optional<T> prev_value_;
	bool prev_value_undefinite_;

public:
	CopyMandatoryField(): prev_value_undefinite_(true) { }
	CopyMandatoryField(const T& val) : init_value_(val), prev_value_undefinite_(true) { }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		if (pmap.fetch_bit()) {
			fast_scan_without_null(*value, buf, end);
			value.enable();
			prev_value_ = value;
			prev_value_undefinite_ = false;
		} else {
			if (prev_value_undefinite_) {
				if (init_value_) {
					prev_value_ = init_value_;
					value = init_value_;
				} else
					throw MandatoryFastFieldAbsent(number());
				prev_value_undefinite_ = false;
			} else {
				if (prev_value_)
					value = prev_value_;
				else
					throw MandatoryFastFieldAbsent(number());
			}
		}
	}

	void encode(const Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		if (prev_value_undefinite_) {
			if (value) {
				fast_encode_without_null(*value, buf, end);
				pmap.push_back(true);
				prev_value_ = value;
				prev_value_undefinite_ = false;
			} else pmap.push_back(false);
		} else {
			if (value==prev_value_)
				pmap.push_back(false);
			else {
				fast_encode_without_null(*value, buf, end);
				pmap.push_back(true);
				prev_value_ = value;
			}
		}
	}

	void reset() {
		prev_value_.disable();
		prev_value_undefinite_ = true;
	}
};

template<typename T, size_t NUMBER>
class CopyOptionalField {
	Optional<T> init_value_;
	Optional<T> prev_value_;
	bool prev_value_undefinite_;

public:
	CopyOptionalField(): prev_value_undefinite_(true) { }
	CopyOptionalField(const T& val) : init_value_(val), prev_value_undefinite_(true) { }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		if (pmap.fetch_bit()) {
			fast_scan_with_null(value, buf, end);
			if (value)
				prev_value_ = value;
			else
				prev_value_.disable();
			prev_value_undefinite_ = false;
		} else {
			if (prev_value_undefinite_) {
				if (init_value_) {
					prev_value_ = init_value_;
					value = init_value_;
				} else
					prev_value_.disable();
				prev_value_undefinite_ = false;
			} else {
				if (prev_value_) value = prev_value_;
			}
		}
	}

	void encode(const Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		if (prev_value_undefinite_) {
			if (value) {
				fast_encode_with_null(value, buf, end);
				pmap.push_back(true);
				prev_value_ = value;
				prev_value_undefinite_ = false;
			} else pmap.push_back(false);
		} else {
			if (value==prev_value_)
				pmap.push_back(false);
			else {
				fast_encode_with_null(value, buf, end);
				pmap.push_back(true);
				prev_value_ = value;
			}
		}
	}

	void reset() {
		prev_value_.disable();
		prev_value_undefinite_ = true;
	}
};

template<typename T, size_t NUMBER>
class DefaultMandatoryField {
	Optional<T> init_value_;

public:
	DefaultMandatoryField() { }
	DefaultMandatoryField(const T& val) : init_value_(val) { }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		if (pmap.fetch_bit()) {
			fast_scan_without_null(*value, buf, end);
			value.enable();
		} else {
			if (init_value_)
				value = init_value_;
			else
				throw MandatoryFastFieldAbsent(number());
		}
	}

	void encode(const Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		if (value==init_value_) pmap.push_back(false);
		else {
			fast_encode_without_null(*value, buf, end);
			pmap.push_back(true);
		}
	}

	void reset() { }
};

template<typename T, size_t NUMBER>
class DefaultOptionalField {
	Optional<T> init_value_;

public:
	DefaultOptionalField() { }
	DefaultOptionalField(const T& val) : init_value_(val) { }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		if (pmap.fetch_bit())
			fast_scan_with_null(value, buf, end);
		else {
			if (init_value_)
				value = init_value_;
			else
				value.disable();
		}
	}

	void encode(const Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		if (value==init_value_) pmap.push_back(false);
		else {
			fast_encode_with_null(value, buf, end);
			pmap.push_back(true);
		}
	}

	void reset() { }
};

template<typename T, size_t NUMBER>
class DeltaMandatoryField {
	T init_value_;  // NB: init_value_ must be initialized by base value if specific init is absent
	Optional<T> prev_value_;
	bool prev_value_undefinite_;

public:
	DeltaMandatoryField(): init_value_(), prev_value_undefinite_(true) { }
	DeltaMandatoryField(const T& val) : init_value_(val), prev_value_undefinite_(true) { }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		fast_scan_without_null(*value, buf, end);
		value.enable();
		if (prev_value_)
			*value += *prev_value_;
		else {
			if (prev_value_undefinite_) {
				*value += init_value_;
				prev_value_undefinite_ = false;
			} else
				throw MissingPreviousValueInFastDeltaField(number());
		}
		prev_value_ = value;
	}

	void encode(Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		if (value) {
			T x = *value - (prev_value_undefinite_ ? init_value_ : *prev_value_);
			prev_value_ = x;
				fast_encode_without_null(x, buf, end);
			prev_value_undefinite_ = false;
		} else
			throw MandatoryFastFieldAbsent(number());
	}

	void reset() {
		prev_value_.disable();
		prev_value_undefinite_ = true;
	}
};

template<typename T, size_t NUMBER>
class DeltaOptionalField {
	T init_value_;  // NB: init_value_ must be initialized by base value if specific init is absent
	Optional<T> prev_value_;
	bool prev_value_undefinite_;

public:
	DeltaOptionalField(): init_value_(), prev_value_undefinite_(true) { }
	DeltaOptionalField(const T& val) : init_value_(val), prev_value_undefinite_(true) { }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		fast_scan_with_null(value, buf, end);
		if (value) {
			if (prev_value_)
				*value += *prev_value_;
			else {
				if (prev_value_undefinite_) {
					*value += init_value_;
					prev_value_undefinite_ = false;
				} else
					throw MissingPreviousValueInFastDeltaField(number());
			}
			prev_value_ = value;
		}
	}

	void encode(Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		if (value) {
			T x = *value - (prev_value_undefinite_ ? init_value_ : *prev_value_);
			prev_value_ = x;
			fast_encode_with_null(prev_value_, buf, end);
			prev_value_undefinite_ = false;
		}
	}

	void reset() {
		prev_value_.disable();
		prev_value_undefinite_ = true;
	}
};

template<typename T, size_t NUMBER>
class IncrementMandatoryField {
	Optional<T> init_value_;
	Optional<T> prev_value_;
	bool prev_value_undefinite_;

public:
	IncrementMandatoryField(): prev_value_undefinite_(true) { }
	IncrementMandatoryField(const T& val) : init_value_(val), prev_value_undefinite_(true) { }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		if (pmap.fetch_bit()) {
			fast_scan_without_null(*value, buf, end);
			value.enable();
			prev_value_ = value;
			prev_value_undefinite_ = false;
		} else {
			if (prev_value_undefinite_) {
				if (init_value_) {
					value = init_value_;
					prev_value_ = init_value_;
					prev_value_undefinite_ = false;
				} else
					throw MandatoryFastFieldNull(number());
			} else {
				if (prev_value_) {
					++(*prev_value_);
					value = prev_value_;
				} else
					throw MandatoryFastFieldAbsent(number());
			}
		}
	}

	void encode(Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		if (value && prev_value_ && *value - *prev_value_ == 1) {
			pmap.push_back(false);
			*prev_value_ = *value;
		} else if (prev_value_undefinite_ && value && init_value_ && *value - *init_value_ == 1) {
			pmap.push_back(false);
			*prev_value_ = *value;
			prev_value_undefinite_ = false;
		} else {
			if (!value)
				throw MandatoryFastFieldNull(number());
			fast_encode_without_null(*value, buf, end);
			pmap.push_back(true);
			prev_value_ = value;
			prev_value_undefinite_ = false;
		}
	}

	void reset() {
		prev_value_.disable();
		prev_value_undefinite_ = true;
	}
};

template<typename T, size_t NUMBER>
class IncrementOptionalField {
	Optional<T> init_value_;
	Optional<T> prev_value_;
	bool prev_value_undefinite_;

public:
	IncrementOptionalField(): prev_value_undefinite_(true) { }
	IncrementOptionalField(const T& val) : init_value_(val), prev_value_undefinite_(true) { }

	static constexpr size_t number() { return NUMBER; }

	void scan(Optional<T>& value, const char* &buf, const char* end, PMap& pmap) {
		if (pmap.fetch_bit()) {
			fast_scan_with_null(value, buf, end);
			prev_value_ = value;
			prev_value_undefinite_ = false;
		} else {
			if (prev_value_undefinite_) {
				if (init_value_) {
					value = init_value_;
					prev_value_ = init_value_;
				} else
					prev_value_.disable();
				prev_value_undefinite_ = false;
			} else {
				if (prev_value_) {
					++(*prev_value_);
					value = prev_value_;
				} else
					value.disable();
			}
		}
	}

	void encode(Optional<T>& value, char* &buf, char* end, PMap& pmap) {
		if (value && prev_value_ && *value - *prev_value_ == 1) {
			pmap.push_back(false);
			*prev_value_ = *value;
		} else if (prev_value_undefinite_ && value && init_value_ && *value - *init_value_ == 1) {
			pmap.push_back(false);
			*prev_value_ = *value;
			prev_value_undefinite_ = false;
		} else {
			fast_encode_with_null(value, buf, end);
			pmap.push_back(true);
			prev_value_ = value;
			prev_value_undefinite_ = false;
		}
	}

	void reset() {
		prev_value_.disable();
		prev_value_undefinite_ = true;
	}
};


}


#endif /* FAST_FIELDS_H_ */
