#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 0; i <= n; i++)
    {
        cin >> a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1e18));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int l = 1; l <= 6; l++)
            {
                int ne = i + l;
                if (ne > n)
                    continue;
                dp[ne][j + 1] = max(dp[ne][j + 1], dp[i][j] + a[ne]);
            }
        }
    }
    int ans = -1e18;
    int pos = -1;
    for (int i = 1; i <= n; i++){
        if(ans < dp[i][k]){
            ans = dp[i][k];
            pos = i;
        }
    }
    cout << ans << endl;
    vector<int> path;
    while(pos){
        path.push_back(pos);
        for(int i = 1; i <= 6; i++){
            if(pos - i >= 0 && dp[pos][k] == dp[pos - i][k - 1] + a[pos]){
                pos -= i;
                k--;
                break;
            }
        }
    }
    reverse(path.begin(), path.end());
    for(int i = 0; i < path.size(); i++){
        cout << path[i] << " ";
    }
    cout << endl;
    return 0;
}