#include<iostream>
#include<math.h>
#include<fstream>
#include<vector>
#define PI 3.14159265
using namespace std;
vector<double> modulacja_amp(vector<double>x)
{
    vector<double>mod;
    for(int j=0;j<x.size();j++)
    {
        mod.push_back((90*x[j]+1)*cos(2*PI*1000*j));
    }
    return mod;

}
vector<double> modulacja_faz(vector<double>x)
{
    vector<double>mod;
    for(int j=0;j<x.size();j++)
    {
        mod.push_back(cos(2*PI*1000*j+60*x[j]));
    }
    return mod;
}

int main() {
    ifstream myFile;
    myFile.open("f1.csv");
    string p;
    string q;
    vector<double> y;
    vector<double> x;
    int i=1;
    while (i<=501)
    {
        getline(myFile, p,',');
        double fun = stod(p);
        y.push_back(fun);
        getline(myFile,q,'\n');
        double fin = stod(q);
        x.push_back(fin);
        i++;


    }
    myFile.close();
    vector<double>mod_amp;
    mod_amp=modulacja_amp(y);
    ofstream plik1;
    plik1.open("mod_a.csv");
    for(int i=0;i<mod_amp.size();i++)
    {
        plik1<<mod_amp[i]<<","<<x[i]<<endl;
    }
    plik1.close();
    vector<double>mod_faz;
    mod_faz=modulacja_faz(y);
    plik1.open("mod_f.csv");
    for(int i=0;i<mod_faz.size();i++)
    {
        plik1<<mod_faz[i]<<","<<x[i]<<endl;
    }
    return 0;
}
