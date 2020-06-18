//
// Created by shadowchris on 20.05.2020.
//
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
#define PI 3.14159265
using namespace std;

vector<double> ASK(string binary,double A1,double A0)
{
    double A2=A0;
    double f=100;
    int wydluzenie=500;
    vector<double>out;
    string::iterator it;
    float index=0;
    int ind=1;
    for(it=binary.begin();it<binary.end();it++)
    {
        if(*it=='0')
        {

            for(int i=0;i<wydluzenie;i++) {

                out.push_back(A1 * sin(2 * PI * f * index+0));
                index = index + 0.00002;
            }
        }
        else if(*it=='1')
        {

            for(int i=0;i<wydluzenie;i++) {

                out.push_back(A2 * sin(2 * PI * f* index+0));
                index = index + 0.00002;
            }

        }
        ind++;
    }
    return out;

}
vector<double> FSK(string binary,double f1,double f2)
{
    double A=1;
    int wydluzenie=500;
    vector<double>out;
    string::iterator it;
    float index=0;
    int ind=1;
    for(it=binary.begin();it<binary.end();it++)
    {

        if(*it=='0')
        {

            for(int i=0;i<wydluzenie;i++) {

                out.push_back(A * sin(2 * PI * f1 * index+0));
                index = index + 0.00002;
            }
        }
        else if(*it=='1')
        {

            for(int i=0;i<wydluzenie;i++) {

                out.push_back(A * sin(2 * PI * f2* index+0));
                index = index + 0.00002;
            }
        }
        ind++;
    }
    return out;

}
vector<double>PSK(string binary,double fi1,double fi2) {
    double A=1;
    double f=100;
    int wydluzenie=500;
    vector<double>out;
    string::iterator it;
    float index=0;
    int ind=1;
    for(it=binary.begin();it<binary.end();it++)
    {
        if(*it=='0')
        {

            for(int i=0;i<wydluzenie;i++) {

                out.push_back(A * sin(2 * PI * f * index+fi1));
                index = index + 0.00002;
            }
        }
        else if(*it=='1')
        {

            for(int i=0;i<wydluzenie;i++) {

                out.push_back(A * sin(2 * PI * f* index+fi2));
                index = index + 0.00002;
            }
        }
        ind++;
    }
    return out;
}