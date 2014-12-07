#ifndef PMAP_H_
#define PMAP_H_

#include <cstdint>

namespace FIX {

class PMap {
public:
	PMap() : bitmap_(0), bitmask_(1) { }
	PMap(const PMap& m) : bitmap_(m.bitmap_), bitmask_(1) { }

	bool operator*() const { return bitmap_ & bitmask_; }
	void next() { bitmask_ <<= 1; }

	bool fetch_bit() {
		bool result = bitmap_ & bitmask_;
		bitmask_ <<= 1;
		return result;
	}

	void set_bit() {
		bitmap_ |= bitmask_;
		bitmask_ <<= 1;
	}

	void clear_bit() {
		bitmap_ &= ~bitmask_;
		bitmask_ <<= 1;
	}

	void push_back(bool flag) {
		if (flag) bitmap_ |= bitmask_;
		bitmask_ <<= 1;
	}

	void reset() { bitmask_ = 1; }
	void clear() { bitmap_ = 0; bitmask_ = 1; }
	bool empty() const { return bitmap_==0; }

private:
	uint64_t bitmap_;
	uint64_t bitmask_;  // mask to extract a bit by (bitmap_ & bitmask_)
};

}

#endif  // PMAP_H_
