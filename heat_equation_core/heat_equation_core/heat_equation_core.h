#pragma once

using namespace System;

namespace heatequationcore 
{
	extern "C" _declspec(dllimport) double* _cdecl initial_time_or_space_point(double, double, UInt32);
	extern "C" _declspec(dllimport) double** _cdecl initial_matrix(UInt32, UInt32, double*, double*, double(*)(double, double), double(*)(double, double), double(*)(double, double));
	extern "C" _declspec(dllimport) double** _cdecl solve_equation(UInt32, UInt32, double , double , double, double*, double*, double(*), double**);
}
