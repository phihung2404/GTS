#include <iostream>
#include <fstream>
#include <cmath>

#define sll 200
using namespace std;
double epsilon = 1e-9;

void giai_pt_bac_hai(double a, double b, double c, double d[2]) {
    double delta = b * b - 4 * a * c;
    d[0] = -b / 2 / a;
    d[1] = pow(-delta, 0.5) / 2 / a;
}

void powermethod(double A[20][20], int n) {
    int N = 0;
    double vector[20], temp[20], temp1[20];
    int chiso = 0;
    double max = 0;
    double saiso;
    bool TH1 = true;
    bool TH2 = false;
    bool TH3 = false;

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
        cout << "TH1: Tri rieng thuc troi don";
        cout << endl << "Gia tri rieng la: " << max;
        cout << endl << "Vector rieng la: " << endl;
        for (int i = 0; i < n; i++) {
            cout << vector[i] << endl;
        }
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
        cout << endl << "TH2: Hai tri rieng doi nhau" << endl;
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
            cout << (vector[i] + lambda * temp1[i]) / chia << endl;
        }
        cout << endl << "Gia tri rieng la: " << -lambda;
        cout << endl << "Vector rieng la: " << endl;
        for (int i = 0; i < n; i++) {
            cout << (vector[i] - lambda * temp1[i]) / chia << endl;
        }
    }
    if (TH3) {
        cout << "TH3: Tri rieng phuc lien hop" << endl;
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
        while (N <= 50) {
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

        double a = temp1[0] * vector[1] - temp1[1] * vector[0];
        double b = temp2[1] * vector[0] - temp2[0] * vector[1];
        double c = temp2[0] * temp1[1] - temp2[1] * temp1[0];
        double d[2];
        giai_pt_bac_hai(a, b, c, d);
        double M[20];
        for (int i = 0; i < n; i++) {
            M[i] = temp1[i] - d[0] * vector[i];
        }
        cout << endl << "Voi gia tri rieng la: " << d[0] << " + " << d[1] << "i";
        cout << endl << "Vector rieng la: " << endl;
        for (int i = 0; i < n; i++) {
            cout << M[i] << " + " << -d[1] * vector[i] << "i" << endl;
        }
        cout << endl << "Voi gia tri rieng la: " << d[0] << " - " << d[1] << "i";
        cout << endl << "Vector rieng la: " << endl;
        for (int i = 0; i < n; i++) {
            cout << M[i] << " + " << d[1] * vector[i] << "i" << endl;
        }
    }
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
    powermethod(A, n);
    return 0;
}
