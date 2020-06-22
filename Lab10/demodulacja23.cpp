
#include <iostream>
#include<vector>
#include <math.h>
#include <fstream>
#include <stdexcept>
#include "Header.h"
using namespace std;

double h = 0.8;
/*
vector<double> mnozenie(vector<double> in1, vector<double> in2)
{
	std::vector<double> out;
	for (size_t i = 0; i < in1.size(); i++)
	{
		out.push_back(in1[i] * in2[i]);
	}
	return out;
}

void out_file(vector<double> y, vector<double> x, string fileName)
{
	std::ofstream myfile;
	myfile.open(fileName);
	for (double i = 0; i < y.size(); i++)
	{
		myfile << y[i] << "," << x[i] << '\n';
	}
	myfile.close();
}

vector<double> calka(vector<double> input)
{
	double temp;
	vector<double> out;
	for (size_t i = 0; i < input.size();)
	{
		temp = 0;
		for (size_t j = 0; j < 500; j++)
		{
			temp += input[i];
			out.push_back(temp);
			i++;
		}
	}
	return out;
}

vector<double> roznica(vector<double> in1, vector<double> in2)
{
	std::vector<double> out;
	for (size_t i = 0; i < in1.size(); i++)
	{
		out.push_back(in1[i] - in2[i]);
	}
	return out;
}

vector<double> demodulacja(vector<double> input)
{
	vector<double> out;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] > h)
			out.push_back(1);
		else
			out.push_back(0);
	}
	return out;
}
*/