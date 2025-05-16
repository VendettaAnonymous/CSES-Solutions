#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

#define int long long int
#define ld long double
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oSet; // [find_by_order ==> given address at index] |==| [order_of_key ==> Number of element smaller then X]

const int mod = 1e9 + 7;
int t, n, q;
const int N = 2e5 + 10;
int col[N]{};
vector<vector<int>> adj(N);
int ans[N]{};
set<int> color[N];

void solve(int u, int p)
{
    for (auto &&nei : adj[u])
    {
        if (nei != p)
        {
            solve(nei, u);
            if (color[nei].size() > color[u].size())
            {
                swap(color[nei], color[u]);
            }
            for (auto &&it : color[nei])
            {
                color[u].insert(it);
            }
        }
    }
    color[u].insert(col[u]);
    ans[u] = color[u].size();
}

int32_t main()
{
    fastio;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> col[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve(0, -1);
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}
