#pragma once
#include <windows.h>
using namespace System;

namespace VineCopulaWrapper {

	public ref class VineCopulaBridge
	{
	public:
		VineCopulaBridge();
		~VineCopulaBridge();

		array<double>^ Hinv1(int^ family, int^ size, array<double>^ u, array<double>^ v, double^ theta, double^ nu, array<double>^ out);
				
		//double Average(array<double>^ numbers, int ^ b);

	};
}
