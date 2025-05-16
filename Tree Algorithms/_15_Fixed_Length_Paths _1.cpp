#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define ld long double
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
const int mod = 1e9 + 7;
int t, n, q, k;
const int N = 2e5 + 7;
vector<vector<int>> adj(N);
int sz[N]{};
int deadNode[N]{};
int cnt[N]{};
int ans = 0;
int dfs(int u, int p = -1)
{
    sz[u] = 1;
    for (auto &&i : adj[u])
    {
        if (i != p && !deadNode[i])
            sz[u] += dfs(i, u);
    }
    return sz[u];
}

int centroid(int u, int desered, int p = -1)
{
    for (auto &&i : adj[u])
    {
        if (i != p && !deadNode[i])
        {
            if ((sz[i] * 2) > desered)
            {
                return centroid(i, desered, u);
            }
        }
    }
    return u;
}
int max_depth = 0;
void countPath(int u, bool flag, int p = -1, int depth = 1)
{
    if (depth > k)
        return;
    max_depth = max(max_depth, depth);
    if (flag && k - depth >= 0)
        ans += cnt[k - depth];
    else
        cnt[depth]++;
    for (auto &&it : adj[u])
        if (it != p && !deadNode[it])
            countPath(it, flag, u, depth + 1);
}

void centroid_decomp(int u = 0)
{

    int centro = centroid(u, dfs(u));
    deadNode[centro] = 1;
    fill(cnt, cnt + max_depth + 1, 0);
    cnt[0] = 1;
    max_depth = 0;

    for (auto &&nei : adj[centro])
    {
        if (!deadNode[nei])
        {
            countPath(nei, true, centro);
            countPath(nei, false, centro);
        }
    }

    for (auto &&nei : adj[centro])
    {
        if (!deadNode[nei])
            centroid_decomp(nei);
    }
}

int32_t main()
{
    fastio;
    int u, v;
    cin >> n >> k;
    for (int i = 0; i < (n - 1); i++)
    {
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    centroid_decomp();
    cout << ans << "\n";

    return 0;
}
