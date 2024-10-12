#include <iostream>
#include <queue>
using namespace std;
int ans=0,a[10001] ,b[10001] ,prefix[10001] ,m,n;
queue<int> start;
int main() {
    // Nhap so luong phan tu cua mang A va B
    cout<<"Nhap vao so luong phan tu A va B: ";
    cin >> n >> m;
    cout<<"Nhap vao phan tu A: ";
    // Nhap cac phan tu cua mang A
    for (int i = 1; i <= n; i++) cin >> a[i];
    cout<<"Nhap vao phan tu B: ";
    // Nhap cac phan tu cua mang B
    for (int i = 1; i <= m; i++) cin >> b[i];

    int j = 0;

    // Xay dung mang tien to (prefix) cho mang A
    for (int i = 2; i <= n; i++) {
        while (j > 0 && a[i] != a[j + 1]) {
            j = prefix[j];
        }
        if (a[i] == a[j + 1]) {
            j++;
        }
        prefix[i] = j;
    }

    j = 0;

    // Thuc hien thuat toan KMP de tim A trong B
    for (int i = 1; i <= m; i++) {
        while (j > 0 && b[i] != a[j + 1]) {
            j = prefix[j];
        }
        if (b[i] == a[j + 1]) {
            j++;
        }
        if (j == n) {
            start.push(i - n);  // Luu vi tri bat dau cua A trong B
            ans++;  // Tang bien dem so lan xuat hien
            j = prefix[j];
        }
    }

    // In ra ket qua
    cout << "Xau con xuat hien " << ans<< " lan";
    if(!start.empty()) cout<< " o vi tri: ";
    while (!start.empty()) {
        int s = start.front();
        cout << s << " ";
        start.pop();
    }
    cout << "\n";

    return 0;
}
