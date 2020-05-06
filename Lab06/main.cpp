#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
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
vector<double>calka(vector<double>funkcja) {
    int Tb = 500;
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
vector<double>demodulacja(vector<double>funkcja,int limit)
{
    int h=limit;
    vector<double>out;
    for(int i=0;i<funkcja.size();i++)
    {
        if(funkcja[i]>h) {out.push_back(1);
            if(i%499==0)
              cout<<"1";
        }
        else {out.push_back(0);
           if(i%499==0)
            cout<<"0";}
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
int main() {
    ifstream myFile;
    myFile.open("ask.csv");
    string p;
    string q;
    vector<double> data;
    while (getline(myFile, p, ',')) {
        getline(myFile, q);
        double fun = stod(p);
        data.push_back(fun);
    }
    myFile.close();
    myFile.open("psk.csv");
    vector<double> data2;
    while (getline(myFile, p, ',')) {
        getline(myFile, q);
        double fun = stod(p);
        data2.push_back(fun);
    }
    myFile.close();
    myFile.open("fsk.csv");
    vector<double> data3;
    while (getline(myFile, p, ',')) {
        getline(myFile, q);
        double fun = stod(p);
        data3.push_back(fun);
    }
    myFile.close();
    int N = data.size();
    int Tb=N/500;
    vector<double>ask;
    ask=ASK_nosny(Tb);
    ofstream plik1;
    plik1.open("ask_nosny.csv");
    for(double i=0;i<ask.size();i++)
    {
        plik1<<ask[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>przemnozone;
    przemnozone=mnozenie(ask,data);
    plik1.open("ASK_x(t).csv");
    for(double i=0;i<przemnozone.size();i++)
    {
        plik1<<przemnozone[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>caleczka;
    caleczka=calka(przemnozone);
    plik1.open("calka.csv");
    for(double i=0;i<caleczka.size();i++)
    {
        plik1<<caleczka[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>demo;
    demo=demodulacja(caleczka,4000);
    plik1.open("demodulowany.csv");
    for(double i=0;i<demo.size();i++)
    {
        plik1<<demo[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double> psk_nosny;
    psk_nosny=PSK_nosny(Tb);
    plik1.open("psk_nosny.csv");
    for(double i=0;i<psk_nosny.size();i++)
    {
        plik1<<psk_nosny[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double> psk_mult;
    psk_mult=mnozenie(psk_nosny,data2);
    plik1.open("psk_przemnozony.csv");
    for(double i=0;i<psk_mult.size();i++)
    {
        plik1<<psk_mult[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double> psk_calka;
    psk_calka=calka(psk_mult);
    plik1.open("psk_calka.csv");
    for(double i=0;i<psk_calka.size();i++)
    {
        plik1<<psk_calka[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double> psk_demo;
    psk_demo=demodulacja(psk_calka,40);
    plik1.open("psk_demodulacja.csv");
    for(double i=0;i<psk_demo.size();i++)
    {
        plik1<<psk_demo[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double> fsk_nosny1,fsk_nosny2;
    fsk_nosny1=FSK_nosny1(Tb);
    fsk_nosny2=FSK_nosny2(Tb);
    plik1.open("fsk_nosny1.csv");
    for(double i=0;i<fsk_nosny1.size();i++)
    {
        plik1<<fsk_nosny1[i]<<","<<i<<endl;
    }
    plik1.close();
    plik1.open("fsk_nosny2.csv");
    for(double i=0;i<fsk_nosny2.size();i++)
    {
        plik1<<fsk_nosny2[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>fsk_x1,fsk_x2;
    fsk_x1=mnozenie(data3,fsk_nosny1);
    fsk_x2=mnozenie(data3,fsk_nosny2);
    plik1.open("fsk_x1.csv");
    for(double i=0;i<fsk_x1.size();i++)
    {
        plik1<<fsk_x1[i]<<","<<i<<endl;
    }
    plik1.close();
    plik1.open("fsk_x2.csv");
    for(double i=0;i<fsk_x2.size();i++)
    {
        plik1<<fsk_x2[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>roz,calk;
    roz=roznica(fsk_x1,fsk_x2);
    calk=calka(roz);
    plik1.open("fsk_calka.csv");
    for(double i=0;i<calk.size();i++)
    {
        plik1<<calk[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>demodulacja_fsk;
    demodulacja_fsk=demodulacja(calk,20);
    plik1.open("fsk_demodulacja.csv");
    for(double i=0;i<demodulacja_fsk.size();i++)
    {
        plik1<<demodulacja_fsk[i]<<","<<i<<endl;
    }
    plik1.close();
    return 0;
}
