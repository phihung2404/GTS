#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
#define eta 1e-7 //co the thay doi gia tri eta <=epsilon de phu hop
double epsilon = 1e-6;

int sign, n;
double R1,R2; // [R1,R2] la mien nghiem
double cuctri[20];
int so_cuctri = 1;

double f(double x, double a[]) {
    double sum = 0;
    for (int i = 0; i < n + 1; i++) {
        sum += a[i] * pow(x, i);
    }
    return sum;
}

double f1(double x, double a[]) {
    double sum = 0;
    for (int i = 1; i < n + 1; i++) {
        sum += a[i] * i * pow(x, i - 1);
    }
    return sum;
}

double cantren(double a[]) {
    double b[n + 1];
    if (a[n] < 0) {
        for (int i = 0; i < n + 1; i++) {
            b[i] = -a[i];
        }
    }
    else {
        for (int i = 0; i < n + 1; i++) {
            b[i] = a[i];
        }
    }
    double max = fabs(b[0]);
    int j = -1;
    for (int i = 0; i < n; i++) {
        if (b[i] < 0) {
            j = i;
            if (fabs(b[i]) > max) {
                max = fabs(b[i]);
            }
        }
    }
    if (j == -1) return 0;
    else {
        int k = n - j;
        return 1 + pow(max / fabs(a[n]), 1.0 / k);
    }
}
double canduoi(double a[]) {
    double c[n+1];
    for (int i = 0; i < n+1; i++) {
        c[i] = a[i]*pow(-1, i);
    }
    double b[n + 1];
    if (c[n] < 0) {
        for (int i = 0; i < n + 1; i++) {
            b[i] = -c[i];
        }
    }
    else {
        for (int i = 0; i < n + 1; i++) {
            b[i] = c[i];
        }
    }
    double max = fabs(b[0]);
    int j = -1;
    for (int i = 0; i < n; i++) {
        if (b[i] < 0) {
            j = i;
            if (fabs(b[i]) > max) {
                max = fabs(b[i]);
            }
        }
    }
    if (j == -1) return 0;
    else {
        int k = n - j;
        return -(1 + pow(max / fabs(a[n]), 1.0 / k));
    }
}

double fixeta(double x0, double a[]) {
    double etaa = eta;
    while (((f1(x0, a) * f1(x0 + sign * etaa * f1(x0, a), a)) >= 0) && (etaa < 1))
        etaa *= 2;
    while ((f1(x0, a) * f1(x0 + sign * etaa * f1(x0, a), a)) <= 0)
        etaa /= 2;
    return etaa;
}

double gda(double x0, double a[]) {
    if (f1(x0, a) == 0)
        return x0;
    if (f1(x0, a) < 0)
        sign = -1;
    if (f1(x0, a) > 0)
        sign = 1;
    double x = x0 + sign * eta * f1(x0, a);
    while (fabs(f1(x, a)) > epsilon) {
        x = x0 + sign * eta * f1(x0, a);
        x0 = x;
        if (x0 > R2)
            return R2;
    }
    cuctri[so_cuctri] = x;
    so_cuctri++;
    return x;
}

void tim_cuc_tri(double a[]) {
    double i= R1;
    cuctri[0] = R1;
    do {
        i = gda(i, a);
        do {
            i += epsilon;
            if (i >= R2)
                break;
        } while ((f1(i, a) * f1(i + epsilon, a) > 0) && (fabs(f1(i, a)) > fabs(f1(i + epsilon, a))));
    } while (i <= R2);
    cuctri[so_cuctri] = R2;
}

int kiemtra(double a, double b, double c[]) {
    if (fabs(f(a, c)) < epsilon || fabs(f(b, c)) < epsilon) {
        cout << "Nghiem nam o dau mut";
        return 1;
    }
    if (a >= b) {
        cout << "Dau vao khong hop le do a>=b" << endl;
        return 0;
    }
    if (f(a, c) * f(b, c) > 0) {
        cout << "Dau vao khong hop le do f(a)*f(b)>0";
        return 0;
    }
    return 1;
}

double chiadoi(double a, double b, double d[]) {
    double c;
    int dem = 0;
    if (fabs(f(a, d)) < epsilon) {
        cout << endl
             << "Nghiem gan dung nam o dau mut la : " << a;
        return a;
    }
    if (fabs(f(b, d)) < epsilon) {
        cout << endl
             << "Nghiem gan dung nam o dau mut la : " << b;
        return b;
    }
    while (fabs(a - b) >= epsilon) {
        c = (a + b) / 2;
        double fc = f(c, d);
        if (fc == 0)
            return c;
        if (fc * f(a, d) < 0)
            b = c;
        else
            a = c;
        dem++;
    }
    cout << endl
         << "So lan lap : " << dem;
    cout << endl
         << "Nghiem gan dung la : " << c;
    return c;
}

void giai_ptdt(double a[], int n, double x[]) {
    so_cuctri = 1;
    for (int i = 0; i < n + 1; i++) {
        cuctri[i] = 0;
    }
    tim_cuc_tri(a);
    cout << "Khoang nghiem cua da thuc la: "
         << "[ " << R1 << " , " << R2 << " ]" << endl;
    cout << "Cac cuc tri cua ham so la: " << endl;
    for (int i = 1; i < so_cuctri; i++) {
        cout << "(" << cuctri[i] << ", " << f(cuctri[i], a) << ")" << endl;
    }
    int songhiem = 0;
    for (int i = 0; i < so_cuctri; i++) {
        if (kiemtra(cuctri[i], cuctri[i + 1], a) == 1) {
            x[songhiem] = chiadoi(cuctri[i], cuctri[i + 1], a);
            songhiem++;
        }
        cout << endl;
    }
    cout << endl
         << "Nghiem cua phuong trinh da thuc la: " << endl;
    for (int i = 0; i < songhiem; i++) {
        cout << x[i] << ", ";
    }
    cout << endl;
    for (int i = 0; i < so_cuctri + 1; i++) {
        cout << cuctri[i] << ", ";
    }
}

int main() {
    cout << "Nhap vao bac da thuc: "; // n la bac cua da thuc
    cin >> n;
    double a[n + 1];
    cout << "Nhap va he so da thuc" << endl;
    for (int i = n; i >= 0; i--) {
        cout << "a[" <<i << "]: ";
        cin >> a[i];
    }
    R1=canduoi(a);
    R2=cantren(a);
    cout << "Khoang nghiem cua da thuc la: "
         << "[ " << R1 << " , " << R2 << " ]" << endl;
    for (int i = 0; i < n + 1; i++) {
        cuctri[i] = 0;
    }
    double x[n];
    giai_ptdt(a, n, x);

    return 0;
}
