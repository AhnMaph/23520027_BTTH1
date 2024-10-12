#include <bits/stdc++.h>
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
int sosanh(int tu_a,int mau_a,int tu_b, int mau_b)
    {
        if(mau_a*mau_b == 0) return -1;
        int A = tu_a*mau_b;
        int B = tu_b*mau_a;
        if(A>B) return 0;
        else if(A<B) return 1;
        else return 2;
    }
void xuat(int tu, int mau)
{
    if(tu>0&&mau<0) cout<<tu*-1<<"/"<<mau*-1;
    else cout<< tu<<"/"<<mau;
}
int main()
{
    int tu1,mau1,tu2,mau2;
    cout<<"Nhap vao hai phan so\n";
    cout<<"Phan so A: ";
    cin>>tu1>>mau1;
    cout<<"Phan so B: ";
    cin>>tu2>>mau2;
    cout<<"\n";
    int x = sosanh(tu1,mau1,tu2,mau2);
    if(x == -1) cout<<"Mau phai khac 0\n";
    else if (x == 0)
        {
            cout<<"Phan so A lon nhat ";
            xuat(tu1,mau1);
        }
    else if (x == 1)
        {
            cout<<"Phan so B lon nhat ";
            xuat(tu2,mau2);
        }
    else
    {
        cout<<"Phan so A va B lon nhat ";
        xuat(tu2,mau2);
        cout<<" = ";
        xuat(tu1,mau1);
    }
    return 0;
}
