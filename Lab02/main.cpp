#include <iostream>
#include <math.h>
#include <fstream>
# define M_PI    3.14159265358979323846
using namespace std;
double sygnal(double a,double f,double ro,double t)
{
    double w=2*M_PI*f;
    double probka=a*sin(w*t+ro);
    return probka;
}

int main()
{
    double a=1.0;
    double f=8;
    double ro=4*M_PI;
    ofstream plik1;
    plik1.open("f1.csv");
    for(double t=0;t<5;t=t+0.01){
    plik1<<sygnal(a,f,ro,t)<<","<<t<<endl;
    }
    plik1.close();
    ofstream plik2;
    plik2.open("f2.csv");
    for(double t=0;t<5;t=t+0.01)
    {
        plik2<<round((sygnal(a,f,ro,t)+1) * pow(2, (16-1)))<<","<<t<<endl;
    }
    plik2.close();
    ofstream plik3;
    plik3.open("f3.csv");
    for(double t=0;t<5;t=t+(0.01/2))
    {
        plik3<<round((sygnal(a,f,ro,t)+1) * pow(2, (8-1)))<<","<<t<<endl;
    }
    plik3.close();
    return 0;
}
