#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int find(int index[], int m) {
    int k = 0;
    int max = 0;
    for (int i = 0; i < m; i++) {
        if (index[i] > max) {
            k = i;
            max = index[i];
        }
    }
    return k;
}

int Gauss(double A[20][20], int m, int n) {
    int index[20];
    int j = 0;
    double x[20];
    for (int i = 0; i < m; i++) {
        index[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int kiemtra;
        do {
            kiemtra = 0;
            if (fabs(A[i][j]) < 1e-9) {
                kiemtra = -1;
                for (int k = i + 1; k < m; k++) {
                    if (fabs(A[k][j]) > 1e-9) {
                        kiemtra = k;
                        break;
                    }
                }
                if (kiemtra != -1) {
                    for (int k = 0; k < n + 1; k++) {
                        double c = A[i][k];
                        A[i][k] = A[kiemtra][k];
                        A[kiemtra][k] = c;
                    }
                } else j++;
            }
        }
        while (kiemtra == -1 && j < n + 1);
        if (kiemtra != -1) index[i] = j;

        if (kiemtra != -1) {
            for (int k = i + 1; k < m; k++) {
                double c = A[k][j] / A[i][j];
                for (int l = 0; l < n + 1; l++) {
                    A[k][l] = A[k][l] - c * A[i][l];
                }
            }
        }
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n + 1; c++) {
                cout << A[r][c] << " ";
            }
            cout << endl;
        }
        cout<<"----------------------------------------------------------------"<<endl;

        j++;
        if (j == n) break;
    }
    for (int i = 0; i < m; i++) {
        cout << index[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        for (int c = 0; c < n + 1; c++) {
            cout << A[i][c] << " ";
        }
        cout << endl;
    }
    int ind = find(index, m);

    if (index[ind] == n - 1) {
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0;
            for (int k = i + 1; k < n; k++) {
                sum += A[i][k] * x[k];
            }
            x[i] = (A[i][n] - sum)/A[i][i];
        }
        cout << "He co nghiem duy nhat:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x["<<i+1<<"]= " << x[i] << endl;
        }
    }
    if (index[ind] == n) {
        cout << "He vo nghiem";
    }
    if (index[ind] < n - 1) {
        cout << "He vo so nghiem";
    }

    return 0;
}

int main() {
    int n, m;
    double A[20][20];
    ifstream file("Matran.txt");
    if (!file) {
        cout << "Khong the mo file Matran.txt" << endl;
        return 1;
    }
    file >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n + 1; j++) {
            file >> A[i][j];
        }
    }
    file.close();
    Gauss(A, m, n);

    return 0;
}
