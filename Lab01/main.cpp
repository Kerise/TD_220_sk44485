
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <cmath>
#include <fstream>
#define M_PI 3.14159265358979323846
double a = 5;
double b = 8;
double c = 4;

double f1(double t)
{
	double y1 = a * (t*t) + b * t + c;
	return y1;
}

double f2(double t)
{
	double y2 = 2 * (f1(t)*f1(t)) + 12 * cos(t);
	return y2;
}

double f3(double t)
{
	double y3 = sin(2 * M_PI * 7 * t)*f1(t) - 0.2*log10(abs(f2(t)) + M_PI);
	return y3;
}

double f4(double t)
{
	double y4 = sqrt(abs(f2(t)*f2(t)*f3(t))) - 1.8*sin(0.4*t*f3(t)*f1(t));
	return y4;
}

double f5_1(double t)
{
	double y5 = 0;
	y5 = (1 - 7 * t)*sin((2 * M_PI*t * 10) / (t + 0.04));
	return y5;
}
double f5_2(double t)
{
	double y5 = 0;
	y5 = 0.63*t*sin(125 * t);
	return y5;
}
double f5_3(double t)
{
	double y5 = 0;
	y5 = pow(t, -0.662) + 0.77*sin(8 * t);
	return y5;
}

double f6(double t)
{
	double N = 2;
	double y6 = 0;
	for (double n = 1; n <= N; n++)
	{
		y6 += cos(12 * t*(n*n) + cos(16 * t*n)) / (n*n);
	}
	return y6;
}
double f7(double t)
{
	double N = 4;
	double y7 = 0;
	for (double n = 1; n <= N; n++)
	{
		y7 += cos(12 * t*(n*n) + cos(16 * t*n)) / (n*n);
	}
	return y7;
}

double f8(double t)
{
	double N = 58;
	double y8 = 0;
	for (double n = 1; n <= N; n++)
	{
		y8 += cos(12 * t*(n*n) + cos(16 * t*n)) / (n*n);
	}
	return y8;
}
int main()
{


	double x1, x2;

	double delta = (b*b) - 4 * (a*c);
	if (delta < 0)
	{
		std::cout << "Nie ma miejsc zerowych" << std::endl;
	}
	else if (delta >= 0)
	{
		x1 = -b + sqrt(delta) / (2 * a);
		x2 = -b - sqrt(delta) / (2 * a);
		std::cout << "x1:" << x1 << "\nx2:" << x2 << "\n";
	}
	int i = 1;
	double y1 = 0;
	std::ofstream function1;
	function1.open("f1.csv");
	for (double t = -10; t <= 10; t += 0.01)
	{
		function1 << f1(t) << "," << t << std::endl;
	}
	function1.close();
	std::ofstream function2;
	function2.open("f2.csv");
	double krok = double(1) / double(22050);
	for (double t = 0; t <= 1; t += krok)
	{
		function2 << f2(t) << "," << t << "\n";
	}
	function2.close();

	std::ofstream function3;
	function3.open("f3.csv");
	for (double t = 0; t <= 1; t += krok)
	{
		function3 << f3(t) << "," << t << "\n";
	}
	function3.close();

	std::ofstream function4;
	function4.open("f4.csv");
	for (double t = 0; t <= 1; t += krok)
	{
		function4 << f4(t) << "," << t << "\n";
	}
	function4.close();

	std::ofstream function5_1;
	std::ofstream function5_2;
	std::ofstream function5_3;
	function5_1.open("f5.csv");
	function5_2.open("f5_2.csv");
	function5_3.open("f5_3.csv");
	for (double t = 0; t <= 1; t += krok)
	{
		if (t >= 0 && t < 0.22)
		{
			function5_1 << f5_1(t) << "," << t << "\n";
		}
		else if (t >= 0.22 && t < 0.7)
		{
			function5_2 << f5_2(t) << "," << t << "\n";
		}
		else if (t >= 0.7 && t <= 1.0)
		{
			function5_3 << f5_3(t) << "," << t << "\n";
		}
	}
	function5_1.close();
	function5_2.close();
	function5_3.close();

	std::ofstream function6;
	function6.open("f6.csv");
	for (double t = 0; t <= 1; t += krok)
	{
		function6 << f6(t) << "," << t << "\n";
	}
	function6.close();

	std::ofstream function7;
	function7.open("f7.csv");
	for (double t = 0; t <= 1; t += krok)
	{
		function7 << f7(t) << "," << t << "\n";
	}
	function7.close();

	std::ofstream function8;
	function8.open("f8.csv");
	for (double t = 0; t <= 1; t += krok)
	{
		function8 << f8(t) << "," << t << "\n";
	}
	function8.close();

	return 0;
}

