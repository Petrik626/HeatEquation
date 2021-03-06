#include "stdafx.h"

#include "heat_equation_core.h"

namespace heatequationcore
{
	double*  initial_time_or_space_point(double start, double end, UInt32 amount_points)
	{
		double* array = new double[amount_points];
		double step = (end - start) / (amount_points - 1);

		for (int i = 0; i < amount_points; i++)
		{
			array[i] = (start + i * step);
		}

		return array;
	}

	double** initial_matrix(UInt32 count_point_on_space, UInt32 count_point_on_time, double* space, double *time, double(*left)(double x, double t), double(*right)(double x, double t), double(*start_condition)(double x, double t))
	{
		double **matrix = new double* [count_point_on_time];
		for (int i = 0; i < count_point_on_time; i++)
		{
			matrix[i] = new double[count_point_on_space];
		}

		for (int i = 0; i < count_point_on_time; i++)
		{
			for (int j = 0; j < count_point_on_space; j++)
			{
				matrix[i][j] = 0.0;
			}
		}

		double time1 = time[0];
		for (int i = 0; i < count_point_on_space; i++)
		{
			matrix[0][i] = start_condition(space[i], time1);
		}

		double space1 = space[0], space_N = time[count_point_on_space - 1];
		for (int i = 0; i < count_point_on_time; i++)
		{
			matrix[i][0] = left(space1, time[i]);
			matrix[i][count_point_on_space - 1] = right(space_N, time[i]);
		}

		return matrix;
	}

	double** solve_equation(UInt32 count_point_on_space, UInt32 count_point_on_time, double a, double h, double tao, double *space, double *time, double(*f)(double x, double t), double **matrix)
	{
		for (int i = 1; i < count_point_on_time; i++)
		{
			for (int j = 0; j < count_point_on_space - 1; j++)
			{
				matrix[i][j] = tao * (matrix[i - 1][j - 1] - (2 - (h*h) / tao)*matrix[i - 1][j] + matrix[i - 1][j + 1]) / (h*h) + f(space[i], time[j]);
			}
		}

		return matrix;
	}
}

