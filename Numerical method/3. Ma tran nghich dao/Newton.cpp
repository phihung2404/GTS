#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
double epsilon = 1e-10;

int main() {
    int n;
    double A[20][20];
    ifstream file("Matrannghichdao.txt");
    if (!file) {
        cout << "Khong the mo file Matrannghichdao.txt" << endl;
        return 1;
    }
    file >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> A[i][j];
        }
    }
    file.close();

    double E[20][20], X[20][20], G[20][20], temp[20][20];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            E[i][j] = 0;
        }
        E[i][i] = 1;
    }

    cout << "Ma tran A: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    // Ma tran xap xi ban dau X0
    double chuan_A_1 = 0;
    double chuan_A_vocung = 0;

    for (int j = 0; j < n; j++) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += fabs(A[i][j]);
        }
        if (sum > chuan_A_1)
            chuan_A_1 = sum;
    }
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += fabs(A[i][j]);
        }
        if (sum > chuan_A_vocung)
            chuan_A_vocung = sum;
    }
//Tim ma tran xap xi dau vao
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            X[i][j] = A[j][i] / chuan_A_vocung / chuan_A_1;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            double sum=0;
            for (int k = 0; k < n; k++){
                sum+=A[i][k]*X[k][j];
            }
            G[i][j] = sum-E[i][j];
        }
    }

//Buoc lap 
    double q=0;
    for (int i = 0; i < n; i++){
        double sum=0;
        for (int j = 0; j < n; j++){
            sum+=fabs(G[i][j]);
        }
        if (sum>q) q=sum;
    }
    if (q >= 1.0) {
        cout << "Phuong phap Newton khong hoi tu do q = " << q << " >= 1" << endl;
        return 0;
    }
    double chuan_X0_vocung =0;
    for (int i = 0; i <n; i++){
        double sum=0;
        for (int j = 0; j < n; j++){
            sum+=fabs(X[i][j]);
        }
        if (sum>chuan_X0_vocung) chuan_X0_vocung=sum;
    }
    double eps = epsilon * (1-q)/chuan_X0_vocung;
    int k=0;
    while(pow(q,pow(2,k))>=eps && k < 50){
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                temp[i][j]= X[i][j];
            }
        }
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                double sum=0;
                for (int t=0;t<n; t++){
                    sum+=A[i][t]*temp[t][j];
                }
                G[i][j]=sum-E[i][j];
            }
        }
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                double sum=0;
                for (int t=0;t<n;t++){
                    sum+=temp[i][t]*G[t][j];
                }
                X[i][j]=temp[i][j]-sum;
            }
        }
        k++;
    }

    cout << "Ma tran nghich dao cua A la:" << endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout<<X[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"So buoc lap: "<<k<<endl;

    return 0;
}
