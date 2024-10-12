#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <iomanip>

using namespace std;

struct ChuyenBay {
    string ma;
    string ngay;
    string gio;
    string noiDi;
    string noiDen;
};

bool kiemTraMaTrung(const vector<ChuyenBay>& ds, const string& ma) {
    for (const auto& cb : ds) {
        if (cb.ma == ma) {
            return true;
        }
    }
    return false;
}

bool kiemTraMa(const string& ma) {
    regex pattern("^[A-Za-z0-9]{1,5}$");
    return regex_match(ma, pattern);
}

// Kiem tra nam nhuan
bool laNamNhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

// Kiem tra ngay hop le (dd/mm/yyyy)
bool ktraNgay(const string& ngay) {
    regex pattern("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
    if (!regex_match(ngay, pattern)) return false;

    // lay ngay thang nam tu string
    int day = stoi(ngay.substr(0, 2));
    int month = stoi(ngay.substr(3, 2));
    int year = stoi(ngay.substr(6, 4));

    int ngayTrongThang[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (laNamNhuan(year)) ngayTrongThang[2] = 29;

    return (day > 0 && day <= ngayTrongThang[month]);
}

bool ktraGio(const string& gio) {
    regex pattern("^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");
    return regex_match(gio, pattern);
}

bool ktraDiaChi(const string& diaDanh) {
    regex pattern("^[A-Za-z\\s]{1,20}$");
    return regex_match(diaDanh, pattern);
}

ChuyenBay nhapChuyenBay(const vector<ChuyenBay>& ds) {
    ChuyenBay cb;
    cout << "    Nhap ma chuyen bay: ";
    while (true) {
        cin >> cb.ma;
        if (!kiemTraMa(cb.ma)) {
            cout << "(!) Ma khong hop le. Nhap lai: ";
        } else if (kiemTraMaTrung(ds, cb.ma)) {
            cout << "(!) Ma bi trung. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "    Nhap ngay bay (dd/mm/yyyy): ";
    while (true) {
        cin >> cb.ngay;
        if (ktraNgay(cb.ngay)) break;
        else cout << "(!) Ngay khong hop le. Nhap lai: ";
    }

    cout << "    Nhap gio bay (GG:PP): ";
    while (true) {
        cin >> cb.gio;
        if (ktraGio(cb.gio)) break;
        else cout << "(!) Gio khong hop le. Nhap lai: ";
    }

    cout << "    Nhap noi chuyen bay khoi hanh: ";
    cin.ignore();
    while (true) {
        getline(cin, cb.noiDi);
        if (ktraDiaChi(cb.noiDi)) break;
        else cout << "(!) Noi chuyen bay khoi hanh khong hop le. Nhap lai: ";
    }

    cout << "    Nhap noi chuyen bay ket thuc: ";
    while (true) {
        getline(cin, cb.noiDen);
        if (ktraDiaChi(cb.noiDen)) break;
        else cout << "(!) Noi chuyen bay ket thuc khong hop le. Nhap lai: ";
    }

    cout << string(75, '-') << "\n";  // Dòng phân cách giữa các chuyến bay
    return cb;
}

void xuatChuyenBay(const ChuyenBay& cb) {
    cout << left << setw(10) << cb.ma
         << setw(15) << cb.ngay
         << setw(10) << cb.gio
         << setw(20) << cb.noiDi
         << setw(20) << cb.noiDen << "\n";
}

bool soSanhChuyenBay(const ChuyenBay& a, const ChuyenBay& b) {
    if (a.ngay == b.ngay) {
        return a.gio < b.gio;
    }
    return a.ngay < b.ngay;
}

void timKiem(const vector<ChuyenBay>& ds, const string& key) {
    bool timThay = false;
    vector<ChuyenBay> res;
    for (const auto& cb : ds) {
        if (cb.ma == key || cb.noiDi == key || cb.noiDen == key) {
            res.push_back(cb);
            timThay = true;
        }
    }
    if (!timThay) cout << "(!) Khong tim thay chuyen bay nao voi tu khoa \"" << key << "\"" << "\n";
    else {
        int i = 1;
        cout << "\n                         Tim thay cac chuyen bay:\n";
        cout << string(75, '-') << "\n";
        cout << left << setw(10) << "Ma"
             << setw(15) << "Ngay"
             << setw(10) << "Gio"
             << setw(20) << "Noi Di"
             << setw(20) << "Noi Den" << "\n";
        cout << string(75, '-') << "\n";
        for (const auto& cb : res) {
            xuatChuyenBay(cb);
            i++;
        }
    }
}

void lietKe(const vector<ChuyenBay>& ds, const string& noi, const string& ngay) {
    bool timThay = false;
    vector<ChuyenBay> res;
    for (const auto& cb : ds) {
        if (cb.noiDi == noi && cb.ngay == ngay) {
            res.push_back(cb);
            timThay = true;
        }
    }
    if (!timThay) cout << "(!) Khong co chuyen bay nao khoi hanh tu " << noi << " vao ngay " << ngay << "\n";
    else {
        int i = 1;
        cout << "\n                         Tim thay cac chuyen bay:\n";
        cout << string(75, '-') << "\n";
        cout << left << setw(10) << "Ma"
             << setw(15) << "Ngay"
             << setw(10) << "Gio"
             << setw(20) << "Noi Di"
             << setw(20) << "Noi Den" << "\n";
        cout << string(75, '-') << "\n";
        for (const auto& cb : res) {
            xuatChuyenBay(cb);
            i++;
        }
        cout << string(75, '-') << "\n";
    }
}

int demChuyenBay(const vector<ChuyenBay>& ds, const string& noiDi, const string& noiDen) {
    int dem = 0;
    for (const auto& cb : ds) {
        if (cb.noiDi == noiDi && cb.noiDen == noiDen) {
            dem++;
        }
    }
    return dem;
}

int main() {
    vector<ChuyenBay> ds;
    char luaChon;
    int n;
        do {
        cout << "==== QUAN LY THONG TIN BAY ====\n";
        cout << "1. Nhap so chuyen bay\n";
        cout << "2. Xuat danh sach chuyen bay\n";
        cout << "3. Tim kiem chuyen bay theo ma bay/noi bay/noi dap\n";
        cout << "4. Tim kiem chuyen bay theo noi bay - thoi gian bay\n";
        cout << "5. Xuat so luong chuyen bay co noi bay - noi dap\n";
        cout << "6. Thoat\n";
        cout << "Lua chon: ";
        cin >> luaChon;

        cout << string(35, '-') <<"start"<< string(35, '-') << "\n";

        switch (luaChon) {
        case '1': {
            cout << "Nhap so luong chuyen bay: ";
            cin >> n;
            cout << string(75, '-') << "\n";
            for (int i = 0; i < n; ++i) {
                cout << "(+) Nhap thong tin cho chuyen bay " << i + 1 << ":" << "\n";
                ds.push_back(nhapChuyenBay(ds));
            }
            sort(ds.begin(), ds.end(), soSanhChuyenBay);
            cout<<"(+) Nhap thanh cong chuyen bay\n";
            cout << string(36, '-') <<"end"<< string(36, '-') << "\n";

            break;
        }
        case '2': {
            if(ds.size()==0)
            {
                cout << "(!) Vui long nhap chuyen bay truoc.\n";
                cout << string(36, '-') <<"end"<< string(36, '-') << "\n";
                break;
            }
    cout << "\n                    Danh sach chuyen bay da sap xep:\n";
    cout << string(75, '-') << "\n";
    cout << left << setw(10) << "Ma"
         << setw(15) << "Ngay"
         << setw(10) << "Gio"
         << setw(20) << "Noi Di"
         << setw(20) << "Noi Den" << "\n";
         cout << string(75, '-') << "\n";
    for (const auto& cb : ds) {
        xuatChuyenBay(cb);
    }
    cout << string(75, '-') << "\n\n";
    cout << string(36, '-') <<"end"<< string(36, '-') << "\n";
        break;
        }
    case '3': {
    string key;
    cout << "(+) Nhap ma bay hoac dia diem khoi hanh hoac ket thuc de tim kiem: ";
    cin.ignore();
    getline(cin, key);
    timKiem(ds, key);
    cout << string(36, '-') <<"end"<< string(36, '-') << "\n";
        break;
    }
    case '4': {
    string diadiem, ngay;
    cout << "\n(+) Nhap dia diem chuyen bay khoi hanh: ";
    cin.ignore();
    getline(cin, diadiem);
    cout << "    Nhap ngay chuyen bay khoi hanh (dd/mm/yyyy): ";
    getline(cin, ngay);
    lietKe(ds, diadiem, ngay);
    cout <<"\n"<<string(36, '-') <<"end"<< string(36, '-') << "\n";
    break;
    }
    case '5': {
    string noiDi, noiDen;
    cout<<"\n(+) Cung cap noi khoi hanh va ket thuc cua chuyen bay";
    cout << "\n    Nhap dia diem chuyen bay khoi hanh: ";
    cin.ignore();
    getline(cin, noiDi);
    cout << "    Nhap dia diem chuyen bay ket thuc: ";
    getline(cin, noiDen);
    int dem = demChuyenBay(ds, noiDi, noiDen);
    cout << "->  So luong chuyen bay tu " << noiDi << " den " << noiDen << " la : " << dem << "\n\n";
    cout << string(36, '-') <<"end"<< string(36, '-') << "\n";
    break;
    }
    case '6': {
                cout << "(!) Chuong trinh ket thuc.\n";
                cout << string(36, '-') <<"end"<< string(36, '-') << "\n";
                break;
            }
    default:
            cout << "(!) Lua chon khong hop le. Vui long nhap lai.\n";
            cout << string(36, '-') <<"end"<< string(36, '-') << "\n";
        }
    } while (luaChon != '6');

    return 0;
}
