#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 500010
#define M 31
#define ec ' '
#define one 1ll
//#define endl '\n'
const int mod = 998244353;
#define inf 0x7f7f7f7f
int n, m;
int a[M][M][M][M][M];
int b[M];
signed main()
{
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    int k;
    while(cin>>k)
    {
        if(k==0)break;
        for (int i = 1; i <= 5;i++)
            b[i] = 0;
        for (int i = 1; i <= k; i++)
        {
            cin >> b[i];
            n += b[i];
        }
        memset(a, 0, sizeof(a));
        a[0][0][0][0][0] = 1;
        for (int i = 0; i <= b[1]; i++)
        {
            for (int j = 0; j <= b[2];j++)
            {
                for (int x = 0; x <= b[3];x++)
                {
                    for (int y = 0; y <= b[4];y++)
                  {
                    for (int z = 0; z <= b[5];z++)
                    {
                        
                        int cur = a[i][j][x][y][z];
                        // if(cur==0)
                        // {
                        //     continue;
                        // }
                        if (i < b[1])
                        {
                            a[i + 1][j][x][y][z] += cur;
                        }
                        if(j<b[2]&&j<i)
                        {
                            a[i][j + 1][x][y][z] += cur;
                        }
                        if(x<b[3]&&x<j)
                        {
                            a[i][j][x + 1][y][z] += cur;
                        }
                        if(y<b[4]&&y<x)
                        {
                            a[i][j][x][y + 1][z] += cur;
                        }
                        if(z<b[5]&&z<y)
                        {
                            a[i][j][x][y][z + 1] += cur;
                        }
                   }
                  }
                }
            }
        }
        cout << a[b[1]][b[2]][b[3]][b[4]][b[5]] << endl;
    }
    return 0;
}