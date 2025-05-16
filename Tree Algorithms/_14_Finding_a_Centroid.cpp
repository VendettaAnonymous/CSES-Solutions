#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define ld long double

int t, n, q;
const int N = 2e5 + 7;
vector<vector<int>> adj(N);
int siz[N]{};
int dfs(int u, int p)
{
    siz[u] = 1;
    for (auto &&it : adj[u])
    {
        if (it != p)
        {
            siz[u] += dfs(it, u);
        }
    }
    return siz[u];
}

int centroid(int u, int p)
{
    for (auto &&it : adj[u])
    {
        if (it != p)
        {
            if ((siz[it] * 2) > n)
            {
                return centroid(it, u);
            }
        }
    }
    return u;
}

int32_t main()
{

    int u, v;
    cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);
    cout << centroid(0, -1) + 1;

    return 0;
}
