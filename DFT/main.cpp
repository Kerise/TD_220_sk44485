#include<iostream>
#include<math.h>
#include<fstream>
#include<vector>
using namespace std;
#include <cstdlib>
#include <ctime>
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
vector<DFT_Coeff> dft(double N,vector<double>x){
    DFT_Coeff dft_value;
    int prev_proc;
    int procent;
    N=N/100;
    cout<<N;
    vector<DFT_Coeff>complex(N);
    cout<<"in DFT"<<endl;
    for(double j=0;j<N;j++){
        procent=(double)(j/N)*100;

        if(prev_proc!=procent){
            cout.precision(2);
            cout<<"licze "<<procent<<"%"<<endl;
        }
        prev_proc=procent;
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

double min(double max_w,double M[],double f[], int size) //Funkcja min
{
    float min = M[0];
    for (int i = 0; i < size/ 2; i++)
    {
        if (M[i] > max_w)
        {
            min = f[i];
            return min;
        }
    }
}

double max(double max_w,double M[], double f[], int size) //Funkcja max
{
    float max = M[size/2];
    for (int i = size/2; i > 0; i--)
    {
        if (M[i] > max_w && M[i]>0)
        {
            max = f[i];
            return max;
        }
    }
}

double max_2(double M[], double f[], int size) //Funkcja max
{
    double max_w = M[0];

    for (int i = 0; i < size / 2; i++)
    {
        if (M[i] > max_w)
        {
            max_w = M[i];
        }
    }
    max_w = max_w - 3;
    return max_w;
}
double szerokosc(string filename)
{
    std::ifstream File(filename);
    string a, b, c;
    std::vector<double> m;
    std::vector<double> mprim;
    std::vector<double> hZ;
    while (getline(File, a, ','))
    {
        getline(File, b, ',');
        getline(File, c);
        hZ.push_back(stod(b));
        mprim.push_back(stod(c));
    }

    double min = 0;
    double minVal = 0;
    for (size_t i = 0; i < mprim.size(); i++)
    {
        if (mprim[i] < minVal && mprim[i] > (-3))
        {
            min = hZ[i];
            minVal = mprim[i];
        }
    }

    double max = 0;
    double maxVal = 0;
    for (size_t i = 0; i < mprim.size(); i++)
    {
        if (mprim[i] > maxVal)
        {
            max = hZ[i];
            maxVal = mprim[i];
        }
    }

    return abs(max - min);
}
int main() {
    srand(time(0));
    const static int q = 15;
    const static float c1 = (1 << q) - 1;
    const static float c2 = ((int)(c1 / 3)) + 1;
    const static float c3 = 1.f / c1;

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
    myFile.open("ask.csv");
    string p;
    string p2;
    vector<double> data;
    while (getline(myFile, p, ',')) {
        getline(myFile, p2);
        double fun = stod(p);
        data.push_back(fun);
    }
    int N = data.size();
        vector<double> zA_szum;
        vector<double> zF_szum;
        vector<double> zP_szum;
        float noise=0.f;
        plik1.open("noise.csv");
        float random = 0.f;
        double alfa=0.9;
        for (int i = 0; i <N; i++)
        {
            random = ((float)rand() / (float)(RAND_MAX+1));
            noise = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3;

            zA_szum.push_back((data[i] * alfa) + (noise * (1 - alfa)));
            zF_szum.push_back((data[i] * alfa) + (noise * (1 - alfa)));
            zP_szum.push_back((data[i] * alfa) + (noise * (1 - alfa)));
        }
        plik1.close();

    cout<<"station1"<<endl;
    vector<DFT_Coeff> complex(N);
    complex = dft(N,data);
    cout<<N<<endl;
    plik1.open("f1.csv");
    double M[N];
    double fk=0;
    for (size_t j = 0; j < complex.size(); j++) {
        M[j] = sqrt(pow(complex[j].real, 2) + pow(complex[j].img, 2));
       double decybel;
        decybel = 10 * log10(M[j]);
        fk=j*((double)100/(double)N);
        plik1 << decybel*alfa<< "," <<fk<< endl;
    }
    plik1.close();
    vector<DFT_Coeff> complex2(N);
    complex2 =dft(N,zF_szum);
    plik1.open("fsk_Szum.csv");
    for (size_t j = 0; j < complex2.size(); j++) {
        M[j] = sqrt(pow(complex2[j].real, 2) + pow(complex2[j].img, 2));
        double decybel;
        decybel = 10 * log10(M[j]);
        fk=j*((double)100/(double)N);
        plik1 << decybel*alfa<< "," <<fk<< endl;
    }
    plik1.close();
  /*  double max_temp;
    max_temp=max_2(M,fs,N);
    double max1;
    max1=max(max_temp,M,fs,N);
    double min1=min(max_temp,M,fs,N);
    double szerokosc_2;
    string file_name="f1.csv";
    szerokosc_2=szerokosc(file_name);
    cout<<szerokosc_2;

   /* vector<double> idftfun(N);
    idftfun=idft(N,complex);
    plik1.open("idft.csv");
    cout<<idftfun.size();
    int iterator=0;
    for (double j = 0; j<1; j=j+((double)1/(double)idftfun.size())) {
        plik1<<idftfun[iterator]<<","<<j<<endl;
        iterator++;
    }
    plik1.close();
    */
}