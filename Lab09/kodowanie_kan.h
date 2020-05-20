//
// Created by shadowchris on 20.05.2020.
//
using namespace std;
#ifndef TOR_TRANSMISYJNY_KODOWANIE_KAN_H
#define TOR_TRANSMISYJNY_KODOWANIE_KAN_H
//kodowanie_kan.h
string S2BS(string in,int switcher);
string kodowanie_SECDED(vector<int>pack);
string dekodowanie2(vector<int>pack,int ktora);
//modulacja.h
vector<double>PSK(string binary,double fi1,double fi2);
vector<double> ASK(string binary,double A1,double A0);
vector<double> FSK(string binary,double f1,double f2);

//demodulacja.h
vector<double> ASK_nosny(int Tb);
vector<double> mnozenie(vector<double>ask_nosny,vector<double>ask);
vector<double>calka(vector<double>funkcja,int Tb);
vector<double>demodulacja(vector<double>funkcja,double limit,int Tb);

#endif //TOR_TRANSMISYJNY_KODOWANIE_KAN_H
