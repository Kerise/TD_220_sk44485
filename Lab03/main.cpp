#include<iostream>
#include<math.h>
#include<fstream>
#include<vector>
using namespace std;
#define PI 3.14159265
class DFT_Coeff {
public:
    double real, img;
    DFT_Coeff() {{
        real= 0.0;
        img= 0.0;
    }}
};
double sygnal(double a,double f,double ro,double t)
{
    double w=2*M_PI*f;
    double probka=a*sin(w*t+ro);
    return probka;
}
vector<DFT_Coeff> dft(int N,vector<double>x){
    DFT_Coeff dft_value;
    N=x.size();
    vector<DFT_Coeff>complex(N);
    for(int j=0;j<N;j++){
        complex[j]=dft_value;
        for (int i = 0; i < N; i++) {
            complex[j].real += x[i] * (cos(((-1)*2 * PI * j * i) / N));
            complex[j].img += x[i] * (sin(((-1)*2 * PI * j * i) / N));
        }}
    return complex;
}
vector<double> idft(int N,vector<DFT_Coeff>x)
{
    N=x.size();
    vector<double>out(N);
    for(int j=0;j<N;j++){
        out[j]=0;
        for (int i = 0; i < N;i++) {
            out[j] += ((double)1/(double)N)*(x[i].real * (cos(((-1)*2 * PI * j * i) / N))+
                    x[i].img * (sin(((-1)*2 * PI * j * i) / N)));
        }}
    return out;

}
int main() {
    int N = 20;
    double a;
    vector<double>x;
    a = 1.0;
    double f = 5;
    double ro = 4 * M_PI;
    int i = 0;
    ofstream plik1;
    double probka;
    for (double t = 0; t < 1; t = t + ((double) 1 / (double) 20)) {
        probka=sygnal(a, f, ro, t);
        x.push_back(probka);
        i++;
    }
    ifstream myFile;
    myFile.open("f8.csv");
    string p;
    string q;
    vector<double> data;
    while (getline(myFile, p, ',')) {
        getline(myFile, q);
        double fun = stod(p);
        data.push_back(fun);
    }

    vector<DFT_Coeff> complex(N);
    complex = dft(N,data);
    plik1.open("f1.csv");
    double M[N];
    for (size_t j = 0; j < N; j++) {
        M[j] = sqrt(pow(complex[j].real, 2) + pow(complex[j].img, 2));
        double decybel;
        decybel = 10 * log10(M[j]);
        plik1 << decybel<< "," << j << endl;
    }
    plik1.close();
    vector<double> idftfun(N);
    idftfun=idft(N,complex);
    plik1.open("idft.csv");
    cout<<idftfun.size();
    int iterator=0;
    for (double j = 0; j<1; j=j+((double)1/(double)idftfun.size())) {
        plik1<<idftfun[iterator]<<","<<j<<endl;
        iterator++;
    }
    plik1.close();
}