#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 500010
#define M 3001
#define ec ' '
#define one 1ll
//#define endl '\n'
const int mod = 998244353;
#define inf 0x7f7f7f7f
int n, m;
int a[N], b[N];
int f[M][M];
signed main()
{
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n;i++)
    {
        cin >> b[i];
    }
    for (int i = 1; i <= n;i++)
    {
        int val = 0;
        for (int j = 1; j <= n; j++)
        {
            if(a[i]!=b[j])
            {
                f[i][j] = f[i - 1][j];
            }
            else 
            {
                f[i][j] = val + 1;
            }
            if(b[j]<a[i])
            {
                val = max(f[i-1][j], val);
            }
        }
    
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, f[n][i]);
    }
    cout << ans;
    return 0;
}