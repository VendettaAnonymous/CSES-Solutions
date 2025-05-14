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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oSet;

const int mod = 1e9 + 7;
const int max_val = 2e5 + 7;
int t, n, q;
vector<int> adj[max_val], chain[max_val];
int node_val[max_val]{}, sz[max_val]{}, p[max_val], H[max_val], pos[max_val], chainidx[max_val];

struct node
{
    int l, r, mx;
    node *left;
    node *right;
    node(int a, int b)
    {
        l = a;
        r = b;
        mx = 0;
        left = nullptr;
        right = nullptr;
    }
};

int dfs(int u, int pa, int h)
{
    sz[u] = 1;
    p[u] = pa;
    H[u] = h;
    for (auto &&it : adj[u])
    {
        if (it != pa)
        {
            sz[u] += dfs(it, u, h + 1);
        }
    }
    return sz[u];
}
node *root[max_val];

node *built(int l, int r)
{
    node *temp = new node(l, r);
    if (l != r)
    {
        int mid = (l + r) / 2;
        temp->left = built(l, mid);
        temp->right = built(mid + 1, r);
    }
    return temp;
}

void update(node *root, int idx, int val)
{
    if (root->l == root->r)
    {
        root->mx = val;
        return;
    }
    int mid = (root->l + root->r) / 2;
    update((idx <= mid ? root->left : root->right), idx, val);
    root->mx = max(root->left->mx, root->right->mx);
}

void HLD_Build(int n)
{
    chain[n].push_back(n);
    for (int i = 0; i < chain[n].size(); i++)
    {
        int v = chain[n][i];
        pos[v] = i;
        chainidx[v] = n;
        for (int j : adj[v])
        {
            if (j != p[v])
            {
                if (sz[j] * 2 >= sz[v])
                {
                    chain[n].push_back(j);
                }
                else
                {
                    HLD_Build(j);
                }
            }
        }
    }

    root[n] = built(0, chain[n].size() - 1);
}

int querAns(node *root, int ql, int qr)
{
    if (root->r < ql || root->l > qr)
    {
        return LLONG_MIN;
    }
    if (root->l >= ql && root->r <= qr)
    {
        return root->mx;
        ;
    }
    return max(querAns(root->left, ql, qr), querAns(root->right, ql, qr));
}

int query(int u, int v)
{
    int ans = 0;
    while (chainidx[u] != chainidx[v])
    {
        if (H[u] > H[v])
            swap(u, v);
        ans = max(ans, querAns(root[chainidx[v]], 0, pos[v]));
        v = p[chainidx[v]];
    }

    if (pos[u] > pos[v])
    {
        swap(u, v);
    }
    ans = max(ans, querAns(root[chainidx[v]], pos[u], pos[v]));
    return ans;
}

int32_t main()
{
    fastio;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        cin >> node_val[i];
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

    dfs(0, -1, 0);
    HLD_Build(0);

    for (int i = 0; i < n; i++)
    {
        update(root[chainidx[i]], pos[i], node_val[i]);
    }

    while (q--)
    {
        int g, u, v;
        cin >> g >> u >> v;
        u--;
        if (g == 1)
        {
            node_val[u] = v;
            update(root[chainidx[u]], pos[u], node_val[u]);
        }
        else
        {
            v--;
            cout << query(u, v) << " ";
        }
    }

    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;
// #define lli long long int
// #define vec vector
// #define pb push_back
// #define s(x) scanf("%d", &x)
// #define all(x) x.begin(), x.end()
// #define pii pair<int, int>
// #define fi first
// #define se second
// #define SZ 200005

// const int N = SZ;
// struct node
// {
//     int l, r, mx;
//     node *left, *right;
//     node(int ll, int rr) : l(ll), r(rr), mx(0), left(NULL), right(NULL) {}
// };

// /******** SEGTREE-ON EACH CHAIN ******/

// void update(node *p, int idx, int val)
// {
//     if (p->l == p->r)
//     {
//         p->mx = val;
//         return;
//     }
//     int mid = (p->l + p->r) >> 1;
//     update((idx <= mid ? p->left : p->right), idx, val);
//     p->mx = max(p->left->mx, p->right->mx);
// }

// int query(node *p, int ql, int qr)
// {
//     if (qr < p->l or p->r < ql)
//         return 0;
//     if (ql <= p->l and p->r <= qr)
//         return p->mx;
//     return max(query(p->left, ql, qr), query(p->right, ql, qr));
// }

// node *build(int l, int r)
// {
//     node *p = new node(l, r);
//     if (l < r)
//     {
//         int mid = (l + r) >> 1;
//         p->left = build(l, mid);
//         p->right = build(mid + 1, r);
//     }
//     return p;
// }

// /********* SETUP SUBSIZE,PARENT,HEIGHT ********/

// vector<int> adj[N];
// int n, q;

// node *root[N]; /**holds root of segtree of each chain**/
// vector<int> chain[N];
// int sz[N], H[N], P[N], chainIdx[N], pos[N];

// void dfs_setup(int n, int p, int h)
// {
//     P[n] = p;
//     H[n] = h;
//     sz[n] = 1;
//     for (int i : adj[n])
//     {
//         if (i - p)
//         {
//             dfs_setup(i, n, h + 1);
//             sz[n] += sz[i];
//         }
//     }
// }

// /************ HLD,HLD-QUERY***********************/

// void HLD_build(int n)
// {
//     chain[n].pb(n);
//     for (int i = 0; i < chain[n].size(); i++)
//     {
//         int v = chain[n][i];
//         chainIdx[v] = n;
//         pos[v] = i;
//         for (int j : adj[v])
//             if (j - P[v])
//                 2 * sz[j] >= sz[v] ? chain[n].pb(j) : HLD_build(j);
//     }
//     root[n] = build(0, chain[n].size() - 1);
// }

// int HLD_query(int u, int v)
// {

//     int ans = 0;
//     while (chainIdx[u] != chainIdx[v])
//     {
//         if (H[chainIdx[u]] > H[chainIdx[v]])
//             swap(u, v);
//         ans = max(ans, query(root[chainIdx[v]], 0, pos[v]));
//         v = P[chainIdx[v]];
//     }

//     if (pos[u] > pos[v])
//         swap(u, v);

//     ans = max(ans, query(root[chainIdx[u]], pos[u], pos[v]));
//     return ans;
// }
// /******************************************************/

// int main()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     cin >> n >> q;

//     int val[n];
//     for (int i = 0; i < n; i++)
//     {
//         cin >> val[i];
//     }

//     for (int i = 0; i < n - 1; i++)
//     {
//         int u, v;
//         cin >> u >> v;
//         u--;
//         v--;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     dfs_setup(0, 0, 0);
//     HLD_build(0);
//     for (int i = 0; i < n; i++)
//     {
//         update(root[chainIdx[i]], pos[i], val[i]);
//     }

//     for (int i = 0; i < q; i++)
//     {
//         int type;
//         cin >> type;
//         if (type == 1)
//         {
//             int u, x;
//             cin >> u >> x;
//             u--;
//             update(root[chainIdx[u]], pos[u], x);
//         }
//         else
//         {
//             int u, v;
//             cin >> u >> v;
//             cout << HLD_query(u - 1, v - 1) << " ";
//         }
//     }
// }