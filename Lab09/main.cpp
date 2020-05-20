#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
#include "kodowanie_kan.h"

using namespace std;
string BS2S(string in)
{
    stringstream sstream(in);
    string output;
    while(sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }
    output.pop_back();
    return output;

}
int main() {
    int Tb;
    double fs=1000;
    double A1=1.0;
    double A0=0.0;

    cout<<"podaj ciag ascii"<<endl;
    string input;
    getline(cin,input);
    string binary;
    binary=S2BS(input,1);
    cout<<"binarnie:"<<binary<<endl;
    vector<int>package;
    string h1;
    int a=0;
    for(int i=0;i<=binary.size();i++)
    {
        if(a<4) {
            a++;
            package.push_back(int(binary[i]));
        }
        else {
            a=0;
            h1+=kodowanie_SECDED(package);
            package.clear();
            i--;
        }

    }
    cout<< "kodowane_kan:"<<h1<<endl;
    vector<double>ask;
    ask=ASK(h1,A1,A0);
    ofstream plik1;
    plik1.open("ask.csv");
    for(double i=0;i<ask.size();i++)
    {
        plik1<<ask[i]<<","<<i<<endl;
    }
    plik1.close();
    int N =ask.size();
    vector<double>ask2;
    Tb=N/500;
    ask2=ASK_nosny(Tb);
    plik1.open("ask_nosny.csv");
    for(double i=0;i<ask2.size();i++)
    {
        plik1<<ask2[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>przemnozone;
    przemnozone=mnozenie(ask2,ask);
    plik1.open("ASK_x(t).csv");
    for(double i=0;i<przemnozone.size();i++)
    {
        plik1<<przemnozone[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>caleczka;
    caleczka=calka(przemnozone,Tb);
    plik1.open("calka.csv");
    for(double i=0;i<caleczka.size();i++)
    {
        plik1<<caleczka[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>demo;
    demo=demodulacja(caleczka,0.4,Tb);
    plik1.open("demodulowany.csv");
    for(double i=0;i<demo.size();i++)
    {
        plik1<<demo[i]<<","<<i<<endl;
    }
    plik1.close();
    string encoded;
    for(int i=0;i<demo.size();i+=Tb)
    {
        if(demo[i]==1)
        {
            encoded+="1";
        }
        else if(demo[i]==0 )
        {
            encoded+="0";
        }
    }
    cout<<"zdemodulowany:"<<encoded<<endl;
    int a3=0;
    int ilosc_paczek=0;
    vector<int>package3;
    string decoded_SECDED;
    for(int i=0;i<=encoded.size();i++)
    {
        if(a3<8)
        {
            a3++;
            package3.push_back(int(encoded[i]));
        }
        else{
            a3=0;
            decoded_SECDED+=dekodowanie2(package3,ilosc_paczek);
            package3.clear();
            i--;
            ilosc_paczek++;
        }
    }
    cout<<"odkodowane_SECDED: "<<decoded_SECDED<<endl;
    string final;
    final=BS2S(decoded_SECDED);
    cout<<final<<endl;
    return 0;
}
