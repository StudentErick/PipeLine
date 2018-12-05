#include "stdafx.h"
#include "CppUnitTest.h"

#include "../RenderingPipeline/Vector4.h"
#include "../RenderingPipeline/Vector4.cpp"
#include "../RenderingPipeline/Matrix4x4.h"
#include "../RenderingPipeline/Matrix4x4.cpp"

#include <cmath>
using std::fabs;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
const double eps = 0.1;  // 浮点数的比较，使用减法误差方式
namespace MathTest
{
	TEST_CLASS(Vector4_TEST)
	{
	public:
		TEST_METHOD(sub)
		{
			Vector4 v1(1, 12.2, 3);
			Vector4 v2(-2, -8, 8.4);
			Vector4 res = v1 - v2;
			// 3  20.2 -5.4
			Assert::IsTrue(fabs(res.X() - 3.0) <= eps);
			Assert::IsTrue(fabs(res.Y() - 20.2) <= eps);
			Assert::IsTrue(fabs(res.Z() - (-5.4)) <= eps);
		}

		TEST_METHOD(add)
		{
			Vector4 v1(1, 12.2, 3);
			Vector4 v2(-2, -8, 8.4);
			Vector4 res = v1 + v2;
			// -1  4.2 11.4
			Assert::IsTrue(fabs(res.X() - (-1)) <= eps);
			Assert::IsTrue(fabs(res.Y() - 4.2) <= eps);
			Assert::IsTrue(fabs(res.Z() - 11.4) <= eps);
		}

		TEST_METHOD(dot)
		{
			Vector4 v1(1, 12.2, 3);
			Vector4 v2(-2, -8, 8.4);
			double res1 = v1.dot(v2);
			Assert::IsTrue(fabs(res1 + 74.4) <= eps);
			res1 = v1.dot(v1);
			Assert::IsTrue(fabs(res1 - 158.84) <= eps);
		}

		TEST_METHOD(cross)
		{
			Vector4 v1(1, 12.2, 3);
			Vector4 v2(-2, -8, 8.4);
			Vector4 res = v1.cross(v2);

			// 126.48  -14.4    16.4
			Assert::IsTrue(fabs(res.X() - 126.48) <= eps);
			Assert::IsTrue(fabs(res.Y() + 14.4) <= eps);
			Assert::IsTrue(fabs(res.Z() - 16.4) <= eps);

			// 0 0 0 
			res = v1.cross(v1);
			Assert::IsTrue(fabs(res.X() - 0) <= eps);
			Assert::IsTrue(fabs(res.Y() - 0) <= eps);
			Assert::IsTrue(fabs(res.Z() - 0) <= eps);
		}

		TEST_METHOD(len)
		{
			Vector4 v1(10, -4.6, 11.6);
			Vector4 v2(0, 0, 0);
			double res = v1.length();
			Assert::IsTrue(fabs(res - 15.9912476061) <= eps);
			res = v2.length();
			Assert::IsTrue(fabs(res - 0) <= eps);
		}

		TEST_METHOD(normalize)
		{
			Vector4 v1(2.3, 4.5, 6.99);
			Vector4 v2(-3, -7, -10.3);
			v1.normalize();
			v2.normalize();
			Assert::IsTrue(fabs(v1.length() - 1) <= eps);
			Assert::IsTrue(fabs(v2.length() - 1) <= eps);

			Assert::IsTrue(fabs(v1.X() - 0.2666) <= 0.01);
			Assert::IsTrue(fabs(v1.Y() - 0.5217) <= 0.01);
			Assert::IsTrue(fabs(v1.Z() - 0.8103) <= 0.01);
			Assert::IsTrue(fabs(v2.X() + 0.2341) <= 0.01);
			Assert::IsTrue(fabs(v2.Y() + 0.5464) <= 0.01);
			Assert::IsTrue(fabs(v2.Z() + 0.8040) <= 0.01);
		}
	};

	TEST_CLASS(Matrix4x4_TEST)
	{
	public:

		TEST_METHOD(add)
		{
			//for (int i = 0; i < 4; ++i) {
			//	for (int j = 0; j < 4; ++i) {
			//		
			//	}
			//}
			//Matrix4x4 mat1()
		}

		TEST_METHOD(sub)
		{

		}

		TEST_METHOD(mul_mat)
		{
			double m1[4][4], m2[4][4];
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					m1[i][j] = i + i * 7 - 5;
					m2[i][j] = i + j * 3 + 10;
				}
			}
			Matrix4x4 mat1(m1);
			Matrix4x4 mat2(m2);
			Matrix4x4 mat3 = mat1 * mat2;
			double m3[4][4] ={ 
				{-230, -290, -350, -410},
				{138,  174  ,210  ,246 },
				{506,  638,  770,  902},
				{874, 1102, 1330, 1558 }
			};
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::IsTrue(fabs(mat3.getVal(i, j) - m3[i][j]) < eps);
				}
			}
		}

		TEST_METHOD(mul_vec4)
		{
			double m1[4][4], m2[4];
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					m1[i][j] = i + i * 7 - 5;
				}
				m2[i] = (i + 7) / 3 + 9;
			}
			Matrix4x4 mat1(m1);
			Vector4 vec(m2);
			Vector4 res = mat1 * vec;
			Assert::IsTrue(fabs(res.X() + 230) <= eps);
			Assert::IsTrue(fabs(res.Y() - 138) <= eps);
			Assert::IsTrue(fabs(res.Z() - 506) <= eps);
			Assert::IsTrue(fabs(res.W() - 874) <= eps);
		}

		TEST_METHOD(transpose)
		{

		}
	};
}