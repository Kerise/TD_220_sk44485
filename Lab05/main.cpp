#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
#define PI 3.14159265
using namespace std;

string S2BS(string in,int switcher)
{
    int littleEndian=1;
    string output;
    string out;
    if(switcher == littleEndian) {
        int size = in.length();
            for (int j = 0; j <=size; j++) {
                int val=int(in[j]);
                output="";
                while(val>0)
                {
                    (val%2)?output.push_back('1'):output.push_back('0');
                    val/=2;
                }
                reverse(output.begin(),output.end());
                out=out+output;
            }
        return out;
    } else
    {
        int size = in.length();
        for (int j = 0; j <size; j++) {
            int val=int(in[j]);
            output="";
            while(val>0)
            {
                (val%2)?output.push_back('1'):output.push_back('0');
                val/=2;
            }
            out=out+output;
            }
            return out;
    }

}
vector<double> ASK(string binary)
{
    double A1=1;
    double A2=8;
    double f=100;
    int wydluzenie=10;
    vector<double>out;
    string::iterator it;
    int index=1;
    for(it=binary.begin();it<binary.end();it++)
    {
        if(*it=='0')
        {
            for(int i=0;i<wydluzenie;i++) {
                out.push_back(A1 * sin(2 * PI * f * index+0));
            }
        }
        else if(*it=='1')
        {
            for(int i=0;i<wydluzenie;i++) {
                out.push_back(A2 * sin(2 * PI * f* index+0));
            }
        }
    }
    return out;

}
vector<double> FSK(string binary,double f1,double f2)
{
    double A=1;
    int wydluzenie=10;
    vector<double>out;
    string::iterator it;
    int index=1;
    for(it=binary.begin();it<binary.end();it++)
    {
        if(*it=='0')
        {
            for(int i=0;i<wydluzenie;i++) {
                out.push_back(A * sin(2 * PI * f1 * index+PI));
            }
        }
        else if(*it=='1')
        {
            for(int i=0;i<wydluzenie;i++) {
                out.push_back(A * sin(2 * PI * f2* index+PI));
            }
        }
    }
    return out;

}
vector<double>PSK(string binary) {
    double A = 1;
    double f=100;
    int wydluzenie = 10;
    vector<double> out;
    string::iterator it;
    int index = 1;
    for (it = binary.begin(); it < binary.end(); it++) {
        if (*it == '0') {
            for (int i = 0; i < wydluzenie; i++) {
                out.push_back(A * sin(2 * PI * f * index + 0));
            }
        } else if (*it == '1') {
            for (int i = 0; i < wydluzenie; i++) {
                out.push_back(A * sin(2 * PI * f * index + PI));
            }
        }
    }
    return out;
}
    int main() {
    int N=100;
    double Tb=5;
    double f1,f2;
    f1=(N+1)/Tb;
    f2=(N+2)/Tb;
    string character;
    cin>>character;
    string binary;
    binary=S2BS(character,1);
    cout<<"\n"<<binary<<endl;
    vector<double>ask;
    ask=ASK(binary);
    ofstream plik1;
    plik1.open("ask.csv");
    cout<<ask.size();
    for(double i=0;i<ask.size();i++)
    {
        plik1<<ask[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>fsk;
    fsk=FSK(binary,f1,f2);
    plik1.open("fsk.csv");
    for(double i=0;i<fsk.size();i++)
    {
        plik1<<fsk[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<double>psk;
    psk=PSK(binary);
    plik1.open("psk.csv");
    for(double i=0;i<psk.size();i++)
    {
        plik1<<psk[i]<<","<<i<<endl;
    }
    plik1.close();
    return 0;
}
