#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
double epsilon = 1e-5;

int kiemtra(int index[], int n) {
    for (int i = 0; i < n; i++) {
        if (i!=index[i]) {
            return i;
        }
    }
    return -1; // -1 là ma trận là ma trận đường chéo
}

int main(){
    int n;
    double A[20][40];
    ifstream file("Matrannghichdao.txt");
    if (!file) {
        cout << "Khong the mo file Matrannghichdao.txt" << endl;
        return 1;
    }
    file >> n;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            file >> A[i][j];
        }
    }
    file.close(); 
    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2 * n; j++) {
            if (j == i + n)
                A[i][j] = 1;
            else
                A[i][j] = 0;
        }
    }

    int index_hang[20], index_cot[20],index[20],dem=0;
    for (int i=0; i<n; i++){
        index_hang[i] = 0;
        index_cot[i] = 0;
    }

    while (dem<n){
        dem++;
        int hang = -1, cot = -1;
        double max_val = 0;
        for (int i=0; i<n; i++){
            if (index_hang[i]==1) continue;
            for (int j=0; j<n; j++){
                if (index_cot[j]==1) continue;
                if (fabs(fabs(A[i][j]) - 1.0) < 1e-9) {
                    hang = i;
                    cot = j;
                    break;
                }
                if (fabs(A[i][j]) > max_val) {
                    max_val = fabs(A[i][j]);
                    hang = i;
                    cot = j;
                }
            }
            if (hang != -1 && fabs(fabs(A[hang][cot]) - 1.0) < 1e-9) break;
        }
        if (hang == -1 || fabs(A[hang][cot]) < 1e-9) {
            cout<<"Ma tran khong kha nghich";
            return 0;
        }
        double ptg = A[hang][cot];
        cout<<endl<<"Phan tu giai la: "<<ptg;
        index_hang[hang]=1;
        index_cot[cot]=1;
        index[hang]=cot;

        for (int i=0; i<n; i++) {
            if (i==hang) continue;
            double c=A[i][cot]/ptg;
            for (int j=0; j<2*n; j++) {
                A[i][j]-=c*A[hang][j];
            }
        }
        cout<<endl<<"("<<hang+1<<","<<cot+1<<")"<<endl;
        for (int i=0; i<n; i++){
            for (int j=0; j<2*n; j++){
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
    }

    for (int i=0; i<n; i++){
        double c=A[i][index[i]];
        for (int j=0; j<2*n; j++){
            A[i][j]/=c;
        }
    }
    while (kiemtra(index,n)!=-1) {
        int i=kiemtra(index,n);
        int a=index[i];
        int b=index[a];
        for (int j=0; j<2*n; j++){
            double x=A[i][j];
            A[i][j]=A[a][j];
            A[a][j]=x;
        }
        index[i]=b;
        index[a]=a;
    }

    cout << endl << "Ma tran nghich dao cua A" << endl;
    for (int i=0; i<n; i++){
        for (int j=n; j<2*n; j++){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
