#include "CppUnitTest.h"
#include "FloatFunctionLibrary.h"

#include <math.h>       /* sqrt */

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FloatFunctionLibrary;

namespace FloatTests
{
	TEST_CLASS(FloatTest1)
	{
	public:

		TEST_METHOD(FloatTest)
		{
			float pointOne = 0.1f;
			float one = 1.0f;
			float almostOne = 0;
			for (int i = 0; i < 10; ++i)
				almostOne += pointOne;

			Assert::IsTrue(FloatFunctionLibrary::AlmostEqualRelativeAndAbs(one, almostOne, 0.0f));

			float inbetweenOneAndTwo = 0.1f * 15;
			Assert::IsFalse(FloatFunctionLibrary::AlmostEqualRelativeAndAbs(one, inbetweenOneAndTwo, .1f));

			float val = 2.5f;
			Float_t UlpVal = Float_t(val);

			UlpVal.i++;
			Assert::IsTrue(FloatFunctionLibrary::AlmostEqualUlpsAndAbs(val, UlpVal.f, 0.0f, 1));

			UlpVal.i += 3;
			Assert::IsFalse(FloatFunctionLibrary::AlmostEqualUlpsAndAbs(val, UlpVal.f, 0.0f, 2));

			float nanNum = sqrt(-1.0f);
			Assert::IsTrue(FloatFunctionLibrary::IsNan(nanNum));

			float realFloat = 1.1f;
			Assert::IsFalse(FloatFunctionLibrary::IsNan(realFloat));

			float almostZero = 0.00000001f;
			Assert::IsTrue(FloatFunctionLibrary::AlmostEqualZeroCertain(almostZero));

			float closeToZero = 0.001f;
			Assert::IsFalse(FloatFunctionLibrary::AlmostEqualZeroCertain(closeToZero));
		}
	};
}