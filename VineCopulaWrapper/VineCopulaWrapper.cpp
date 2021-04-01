#include "pch.h"

#include "VineCopulaWrapper.h"

using namespace System;
using namespace System::IO;

namespace VineCopulaWrapper
{

	HMODULE hDllModule;

	VineCopulaBridge::VineCopulaBridge()
	{
		hDllModule = LoadLibrary(TEXT("VinCopulaDll.dll"));

	}

	VineCopulaBridge::~VineCopulaBridge()
	{
		if (hDllModule)
			FreeLibrary(hDllModule);

	}

	// double*  Hinv1(int* family, int* n, double* u, double* v, double* theta, double* nu, double* out)


	array<double>^ VineCopulaBridge::Hinv1(int^ family, int^ size, array<double>^ u, array<double>^ v, double^ theta, double^ nu, array<double>^ output)
	{
		typedef double* (__cdecl* PFNHINV)(int* family, int* size, double* u, double* v, double* theta, double* nu, double* output);
		PFNHINV pfnHinv;

		pin_ptr<int> pPinFamily = &*family;
        int* pPinPtrFamilyAdress = pPinFamily;

		pin_ptr<int> pPinSize = &*size;
		int* pPinPtrSizeAdress = pPinSize;

		pin_ptr<double> pPinArrayUValues = &u[0];
		double* pPinPtrUAdress = pPinArrayUValues;

		pin_ptr<double> pPinArrayVValues = &v[0];
		double* pPinPtrVAdress = pPinArrayVValues;


		pin_ptr<double> pPinArrayThetaValues = &*theta;
		double* pPinPtrThetaAdress = pPinArrayThetaValues;


		pin_ptr<double> pPinArrayNuValues = &*nu;
		double* pPinPtrNuAdress = pPinArrayNuValues;

		pin_ptr<double> pPinOutPutArrayValues = &output[0];
		double* pPinPtrOutputAdress = pPinOutPutArrayValues;

		pfnHinv = (PFNHINV)GetProcAddress(hDllModule, "Hinv");

		// 
		// Hinv1(134, nsize, x, y, -2.55, 0.36, output);
		//
		array<double>^ resultsArray = gcnew array<double>(*size);
		double* results;
		results = pfnHinv(pPinPtrFamilyAdress, pPinPtrSizeAdress, pPinPtrUAdress, pPinPtrVAdress, pPinPtrThetaAdress, pPinPtrNuAdress, pPinPtrOutputAdress);
		//void Hinv(int* family, int* n, double* u, double* v, double* theta, double* nu, double* out)
		
		for (int index = 0 ; index < *size; index++)
		{
			resultsArray[index] = results[index];
		}

		return resultsArray;
	}

	//double  VineCopulaBridge::Average(array<double>^ values, int ^size)
	//{
	//		
	//	typedef double(__cdecl* PFNAVG)(double* numbers, int size);
	//	PFNAVG pfnAvg;

	//	pfnAvg = (PFNAVG)GetProcAddress(hDllModule, "getAverage");

	//	pin_ptr<double> pPinArrayValues = &values[0];

	//	double* pPinPtrAdress = pPinArrayValues;

	//	double avg = pfnAvg(pPinPtrAdress, values->Length);
	//	
	//	return avg;
	//}

}



