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

    double A1[20][20],S[20][20],b1[20],Y[20],X[20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            S[i][j] = 0;
        }
    }
    
//Tim A1 va b1
    //kiem tra tinh doi xung cua A
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
    if (kiemtra_doixung == 1) {
        cout<<"Ma tran A la ma tran vuong doi xung"<<endl;
        cout<<"A1=A"<<endl;
        cout<<"b1=b";
        for (int i=0; i<n ; i++) {
            for (int j=0; j<n ; j++) {
                A1[i][j] = A[i][j];
            }
        }
        for (int i=0; i<n ; i++){
            b1[i] = b[i];
        }

    }
    else {
        cout<<"A khong doi xung"<<endl;
        cout<<"De giai theo Cholesky can nhan 2 ve voi ma tran chuyen vi At"<<endl;
        cout<<"Phuong trinh tro thanh A1*x=b1"<<endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += A[k][i] * A[k][j];
                }
                A1[i][j]=sum;
            }
        }
        for (int i = 0; i < n; i++) {
            b1[i] = 0;
            for (int j = 0; j < n; j++) {
                b1[i] += A[j][i] * b[j];
            }
        }
    }

//Tim ma tran S
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            double sum=0;
            for (int k = 0; k < n; k++){
                sum += S[k][i]*S[k][j];
            }
            if (i == j) {
                double val = A1[i][i] - sum;
                if (val <= 0) {
                    cout << "Ma tran khong xac dinh duong!" << endl;
                    return 1;
                }
                S[j][i] = sqrt(val);
            }
            if(j < i) {
                S[j][i] = (A1[j][i] - sum)/S[j][j];
            }
        }
    }
//Tim Y
    for (int i=0;i<n;i++) {
        Y[i]=0;
        double sum=0;
        for (int j=0;j<i;j++) {
            sum+=S[j][i]*Y[j];
        }
        Y[i]=(b1[i] - sum)/S[i][i];
    }
//Tim X
    for (int i=n-1;i>=0;i--) {
        X[i]=0;
        double sum=0;
        for (int j=i+1;j<n;j++) {
            sum+=S[i][j]*X[j];
        }
        X[i]=(Y[i]-sum)/S[i][i];
    }

    cout<<endl<<"Ma tran A1: "<<endl;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cout<<A1[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Ma tran b1:"<<endl;
    for (int i=0;i<n;i++) {       
            cout<<b1[i]<<" ";  
    }
    cout<<endl<<"Phan tich A1 theo Cholesky A1=St*S"<<endl;
    cout<<"Ma tran S: "<<endl;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cout<<S[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Phuong trinh tro thanh St*S*x=b1"<<endl;
    cout<<"Dat y=S*x ta co: St*Y=b1"<<endl;
    cout<<"Giai phuong trinh tren ta duoc:"<<endl;
    cout<<"Nghiem y: "<<endl;
    for (int i=0;i<n;i++) {       
            cout<<Y[i]<<" ";  
    }
    cout<<endl<<"Giai phuong trinh S*x=y"<<endl;
    cout<<"Ta co nghiem x: "<<endl;
    for (int i=0;i<n;i++) {       
            cout<<X[i]<<" ";  
    }

    return 0;
}
