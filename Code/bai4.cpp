#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

double Sin(double x) {
    double term = x; // So hang dau tien cua x
    double sum = x;  // Gia tri ban dau cua sin(x)
    int n = 1;

    while (fabs(term) > 0.00001) { // so sanh voi gia tri tuyet doi cua term
        term *= -x * x / ((2 * n) * (2 * n + 1)); // Tinh so hang tiep theo
        sum += term;
        n++;
    }
    return sum;
}

int main() {
    double x;
    cout << "Nhap gia tri cua x (radian): ";
    cin >> x;
    double result = Sin(x);
    cout << "Gia tri cua sin(" << x << ") cua chuong trinh: "<< result<<"\n";
    return 0;
}


/*
Code de test:

    double test[7] = {0, -M_PI / 2, M_PI / 2, 3 * M_PI / 2, 0.1, 5 * M_PI / 6, 10};
    string true_val[7] = {"0","-pi/2","pi/2","3*pi/2","0.1","5*pi/6","10"};
    cout<<"=============================================================\n";
    for (int i=0;i<7 ;i++)
    {
        double result = Sin(test[i]);
        cout<<"Test case "<<i+1<<":\n";
        cout << "Gia tri cua sin(" << true_val[i] << ") cua chuong trinh: "<< result<<"\n";
        cout<<"Gia tri sin(x) cua C++: "<<sin(test[i])<<"\n";
        cout<<"=============================================================\n";
    }
*/
