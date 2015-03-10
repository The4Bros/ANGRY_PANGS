#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\ProjectPANG\CoorXY.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Punt2DUnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(CoorXY_ConstructorVacio)
		{
			CoorXY<int>* target1 = new CoorXY<int>();
			Assert::IsTrue(target1->x == 0 && target1->y == 0);

			CoorXY<float>* target2 = new CoorXY<float>();
			Assert::IsTrue(target2->x == 0.0f && target2->y == 0.0f);

			CoorXY<double>* target3 = new CoorXY<double>();
			Assert::IsTrue(target3->x == 0 && target3->y == 0);
		}

		TEST_METHOD(CoorXY_ConstructorXY)
		{
			int iactualX = 2;
			int iactualY = 3;
			int iexpectedX = iactualX;
			int iexpectedY = iactualY;
			CoorXY<int>* target1 = new CoorXY<int>(iactualX, iactualY);
			Assert::IsTrue(target1->x == iexpectedX && target1->y == iexpectedY);

			float factualX = 2.1;
			float factualY = 3.2;
			float fexpectedX = factualX;
			float fexpectedY = factualY;
			CoorXY<float>* target2 = new CoorXY<float>(factualX, factualY);
			Assert::IsTrue(target2->x == fexpectedX && target2->y == fexpectedY);

			double dactualX = 2;
			double dactualY = 3;
			double dexpectedX = dactualX;
			double dexpectedY = dactualY;
			CoorXY<double>* target3 = new CoorXY<double>(dactualX, dactualY);
			Assert::IsTrue(target3->x == dexpectedX && target3->y == dexpectedY);
		}

		TEST_METHOD(CoorXY_Equal)
		{
			int iactualX = 2;
			int iactualY = 3;
			int iexpectedX = iactualX;
			int iexpectedY = iactualY;
			CoorXY<int>* target1 = new CoorXY<int>();
			CoorXY<int>* target2 = new CoorXY<int>(iactualX, iactualY);
			*target1 = *target2;
			Assert::IsTrue(target1->x == iexpectedX && target1->y == iexpectedY);
			
			float factualX = 2.1;
			float factualY = 3.2;
			float fexpectedX = factualX;
			float fexpectedY = factualY;
			CoorXY<float>* target3 = new CoorXY<float>();
			CoorXY<float>* target4 = new CoorXY<float>(factualX, factualY);
			*target3 = *target4;
			Assert::IsTrue(target3->x == fexpectedX && target3->y == fexpectedY);
			
			double dactualX = 2;
			double dactualY = 3;
			double dexpectedX = dactualX;
			double dexpectedY = dactualY;
			CoorXY<float>* target5 = new CoorXY<float>();
			CoorXY<float>* target6 = new CoorXY<float>(dactualX, dactualY);
			*target5 = *target6;
			Assert::IsTrue(target5->x == dexpectedX && target5->y == dexpectedY);
		}
		
		TEST_METHOD(CoorXY_Substract)
		{
			int iactualX = 2;
			int iactualY = 3;
			int iexpectedX = iactualX;
			int iexpectedY = iactualY;
			CoorXY<int>* target1 = new CoorXY<int>();
			CoorXY<int>* target2 = new CoorXY<int>(iactualX, iactualY);
			CoorXY<int>* target3 = new CoorXY<int>(iactualX, iactualY);
			*target1 = *target2 - *target3;
			Assert::IsTrue(target1->x == iexpectedX && target1->y == iexpectedY);

			float factualX = 2.1;
			float factualY = 3.2;
			float fexpectedX = factualX;
			float fexpectedY = factualY;
			CoorXY<float>* target3 = new CoorXY<float>();
			CoorXY<float>* target4 = new CoorXY<float>(factualX, factualY);
			target3 = target4;
			Assert::IsTrue(target3->x == fexpectedX && target3->y == fexpectedY);

			double dactualX = 2;
			double dactualY = 3;
			double dexpectedX = dactualX;
			double dexpectedY = dactualY;
			CoorXY<float>* target5 = new CoorXY<float>();
			CoorXY<float>* target6 = new CoorXY<float>(dactualX, dactualY);
			target5 = target6;
			Assert::IsTrue(target5->x == dexpectedX && target5->y == dexpectedY);
		}
		/*
		TEST_METHOD(Punt2D_Add)
		{
			CoorXY* target1 = new CoorXY(1, 0);
			CoorXY* target2 = new CoorXY(2, 2);
			CoorXY* target3 = new CoorXY();

			*target3 = *target1 + *target2;

			Assert::IsTrue(target3->x == 3 && target3->y == 2);
		}

		TEST_METHOD(Punt2D_AddEqual)
		{
			CoorXY* target1 = new CoorXY(1, 2);
			CoorXY* target2 = new CoorXY(2, 4);

			*target1 += *target2;

			Assert::IsTrue(target1->x == 3 && target1->y == 6);
		}

		TEST_METHOD(Punt2D_SubstractEqual)
		{
			CoorXY* target1 = new CoorXY(2, 4);
			CoorXY* target2 = new CoorXY(1, 2);

			*target1 -= *target2;

			Assert::IsTrue(target1->x == 1 && target1->y == 2);
		}

		TEST_METHOD(Punt2D_Same)
		{
			CoorXY* target1 = new CoorXY(1, 1);
			CoorXY* target2 = new CoorXY(1, 1);

			Assert::IsTrue(*target1 == *target2);
		}

		TEST_METHOD(Punt2D_Different)
		{
			CoorXY* target1 = new CoorXY(1, 1);
			CoorXY* target2 = new CoorXY(1, 2);
			CoorXY* target3 = new CoorXY(2, 2);

			Assert::IsTrue(*target1 != *target2);
			Assert::IsTrue(*target1 != *target3);
		}
		*/
	};
}