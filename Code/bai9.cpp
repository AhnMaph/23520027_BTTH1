#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

struct SoTietKiem {
    string maSo;
    string loaiTietKiem;
    string hoTen;
    string cmnd;
    string ngayMoSo;
    double soTienGui;
    int kyHan; // Ky han gui tiet kiem (thang)
};

// Ham chuyen doi ngay dang chuoi (dd/mm/yyyy) sang std::tm
tm stringToDate(const string& date) {
    tm t = {};
    t.tm_mday = stoi(date.substr(0, 2));
    t.tm_mon = stoi(date.substr(3, 2)) - 1;  // Thang trong tm tinh tu 0
    t.tm_year = stoi(date.substr(6, 4)) - 1900;  // Nam trong tm tinh tu 1900
    return t;
}

// Ham tinh so ngay giua hai ngay
int tinhSoNgay(const string& ngayMoSo) {
    tm moSo = stringToDate(ngayMoSo);
    time_t t1 = mktime(&moSo);  // Chuyen ve time_t

    // Lay ngay hien tai
    time_t now = time(0);
    tm* today = localtime(&now);
    time_t t2 = mktime(today);

    // Tinh khoang cach giua hai ngay (don vi giay) roi doi ra ngay
    int soNgay = difftime(t2, t1) / (60 * 60 * 24);
    return soNgay;
}

bool ktraMaSo(const string& maSo) {
    regex pattern("^[A-Za-z0-9]{1,5}$");
    return regex_match(maSo, pattern);
}

bool ktraloaiTietKiem(const string& loai) {
    if(loai=="ngan han") return true; // <=6
    if(loai == "dai han") return true;// >=6
    if(loai == "khong ky han") return true;
    return false;
}

bool ktraHoTen(const string& hoTen) {
    regex pattern("^[A-Za-z\\s]{1,30}$");
    return regex_match(hoTen, pattern);
}

bool ktraCMND(const string& cmnd) {
    regex pattern("^\\d{9}|\\d{12}$");
    return regex_match(cmnd, pattern);
}

// Kiem tra nam nhuan
bool laNamNhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

// Kiem tra ngay hop le (dd/mm/yyyy)
bool ktraNgay(const string& ngay) {
    regex pattern("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
    if (!regex_match(ngay, pattern)) return false;
    if(tinhSoNgay(ngay)<0) return false;
    int day = stoi(ngay.substr(0, 2));
    int month = stoi(ngay.substr(3, 2));
    int year = stoi(ngay.substr(6, 4));

    int ngayTrongThang[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (laNamNhuan(year)) ngayTrongThang[2] = 29;

    return (day > 0 && day <= ngayTrongThang[month]);
}
bool ktratrungMaSo(const vector<SoTietKiem>& ds, const string& maSo) {
    for (const auto& stk : ds) {
        if (stk.maSo == maSo) {
            return true;
        }
    }
    return false;
}
bool ktraKH(const int kyHan,const string& loai)
{
    if(loai=="ngan han" && kyHan<=6) return true; // <=6
    if(loai =="dai han" && kyHan>=6) return true;// >=6
    if(loai == "khong ky han") return true;
    return false;
}

SoTietKiem nhapSoTietKiem(const vector<SoTietKiem>& ds) {
    SoTietKiem stk;
    cout << " \t    Nhap ma so: ";
    while (true) {
        cin >> stk.maSo;
        if (!ktraMaSo(stk.maSo)||ktratrungMaSo(ds,stk.maSo)) {
            cout << "\t(!) Ma so bi trung hoac khong hop le. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "\t    Nhap loai tiet kiem (ngan han, dai han, khong ky han): ";
    while (true) {
        cin.ignore();
        getline(cin, stk.loaiTietKiem);
        if (!ktraloaiTietKiem(stk.loaiTietKiem)) {
            cout << "\t(!) Loai tiet kiem khong hop le. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "\t    Nhap ho ten khach hang: ";
    while (true) {
        getline(cin, stk.hoTen);
        if (!ktraHoTen(stk.hoTen)) {
            cout << "\t(!) Ho ten khong hop le. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "\t    Nhap CMND (9 hoac 12 chu so): ";
    while (true) {
        cin >> stk.cmnd;
        if (!ktraCMND(stk.cmnd)) {
            cout << "\t(!) CMND khong hop le. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "\t    Nhap ngay mo so (dd/mm/yyyy): ";
    while (true) {
        cin >> stk.ngayMoSo;
        if (ktraNgay(stk.ngayMoSo)) break;
        else cout << "\t(!) Ngay khong hop le. Nhap lai: ";
    }

    cout << "\t    Nhap so tien gui VND(so duong): ";
    while (true) {
        cin >> stk.soTienGui;
        if (stk.soTienGui > 0) break;
        else cout << "\t(!) So tien gui phai la so duong. Nhap lai: ";
    }

    cout << "\t    Nhap ky han (thang): ";
    while (true) {
        int kh;
        cin >> kh;
        if (kh <= 0)
        {
            cout << "\t(!) Ky han phai la so duong. Nhap lai: ";
            continue;
        }
        if(ktraKH(kh, stk.loaiTietKiem))
            {
                stk.kyHan = kh;
                break;
            }
        else cout << "\t(!) Day la loai so tiet kiem "<<stk.loaiTietKiem<<". Vui long nhap lai: ";

    }

    return stk;
}
// Ham so sanh đe sap xep danh sach so tiet kiem
bool sapXepSTK(const SoTietKiem& a, const SoTietKiem& b) {
    // So sanh theo so tien gui giam dan
    if (a.soTienGui != b.soTienGui) {
        return a.soTienGui > b.soTienGui;  // So tien gui giam dan
    }
    tm ngayMoSoA = stringToDate(a.ngayMoSo);
    tm ngayMoSoB = stringToDate(b.ngayMoSo);

    return difftime(mktime(&ngayMoSoA), mktime(&ngayMoSoB)) < 0;
}

void tinhlaiSTK(SoTietKiem& stk, double laiSuat) {
    int soNgay = tinhSoNgay(stk.ngayMoSo);  // Tinh so ngay tu khi mo so đen hien tai
    double lai = stk.soTienGui * (laiSuat / 100) * (soNgay / 365.0);  // Cong thuc tinh lai theo nam
    stk.soTienGui += lai;
    cout << "\t(!) Lai suat tinh theo thoi gian gui la: " << lai << " VND\n";
}

void xuatSoTietKiem(const SoTietKiem& stk) {
    cout << left << setw(10) << stk.maSo
         << setw(15) << stk.loaiTietKiem
         << setw(20) << stk.hoTen
         << setw(15) << stk.cmnd
         << setw(15) << stk.ngayMoSo
         << setw(15) << stk.soTienGui << "\n";
}

void capNhatLaiSuat(vector<SoTietKiem>& ds, double laiSuatNganHan, double laiSuatDaiHan) {
    for (auto& stk : ds) {
        int soNgay = tinhSoNgay(stk.ngayMoSo);
        double lai = 0;
        if (stk.kyHan <= 6) {  // Ngan han
            lai = stk.soTienGui * (laiSuatNganHan / 100) * (soNgay / 365.0);
        } else {  // Dai han
            lai = stk.soTienGui * (laiSuatDaiHan / 100) * (soNgay / 365.0);
        }
        stk.soTienGui += lai;
        cout << "\t(!) Tinh lai cho so " << stk.maSo << ": " << lai << " VND\n";
    }
}


void rutTien(SoTietKiem& stk, double laiSuat, double laiSuatRutTruocHan) {
    double soTienRut;
    cout << "\t(+) Nhap so tien can rut: ";
    cin >> soTienRut;

    if (soTienRut <= 0) {
        cout << "\t(!) So tien rut phai lon hon 0.\n";
        return;
    }

    // Kiem tra thoi gian gui
    int soNgay = tinhSoNgay(stk.ngayMoSo);
    bool rutTruocHan = soNgay < (stk.kyHan * 30); // Neu so ngay đa gui < ky han

    if (soTienRut > stk.soTienGui) {
        cout << "\t(!) So tien rut lon hon so tien trong so tiet kiem.\n";
    } else {
        // Tính lãi suất
        double lai;
        if(stk.loaiTietKiem != "khong ky han")
        {
            if (rutTruocHan) {
            lai = stk.soTienGui * (laiSuatRutTruocHan / 100) * (soNgay / 365.0);
            cout << "\t(!) Ban rut tien truoc han, lai suat ap dung la: " << laiSuatRutTruocHan << "%/nam\n";
            } else {
                lai = stk.soTienGui * (laiSuat / 100) * (soNgay / 365.0);
                cout << "\t(!) Ban rut tien dung han, lai suat ap dung la: " << laiSuat << "%/nam\n";
            }
        }

        stk.soTienGui -= soTienRut;  // Rut tien
        cout << "\t(!) Ban da rut thanh cong: " << soTienRut << " VND\n";
        cout << "    Lai thang duoc tinh la: " << lai << " VND\n";
        cout << "    So du con lai trong so tiet kiem: " << stk.soTienGui << " VND\n";
    }
}
// Ham tim kiem so tiet kiem theo CMND hoac mâ so
void timSTK(const vector<SoTietKiem>& ds) {
    string keyword;
    cout << "\t(+) Nhap CMND hoac ma so de tim kiem: ";
    cin.ignore();
    getline(cin, keyword);
    vector<SoTietKiem> res;
    bool timThay = false;
    for (const auto& stk : ds) {
        if (stk.cmnd == keyword || stk.maSo == keyword) {
            res.push_back(stk);
            timThay = true;
        }
    }

    if (!timThay) {
        cout << "\t(!) Khong tim thay so tiet kiem voi CMND hoac ma so nay.\n";
    }
    else
    {
        cout<<"\n";
        cout<<"\t\t\t        Cac So Tiet Kiem Tim Thay\n";
            cout << string(90, '-') << "\n";
            cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND)" << "\n";
            cout << string(90, '-') << "\n";

            for (const auto& stk : res) {
                xuatSoTietKiem(stk);
            }
            cout << string(90, '-') << "\n";
    }
}

// Ham liet ke so tiet kiem theo khoang thoi gian
void timtheoDate(const vector<SoTietKiem>& ds) {
    string ngayBatDau, ngayKetThuc;
    while(1){
        cout << "\t(+) Nhap ngay bat dau (dd/mm/yyyy): ";
        cin >> ngayBatDau;
        cout << "\t    Nhap ngay ket thuc (dd/mm/yyyy): ";
        cin >> ngayKetThuc;

        if (!ktraNgay(ngayBatDau) || !ktraNgay(ngayKetThuc)) {
            cout << "\t(!) Ngay nhap khong hop le!\n";
            continue;
        }
        break;
    }
    tm dateStart = stringToDate(ngayBatDau);
    tm dateEnd = stringToDate(ngayKetThuc);
    time_t tStart = mktime(&dateStart);
    time_t tEnd = mktime(&dateEnd);

    bool coSoTietKiem = false;
    vector<SoTietKiem> res;

    for (const auto& stk : ds) {
        tm ngayMoSo = stringToDate(stk.ngayMoSo);
        time_t tNgayMoSo = mktime(&ngayMoSo);
        if (difftime(tNgayMoSo, tStart) >= 0 && difftime(tEnd, tNgayMoSo) >= 0) {
            res.push_back(stk);
            coSoTietKiem = true;
        }
    }

    if (!coSoTietKiem) {
        cout << "\t(!) Khong co so tiet kiem nao trong khoang thoi gian nay.\n";
    }
    else
    {
        cout<<"\n";
        cout<<"\t\t\t        Cac So Tiet Kiem Tim Thay\n";
            cout << string(90, '-') << "\n";
            cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND) " << "\n";
            cout << string(90, '-') << "\n";

            for (const auto& stk : res) {
                xuatSoTietKiem(stk);
            }
            cout << string(90, '-') << "\n";
    }
}

int main() {
    vector<SoTietKiem> dsSoTK;
    double laiSuatNganHan=2, laiSuatDaiHan=3,laiSuatKThoiHan = 0.05;
    char luaChon;

    do {// Cac chuc nang co trong chuong trinh
    cout << "================================ QUAN LY SO TIET KIEM ================================\n";
    cout << "\t1. Nhap so tiet kiem\n";
    cout << "\t2. Rut tien\n";
    cout << "\t3. Xem danh sach so tiet kiem\n";
    cout << "\t4. Cap nhat lai suat\n";
    cout << "\t5. Tim kiem theo ten hoac CMND\n";
    cout << "\t6. Tim kiem cac so tiet kiem duoc mo trong 1 khoang thoi gian\n";
    cout << "\t7. Tinh tien lai hien tai\n";
    cout << "\t8. Thoat\n";
    cout << "\tLua chon: ";
    cin >> luaChon;
    cout<<"\n";
    switch (luaChon) {
        case '1': {
            int n,i=1 ;
            cout << "\t(+) Nhap so luong STK can nhap: ";
            cin>>n;
            while(n--)
            {
                cout<<"\t"<<i<<".\n";
                SoTietKiem stk = nhapSoTietKiem(dsSoTK);

                if(stk.loaiTietKiem == "dai han") tinhlaiSTK(stk, laiSuatDaiHan);
                else if (stk.loaiTietKiem == "ngan han")  tinhlaiSTK(stk, laiSuatNganHan);
                else tinhlaiSTK(stk, laiSuatKThoiHan);

                dsSoTK.push_back(stk);

                cout << "\t(+) Da nhap thanh cong so tiet kiem thu "<<i<<"!\n";
                i++;
            }
            sort(dsSoTK.begin(), dsSoTK.end(), sapXepSTK);
            break;
        }
        case '2': {
            if (dsSoTK.empty()) {
                cout << "\t(!) Vui long nhap so tiet kiem!\n";
            } else {
                cout << "\t(+) Chon so tiet kiem de rut:\n";

                cout << string(90, '-') << "\n";
                cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND)" << "\n";
                cout << string(90, '-') << "\n";

            for (const auto& stk : dsSoTK) {
                xuatSoTietKiem(stk);
            }
            cout << string(90, '-') << "\n";

                string Mastk;
                int s=0;
                cout << "\t(+) Nhap ma so tiet kiem: ";
                cin >> Mastk;
                for (const auto& stk : dsSoTK) {
                    if(stk.maSo == Mastk) break;
                    s++;
                }
                if (ktratrungMaSo(dsSoTK,Mastk)) {
                    if(dsSoTK[s].loaiTietKiem == "dai han") rutTien(dsSoTK[s], laiSuatDaiHan, 1.0);// Lãi suất 3% cho năm, 1% nếu rút trước hạn
                    else if (dsSoTK[s].loaiTietKiem == "ngan han") rutTien(dsSoTK[s], laiSuatNganHan, 0.05);
                    else rutTien(dsSoTK[s], laiSuatKThoiHan, 0.05);
                } else {
                    cout << "\t(!) Lua chon khong hop le.\n";
                }
            }
            break;
        }
        case '3': {
            if(dsSoTK.size()==0)
            {
                cout<<"\t(!) Vui long nhap so tiet kiem.\n";
                break;
            }
            cout << string(90, '-') << "\n";
            cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND)" << "\n";
            cout << string(90, '-') << "\n";

            for (const auto& stk : dsSoTK) {
                xuatSoTietKiem(stk);
            }
            cout << string(90, '-') << "\n";
            break;
        }
        case '4': {  // Chuc nang cap nhat lai suat
            cout << "\t(+) Nhap lai suat ngan han (%/nam): ";
            cin >> laiSuatNganHan;
            cout << "\t(+) Nhap lai suat dai han (%/nam): ";
            cin >> laiSuatDaiHan;
            capNhatLaiSuat(dsSoTK, laiSuatNganHan, laiSuatDaiHan);
            break;
        }
        case '5': {
            if (dsSoTK.empty()) {
                cout << "\t(!) Vui long nhap so tiet kiem!\n";
                break;
                }
                timSTK(dsSoTK);
                break;
            }
            case '6': {
                if (dsSoTK.empty()) {
                cout << "\t(!) Vui long nhap so tiet kiem!\n";
                    break;
                }
                timtheoDate(dsSoTK);
                break;
            }
        case '7':
            {
                if (dsSoTK.empty()) {
                cout << "\t(!) Vui long nhap so tiet kiem!\n";
                break;
                }
                cout << "\t(+) Chon so tiet kiem de tinh tien lai:\n";
                cout << string(90, '-') << "\n";
                cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND)" << "\n";
                cout << string(90, '-') << "\n";

            for (const auto& stk : dsSoTK) {
                xuatSoTietKiem(stk);
            }
            cout << string(90, '-') << "\n";
            string Mastk;
                int s=0;
                cout << "\t(+) Nhap ma so tiet kiem: ";
                cin >> Mastk;
                for (const auto& stk : dsSoTK) {
                    if(stk.maSo == Mastk) break;
                    s++;
                }
                if (ktratrungMaSo(dsSoTK,Mastk)) {
                    if(dsSoTK[s].loaiTietKiem == "dai han") tinhlaiSTK(dsSoTK[s], laiSuatDaiHan);
                    else if (dsSoTK[s].loaiTietKiem == "ngan han")  tinhlaiSTK(dsSoTK[s], laiSuatNganHan);
                    else tinhlaiSTK(dsSoTK[s], laiSuatKThoiHan);
                }
                else cout << "\t(!) Lua chon khong hop le.\n";
                break;

            }
        case '8': {
            cout << "(!) Thoat chuong trinh.\n";
            break;
        }
        default:
            cout << "\t(!) Lua chon khong hop le. Vui long nhap lai.\n";
    }
} while (luaChon != '8');
return 0;
}
