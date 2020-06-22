//
// Created by shadowchris on 20.05.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>>
#include "Header.h"
using namespace std;
string S2BS(string in,int switcher)
{
    int littleEndian=1;
    string output;
    string out;
    if(switcher == littleEndian) {
        int size = in.length();
        for (int j = 0; j <size; j++) {
            int val=int(in[j]);
            output="";
            while(val>0)
            {
                (val%2)?output.push_back('1'):output.push_back('0');
                val/=2;
            }
            reverse(output.begin(),output.end());
            while(output.size()<8)
            {
                output='0'+output;
            }
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
string kodowanie(vector<int>pack)
{
    string out;
    int p1,p2,p3;
    p1=(pack[0]+pack[1]+pack[3])%2;
    p2=(pack[0]+pack[2]+pack[3])%2;
    p3=(pack[1]+pack[2]+pack[3])%2;
    out.push_back(p1+'0');
    out.push_back(p2+'0');
    out.push_back(pack[0]);
    out.push_back(p3+'0');
    out.push_back(pack[1]);
    out.push_back(pack[2]);
    out.push_back(pack[3]);
    return out;
}
string negowanie(string binary,int index)
{
    index--;
    if(binary[index]=='0')
        binary[index]='1';
    else if(binary[index]=='1')
        binary[index]='0';
    return binary;
}
string dekodowanie(vector<int>pack,int ktora) {
    string out;
    int p1, p2, p3, n;
    p1 = (pack[0] + pack[2] + pack[4] + pack[6]) % 2;
    p2 = (pack[1] + pack[2] + pack[5] + pack[6]) % 2;
    p3 = (pack[3] + pack[4] + pack[5] + pack[6]) % 2;
    n = p1 * 1 + p2 * 2 + p3 * 4;

    if (n > 0)
    {
        //cout<<"Blad na "<<n+(7*ktora)<<" bicie"<<endl;
        n--;
        if(pack[n]==49)pack[n]=48;
        else if(pack[n]==48)pack[n]=49;
    }
    out.push_back(pack[2]);
    out.push_back(pack[4]);
    out.push_back(pack[5]);
    out.push_back(pack[6]);
    return out;

}
string kodowanie_SECDED(vector<int>pack)
{
    string out;
    int p1,p2,p3,p4;
    p1=(pack[0]+pack[1]+pack[3])%2;
    p2=(pack[0]+pack[2]+pack[3])%2;
    p3=(pack[1]+pack[2]+pack[3])%2;
    out.push_back(p1+'0');
    out.push_back(p2+'0');
    out.push_back(pack[0]);
    out.push_back(p3+'0');
    out.push_back(pack[1]);
    out.push_back(pack[2]);
    out.push_back(pack[3]);
    p4=((int)out[0]+(int)out[1]+(int)out[2]+(int)out[3]+(int)out[4]+(int)out[5]+(int)out[6])%2;
    out.push_back(p4+'0');
    return out;
}
string dekodowanie2(vector<int>pack,int ktora)
{

    int p1,p2,p3,p4;
    int a;
    string out;
    p4=((int)pack[0]+(int)pack[1]+(int)pack[2]+(int)pack[3]+(int)pack[4]+(int)pack[5]+(int)pack[6])%2;
    if(pack[7]==48)a=0;
    if(pack[7]==49)a=1;
   // if(p4!=a)cout<<"50% szans na naprawe"<<endl;
    p1=(pack[0]+pack[2]+pack[4]+pack[6])%2;
    p2=(pack[1]+pack[2]+pack[5]+pack[6])%2;
    p3=(pack[3]+pack[4]+pack[5]+pack[6])%2;
    int n;
    n=p1*1+p2*2+p3*4;
    if(n>0)
    {
       // cout<<"Blad na "<<n+(7*ktora)<<" bicie"<<endl;
        n--;
        if(pack[n]==49)pack[n]=48;
        else if(pack[n]==48)pack[n]=49;
    }
    p4=((int)pack[0]+(int)pack[1]+(int)pack[2]+(int)pack[3]+(int)pack[4]+(int)pack[5]+(int)pack[6])%2;
    if(p4==a)
    {
        out.push_back(pack[2]);
        out.push_back(pack[4]);
        out.push_back(pack[5]);
        out.push_back(pack[6]);

    } else
    {
        /*ktora++;
        string kt=to_string(ktora);
        string error="Wystąpiły conajmnije 2 błedy!!\nPaczka "+kt;
        error+=" Odrzucona \n";
        cout<<error<<endl;
       return "[x]";
         */
        out.push_back(pack[2]);
        out.push_back(pack[4]);
        out.push_back(pack[5]);
        out.push_back(pack[6]);

    }
    return out;
}

