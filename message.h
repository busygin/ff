/*
 * message.h
 *
 *  Created on: Jun 7, 2014
 *      Author: busygin
 */

#ifndef FIX_MESSAGE_H_
#define FIX_MESSAGE_H_

#include <cctype>
#include <cstdint>
#include <cmath>
#include <cstring>
#include <type_traits>
#include <string>

#include <boost/lexical_cast.hpp>

#include "utils.h"


namespace FIX {


struct Decimal {
    int64_t mantissa;
    int32_t exponent;

    Decimal(int64_t i_mantissa=0, int32_t i_exponent=0) : mantissa(i_mantissa), exponent(i_exponent) { }

    double to_double() const { return mantissa * std::pow(10.0, exponent); }  // TODO: make it faster than using std::pow
};


// ===============

template<typename T>
inline void fixscan(T& var, const char* from, const char* to) { var = boost::lexical_cast<T>(from, to-from); }

template<>
inline void fixscan<char>(char& var, const char* from, const char* to) { var = *from; }

template<>
inline void fixscan<bool>(bool& var, const char* from, const char* to) { var = (*from=='Y' || *from=='y'); }

template<>
inline void fixscan<std::string>(std::string& var, const char* from, const char* to) { var.assign(from,to); }

template<>
inline void fixscan<Decimal>(Decimal& var, const char* from, const char* to) {
    bool is_negative = (*from=='-');
    if (is_negative) ++from;
    var.mantissa = 0;
    var.exponent = 0;
    bool after_decimal_point = false;
    for(; from<to; ++from) {
	if (isdigit(*from)) {
	    var.mantissa = 10*var.mantissa + (*from - '0');
	    if (after_decimal_point) --var.exponent;
	} else if (*from=='.')
	    after_decimal_point = true;
    }
    if (is_negative) var.mantissa = -var.mantissa;
}

// ===============

inline void fixcopy(char* &buf, char value) { *buf++ = value; }
inline void fixcopy(char* &buf, const std::string &value) { for(const char& p : value) *buf++ = p; }
inline void fixcopy(char* &buf, int64_t value) { signed_itoa(buf, value); }
inline void fixcopy(char* &buf, uint64_t value) { unsigned_itoa(buf, value); }

inline void fixcopy(char* &buf, const Decimal& value) {
    if (value.exponent<0) {
	int64_t mantissa = value.mantissa;
	if (mantissa<0) {
	    *buf++ = '-';
	    mantissa = -mantissa;
	}
	char* p = buf;
	unsigned_itoa(buf, mantissa);
	int32_t exponent = -value.exponent;
	int32_t len = buf - p;
	int32_t n_pad = exponent - len + 2;
	if (n_pad>1) {  // abs(value)<1, the output is 0.<decimal fraction>
	    memmove(p+n_pad, p, static_cast<size_t>(len));
	    buf += n_pad;
	    *p++ = '0'; *p++ = '.';
	    n_pad -= 2;
	    if (n_pad>0) memset(p, '0', static_cast<size_t>(n_pad));
	} else {  // abs(value)>1, just insert decimal point at the proper position
	    p = buf - exponent;
	    memmove(p+1, p, static_cast<size_t>(exponent));
	    *p = '.';
	    ++buf;
	}
    } else {
	signed_itoa(buf, value.mantissa);
	if (value.exponent>0) {
	    memset(buf, '0', static_cast<size_t>(value.exponent));
	    buf += value.exponent;
	}
    }
}

// ===============


template<typename T, size_t NUMBER, typename TRAITS>
class Field {
	T value_;

public:
	Field() { }
	Field(const T& val) : value_(val) { }

	const T& value() const { return value_; }
	T& value() { return value_; }

	static constexpr size_t number() { return NUMBER; }
	static constexpr const char* name() { return TRAITS::name(); }
	static constexpr const char* fixtype() { return TRAITS::fixtype(); }

	void scan(const char* &buf, const char* end) {
		const char* p = buf;
		while (*buf!='\x01') {
			++buf;
#ifdef BUFFER_RANGE_CHECK
			if (buf>=end)
				throw UnexpectedEndOfMessageBuffer();
#endif
		}
		fixscan(value_, p, buf);
		++buf;
	}

	// this version of scan is for fields with length defined in the previous field
	// must have std::string type
	void scan(const char* &buf, const char* end, size_t len) {
		static_assert(std::is_same<T,std::string>::value, "Data fields must be stored in std::string");
		const char* p = buf;
		buf += len;
#ifdef BUFFER_RANGE_CHECK
		if (buf>=end)
			throw UnexpectedEndOfMessageBuffer();
#endif
		value_.assign(p,buf);
		++buf;
	}

	void encode(char* &buf, char* end) const {
		unsigned_itoa(buf, number());
		*(buf++) = '=';
		fixcopy(buf, value_);
		*(buf++) = '\x01';
#ifdef BUFFER_RANGE_CHECK
		if (buf>=end)
			throw UnexpectedEndOfMessageBuffer();
#endif
	}
};


} // namespace FIX


#endif /* FIX_MESSAGE_H_ */
