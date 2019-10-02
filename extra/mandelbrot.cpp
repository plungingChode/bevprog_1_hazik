#include <string.h>
#include <iostream>
#include <fstream>

const std::string mandelbrot_plang(double x_step, double y_step) 
{
	const double x_max =  1.0;
	const double x_min = -2.5;

	const double y_max =  1.0;
	const double y_min = -1.0;

	double c[2];
	double a[2];
	double an[2];

	std::string result = "";

	for (double y = y_max; y >= y_min; y -= y_step)
	{
		for (double x = x_min; x <= x_max; x += x_step)
		{
			c[0] = x;
			c[1] = y;

			a[0] = x;
			a[1] = y;

			bool inf = false;
			for (int i = 0; i < 20; i++)
			{
				double real = a[0];

				//a ^ 2
				a[0] = real * real - a[1] * a[1];
				a[1] = 2 * real * a[1];

				//a + c
				an[0] = a[0] + c[0];
				an[1] = a[1] + c[1];

				//abs
				double abs = an[0] * an[0] - an[1] * an[1];
				if (abs < 0) abs *= -1;

				if (abs >= 4)
				{
					inf = true;
					break;
				}

				a[0] = an[0];
				a[1] = an[1];
			}

			if (inf)
			{
				result += ' ';
			}
			else 
			{
				result += '*';
			}
		}
		result += '\n';
	}

	return result;
}

const std::string mandelbrot_wiki(double x_step, double y_step)
{
	const double x_max =  1.0;
	const double x_min = -2.5;

	const double y_max =  1.0;
	const double y_min = -1.0;

	std::string result = "";

	for (double y0 = y_max; y0 >= y_min; y0 -= y_step)
	{
		for (double x0 = x_min; x0 < x_max; x0 += x_step)
		{
			double x = 0.0;
			double y = 0.0;
			bool inf = false;
			for (int i = 0; i < 100; i++)
			{
				if (x*x + y * y >= 4) 
				{
					inf = true;
					break;
				}
				double xtemp = x * x - y * y + x0;
				y = 2 * x*y + y0;
				x = xtemp;
			}
			if (inf)
			{
				result += ' ';
			}
			else
			{
				result += '*';
			}
		}
		result += '\n';
	}

	return result;
}

int main() {
	double step_x, step_y;
	char mode;

	std::cout << "mode (w = wiki, * = plang): ";
	std::cin >> mode;
	if (mode != 'w') mode = 'p';

	std::cout << "step x (0 = 0.005): ";
	std::cin >> step_x;
	if (step_x == 0) step_x = 0.005;

	std::cout << "step y (0 = 0.01): ";
	std::cin >> step_y;
	if (step_y == 0) step_y = 0.01;

	std::string result;
	if (mode == 'p') 
	{
		result = mandelbrot_plang(step_x, step_y);
	}
	else 
	{
		result = mandelbrot_wiki(step_x, step_y);
	}

	std::ofstream file;
	file.open("output.txt");
	file << "step x: " << step_x << ", step y: " << step_y << ", mode: " << mode << '\n' << result;
	file.close();

	return 0;
}