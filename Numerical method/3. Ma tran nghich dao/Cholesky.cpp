#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
double epsilon = 1e-5;

int main(){
    int n;
    double A[20][20];
    ifstream file("Matrannghichdao.txt");
	if (!file) {
        cout << "Khong the mo file Matrannghichdao.txt" << endl;
        return 1;
    }
    file>>n;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            file >> A[i][j];
        }
    }
    file.close(); 

    double A1[20][20],S[20][20],B1[20][20],E[20][20],Y[20][20],X[20][20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            S[i][j] = 0;
        }
    }

//Ma tran E
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (j==i) E[i][j] = 1;
            else E[i][j] = 0;
        }
    }
// Kiem tra tinh doi xung cua A
    int kiemtra_doixung = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(A[i][j] - A[j][i]) > 1e-9) {
                kiemtra_doixung = 0;
                break;
            }
        }
        if (kiemtra_doixung == 0) break;
    }
//Tim A1,B1
    if (kiemtra_doixung == 1) {
        cout<<"Ma tran A la ma tran vuong doi xung"<<endl;
        cout<<"AX=E"<<endl;//A1=A,Z=X
        for (int i=0; i<n ; i++) {
            for (int j=0; j<n ; j++) {
                A1[i][j] = A[i][j];
            }
        }
        for (int i=0; i<n ; i++) {
            for (int j=0; j<n ;j++){
                B1[i][j]=E[i][j];
            }
        }
    }
    else {
        cout<<"A khong doi xung"<<endl;
        cout<<"De su dung pp Cholesky nhan 2 ve voi At "<<endl;
        cout<<"Phuong trinh tro thanh At*A*X=At "<<endl;//A1=A*At
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += A[k][i] * A[k][j];
                }
                A1[i][j]=sum;
            }
        }
        for (int i = 0; i <n;i++) {
            for (int j = 0; j<n;j++ ){
                B1[i][j]= A[j][i];
            }
        }

    }
//Tim ma tran S
    for (int i = 0; i < n; i++) {
        for (int j =0;j<n;j++){
            double sum=0;
            for (int k=0;k<n;k++){
                sum+=S[k][i]*S[k][j];
            }
            if (i == j) {
                double val = A1[i][i] - sum;
                if (val <= 0) {
                    cout << "Ma tran khong xac dinh duong!" << endl;
                    return 1;
                }
                S[j][i] = sqrt(val);
            }
            if(j<i) {
                S[j][i] = (A1[j][i] - sum)/S[j][j];
            }
        }
    }
    cout<<endl<<"At*A=St*S "<<endl;
    cout<<"Ta tim duoc ma tran tam giac tren S: "<<endl;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cout<<S[i][j]<<" ";
        }
        cout<<endl;
    }
//giai St*(S*X)=B1
    cout<<endl<<"Giai SX = "<<endl;
    for (int k=0; k<n; k++) {
        for (int i=0;i<n;i++) {
            Y[i][k]=0;
            double sum=0;
            for (int j=0;j<i;j++) {
                sum+=S[j][i]*Y[j][k];
            }
            Y[i][k]=(B1[i][k] - sum)/S[i][i];
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cout<<Y[i][j]<<" ";
        }
        cout<<endl;
    }
//Tim Y=SX => X
    for (int k=0; k<n; k++) {
        for (int i=n-1;i>=0;i--) {
            X[i][k]=0;
            double sum=0;
            for (int j=i+1;j<n;j++) {
                sum+=S[i][j]*X[j][k];
            }
            X[i][k]=(Y[i][k]-sum)/S[i][i];
        }
    }

    cout<<endl<<"Ma tran nghich dao cua A la X"<<endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout<<X[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
