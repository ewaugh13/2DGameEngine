#include "FloatFunctionLibrary.h"

namespace FloatFunctionLibrary
{
	bool FloatFunctionLibrary::AlmostEqualRelativeAndAbs(float i_A, float i_B, float i_maxDiff, float i_maxRelDiff)
	{
		// Check if the numbers are really close -- needed
		// when comparing numbers near zero.
		float diff = static_cast<float>(fabs(i_A - i_B));
		if (diff <= i_maxDiff)
			return true;

		i_A = static_cast<float>(fabs(i_A));
		i_B = static_cast<float>(fabs(i_B));
		// Find the largest
		float largest = (i_B > i_A) ? i_B : i_A;

		if (diff <= largest * i_maxRelDiff)
			return true;
		return false;
	}

	bool FloatFunctionLibrary::AlmostEqualUlpsAndAbs(float i_A, float i_B, float i_maxDiff, unsigned int i_maxUlpsDiff)
	{
		// Check if the numbers are really close -- needed
		// when comparing numbers near zero.
		float absDiff = static_cast<float>(fabs(i_A - i_B));
		if (absDiff <= i_maxDiff)
			return true;

		Float_t uA(i_A);
		Float_t uB(i_B);

		// Different signs means they do not match.
		if (uA.Negative() != uB.Negative())
		{
			// Check for equality to make sure +0==-0
			if (i_A == i_B)
				return true;
			return false;
		}

		// Find the difference in ULPs.
		unsigned int ulpsDiff = abs(uA.i - uB.i);
		if (ulpsDiff <= i_maxUlpsDiff)
			return true;

		return false;
	}
}