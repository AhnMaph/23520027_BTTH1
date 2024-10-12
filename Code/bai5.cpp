#include <iostream>
/*
Viết chương trình nhập vào một ngày.
- Tìm ngày kế tiếp và xuất kết quả.
- Tìm ngày trước ngày này và xuất kết quả.
- Tính xem ngày đó là ngày thứ bao nhiêu trong năm và xuất kết quả.
*/
using namespace std;
int ngay,thang,nam;
int day[13] ={31,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //ngay trong thang

void xuat_trc(int ngay,int thang,int nam)
{
    cout<<"Ngay truoc ngay nay la: "<<ngay<<"/"<<thang<<"/"<<nam<<"\n";
}

void xuat_sau(int ngay,int thang,int nam)
{
    cout<<"Ngay sau ngay nay la: "<<ngay<<"/"<<thang<<"/"<<nam<<"\n";
}

void before_this(int ngay,int thang,int nam)
{
    int d=ngay,y=nam,m=thang;
    if(ngay*thang == 1) y = nam - 1;

    if(ngay*thang==1) m = 12;
    else if(ngay==1) m = thang - 1;
    if(ngay==1) d = day[thang-1];
    else d = ngay - 1;

    cout<<"Ngay truoc ngay nay la: "<<d<<"/"<<m<<"/"<<y<<"\n";

}
void after_this(int ngay,int thang,int nam)
{
    int d=ngay,y=nam,m=thang;
    if(ngay==31&&thang==12) y = nam + 1;

    if(ngay==31&&thang==12) m = 1;
    else if(ngay==day[thang]) m = thang + 1;

    if(ngay==day[thang]) d = 1;
    else d = ngay + 1;

    cout<<"Ngay sau ngay nay la: "<<d<<"/"<<m<<"/"<<y<<"\n";
}


void day_nth(int ngay,int thang,int nam)
{
    int dem = 0;
    for(int i=1;i<=thang;i++)
    {
        dem=dem+day[i];
    }
    dem = dem-(day[thang]-ngay);
    cout<<"Day la ngay thu "<<dem<<" trong nam "<<nam<<"\n";
}
int main()
{
    string date;
    int ngay,thang,nam;
    while(1)
    {
        cout<<"Nhap vao mot ngay (dd/mm/yyyy): ";
        cin>>date;
        ngay = stoi(date.substr(0, 2));
        thang = stoi(date.substr(3, 2));
        nam = stoi(date.substr(6, 4));

        if((nam%4 == 0 && nam%100 != 0) || (nam%400 == 0)) day[2] = 29;
        else day[2] = 28;

        if((thang>0&&thang<=12)&&(ngay>0&&ngay<=day[thang])&&nam>0)
        {
            break;
        }
        else
        {
            cout<<"Ngay thang nam sai, nhap lai\n";
        }
    }
    before_this(ngay,thang,nam);
    after_this(ngay,thang,nam);
    day_nth(ngay,thang,nam);
    return 0;
}
