#include<iostream>
#include<cmath>
using namespace std;
double epsilon= 1e-4;
double h=pow(10,(int(log10(epsilon))));
#define eps 1e-4

double f(double x){
    return pow(x,3)-x-1;
}
double f1(double x){
    return (f(x+h)-f(x-h))/(2*h);
}
double f2(double x){
    return (f1(x+h)-f1(x-h))/(2*h);
}
double tim_M1(double a, double b) // khoi tao ham tim M1 = max|f'(x)| tren [a,b]
{
	double max=fabs(f1(a)),i=a+eps;
	do
	{
		if (fabs(f1(i)) > max) max=fabs(f1(i));
		i+=eps;
	}
	while (i<=b);
	return max;
}
double tim_m1(double a, double b){
    double min=fabs(f1(a)),i=a+eps;
    do{
        if (fabs(f1(i)) < min) min=fabs(f1(i));
        i+=eps;
    }
    while (i<=b);
    return min;
}
double tim_M2(double a, double b){
    double max=fabs(f2(a)),i=a+eps;
    do{
        if (fabs(f2(i)) > max) max=fabs(f2(i));
        i+=eps;
    }
    while (i<=b);
    return max;
}
double tim_m2(double a, double b){
    double min=fabs(f2(a)),i=a+eps;
        do{
            if (fabs(f2(i)) < min) min=fabs(f2(i));
            i+=eps;
        }
        while (i<=b);
        return min;
}

int kiemtra(double a,double b){
    if (f(a)==0||f(b)==0){
        cout<<"Nghiem nam o dau mut";
        return 1;
    }
    if(a>=b){
        cout<<"Dau vao khong hop le do a>=b"<<endl;
        return 0;
    }
    if (f(a)*f(b)>0){
        cout<<"Dau vao khong hop le do f(a)*f(b)>0";
        return 0;
    }
    return 1;
}
int kiemtradondieu(double a,double b){
    double f1_a = f1(a), f2_a = f2(a);
    for (double i = a; i <= b; i += eps) {
        if (f1(i) * f1_a <= 0 || f2(i) * f2_a <= 0) {
            cout<<"f'(x) hoac f''(x) doi dau tren [a,b]";
            return 0;
        }
    }
    cout<<"f'(x) va f''(x) giu nguyen dau tren [a,b]. ";
    return 1;
}

void daycung(double a,double b){
    double x,d;
    if (f(a)*f2(a)>0){
        d=a;
        x=b;
    }
    else{
        d=b;
        x=a;
    }
    int dem=0;
    cout<<endl<<x;
    double tol = epsilon*tim_m1(a,b);
    while (fabs(f(x))>tol){
        x=x-f(x)*(x-d)/(f(x)-f(d));
        dem++;
    }
    cout<<endl<<"So lan lap : "<<dem;
    cout<<endl<<"Nghiem gan dung x= "<<x<<endl;
}
int main(){
    double a,b;
    cout<<"Nhap vao a: ";
    cin>>a;
    cout<<"Nhap vao b: ";
    cin>>b;

    cout<<endl;
    if(kiemtra(a,b)==1&&kiemtradondieu(a,b)==1){
        cout<<"Dau vao hop le"<<endl;
        daycung(a,b);
    }

    return 0;
}
