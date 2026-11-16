#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
double epsilon = 1e-5;

int main(){
    int n;
    double A[20][20],b[20];
    ifstream file("Matrannxn.txt");
	if (!file) {
        cout << "Khong the mo file Matrannxn.txt" << endl;
        return 1;
    }
    file>>n;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            file >> A[i][j];
        }
        file >> b[i];
    }
    file.close(); 

//Kiem tra cheo troi
    int kiemtra_cheotroihang = 0;
    int kiemtra_cheotroicot = 0;
    for (int i=0; i<n; i++){
        double sum=0;
        for (int j=0; j<n; j++){
            if(j!=i) sum+=fabs(A[i][j]);
        }
        if(fabs(A[i][i])>sum){
            kiemtra_cheotroihang=1;
        }
        else {
            kiemtra_cheotroihang = 0;
            break;
        }
    }
    
    for (int j=0; j<n; j++){
        double sum=0;
        for (int i=0; i<n; i++){
            if (i!=j) sum+=fabs(A[i][j]);
        }
        if (fabs(A[j][j])>sum) {
            kiemtra_cheotroicot=1;
        }
        else {
            kiemtra_cheotroicot= 0;
            break;
        }
    }

//Ma tran T
    double T[20][20];
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (j!=i) T[i][j]=0;
            else T[i][j]=1/A[i][i];
        }
    }
    double B[20][20],d[20];
//Neu ma tran A la cheo troi hang
    if (kiemtra_cheotroihang==1){
        cout<<endl<<"----------------------------------------------------------------";
        cout<<endl<<"Ma tran A la ma tran cheo troi hang";
        cout<<endl<<"Lap jacobi ma tran cheo troi hang"<<endl;
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                if (j==i) B[i][j]=0;
                else B[i][j]=-A[i][j]*T[i][i];
            }
        }
        for (int i=0; i<n; i++){
            d[i]=b[i]*T[i][i];
        }

        //Tim ||B|| vo cung
        double chuan_B_vocung=0;
        for (int i=0; i<n; i++){
            double sum=0;
            for (int j=0; j<n; j++){
                sum+=fabs(B[i][j]);
            }
            if (sum>chuan_B_vocung) chuan_B_vocung=sum;
        }
        double eps = epsilon*(1-chuan_B_vocung)/chuan_B_vocung;
        //Buoc lap
        double x[20];
        for (int i=0; i<n; i++){
            x[i]=0;
        }
        double temp[20];
        double chuan_vocung;
        int dem=0;
        cout<<endl<<"Chon X(0)=[ ";
        for (int i=0; i<n; i++){
            cout<<x[i]<<" ";
        }
        cout<<"]";
        do{
            for(int i=0; i<n; i++){
                temp[i]=x[i];
            }
            double c[20];
            for (int i=0; i<n; i++){
                c[i]=0;
                for (int j=0; j<n; j++){
                    c[i]+=temp[j]*B[i][j];
                }
            }
            for (int i=0; i<n; i++){
                x[i]=c[i]+d[i];
            }
            cout<<endl<<"X("<<dem+1<<")=[ ";
            for (int i=0; i<n; i++){
                cout<<x[i]<<" ";
            }
            cout<<"]";
            chuan_vocung=0;
            for (int i=0; i<n; i++){
                if (fabs(x[i]-temp[i])>chuan_vocung) chuan_vocung=fabs(x[i]-temp[i]);
            }
            dem++;
        }
        while (chuan_vocung>=eps);
        cout<<endl<<"So lan lap la: "<<dem<<endl;
        cout<<"Sai so la: "<<eps<<endl;
        cout<<"||B|| vo cung = "<<chuan_B_vocung<<endl;
        cout<<"Nghiem x xap xi: "<<endl;
        for (int i=0;i<n;i++){
            cout<< x[i]<<endl;
        }
    }
    else cout<<endl<<"Ma tran A khong la ma tran cheo troi hang";

//Neu la ma tran cheo troi cot
    if(kiemtra_cheotroicot==1){
        cout<<endl<<"----------------------------------------------------------------";
        cout<<endl<<"Ma tran A la ma tran cheo troi cot";
        cout<<endl<<"Lap jacobi ma tran cheo troi cot"<<endl;
        double max_fabs_aii=fabs(A[0][0]),min_fabs_aii=fabs(A[0][0]);
        for (int i=0;i<n;i++){
            if (fabs(A[i][i])>max_fabs_aii) max_fabs_aii=fabs(A[i][i]);
            if (fabs(A[i][i])<min_fabs_aii) min_fabs_aii=fabs(A[i][i]);
        }
        double B1[20][20];
        for (int j=0;j<n;j++){
            for(int i=0;i<n;i++){
                if(i==j) B1[i][j]=0;
                else B1[i][j]=-A[i][j]*T[j][j];
            }
        }
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                if (j==i) B[i][j]=0;
                else B[i][j]=-A[i][j]*T[i][i];
            }
        }
        for (int i=0; i<n; i++){
            d[i]=b[i]*T[i][i];
        }
        //Tim ||B1||_1
        double chuan_B1_1=0;
        for (int j=0;j<n;j++){
            double sum=0;
            for (int i=0;i<n;i++){
                sum+=fabs(B1[i][j]);
            }
            if (sum>chuan_B1_1) chuan_B1_1=sum;
        }
        double lambda = max_fabs_aii/min_fabs_aii;
        double eps1 = epsilon*(1-chuan_B1_1)/lambda/chuan_B1_1;
        double x[20],temp[20];
        double saiso_chuan_1;   
        int dem=0;

        for (int i=0; i<n; i++){
            x[i]=0;
        }
        cout<<endl<<"Chon X(0)=[ ";
        for (int i=0; i<n; i++){
            cout<<x[i]<<" ";
        }
        cout<<"]";

        do{
            for(int i=0; i<n; i++){
                temp[i]=x[i];
            }
            double c[20];
            for (int i=0; i<n; i++){
                c[i]=0;
                for (int j=0; j<n; j++){
                    c[i]+=temp[j]*B[i][j];
                }
            }
            for (int i=0; i<n; i++){
                x[i]=c[i]+d[i];
            }
            cout<<endl<<"X("<<dem+1<<")=[ ";
            for (int i=0; i<n; i++){
                cout<<x[i]<<" ";
            }
            cout<<"]";
            saiso_chuan_1=0;
            for (int i=0; i<n; i++){
                saiso_chuan_1 += fabs(x[i]-temp[i]);
            }
            dem++;
        }
        while (saiso_chuan_1>=eps1);

        cout<<endl<<"So lan lap la: "<<dem<<endl;
        cout<<"Sai so hau nghiem la: "<<eps1<<endl;
        cout<<"||B||_1 = "<<chuan_B1_1<<endl;
        cout<<"Nghiem x xap xi: "<<endl;
        for (int i=0;i<n;i++){
            cout<< x[i]<<endl;
        }
    }
    else cout<<endl<<"Ma tran A khong la ma tran cheo troi cot";

    return 0;
}
