//
// Created by shadowchris on 20.05.2020.
//

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
#include "kodowanie_kan.h"
#define PI 3.14159265
using namespace std;
vector<double> ASK_nosny(int Tb)
{
    double A2=8;
    double f=100;
    int wydluzenie=500;
    vector<double>out;
    string::iterator it;
    float index=0;
    int ind=1;
    for(int i=0;i<Tb;i++)
    {
        for(int i=0;i<wydluzenie;i++) {
            out.push_back(A2 * sin(2 * PI * f * index + 0));
            index = index + 0.00002;
        }
        ind++;
    }
    return out;

}
vector<double> PSK_nosny(int Tb)
{
    double A2=1;
    double f=100;
    int wydluzenie=500;
    vector<double>out;
    string::iterator it;
    float index=0;
    int ind=1;
    for(int i=0;i<Tb;i++)
    {
        for(int i=0;i<wydluzenie;i++) {
            out.push_back(A2 * sin(2 * PI * f * index + M_PI));
            index = index + 0.00002;
        }
        ind++;
    }
    return out;

}
vector<double> FSK_nosny1(int Tb)
{
    double A2=1;
    double f=100;
    int wydluzenie=500;
    vector<double>out;
    string::iterator it;
    float index=0;
    int ind=1;
    for(int i=0;i<Tb;i++)
    {
        for(int i=0;i<wydluzenie;i++) {
            out.push_back(A2 * sin(2 * PI * f * index + 0));
            index = index + 0.00002;
        }
        ind++;
    }
    return out;

}
vector<double> FSK_nosny2(int Tb)
{
    double A2=1;
    double f=200;
    int wydluzenie=500;
    vector<double>out;
    string::iterator it;
    float index=0;
    int ind=1;
    for(int i=0;i<Tb;i++)
    {
        for(int i=0;i<wydluzenie;i++) {
            out.push_back(A2 * sin(2 * PI * f * index + 0));
            index = index + 0.00002;
        }
        ind++;
    }
    return out;

}
vector<double> mnozenie(vector<double>ask_nosny,vector<double>ask) {
    int size = ask.size();
    vector<double>out;
    double value=0;
    for (int i = 0; i < size; i++)
    {
        value=ask_nosny[i]*ask[i];
        out.push_back(value);
    }
    return out;
}
vector<double>calka(vector<double>funkcja,int Tb) {
    int size=funkcja.size()/500;
    double value=0;
    int index=500;
    vector<double>out;
    for(int j=0;j<size;j++) {
        value=0;
        for (int i = 0; i < Tb; i++) {
            index=(j*500)+i;
            value+=funkcja[index];
            out.push_back(value);
        }
    }
    return out;
}
vector<double>demodulacja(vector<double>funkcja,double limit,int Tb)
{
    int h=limit;
    vector<double>out;
    for(int i=0;i<funkcja.size();i++)
    {
        if(funkcja[i]>h) {out.push_back(0);
        }
        else {out.push_back(1);
                }
    }
    cout<<"\n";
    return out;
}
vector<double>roznica(vector<double>x1,vector<double>x2)
{
    vector<double>out;
    double value=0;
    for(int i=0;i<x1.size();i++)
    {
        value=x2[i]-x1[i];
        out.push_back(value);
    }
    return out;
}