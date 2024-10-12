#include <iostream>
#include <algorithm>
using namespace std;
int gcd(int a, int b)
{
    while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
}
// Ham rut gon phan so
void rutGonPhanSo(int &tu, int &mau) {
    int ucln = gcd(tu, mau);
    tu /= ucln;
    mau /= ucln;
    // Dam bao mau so duong
    if (mau < 0) {
        tu = -tu;
        mau = -mau;
    }
}

// Ham cong hai phan so
void tongPhanSo(int tu1, int mau1, int tu2, int mau2, int &tuKQ, int &mauKQ) {
    tuKQ = tu1 * mau2 + tu2 * mau1;
    mauKQ = mau1 * mau2;
    rutGonPhanSo(tuKQ, mauKQ);
}

// Ham tru hai phan so
void hieuPhanSo(int tu1, int mau1, int tu2, int mau2, int &tuKQ, int &mauKQ) {
    tuKQ = tu1 * mau2 - tu2 * mau1;
    mauKQ = mau1 * mau2;
    rutGonPhanSo(tuKQ, mauKQ);
}

// Ham nhan hai phan so
void tichPhanSo(int tu1, int mau1, int tu2, int mau2, int &tuKQ, int &mauKQ) {
    tuKQ = tu1 * tu2;
    mauKQ = mau1 * mau2;
    rutGonPhanSo(tuKQ, mauKQ);
}

// Ham chia hai phan so
void thuongPhanSo(int tu1, int mau1, int tu2, int mau2, int &tuKQ, int &mauKQ) {
    tuKQ = tu1 * mau2;
    mauKQ = mau1 * tu2;
    if (mauKQ == 0) throw invalid_argument("Loi: Khong the chia cho 0");
    rutGonPhanSo(tuKQ, mauKQ);
}

int main() {
    int tu1, mau1, tu2, mau2;
    int tuKQ, mauKQ;
    while(1)
    {
        // Nhap tu so cua phan so thu
        cout << "Nhap phan so thu nhat: ";
        cin >> tu1 >> mau1;

        // Nhap phan so thu hai
        cout << "Nhap phan so thu hai: ";
        cin >> tu2 >> mau2;

        // Mau phai khac 0
        if (mau2*mau1 == 0) {
            cout << "Loi: Mau so phai khac 0" << "\n";
        }
        else break;
    }

    // Tinh tong hai phan so
    tongPhanSo(tu1, mau1, tu2, mau2, tuKQ, mauKQ);
    cout << "Tong hai phan so la: " << tuKQ;
    if(tuKQ!=0&&tuKQ!=1) cout<< "/" << mauKQ; // xu ly khi tu = 0 hoac tu = 1
    cout << "\n";

    // Tinh hieu hai phan so
    hieuPhanSo(tu1, mau1, tu2, mau2, tuKQ, mauKQ);
    cout << "Tinh hieu hai phan so: " << tuKQ;
    if(tuKQ!=0&&tuKQ!=1) cout<< "/" << mauKQ;
    cout << "\n";
    // Tinh tich hai phan so
    tichPhanSo(tu1, mau1, tu2, mau2, tuKQ, mauKQ);
    cout << "Tinh tich hai phan so: " << tuKQ;
    if(tuKQ!=0&&tuKQ!=1) cout<< "/" << mauKQ;
    cout << "\n";
    // Thuong hai phan so
    try {
        thuongPhanSo(tu1, mau1, tu2, mau2, tuKQ, mauKQ);
        cout << "Thuong hai phan so la: " << tuKQ;
        if(tuKQ!=0&&tuKQ!=1) cout<< "/" << mauKQ << "\n";
    } catch (const exception& e) {
        cout << e.what() << "\n";
    }

    return 0;
}
