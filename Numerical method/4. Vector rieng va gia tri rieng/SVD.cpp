#include <iostream>
#include <fstream>
#include <cmath>

#define sll 250
using namespace std;
double epsilon = 1e-8;
double sigma[20][20];
int sig=0;

void giai_pt_bac_hai(double a, double b, double c, double d[2]) {
    double delta = b * b - 4 * a * c;
    d[0] = -b / 2 / a;
    d[1] = pow(-delta, 0.5) / 2 / a;
}

int powermethod(double A[20][20], int n, double a[], double b[], int h) {
    int N = 0;
    double vector[20], temp[20], temp1[20];
    int chiso = 0;
    double saiso;
    bool TH1 = true;
    bool TH2 = false;
    bool TH3 = false;

    for (int i = 0; i < n; i++) {
        vector[i] = 1 + i + h;
    }
    double max = fabs(vector[0]);

    for (int i = 0; i < n; i++) {
        temp[i] = vector[i];
    }
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int k = 0; k < n; k++) {
            sum += A[i][k] * temp[k];
        }
        vector[i] = sum;
    }
    for (int i = 0; i < n; i++) {
        if (fabs(vector[i]) > max) {
            max = fabs(vector[i]);
            chiso = i;
        }
    }
    max = vector[chiso];
    for (int i = 0; i < n; i++) {
        vector[i] /= max;
    }

    saiso = fabs(vector[0] - temp[0]);
    for (int i = 0; i < n; i++) {
        if (fabs(vector[i] - temp[i]) > saiso) saiso = fabs(vector[i] - temp[i]);
    }
    while (saiso > epsilon && N <= sll) {
        for (int i = 0; i < n; i++) {
            temp[i] = vector[i];
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * temp[k];
            }
            vector[i] = sum;
        }
        max = fabs(vector[0]);
        chiso = 0;
        for (int i = 1; i < n; i++) {
            if (fabs(vector[i]) > max) {
                max = fabs(vector[i]);
                chiso = i;
            }
        }
        max = vector[chiso];
        for (int i = 0; i < n; i++) {
            vector[i] /= max;
        }
        saiso = fabs(vector[0] - temp[0]);

        for (int i = 0; i < n; i++) {
            if (fabs(vector[i] - temp[i]) > saiso) saiso = fabs(vector[i] - temp[i]);
        }
        N++;
    }
    if (N == sll + 1) {
        TH1 = false;
        TH2 = true;
    }
    if (TH1) {
        cout << "TH1";
        cout << endl << "Gia tri rieng la: " << max;
        cout << endl << "Vector rieng la: " << endl;
        for (int i = 0; i < n; i++) {
            cout << vector[i] << endl;
        }
        for (int i = 0; i < n; i++) {
            a[i] = vector[i];
        }
        sigma[sig][sig] = pow(max, 0.5);
        sig++;
    }
    if (TH2) {
        N = 0;
        chiso = 0;
        for (int i = 0; i < n; i++) {
            vector[i] = 1;
        }

        for (int i = 0; i < n; i++) {
            temp[i] = vector[i];
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * temp[k];
            }
            temp1[i] = sum;
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * temp1[k];
            }
            vector[i] = sum;
        }
        max = fabs(vector[0]);
        chiso = 0;
        for (int i = 1; i < n; i++) {
            if (fabs(vector[i]) > max) {
                max = fabs(vector[i]);
                chiso = i;
            }
        }
        max = vector[chiso];
        for (int i = 0; i < n; i++) {
            vector[i] /= max;
        }
        saiso = fabs(vector[0] - temp[0]);
        for (int i = 0; i < n; i++) {
            if (fabs(vector[i] - temp[i]) > saiso) saiso = fabs(vector[i] - temp[i]);
        }
        while (saiso > epsilon && N <= sll) {
            for (int i = 0; i < n; i++) {
                temp[i] = vector[i];
            }
            for (int i = 0; i < n; i++) {
                double sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += A[i][k] * temp[k];
                }
                temp1[i] = sum;
            }
            for (int i = 0; i < n; i++) {
                double sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += A[i][k] * temp1[k];
                }
                vector[i] = sum;
            }
            max = fabs(vector[0]);
            chiso = 0;
            for (int i = 1; i < n; i++) {
                if (fabs(vector[i]) > max) {
                    max = fabs(vector[i]);
                    chiso = i;
                }
            }
            max = vector[chiso];
            for (int i = 0; i < n; i++) {
                vector[i] /= max;
            }
            saiso = fabs(vector[0] - temp[0]);
            for (int i = 0; i < n; i++) {
                if (fabs(vector[i] - temp[i]) > saiso) saiso = fabs(vector[i] - temp[i]);
            }
            N++;
        }
    }
    if (N == sll + 1) {
        TH2 = false;
        TH3 = true;
    }
    if (TH2) {
        cout << endl << "TH2" << endl;
        for (int i = 0; i < n; i++) {
            vector[i] *= max;
        }

        double lambda = pow(max, 0.5);
        double chia = 0;
        for (int i = 0; i < n; i++) {
            if (fabs(vector[i] - lambda * temp1[i]) > chia) chia = fabs(vector[i] - lambda * temp1[i]);
        }
        cout << endl << "Gia tri rieng la: " << lambda;
        cout << endl << "Vector rieng la: " << endl;
        for (int i = 0; i < n; i++) {
            a[i] = (vector[i] + lambda * temp1[i]) / chia;
            cout << (vector[i] + lambda * temp1[i]) / chia << endl;
        }
        cout << endl << "Gia tri rieng la: " << -lambda;
        cout << endl << "Vector rieng la: " << endl;
        for (int i = 0; i < n; i++) {
            b[i] = (vector[i] - lambda * temp1[i]) / chia;
            cout << (vector[i] - lambda * temp1[i]) / chia << endl;
        }
        sigma[sig][sig] = pow(lambda, 0.5);
        sig++;
        sigma[sig][sig] = pow(-lambda, 0.5);
        sig++;
    }
    if (TH3) {
        cout << "TH3";
        N = 0;
        chiso = 0;
        for (int i = 0; i < n; i++) {
            vector[i] = 1;
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * temp[k];
            }
            vector[i] = sum;
        }
        max = fabs(vector[0]);
        chiso = 0;
        for (int i = 1; i < n; i++) {
            if (fabs(vector[i]) > max) {
                max = fabs(vector[i]);
                chiso = i;
            }
        }
        max = vector[chiso];
        for (int i = 0; i < n; i++) {
            vector[i] /= max;
        }
        double temp2[20];
        while (N <= sll) {
            for (int i = 0; i < n; i++) {
                temp[i] = vector[i];
            }
            for (int i = 0; i < n; i++) {
                double sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += A[i][k] * temp[k];
                }
                vector[i] = sum;
            }
            max = fabs(vector[0]);
            chiso = 0;
            for (int i = 1; i < n; i++) {
                if (fabs(vector[i]) > max) {
                    max = fabs(vector[i]);
                    chiso = i;
                }
            }
            max = vector[chiso];
            for (int i = 0; i < n; i++) {
                vector[i] /= max;
            }
            N++;
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << vector[i] << " ";
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * vector[k];
            }
            temp1[i] = sum;
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * temp1[k];
            }
            temp2[i] = sum;
        }

        double a_coef = temp1[0] * vector[1] - temp1[1] * vector[0];
        double b_coef = temp2[1] * vector[0] - temp2[0] * vector[1];
        double c_coef = temp2[0] * temp1[1] - temp2[1] * temp1[0];
        double d[2];
        giai_pt_bac_hai(a_coef, b_coef, c_coef, d);
        double M[20];
        for (int i = 0; i < n; i++) {
            M[i] = temp1[i] - d[0] * vector[i];
        }
        cout << endl << "Voi gia tri rieng la: " << d[0] << "+" << d[1] << "i";
        cout << endl << "Vector rieng la: " << endl;
        cout << "[" << endl;
        for (int i = 0; i < n; i++) {
            cout << M[i] << " + " << d[1] * vector[i] << "i" << endl;
        }
        cout << "]";
        cout << "[" << endl;
        cout << endl << "Voi gia tri rieng la: " << d[0] << "-" << d[1] << "i";
        cout << endl << "Vector rieng la: " << endl;
        for (int i = 0; i < n; i++) {
            cout << M[i] << " + " << -d[1] * vector[i] << "i" << endl;
        }
        cout << endl << "]";
    }
    int TH;
    if (TH1) TH = 1;
    if (TH2) TH = 2;
    if (TH3) TH = 3;
    return TH;
}

int chuanhoa(double a[], int n) {
    int maxIndex = 0;
    double maxValue = fabs(a[0]);

    for (int i = 1; i < n; i++) {
        if (fabs(a[i]) > maxValue) {
            maxValue = fabs(a[i]);
            maxIndex = i;
        }
    }

    return maxIndex;
}

int main() {
    int n;
    double A[20][20];
    ifstream file("Gtr_va_vtr.txt");
    if (!file) {
        cout << "Khong the mo file Gtr_va_vtr.txt" << endl;
        return 1;
    }
    file >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> A[i][j];
        }
    }
    file.close();
    double E[20][20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            E[i][j] = 0;
        }
        E[i][i] = 1;
    }
    double AT_A[20][20], A_AT[20][20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[k][i] * A[k][j];
            }
            AT_A[i][j] = sum;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * A[j][k];
            }
            A_AT[i][j] = sum;
        }
    }
    double U[20][20], V[20][20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sigma[i][j] = 0;
            U[i][j] = 0;
            V[i][j] = 0;
        }
    }
    double a[20], b[20];
    int k = 0;
    while (k < n) {
        int Th = powermethod(AT_A, n, a, b, k);
        double theta[20][20], temp[20][20];
        if (Th == 1) {
            int p = chuanhoa(a, n);
            double tmp = a[p];
            for (int i = 0; i < n; i++) {
                a[i] /= tmp;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    theta[i][j] = E[i][j];
                    temp[i][j] = AT_A[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                theta[i][p] -= a[i];
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int l = 0; l < n; l++) {
                        sum += theta[i][l] * temp[l][j];
                    }
                    AT_A[i][j] = sum;
                }
            }
            for (int i = 0; i < n; i++) {
                V[i][k] = a[i];
            }
            k++;
        }
        if (Th == 2) {
            int p = chuanhoa(a, n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    theta[i][j] = E[i][j];
                    temp[i][j] = AT_A[i][j];
                }
            }
            double tmp = a[p];
            for (int i = 0; i < n; i++) {
                a[i] /= tmp;
            }
            for (int i = 0; i < n; i++) {
                theta[i][p] -= a[i];
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int l = 0; l < n; l++) {
                        sum += theta[i][l] * temp[l][j];
                    }
                    AT_A[i][j] = sum;
                }
            }
            p = chuanhoa(b, n);
            tmp = b[p];
            for (int i = 0; i < n; i++) {
                b[i] /= tmp;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    theta[i][j] = E[i][j];
                    temp[i][j] = AT_A[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                theta[i][p] -= b[i];
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int l = 0; l < n; l++) {
                        sum += theta[i][l] * temp[l][j];
                    }
                    AT_A[i][j] = sum;
                }
            }
            for (int i = 0; i < n; i++) {
                V[i][k] = a[i];
            }
            for (int i = 0; i < n; i++) {
                V[i][k + 1] = b[i];
            }
            k = k + 2;
        }
        if (Th == 3) {
            k = k + 2;
        }
    }
    k = 0;
    while (k < n) {
        int Th = powermethod(A_AT, n, a, b, k);
        double theta[20][20], temp[20][20];
        if (Th == 1) {
            int p = chuanhoa(a, n);
            double tmp = a[p];
            for (int i = 0; i < n; i++) {
                a[i] /= tmp;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    theta[i][j] = E[i][j];
                    temp[i][j] = A_AT[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                theta[i][p] -= a[i];
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int l = 0; l < n; l++) {
                        sum += theta[i][l] * temp[l][j];
                    }
                    A_AT[i][j] = sum;
                }
            }
            for (int i = 0; i < n; i++) {
                U[k][i] = a[i];
            }
            k++;
        }
        if (Th == 2) {
            int p = chuanhoa(a, n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    theta[i][j] = E[i][j];
                    temp[i][j] = A_AT[i][j];
                }
            }
            double tmp = a[p];
            for (int i = 0; i < n; i++) {
                a[i] /= tmp;
            }
            for (int i = 0; i < n; i++) {
                theta[i][p] -= a[i];
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int l = 0; l < n; l++) {
                        sum += theta[i][l] * temp[l][j];
                    }
                    A_AT[i][j] = sum;
                }
            }
            p = chuanhoa(b, n);
            tmp = b[p];
            for (int i = 0; i < n; i++) {
                b[i] /= tmp;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    theta[i][j] = E[i][j];
                    temp[i][j] = A_AT[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                theta[i][p] -= b[i];
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int l = 0; l < n; l++) {
                        sum += theta[i][l] * temp[l][j];
                    }
                    A_AT[i][j] = sum;
                }
            }
            for (int i = 0; i < n; i++) {
                U[k][i] = a[i];
            }
            for (int i = 0; i < n; i++) {
                U[k+1][i] = b[i];
            }
            k = k + 2;
        }
        if (Th == 3) {
            k = k + 2;
        }
    }
    cout << "Ma tran V:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << V[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Ma tran U:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Ma tran Sigma:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << sigma[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
