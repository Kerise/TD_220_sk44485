#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
#include <ctime>
#include <cstdlib>
#include "Header.h"
#define PI 3.14159265
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
    srand(time(0));
    const static int q = 15;
    const static float c1 = (1 << q) - 1;
    const static float c2 = ((int)(c1 / 3)) + 1;
    const static float c3 = 1.f / c1;
    int Tb;
    double fs = 1000;
    double A1 = 1.0;
    double A0 = 0.0;
    double fi1, fi2;
    fi1 = 0;
    fi2 = PI;
    double f1, f2;
    f1 = 100;
    f2 = 200;

    cout << "podaj ciag ascii" << endl;
    string input;
    getline(cin, input);
    string binary;
    binary = S2BS(input, 1);
    cout << "binarnie:" << binary << endl;
    vector<int> package;
    string h1;
    int a = 0;
    for (int i = 0; i <= binary.size(); i++) {
        if (a < 4) {
            a++;
            package.push_back(int(binary[i]));
        } else {
            a = 0;
            h1 += kodowanie_SECDED(package);
            package.clear();
            i--;
        }

    }

    cout << "kodowane_kan:" << h1 << endl;
    vector<double> ask;
    vector<double> psk;
    vector<double> fsk;
    ask = ASK(h1, A1, A0);
    psk = PSK(h1, fi1, fi2);
    fsk = FSK(h1, f1, f2);

    ofstream plik1;
    plik1.open("ask.csv");
    for (double i = 0; i < ask.size(); i++) {
        plik1 << ask[i] << "," << i << endl;
    }
    plik1.close();
    plik1.open("psk.csv");
    for (double i = 0; i < psk.size(); i++) {
        plik1 << psk[i] << "," << i << endl;
    }
    plik1.close();
    plik1.open("fsk.csv");
    for (double i = 0; i < fsk.size(); i++) {
        plik1 << fsk[i] << "," << i << endl;
    }
    plik1.close();

    int N = ask.size();
    vector<double> zA_szum;
    vector<double> zF_szum;
    vector<double> zP_szum;
    float noise=0.f;
    float random = 0.f;
    double alfa=0.99;
    for (int i = 0; i <N; i++)
    {
        random = ((float)rand() / (float)(RAND_MAX+1));
        noise = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3;

        ask[i]=((ask[i] * alfa) + (noise * (1 - alfa)));
        fsk[i]=((fsk[i] * alfa) + (noise * (1 - alfa)));
        psk[i]=((psk[i] * alfa) + (noise * (1 - alfa)));
    }
    vector<double> ask2;
    vector<double> psk2;
    vector<double> fsk2;
    vector<double> fsk2_2;
    Tb = N / 500;
    ask2 = ASK_nosny(Tb);
    plik1.open("ask_nosny.csv");
    for (double i = 0; i < ask2.size(); i++) {
        plik1 << ask2[i] << "," << i << endl;
    }
    plik1.close();
    N = psk.size();
    Tb = N / 500;
    psk2 = PSK_nosny(Tb);
    plik1.open("psk_nosny.csv");
    for (double i = 0; i < psk2.size(); i++) {
        plik1 << psk2[i] << "," << i << endl;
    }
    plik1.close();
    N = fsk.size();
    Tb = N / 500;
    fsk2 = FSK_nosny1(Tb);
    fsk2_2 = FSK_nosny2(Tb);
    plik1.open("fsk_nosny1.csv");
    for (double i = 0; i < fsk2.size(); i++) {
        plik1 << fsk2[i] << "," << i << endl;
    }
    plik1.close();
    plik1.open("fsk_nosny2.csv");
    for (double i = 0; i < fsk2_2.size(); i++) {
        plik1 << fsk2_2[i] << "," << i << endl;
    }
    plik1.close();
    vector<double> przemnozone_ask;
    vector<double> przemnozone_psk;
    vector<double> przemnozone_fsk1, przemnozone_fsk2;
    przemnozone_ask = mnozenie(ask2, ask);
    przemnozone_fsk1 = mnozenie(fsk2, fsk);
    przemnozone_fsk2 = mnozenie(fsk2_2, fsk);
    przemnozone_psk = mnozenie(psk2, psk);

    plik1.open("ASK_x(t).csv");
    for (double i = 0; i < przemnozone_ask.size(); i++) {
        plik1 << przemnozone_ask[i] << "," << i << endl;
    }
    plik1.close();

    plik1.open("PSK_x(t).csv");
    for (double i = 0; i < przemnozone_psk.size(); i++) {
        plik1 << przemnozone_psk[i] << "," << i << endl;
    }
    plik1.close();

    plik1.open("FSK_x1(t).csv");
    for (double i = 0; i < przemnozone_fsk1.size(); i++) {
        plik1 << przemnozone_fsk1[i] << "," << i << endl;
    }
    plik1.close();

    plik1.open("FSK_x2(t).csv");
    for (double i = 0; i < przemnozone_fsk2.size(); i++) {
        plik1 << przemnozone_fsk2[i] << "," << i << endl;
    }
    plik1.close();
    vector<double> caleczka_ask;
    vector<double> caleczka_fsk;
    vector<double> caleczka_psk;
    vector<double> roz;
    roz = roznica(przemnozone_fsk1, przemnozone_fsk2);
    caleczka_ask = calka(przemnozone_ask, Tb);
    caleczka_fsk = calka(roz, Tb);
    caleczka_psk = calka(przemnozone_psk, Tb);

    plik1.open("calka_ask.csv");
    for (double i = 0; i < caleczka_ask.size(); i++) {
        plik1 << caleczka_ask[i] << "," << i << endl;
    }
    plik1.close();
    plik1.open("calka_psk.csv");
    for (double i = 0; i < caleczka_psk.size(); i++) {
        plik1 << caleczka_psk[i] << "," << i << endl;
    }
    plik1.close();
    plik1.open("calka_fsk.csv");
    for (double i = 0; i < caleczka_fsk.size(); i++) {
        plik1 << caleczka_fsk[i] << "," << i << endl;
    }
    plik1.close();
    vector<double> demo_ask;
    vector<double> demo_psk;
    vector<double> demo_fsk;
    demo_ask = demodulacja1(caleczka_ask, 0, Tb);
    demo_psk = demodulacja2(caleczka_psk, 0, Tb);
    demo_fsk = demodulacja3(caleczka_fsk, 0.02, Tb);
    plik1.open("demodulowany_ask.csv");
    for (double i = 1; i < demo_ask.size(); i++) {
        plik1 << demo_ask[i] << "," << i << endl;
    }
    plik1.close();

    plik1.open("demodulowany_psk.csv");
    for (double i = 0; i < demo_psk.size(); i++) {
        plik1 << demo_psk[i] << "," << i << endl;
    }
    plik1.close();

    plik1.open("demodulowany_fsk.csv");
    for (double i = 0; i < demo_fsk.size(); i++) {
        plik1 << demo_fsk[i] << "," << i << endl;
    }
    plik1.close();
    string encoded_ask;
    string encoded_psk;
    string encoded_fsk;
    for (int i = 0; i < demo_ask.size(); i += Tb+1) {
        if (demo_ask[i] == 1) {
            encoded_ask += "1";
        } else if (demo_ask[i] == 0) {
            encoded_ask += "0";
        }
    }
    cout << "zdemodulowany ask:" << encoded_ask << endl;
    for (int i = 1; i < demo_psk.size(); i += Tb+1) {
        if (demo_psk[i] == 1) {
            encoded_psk += "1";
        } else if (demo_psk[i] == 0) {
            encoded_psk += "0";
        }
    }
    encoded_psk+="0";
    cout<<"zdemodulowany psk:"<<encoded_psk<<endl;

    for(int i=0;i<demo_fsk.size();i+=Tb)
    {
      // cout<<demo_fsk[i]<<"   :    "<<i<<endl;
        if(demo_fsk[i]==1)
        {
            encoded_fsk+="1";
        }
        else if(demo_fsk[i]==0 )
        {
            encoded_fsk+="0";
        }
    }
    encoded_fsk.erase(encoded_fsk.begin());
    encoded_fsk.push_back(48);
    cout<<"zdemodulowany fsk:"<<encoded_fsk<<endl;
    int a3=0;
    int ilosc_paczek=0;
    vector<int>package3;
    string decoded_SECDED_ask;
    string decoded_SECDED_psk;
    string decoded_SECDED_fsk;
    for(int i=0;i<=encoded_ask.size();i++)
    {
        if(a3<8)
        {
            a3++;
            package3.push_back(int(encoded_ask[i]));
        }
        else{
            a3=0;
            decoded_SECDED_ask+=dekodowanie2(package3,ilosc_paczek);
            package3.clear();
            i--;
            ilosc_paczek++;
        }
    }

    cout<<"odkodowane_SECDED_ask: "<<decoded_SECDED_ask<<endl;
    string final_ask;
    final_ask=BS2S(decoded_SECDED_ask);
    cout<<"ASCI: "<<final_ask<<endl;
    a3=0;
    ilosc_paczek=0;
    vector<int>package_psk;
    for(int i=0;i<=encoded_psk.size();i++)
    {
        if(a3<8)
        {
            a3++;
            package_psk.push_back(int(encoded_psk[i]));
        }
        else{
            a3=0;
            decoded_SECDED_psk+=dekodowanie2(package_psk,ilosc_paczek);
            package_psk.clear();
            i--;
            ilosc_paczek++;
        }
    }
    cout<<"odkodowane_SECDED_psk: "<<decoded_SECDED_psk<<endl;
    string final_psk;
    final_psk=BS2S(decoded_SECDED_psk);
    cout<<"ASCI: "<<final_psk<<endl;
    a3=0;
    ilosc_paczek=0;
    vector<int>package_fsk;
    for(int i=0;i<=encoded_fsk.size();i++)
    {
        if(a3<8)
        {
            a3++;
            package_fsk.push_back(int(encoded_fsk[i]));
        }
        else{
            a3=0;
            decoded_SECDED_fsk+=dekodowanie2(package_fsk,ilosc_paczek);
            package_fsk.clear();
            i--;
            ilosc_paczek++;
        }
    }
    cout<<"odkodowane_SECDED_fsk: "<<decoded_SECDED_fsk<<endl;
    string final_fsk;
    final_fsk=BS2S(decoded_SECDED_fsk);
    cout<<"ASCI: "<<final_fsk<<endl;
    double counterA=0;
    double counterF=0;
    double counterP=0;
            for(int i=0;i<binary.size();i++)
            {
                if(int(binary[i])!=int(decoded_SECDED_ask[i]))
                {
                    counterA++;
                }
            }
    for(int i=0;i<binary.size();i++)
    {
        if(int(binary[i])!=int(decoded_SECDED_psk[i]))
        {
            counterP++;
        }
    }
    for(int i=0;i<binary.size();i++)
    {
        if(int(binary[i])!=int(decoded_SECDED_fsk[i]))
        {
            counterF++;
        }
    }
    cout << endl;
    cout << "BER dla ASK: "<<(counterA/binary.size())*100 << endl;
    cout << "BER dla PSK: "<<(counterP/binary.size())*100<< endl;
    cout << "BER dla FSK: "<<(counterF/binary.size())*100<< endl;

    return 0;
}
