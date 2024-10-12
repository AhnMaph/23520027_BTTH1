#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <regex>
using namespace std;

struct HocSinh {
    string hoTen;
    double diemToan;
    double diemVan;
    double diemNgoaiNgu;
    double diemTrungBinh;
    string phanLoai;
};
// Kiem tra ten co hop le hay khong
bool hople(const string& name) {
    if (name.length() < 1) {
        return false;
    }
    regex namePattern("^[A-Za-z\\s]+$");
    return regex_match(name, namePattern);
}
// Ham nhap thong tin
void nhapHocSinh(HocSinh &hocsinh) {
    cout << "  - Nhap ho ten khong dau (vd: Nguyen Van A): ";
    getline(cin, hocsinh.hoTen);
    while (!hople(hocsinh.hoTen)) {
        cout << "  (!) Ten khong hop le! Vui long nhap lai: ";
        getline(cin, hocsinh.hoTen);
    }
    cout << "  - Nhap diem Toan (0-10): ";
    while (!(cin >> hocsinh.diemToan) || hocsinh.diemToan < 0 || hocsinh.diemToan > 10) {
        cout << "  - Diem khong hop le! Vui long nhap lai: ";
    }

    cout << "  - Nhap diem Van (0-10): ";
    while (!(cin >> hocsinh.diemVan) || hocsinh.diemVan < 0 || hocsinh.diemVan > 10) {
        cout << "(!) Diem khong hop le! Vui long nhap lai: ";
    }

    cout << "  - Nhap diem Ngoai ngu (0-10): ";
    while (!(cin >> hocsinh.diemNgoaiNgu) || hocsinh.diemNgoaiNgu < 0 || hocsinh.diemNgoaiNgu > 10) {
        cout << "(!) Diem khong hop le! Vui long nhap lai: ";
    }
    cin.ignore();
    hocsinh.diemTrungBinh = (2 * hocsinh.diemToan + hocsinh.diemVan + hocsinh.diemNgoaiNgu) / 4.0;
// xep hang diem theo diem trung binh
    if (hocsinh.diemTrungBinh >= 9) {
        hocsinh.phanLoai = "Xuat sac";
    } else if (hocsinh.diemTrungBinh >= 8) {
        hocsinh.phanLoai = "Gioi";
    } else if (hocsinh.diemTrungBinh >= 6.5) {
        hocsinh.phanLoai = "Kha";
    } else if (hocsinh.diemTrungBinh >= 5) {
        hocsinh.phanLoai = "Trung binh";
    } else {
        hocsinh.phanLoai = "Yeu";
    }
}
// ham lowercase cho tu khoa va ten hoc sinh
string toLower(const string &str) {
    string lowerStr;
    for (char c : str) {
        lowerStr += tolower(c);
    }
    return lowerStr;
}
// ham tim ten theo tu khoa
void timTen(const vector<HocSinh> &hocsinhList, const string &tuKhoa) {
    cout << "\nKet qua tim kiem cho tu khoa '" << tuKhoa << "':\n";

    string lowerTuKhoa = toLower(tuKhoa); // Chuyen doi tu khoa thanh chu thường
    for (const auto &hocsinh : hocsinhList) {
        if (toLower(hocsinh.hoTen).find(lowerTuKhoa) != string::npos) { // Tim kiem khong phan biet hoa thuong
            cout << "Ho ten: " << hocsinh.hoTen
                 << ", Diem trung binh: " << fixed << setprecision(2) << hocsinh.diemTrungBinh
                 << ", Phan loai: " << hocsinh.phanLoai << endl;
        }
    }
}
// Tim diem trung binh cao nhat
void timTBcao(const vector<HocSinh> &hocsinhList) {
    if (hocsinhList.empty()) return;

    const HocSinh *hocsinhCaoNhat = &hocsinhList[0];
    for (const auto &hocsinh : hocsinhList) {
        if (hocsinh.diemTrungBinh > hocsinhCaoNhat->diemTrungBinh) {
            hocsinhCaoNhat = &hocsinh;
        }
    }
    cout << "\n\nHoc sinh co diem trung binh cao nhat:\n";
    cout << "Ho ten: " << hocsinhCaoNhat->hoTen
         << ", Diem trung binh: " << fixed << setprecision(2) << hocsinhCaoNhat->diemTrungBinh
         << ", Phan loai: " << hocsinhCaoNhat->phanLoai <<"\n";
}
// Tim diem trung binh thap nhat
void timTBthap(const vector<HocSinh> &hocsinhList) {
    if (hocsinhList.empty()) return;

    double diemThapNhat = hocsinhList[0].diemToan;
    for (const auto &hocsinh : hocsinhList) {
        if (hocsinh.diemToan < diemThapNhat) {
            diemThapNhat = hocsinh.diemToan;
        }
    }
// Ham in ra nhung hoc sinh co diem toan thap nhat
    cout << "\n\nDanh sach hoc sinh co diem Toan thap nhat (Diem Toan = " << diemThapNhat << "):\n";
    int i = 1;
    for (const auto &hocsinh : hocsinhList) {
        if (hocsinh.diemToan == diemThapNhat) {
            cout <<"\n  "<<i<<"."<< " Ho ten: " << hocsinh.hoTen
             << "\n     Diem trung binh: " << fixed << setprecision(2) << hocsinh.diemTrungBinh
             << "\n     Phan loai: " << hocsinh.phanLoai <<"\n";
             i++;
        }
    }
    cout<<"\n___________________________________________________________________";
}

int main() {
    int n; // ham nhap
    while(1){
        cout << "Nhap so luong hoc sinh: ";
        cin >> n;
        if(n<=0) cout<<"So luong hoc sinh phai lon hon 0\n";
        else break;
    }
    cin.ignore();
cout<<"\n___________________________________________________________________\n";

    vector<HocSinh> hocsinhList(n);
    for (int i = 0; i < n; i++) {
         cout << "\nThong tin hoc sinh "<< (i + 1)<<"\n";
        nhapHocSinh(hocsinhList[i]);
    }
cout<<"\n___________________________________________________________________";

    cout << "\n\nDanh sach hoc sinh:\n";
    int i = 1;
    for (const auto &hocsinh : hocsinhList) {
        cout <<"\n  "<<i<<"."<< " Ho ten: " << hocsinh.hoTen
             << "\n     Diem trung binh: " << fixed << setprecision(2) << hocsinh.diemTrungBinh
             << "\n     Phan loai: " << hocsinh.phanLoai <<"\n";
             i++;
    }
cout<<"\n___________________________________________________________________";
    timTBcao(hocsinhList);
cout<<"\n___________________________________________________________________";
    string tuKhoa;
    cout << "\n\nNhap tu khoa tim kiem: ";
    getline(cin, tuKhoa);
    timTen(hocsinhList, tuKhoa);
cout<<"\n___________________________________________________________________";
    timTBthap(hocsinhList);

    return 0;
}
