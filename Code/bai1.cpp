#include<bits/stdc++.h>
using namespace std;
int n,a[100001],ans=0,k;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int x=1,y=n;
    for(int i=1;i<=n;i++) {
        if(x==y||x>y) break;
        if(a[x]+a[y]<=k) {
            ans=max(ans,a[x]+a[y]);
            x++;
        }
        else if(a[x]+a[y]>k)
        {
            y--;
        }
    }
    cout<<ans;
    return 0;
}
