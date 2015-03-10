#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\ProjectPANG\MainObj.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(MainObj_Constructor)
		{
			MainObj<int>* mainObj1 = new MainObj<int>();
			CoorXY<int>* punt1 = new CoorXY<int>();
			Assert::IsTrue(*punt1 == mainObj1->getPos());

			MainObj<float>* mainObj2 = new MainObj<float>();
			CoorXY<float>* punt2 = new CoorXY<float>();
			Assert::IsTrue(*punt2 == mainObj2->getPos());

			MainObj<double>* mainObj3 = new MainObj<double>();
			CoorXY<double>* punt3 = new CoorXY<double>();
			Assert::IsTrue(*punt3 == mainObj3->getPos());
		}

	};
}