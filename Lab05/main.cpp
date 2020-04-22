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
    double A2=6;
    double f=4;
    vector<double>out;
    string::iterator it;
    int index=1;
    for(it=binary.begin();it<binary.end();it++,index+=10)
    {
        if(*it=='0')
        {
            out.push_back(A1*sin(2*PI*f*index+0));
        }
        else if(*it=='1')
        {
            out.push_back(A2*sin(2*PI*f*index+PI));
        }
    }
    return out;

}
int main() {
    int N=100;
    double Tb=1;
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
    for(int i=0;i<ask.size();i++)
    {
        plik1<<ask[i]<<","<<i<<endl;
    }
    plik1.close();
    return 0;
}
