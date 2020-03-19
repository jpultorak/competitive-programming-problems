//solution https://codeforces.com/contest/342/problem/E
//using Centroid Decomposition and LCA in O(n log^2 n)

#include <bits/stdc++.h>
 
#define FOR(i, a, b) for(int i = a; i<b; ++i)
#define FR(a, b) for(int i = a; i>=b;--i)
#define _upgrade cin.tie(0); ios_base::sync_with_stdio(0)
#define pb push_back
#define mp make_pair
#define INF 1e9
 
using namespace std;
 
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef pair<int, int> iPair;
 
const int MAX = 1e5+2;
const int M = 1e9+7;
 
int n, q, sub[MAX], parent[MAX], ans[MAX], ancestor[MAX][18], tpar[MAX], depth[MAX];
vector<int> tree[MAX];
bool dead[MAX];
 
void get_parents(int v, int pr)
{
    tpar[v] = pr;
    for(auto i : tree[v])
        if(i != pr)
        {
            depth[i] = depth[v]+1;
            get_parents(i, v);
        }
}
void preprocess()
{
    FOR(i, 1, n+1)
        ancestor[i][0] = tpar[i];
    FOR(i, 1, 18)
        FOR(j, 1, n+1)
            ancestor[j][i] = ancestor[ancestor[j][i-1]][i-1];
}
int LCA(int a, int b)
{
    if(depth[a] > depth[b])
        swap(a, b);
    for(int i = 17; i>=0; --i)
        if(depth[ancestor[b][i]] >= depth[a])
            b = ancestor[b][i];
    if(a == b)
        return a;
 
    for(int i = 17; i>=0; --i)
        if(ancestor[b][i] != ancestor[a][i])
        {
            b = ancestor[b][i];
            a = ancestor[a][i];
        }
    return tpar[a];
}
int dist(int a, int b)
{
    return depth[a] + depth[b] - 2*depth[LCA(a, b)];
}
int build(int v, int pr)
{
    sub[v] = 1;
    for(int i : tree[v])
        if(!dead[i] && i != pr)
            sub[v] += build(i, v);
    return sub[v];
}
int find_centroid(int v, int pr, int sz)
{
    for(int i : tree[v])
        if(!dead[i] && sub[i] > sz/2 && i != pr)
            return find_centroid(i, v, sz);
    return v;
}
void decompose(int x, int pr)
{
    int sz = build(x, -1), v = find_centroid(x, -1, sz);
 
    dead[v] = 1;
    parent[v] = pr;
 
    for(int i : tree[v])
        if(!dead[i])
            decompose(i, v);
}
 
void update(int v)
{
    int x = v;
    while(x != 0)
    {
        ans[x] = min(ans[x] , dist(x, v));
        x = parent[x];
    }
}
void query(int v)
{
    int mi = INF, x = v;
    while(x != 0)
    {
        mi = min(mi, ans[x] + dist(x, v));
        x = parent[x];
    }
    cout<<mi<<"\n";
}
int main()
{
    _upgrade;
    cin>>n>>q;
    FOR(i, 0, n-1)
    {
        int a, b;
        cin>>a>>b;
        tree[a].pb(b);
        tree[b].pb(a);
    }
    fill(ans, ans+n+1, INF);
    decompose(1, 0);
    get_parents(1, 1);
    preprocess();
    update(1);
 
    while(q--)
    {
        int type, v;
        cin>>type>>v;
        if(type == 1)
            update(v);
        else
            query(v);
    }
    return 0;
}
