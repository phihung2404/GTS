#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
double epsilon = 1e-6;

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

    double B[20][20], T[20][20], E[20][20], X[20][20];
    double q;
//Kiem tra cheo troi
    int kiemtra_cheotroihang = 0;
    int kiemtra_cheotroicot = 0;
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            if (j != i) sum += fabs(A[i][j]);
        }
        if (fabs(A[i][i]) > sum) {
            kiemtra_cheotroihang = 1;
        } else {
            kiemtra_cheotroihang = 0;
            break;
        }
    }

    for (int j = 0; j < n; j++) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            if (i != j) sum += fabs(A[i][j]);
        }
        if (fabs(A[j][j]) > sum) {
            kiemtra_cheotroicot = 1;
        } else {
            kiemtra_cheotroicot = 0;
            break;
        }
    }

//Ma tran T
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != i) T[i][j] = 0;
            else T[i][j] = 1 / A[i][i];
        }
    }

//Ma tran don vi E
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) E[i][j] = 0;
        E[i][i] = 1;
    }

//Thiet lap B,tim q
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += T[i][k] * A[k][j];
            }
            B[i][j] = E[i][j] - sum;
        }
    }
    q = 0;
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += fabs(B[i][j]);
        }
        q = (sum > q) ? sum : q;
    }
    cout << endl << "B = E-TA " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << "||B||_vocung = q = " << q;

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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            X[i][j] = A[j][i] / chuan_A_vocung / chuan_A_1;
        }
    }
    cout << endl << "Chon ma tran xap xi dau vao X0 la: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << X[i][j] << " ";
        }
        cout << endl;
    }

//Neu la ma tran cheo troi hang
    cout<<endl<<"----------------------------------------------------------------";
    if (kiemtra_cheotroihang == 1) cout << endl << "Ma tran A la ma tran cheo troi hang";
    else cout << endl << "Ma tran A khong la ma tran cheo troi hang";
    if (kiemtra_cheotroihang == 1 && q < 1) {
        double temp[20][20];
        double saiso;
        int dem = 0;
        
        cout << endl;
        cout << "Tim ma tran nghich dao bang pp Jacobi bang cong thuc sai so hau nghiem" << endl;
        double eps = epsilon * (1 - q) / q;
        do {
            saiso = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    temp[i][j] = X[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int k = 0; k < n; k++) {
                        sum += B[i][k] * temp[k][j];
                    }
                    X[i][j] = sum + T[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                double sum = 0;
                for (int j = 0; j < n; j++) {
                    sum += fabs(X[i][j] - temp[i][j]);
                }
                if (sum > saiso) saiso = sum;
            }
            dem++;
        }
        while (saiso >= eps);
        cout << "So lan lap la: " << dem << endl;
        cout << "Dieu kien dung la ||Xk-Xk-1||_vocung >= " << eps << endl;
        cout << "Ma tran nghich dao cua A xap xi: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << X[i][j] << " ";
            }
            cout << endl;
        }
    }

//Neu la ma tran cheo troi cot
    cout<<endl<<"----------------------------------------------------------------";
    if (kiemtra_cheotroicot == 1) cout << endl << "Ma tran A la ma tran cheo troi cot";
    else cout << endl << "Ma tran A khong la ma tran cheo troi cot";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            X[i][j] = A[j][i] / chuan_A_vocung / chuan_A_1;
        }
    }
    if (kiemtra_cheotroicot == 1) {
        double temp[20][20];
        double saiso;
        int dem = 0;
        cout << endl << "Tim ma tran nghich dao bang pp Jacobi bang cong thuc sai so hau nghiem" << endl;
        double max_fabs_aii = fabs(A[0][0]), min_fabs_aii = fabs(A[0][0]);
        for (int i = 0; i < n; i++) {
            if (fabs(A[i][i]) > max_fabs_aii) max_fabs_aii = fabs(A[i][i]);
            if (fabs(A[i][i]) < min_fabs_aii) min_fabs_aii = fabs(A[i][i]);
        }
        double lambda = max_fabs_aii / min_fabs_aii;
        double B1[20][20];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += A[i][k] * T[k][j];
                }
                B1[i][j] = E[i][j] - sum;
            }
        }
        double chuan_B1_1 = 0;
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int i = 0; i < n; i++) {
                sum += fabs(B1[i][j]);
            }
            if (sum > chuan_B1_1) chuan_B1_1 = sum;
        }
        double eps1 = epsilon * (1 - chuan_B1_1) / lambda / chuan_B1_1;
        do {
            saiso = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    temp[i][j] = X[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int k = 0; k < n; k++) {
                        sum += B[i][k] * temp[k][j];
                    }
                    X[i][j] = sum + T[i][j];
                }
            }
            for (int j = 0; j < n; j++) {
                double sum = 0;
                for (int i = 0; i < n; i++) {
                    sum += fabs(X[i][j] - temp[i][j]);
                }
                if (sum > saiso) saiso = sum;
            }
            dem++;
        }
        while (saiso >= eps1);
        cout << "So lan lap la: " << dem << endl;
        cout << "Dieu kien dung la ||Xk-Xk-1||_1 >= " << eps1 << endl;
        cout << "Ma tran nghich dao cua A xap xi: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << X[i][j] << " ";
            }
            cout << endl;
        }

    }

    return 0;
}
