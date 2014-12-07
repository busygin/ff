/*
 * utils.h
 *
 *  Created on: Jun 18, 2014
 *      Author: busygin
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cstdint>
#include <cctype>
#include <exception>
#include <string>
#include <boost/lexical_cast.hpp>


namespace FIX {


template<typename Handler, typename Msg>
class OnFirstMDEntryFunctor {
	Handler& handler_;
	const Msg& msg_;
public:
	OnFirstMDEntryFunctor(Handler& handler, const Msg& msg) : handler_(handler), msg_(msg) { }
	inline bool operator()() { return handler_.on_first_MDEntry(msg_); }
};

class UnexpectedHeader: public std::exception {
public:
	UnexpectedHeader(size_t tag) : s("Header starts with unexpected tag ") {
		s += boost::lexical_cast<std::string>(tag);
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};

class InvalidFieldTagDelimiter: public std::exception {
public:
	InvalidFieldTagDelimiter(size_t tag) : s("Invalid delimiter after tag ") {
		s += boost::lexical_cast<std::string>(tag);
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};

class UnexpectedTag: public std::exception {
public:
	UnexpectedTag(size_t tag) : s("Unexpected tag encountered: ") {
		s += boost::lexical_cast<std::string>(tag);
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};

class DuplicateTag: public std::exception {
public:
	DuplicateTag(size_t tag) : s("Duplicate tag ") {
		s += boost::lexical_cast<std::string>(tag);
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};

class InvalidChksum: public std::exception {
public:
	InvalidChksum(uint16_t s_expected, uint16_t s_received) : s("Invalid checksum: expected ") {
		s += boost::lexical_cast<std::string>(s_expected) + " received " + boost::lexical_cast<std::string>(s_received);
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};

class UnexpectedEndOfMessageBuffer: public std::exception {
private:
	virtual const char* what() const noexcept {
		return "Unexpected end of message buffer";
	}
};

class UnknownMessageType: public std::exception {
private:
	virtual const char* what() const noexcept {
		return "Unknown message type";
	}
};

class UnknownLength: public std::exception {
public:
	UnknownLength(const char* field) : s("Unknown length for field ") {
		s += field;
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};

class MissingFastTemplateID: public std::exception {
private:
	virtual const char* what() const noexcept {
		return "Missing FAST template ID";
	}
};

class MandatoryFastFieldAbsent: public std::exception {
public:
	MandatoryFastFieldAbsent(size_t tag) : s("Mandatory field is absent in FAST message: ") {
		s += boost::lexical_cast<std::string>(tag);
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};

class MandatoryFastFieldNull: public std::exception {
public:
	MandatoryFastFieldNull(size_t tag) : s("Mandatory field is null in FAST message: ") {
		s += boost::lexical_cast<std::string>(tag);
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};

class MissingPreviousValueInFastDeltaField: public std::exception {
public:
	MissingPreviousValueInFastDeltaField(size_t tag) : s("Missing previous value for FAST delta field: ") {
		s += boost::lexical_cast<std::string>(tag);
	}
private:
	std::string s;
	virtual const char* what() const noexcept {
		return s.c_str();
	}
};


inline void strreverse(char* begin, char* end) {
	char tmp;
	while(--end>begin) {
		tmp = *end;
		*end = *begin;
		*begin++ = tmp;
	}
}

inline void signed_itoa(char* &buf, int64_t value) {
    char* p(buf);
    int64_t tmp_value;
    do {
        tmp_value = value;
        value /= 10;
        *p++ = "9876543210123456789"[9 + (tmp_value - value * 10)];
    } while(value);
    if (tmp_value < 0)
        *p++ = '-';
    char* p1(buf);
    buf = p;
    strreverse(p1, p);
}

inline void unsigned_itoa(char* &buf, uint64_t value) {
    char* p(buf);
    uint64_t tmp_value;
    do {
        tmp_value = value;
        value /= 10;
        *p++ = '0' + static_cast<char>(tmp_value - value * 10);
    } while(value);
    char* p1(buf);
    buf = p;
    strreverse(p1, p);
}

inline uint8_t msg_chksum(const char* buf, const char* end) {
    uint8_t result = 0;
    for(; buf<end; ++buf) result += static_cast<uint8_t>(*buf);
    return result;
}

inline size_t scan_tag(const char* &buf, const char* end) {
    // chksum = '=';  to speed up by one op, as we know '=' will be after tag
    size_t result = 0;
    while (buf<end && isdigit(*buf)) {
	// chksum += static_cast<unsigned char>(*buf);
	result = result*10 + static_cast<size_t>(*(buf++) - '0');
    }
    if ( *buf != '=' )
	throw InvalidFieldTagDelimiter(result);
    ++buf;
#ifdef BUFFER_RANGE_CHECK
    if (buf>=end)
	throw UnexpectedEndOfMessageBuffer();
#endif
    return result;
}

template<typename RecordType>
inline void scan(RecordType& r, size_t& tag, const char* &buf, const char* end) {
    while (r.scan_field(tag, buf, end)) {
	if (buf==end) break;
	tag = scan_tag(buf, end);
    }
}


}

#endif /* UTILS_H_ */
