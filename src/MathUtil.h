/*
 * MathUtil.h
 *
 *  Created on: 2012-12-13
 *      Author: alex
 */

#ifndef MATHUTIL_H_
#define MATHUTIL_H_

#include <stdint.h>

namespace mctools {
class MathUtil {
public:
	virtual ~MathUtil();

	/** Archimede's constant PI, ratio of circle circumference to diameter. */
	static const double PI = 105414357.0 / 33554432.0 + 1.984187159361080883e-9;

	/** Napier's constant e, base of the natural logarithm. */
	static const double E = 2850325.0 / 1048576.0 + 8.254840070411028747e-8;

	static inline int32_t signum(int32_t i) {
		return	(i >> 31) | ((-i >> 31)&0x1);
	}

	/**
	 * 判断数字是否是偶数
	 *
	 * @param num
	 * @return
	 */
	static inline bool isEven(int32_t num) {
		return !(num & 0x0001);
	}

	/**
	 * 判断数字是否是奇数
	 *
	 * @param num
	 * @return
	 */
	static inline bool isOdd(int32_t num) {
		return (num & 0x0001);
	}

	static inline int is_pow_of_2(uint32_t x) {
		return !(x & (x - 1));
	}

	static inline uint32_t next_pow_of_2(uint32_t x) {
		if (is_pow_of_2(x))
			return x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return x + 1;
	}

	static inline uint32_t ReadUTF8(const char* src, uint32_t& sz) {
	    uint8_t b = *src;

	    if ( (b&0x80) == 0) {
	        sz = 1;
	        return b&0x7F;
	    }

	    if ( (b&0xE0) == 0xC0) {
	        sz = 2;
	        return ((b&0x1F)<<6) |(*(src+1) &0x3F);
	    }

	    if ( (b&0xF0) == 0xE0) {
	        sz = 3;
	        return ((b&0x0F)<<12)|((*(src+1)&0x3F)<<6)|((*(src+2)&0x3F));
	    }

	    sz = 4;
	    return ((b&0x0F)<<18)|((*(src+1)&0x3F)<<12)|((*(src+2)&0x3F)<<6)|(*(src+3)&0x3F);
	}

private:
	MathUtil();
};
} //end name space
#endif /* MATHUTIL_H_ */
