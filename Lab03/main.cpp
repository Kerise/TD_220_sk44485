#include<iostream>
#include<math.h>
using namespace std;
#define PI 3.14159265
class DFT_Coeff {
   public:
   double real, img;
   DFT_Coeff() {
      real = 0.0;
      img = 0.0;
   }
};
double sygnal(double a,double f,double ro,double t)
{
    double w=2*M_PI*f;
    double probka=a*sin(w*t+ro);
    return probka;
}
int main() {
   int N = 854;
   double a, b, c;
   double x[N];
   a=1.0;
   double f=8;
   double ro=4*M_PI;
   int i=0;
   for(double t=0;t<8.54;t=t+0.01){
   x[i]=sygnal(a,f,ro,t);
   i++;
   }
   double funkcja[N];
   for (int i = 0; i < N; i++) {
      funkcja[i] = (((a * (double) i) + (b * (double) i)) - c);
   }
   int k=i-1;
   double cosin[N];
   double sinu[N];
   for (int n = 0; n < N; n++) {
      cosin[n] = cos((2 * PI * k * n) / N);
      sinu[n] = sin((2 * PI * k * n) / N);
   }
   DFT_Coeff dft_value;
   cout << "The coeffs are: ";
   for (int i = 0; i < N; i++) {
      dft_value.real += x[i] * cosin[i];
      dft_value.img += x[i] * sinu[i];
   }
   cout << "(" << dft_value.real << ") - " << "(" << dft_value.img << " i)";
}
