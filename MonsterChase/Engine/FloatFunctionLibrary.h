#pragma once

#include "float.h"		/* FLT_EPSILON */
#include <math.h>		/* fabs */
#include <stdint.h>		/* int32_t, uint32_t */

/* See https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/ for reference on these functions*/

union Float_t
{
	Float_t(float num = 0.0f) : f(num) {}
	// Portable extraction of components.
	bool Negative() const { return i < 0; }
	int32_t RawMantissa() const { return i & ((1 << 23) - 1); }
	int32_t RawExponent() const { return (i >> 23) & 0xFF; }

	int32_t i;
	float f;
#ifdef _DEBUG
	struct
	{   // Bitfields for exploration. Do not use in production code.
		uint32_t mantissa : 23;
		uint32_t exponent : 8;
		uint32_t sign : 1;
	} parts;
#endif
};

namespace FloatFunctionLibrary
{
	// Equal within a relative epsilon
	bool AlmostEqualRelativeAndAbs(float i_A, float i_B, float i_maxDiff, float i_maxRelDiff = FLT_EPSILON);

	// Equal within a certain Ulps
	bool AlmostEqualUlpsAndAbs(float i_A, float i_B, float i_maxDiff, unsigned int i_maxUlpsDiff);

	// Equal to zero within a certain epsilon
	inline bool AlmostEqualZeroCertain(float i_A, float i_maxCertDiff = FLT_EPSILON) { return fabs(i_A) <= i_maxCertDiff; }

	// If value is a NaN
	inline bool IsNan(float i_A)
	{
		volatile float volA = i_A;
		// If not equal to itself it's a NaN (according to IEEE standard)
		return volA != volA;
	}
};

