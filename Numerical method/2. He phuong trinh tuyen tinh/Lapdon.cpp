#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;
double epsilon = 1.5*1e-3;

int main(){
    int n;
    double C[20][20],d[20];
    ifstream file("Matrannxn.txt");
	if (!file) {
        cout << "Khong the mo file Matrannxn.txt" << endl;
        return 1;
    }
    file>>n;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            file >> C[i][j];
        }
        file >> d[i];
    }
    file.close(); 

    double chuan_C_vocung = 0;
    double chuan_C_1 = 0;
    double x[20],temp[20];
    double saiso;
    int dem;

    for (int i=0; i<n; i++){
        double sum=0;
        for (int j=0; j<n; j++){
            sum+=fabs(C[i][j]);
        }
        if (sum>chuan_C_vocung) chuan_C_vocung=sum;
    }
    for (int j=0;j<n;j++){
        double sum=0;
        for (int i=0;i<n;i++){
            sum+=fabs(C[i][j]);
        }
        if (sum>chuan_C_1) chuan_C_1=sum;
    }

    if(chuan_C_vocung<1){
        double eps = epsilon * (1-chuan_C_vocung)/chuan_C_vocung;
        for (int i=0;i<n;i++){
            x[i]=0;
        }
        dem=0;
        do{
            for (int i=0;i<n;i++){
                temp[i]= x[i];
            }
            for (int i=0;i<n;i++){
                cout<<setprecision(8)<< x[i] <<" ";
            }
            cout<<" "<<dem<<endl;
            for (int i=0;i<n;i++){
                double sum=0;
                for (int j=0;j<n;j++){
                    sum+=C[i][j]*temp[j];
                }
                x[i]=sum;
            }
            for (int i=0;i<n;i++){
                x[i]+=d[i];
            }
            saiso=0;
            for (int i=0;i<n;i++){
                if(fabs(x[i]-temp[i])>saiso) saiso=fabs(x[i]-temp[i]);
            }
            dem++;
        }
        while(saiso>=eps);
        cout<<endl<<"So lan lap la: "<<dem<<endl;
        cout<<"Dieu kien dung:||X(k)-X(k-1)||_oo >=(1-q)*epsilon/q = "<<eps<<endl;
        cout<<"||C||_oo = "<<chuan_C_vocung<<endl;
        cout<<"Nghiem x xap xi: "<<endl;
        for (int i=0;i<n;i++){
            cout<<setprecision(8)<< x[i]<<endl;
        }
    }
    cout<<endl<<"----------------------------------------------------------------"<<endl;
    if(chuan_C_1<1){
        double eps1 = epsilon * (1-chuan_C_1)/chuan_C_1;
        for (int i=0;i<n;i++){
            x[i]=0;
        }
        dem=0;
        do{
            for (int i=0;i<n;i++){
                temp[i]= x[i];
            }
            for (int i=0;i<n;i++){
                cout<< x[i] <<" ";
            }
            cout<<endl;
            for (int i=0;i<n;i++){
                double sum=0;
                for (int j=0;j<n;j++){
                    sum+=C[i][j]*temp[j];
                }
                x[i]=sum;
            }
            for (int i=0;i<n;i++){
                x[i]+=d[i];
            }
            saiso=0;
            for (int i=0;i<n;i++){
                saiso += fabs(x[i]-temp[i]);
            }
            dem++;
        }
        while(saiso>=eps1);
        cout<<endl<<"So lan lap la: "<<dem<<endl;
        cout<<"Nghiem x xap xi: "<<endl;
        for (int i=0;i<n;i++){
            cout<<setprecision(8)<< x[i]<<endl;
        }
    }

    return 0;
}
