#include "stdafx.h"
#include "CppUnitTest.h"

#include "../RenderingPipeline/Vector4.h"
#include "../RenderingPipeline/Vector4.cpp"
#include "../RenderingPipeline/Matrix4x4.h"
#include "../RenderingPipeline/Matrix4x4.cpp"
#include "../RenderingPipeline/Transformer.h"
#include "../RenderingPipeline/Transformer.cpp"
#include "../RenderingPipeline/Camera.h"
#include "../RenderingPipeline/Camera.cpp"
#include "../RenderingPipeline/Projector.h"
#include "../RenderingPipeline/Projector.cpp"
#include "../RenderingPipeline/PerspectiveProjector.h"
#include "../RenderingPipeline/PerspectiveProjector.cpp"
#include "../RenderingPipeline/PolygonCliper.h"
#include "../RenderingPipeline/PolygonCliper.cpp"
#include "../RenderingPipeline/Light.h"
#include "../RenderingPipeline/Light.cpp"
#include "../RenderingPipeline/PolygonCliper.h"
//#include "../RenderingPipeline/PolygonCliper.cpp"

#include <cmath>
#include <memory>
using std::fabs;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
const double eps = 0.01;  // 浮点数的比较，使用减法误差方式

// 测试数学库
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
			double m3[4][4] = {
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

// 测试三维转换
namespace ThreeDTest
{
	TEST_CLASS(Transformer_TEST)
	{
	public:
		TEST_METHOD(Transformer_transformRotationX)  // 绕x轴旋转
		{
			Object cube;
			cube.centerPos = Vector4(0, 0, 0);

			Transformer transformer;
			Point p0(-10, 0, 0);
			Point p1(0, 10, 0);
			Point p2(10, 0, 0);
			Plane plane;

			plane.push_back(p0);
			plane.push_back(p1);
			plane.push_back(p2);
			cube.planes.push_back(plane);

			double angle = PI * 90 / 180;

			// 绕X轴顺时针90
			transformer.transformRotationX(cube, angle);

			auto& plane0 = cube.planes[0];
			p0 = plane0[0];
			p1 = plane0[1];
			p2 = plane0[2];

			Assert::IsTrue(fabs(p0.x + 10) <= 0.001);
			Assert::IsTrue(fabs(p0.y) <= 0.001);
			Assert::IsTrue(fabs(p0.z) <= 0.001);

			Assert::IsTrue(fabs(p1.x) <= 0.001);
			Assert::IsTrue(fabs(p1.y) <= 0.001);
			Assert::IsTrue(fabs(p1.z - 10) <= 0.001);

			Assert::IsTrue(fabs(p2.x - 10) <= 0.001);
			Assert::IsTrue(fabs(p2.y) <= 0.001);
			Assert::IsTrue(fabs(p2.z) <= 0.001);
		}

		TEST_METHOD(Transformer_transformRotationY)  // 绕Y轴旋转
		{
			Object cube;
			cube.centerPos = Vector4(0, 0, 0);

			Transformer transformer;
			Point p0(-10, 0, 0);
			Point p1(0, 10, 0);
			Point p2(10, 0, 0);
			Plane plane;

			plane.push_back(p0);
			plane.push_back(p1);
			plane.push_back(p2);
			cube.planes.push_back(plane);

			double angle = PI * 90 / 180;

			transformer.transformRotationY(cube, angle);

			auto& plane0 = cube.planes[0];
			p0 = plane0[0];
			p1 = plane0[1];
			p2 = plane0[2];

			Assert::IsTrue(fabs(p0.x) <= 0.001);
			Assert::IsTrue(fabs(p0.y) <= 0.001);
			Assert::IsTrue(fabs(p0.z - 10) <= 0.001);

			Assert::IsTrue(fabs(p1.x) <= 0.001);
			Assert::IsTrue(fabs(p1.y - 10) <= 0.001);
			Assert::IsTrue(fabs(p1.z) <= 0.001);

			Assert::IsTrue(fabs(p2.x) <= 0.001);
			Assert::IsTrue(fabs(p2.y) <= 0.001);
			Assert::IsTrue(fabs(p2.z + 10) <= 0.001);
		}

		TEST_METHOD(Transformer_transformRotationZ)  // 绕Z轴旋转
		{
			Object cube;
			cube.centerPos = Vector4(0, 0, 0);

			Transformer transformer;
			Point p0(-10, 0, 0);
			Point p1(0, 10, 0);
			Point p2(10, 0, 0);
			Plane plane;

			plane.push_back(p0);
			plane.push_back(p1);
			plane.push_back(p2);
			cube.planes.push_back(plane);

			double angle = PI * 90 / 180;

			transformer.transformRotationZ(cube, angle);

			auto& plane0 = cube.planes[0];
			p0 = plane0[0];
			p1 = plane0[1];
			p2 = plane0[2];

			Assert::IsTrue(fabs(p0.x) <= 0.001);
			Assert::IsTrue(fabs(p0.y + 10) <= 0.001);
			Assert::IsTrue(fabs(p0.z) <= 0.001);

			Assert::IsTrue(fabs(p1.x + 10) <= 0.001);
			Assert::IsTrue(fabs(p1.y) <= 0.001);
			Assert::IsTrue(fabs(p1.z) <= 0.001);

			Assert::IsTrue(fabs(p2.x) <= 0.001);
			Assert::IsTrue(fabs(p2.y - 10) <= 0.001);
			Assert::IsTrue(fabs(p2.z) <= 0.001);

			// 单独测试点，
			Plane plane1;
			plane1.emplace_back(Point(1, 1, -1));
			cube.planes.clear();
			cube.planes.push_back(plane1);
			transformer.transformRotationZ(cube, angle);
			auto& plane11 = cube.planes[0];
			p0 = plane11[0];
			Assert::IsTrue(fabs(p0.x + 1) <= 0.001);
			Assert::IsTrue(fabs(p0.y - 1) <= 0.001);
			Assert::IsTrue(fabs(p0.z + 1) <= 0.001);
		}

		TEST_METHOD(Transformer_transformOffset)  // 位移测试
		{
			Object cube;
			cube.centerPos = Vector4(0, 0, 0);
			Transformer transformer;

			Vector4 offset(1, 1, 1, 1);
			transformer.transformOffset(cube, offset);

			Assert::IsTrue(fabs(cube.centerPos.X() - 1) <= 0.01);
			Assert::IsTrue(fabs(cube.centerPos.Y() - 1) <= 0.01);
			Assert::IsTrue(fabs(cube.centerPos.Z() - 1) <= 0.01);
		}
	};

	TEST_CLASS(Camera_TEST)
	{
		TEST_METHOD(Camera_Transform)
		{
			Camera camera;
			Vector4 pos(1, 0, 1);
			Vector4 target(0, 0, 0);
			Vector4 up(0, 1, 0);
			camera.setCamera(pos, target, up);

			Object cube, cubeRes;
			cube.centerPos = Vector4(0, 0, 0);
			Plane plane;
			plane.emplace_back(Point(0, 0, 0));
			cube.planes.push_back(plane);
			camera.transform(cube, cubeRes);
			auto& res = cubeRes.planes[0];
			Assert::IsTrue(fabs(res[0].x) <= 0.01);
			Assert::IsTrue(fabs(res[0].y) <= 0.01);
			Assert::IsTrue(fabs(res[0].z + std::sqrt(2)) <= 0.01);
		}
	};
}

// 测试投影矩阵
namespace ProjectTest
{
	TEST_CLASS(Perspective_TEST)
	{
		TEST_METHOD(PerspectiveProject_TEST) 
		{
			PerspectiveProjector perspective;
			perspective.setProjectMat();
			Object obj;
			Plane plane;
			plane.emplace_back(Point(20, 20, -50));
			obj.planes.push_back(plane);
			perspective.project(obj);
			auto& pl = obj.planes[0];
			auto& p = pl[0];
			Assert::IsTrue(fabs(p.x - 200) <= eps);
			Assert::IsTrue(fabs(p.y - 200) <= eps);
		}
	};
}

 // 测试屏幕显示输出过程
namespace ShowOnScreen
{
	TEST_CLASS(PolygonCliper_TEST)
	{
		TEST_METHOD(Clip_Test)
		{
			std::shared_ptr<PolygonCliper>plc=std::make_shared<PolygonCliper>();
			plc->setBoundary(100, -100, -100, 100);
			Object obj;
			Plane plane;

			// 被包含在边界内部
			plane.emplace_back(Point(-50, 50));
			plane.emplace_back(Point(-50, -50));
			plane.emplace_back(Point(50, -50));
			plane.emplace_back(Point(50, 50));
			plane.emplace_back(Point(-50, 50));

			obj.planes.push_back(plane);
			plc->clip(obj);
			plane.clear();
			plane = obj.planes[0];

			Assert::AreEqual<int>(plane.size(), 5);
			Assert::IsTrue(fabs(plane[0].x + 50) < 0.001&&fabs(plane[0].y - 50) < 0.001);
			Assert::IsTrue(fabs(plane[1].x + 50) < 0.001&&fabs(plane[1].y + 50) < 0.001);
			Assert::IsTrue(fabs(plane[2].x - 50) < 0.001&&fabs(plane[2].y + 50) < 0.001);
			Assert::IsTrue(fabs(plane[3].x - 50) < 0.001&&fabs(plane[3].y - 50) < 0.001);
			Assert::IsTrue(plane[0].x == plane[4].x&&plane[0].y == plane[4].y);

			// 边界被图形包含
			obj.planes.clear();
			plane.clear();
			plane.emplace_back(Point(-150, 150));
			plane.emplace_back(Point(-150, -150));
			plane.emplace_back(Point(150, -150));
			plane.emplace_back(Point(150, 150));
			plane.emplace_back(Point(-150, 150));
			obj.planes.push_back(plane);
			plc->clip(obj);
			plane.clear();
			plane = obj.planes[0];

			Assert::IsTrue(plane.size()==5);

			// 边界和图形有部分交点
			obj.planes.clear();
			plane.clear();
			plane.emplace_back(Point(-150, 150));
			plane.emplace_back(Point(0, 150));
			plane.emplace_back(Point(0, 0));
			plane.emplace_back(Point(-150, 0));
			plane.emplace_back(Point(-150, 150));
			obj.planes.push_back(plane);
			plc->clip(obj);
			plane.clear();
			plane = obj.planes[0];
			Assert::IsTrue(plane.size() == 5);

			// 部分交点有漏洞的测试
			obj.planes.clear();
			plane.clear();
			plane.emplace_back(Point(-451, -421));
			plane.emplace_back(Point(-359, -513));
			plane.emplace_back(Point(-303, -542));
			plane.emplace_back(Point(-386, -461));
			plane.emplace_back(Point(-451, -421));
			obj.planes.push_back(plane);
			plc->setBoundary(500, -500, -500, 500);
			plc->clip(obj);
			plane.clear();
			plane = obj.planes[0];

			// 图形完全在边界外
			obj.planes.clear();
			plane.clear();
			plane.emplace_back(Point(150, 150));
			plane.emplace_back(Point(250, 150));
			plane.emplace_back(Point(250, 250));
			plane.emplace_back(Point(150, 250));
			plane.emplace_back(Point(150, 150));
			obj.planes.push_back(plane);
			plc->clip(obj);
			plane.clear();
			plane = obj.planes[0];

			Assert::IsTrue(plane.empty());
		}
	};

	TEST_CLASS(DrawPolygon_TEST)
	{

	};
}