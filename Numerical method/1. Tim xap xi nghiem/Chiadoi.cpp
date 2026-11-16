#include <iostream>
#include <cmath>
using namespace std;
double epsilon=1.0e-9;


double f(double x){
    return pow(x,3)-x-1;
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
double chiadoi(double a,double b){
    double c;
    int dem=0;
    while(fabs(a-b)>=epsilon){
        c=(a+b)/2;
        double fc=f(c);
        if (fc==0) return c;
        if (fc*f(a)<0) b=c;
        else a=c;
        dem++;
    }
    cout<<endl<<"So lan lap : "<<dem;
    cout<<endl<<"Nghiem gan dung la : "<<c;
    return c;
}

int main(){
    double a,b;
    cout<<"Nhap vao a: ";
    cin>>a;
    cout<<"Nhap vao b: ";
    cin>>b;

    // kiemtra(a,b);
    cout<<endl;
    if (kiemtra(a,b)==1){
        cout<<"Dau vao hop le"<<endl;
        chiadoi(a,b);
    }

    return 0;
}