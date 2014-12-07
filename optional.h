/*
 * optional.h
 *
 *  Created on: Aug 21, 2014
 *      Author: busygin
 */

#ifndef OPTIONAL_H_
#define OPTIONAL_H_

#include <ostream>

template<typename T>
class Optional {
public:
	Optional() : enabled_(false) { }
	Optional(const T& v) : value_(v), enabled_(true) { }
	Optional(const Optional<T> & that) : value_(that ? *that : T()), enabled_(that) { }

	const T& operator*() const { return value_; }
	T& operator*() { return value_; }

	const T* operator->() const { return &value_; }
	T* operator->() { return &value_; }

	Optional<T>& operator=(const T& v) {
		value_ = v; enabled_ = true;
		return *this;
	}

	Optional<T>& operator=(const Optional<T>& rhs) {
		enabled_ = rhs.enabled_;
		if (enabled_) value_ = rhs.value_;
		return *this;
	}

	bool operator==(const Optional<T>& rhs) const {
		return (enabled_ ? value_==rhs.value_ : !rhs);
	}

	explicit operator bool() const { return enabled_; }
	bool enabled() const { return enabled_; }

	void enable() { enabled_ = true; }
	void disable() { enabled_ = false; }

private:
	T value_;
	bool enabled_;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Optional<T>& rhs) { return os << bool(rhs); }

#endif /* OPTIONAL_H_ */
