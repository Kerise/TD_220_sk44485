#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
string S2BS(string in,int switcher)
{
    int littleEndian=1;
    string output;
    string out;
    if(switcher == littleEndian) {
        int size = in.length();
        for (int j = 0; j <=size; j++) {
            if(j==2)break;
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
vector<double>TTL (string bin)
{
    vector<double>out;
    string::iterator it;
    int wydluzenie=100;
    for(it=bin.begin();it<bin.end();it++)
    {
        if(*it=='0')
        {
            for(int i=0;i<wydluzenie;i++) {
                out.push_back(0);
            }
        }
        else if(*it=='1')
        {
            for(int i=0;i<wydluzenie;i++)
            {
                out.push_back(1);
            }
        }
    }
    return out;
}
vector<int> CLK(int dlugosc,int Tb)
{
    vector<int>out;
    bool one=true;
    for(int i=0;i<dlugosc;i++)
    {
            if(one==false) {
                out.push_back(1);
                if(i%Tb==0)one=true;
            }
            else if(one==true){
                out.push_back(0);
                if(i%Tb==0) one=false;
            }

    }
return out;
}
vector<int> NRZI(vector<double>TTL,vector<int>CLK)
{
    vector<int>out;
    int value=0;
    bool is_zero=false;
    bool minus=false;
    bool swaped=false;
    int ttl;
    for(int i=1;i<CLK.size();i++)
    {

        if(CLK[i]==0 && is_zero==false)
        {
            ttl=TTL[i];
            if(ttl==1 && swaped==false) {
                if (minus == true) {
                    value = 1;
                    minus = false;
                }
                else if (minus == false) {
                    value = -1;
                    minus=true;
                }
                swaped=true;
            }
            is_zero=true;

        }
        else if(CLK[i]==1 ) {is_zero=false;swaped=false;}
        out.push_back(value);
    }
    return out;
}
string decode(vector<int>NRZI)
{
    vector<int>out;
for(int i=50;i<NRZI.size();)
{
    if(NRZI[i]!=0)
    {
        if(NRZI[i]==-1) out.push_back(0);
        else if(NRZI[i]==1) out.push_back(1);
        i+=100;
    }
    i++;
}
string output;
for(int i=0;i<out.size()-1;i++)
{
    if(!out[i] != !out[i+1])output.push_back('1');
    else output.push_back('0');
}

return output;
}
vector<int> BAMI(vector<int>CLK,vector<double>TTL)
{
    vector<int> output;
    int value=0;
    bool was_minus=false;
    bool was_zero=false;
    int ttl;
    for(int i=1;i<CLK.size();i++)
    {

        if(was_zero==true && CLK[i]==1)
        {
            ttl=TTL[i];
            if(ttl==1 && was_minus==false)
            {
                value=-1;
                was_minus=true;
            }
            else if(ttl==1 && was_minus==true)
            {
                value=1;
                was_minus=false;
            }
            else if(ttl==0)
            {
                value=0;
            }
            was_zero=false;
        }
        else if(CLK[i]==0 )
        {
         was_zero=true;
        }
        output.push_back(value);
    }
    return output;
}
string decode_BAMI(vector<int>BAMI)
{
    string out;
    for(int i =0;i<BAMI.size();i+=100)
    {
        if(BAMI[i]==1 || BAMI[i]==-1) out.push_back('1');
        else out.push_back('0');
    }
    return out;
}
int main() {
    cout<<"podaj ciag ascii"<<endl;
    string input;
    cin>>input;
    string binary;
    binary=S2BS(input,1);
    cout<<binary<<endl;
    vector<double> bin;
    bin=TTL(binary);
    ofstream plik1;
    plik1.open("TTL.csv");
    for(double i=0;i<bin.size();i++)
    {
        plik1<<bin[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<int>clk;
    clk=CLK(bin.size(),50);
    plik1.open("CLK.csv");
    for(double i=0;i<clk.size();i++)
    {
        plik1<<clk[i]<<","<<i<<endl;
    }
    plik1.close();
    vector<int>nrzi;
    nrzi=NRZI(bin,clk);
    plik1.open("NRZI.csv");
    for(double i=0;i<nrzi.size();i++)
    {
        plik1<<nrzi[i]<<","<<i<<endl;
    }
    plik1.close();
    string decoded_NRZI;
    decoded_NRZI=decode(nrzi);
    cout<<decoded_NRZI<<endl; //pierwszy bit obciety ze powodu braku preambuły
    vector<int>bami;
    bami=BAMI(clk,bin);
    plik1.open("BAMI.csv");
    for(double i=0;i<bami.size();i++)
    {
        plik1<<bami[i]<<","<<i<<endl;
    }
    string bami_decoded;
    bami_decoded=decode_BAMI(bami);
    cout<<bami_decoded<<endl;  //pierwszy bit zaklamany z powodu braku preambuły

    return 0;
}
