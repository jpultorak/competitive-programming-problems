//https://codeforces.com/problemset/problem/620/E

#include <bits/stdc++.h>
 
#define FOR(i, a, b) for(int i = a; i<b; ++i)
#define FR(a, b) for(int i = a; i>=b;--i)
#define _upgrade cin.tie(0); ios_base::sync_with_stdio(0)
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define INF 1e9
 
using namespace std;
 
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef pair<int, int> iPair;
 
const int MAX = 4e5+1;
const int M = 1e9+7;
 
int n, q, sub[MAX], TT, id[MAX], c[MAX], temp[MAX], lazy[4*MAX];
vector<int> tree[MAX];
 
ll seg[4*MAX];
void build(int v = 1, int l = 1, int r = n)
{
    if(l == r)
    {
        seg[v] = (1LL<<c[l]);
        return;
    }
    int mid = (l+r)/2;
    build(2*v, l, mid);
    build(2*v+1, mid+1, r);
    seg[v] = seg[2*v] | seg[2*v+1];
}
void up(int v, int l, int r, int a, int b, int col)
{
    if(lazy[v])
    {
        seg[v] = (1LL<<lazy[v]);
        if(l != r)
        {
            lazy[2*v] = lazy[v];
            lazy[2*v+1] = lazy[v];
        }
        lazy[v] = 0;
    }
    if(l > b || r < a)
        return;
    if(l >= a && r <= b)
    {
        seg[v] = (1LL<<col);
        if(l != r)
        {
            lazy[2*v] = col;
            lazy[2*v+1] = col;
        }
        return;
    }
    int mid = (l+r)/2;
    up(2*v, l, mid, a, b, col);
    up(2*v+1, mid+1, r, a, b, col);
    seg[v] = seg[2*v] | seg[2*v+1];
 
}
ll query(int v, int l, int r, int a, int b)
{
    if(lazy[v])
    {
        seg[v] = (1LL<<lazy[v]);
        if(l != r)
        {
            lazy[2*v] = lazy[v];
            lazy[2*v+1] = lazy[v];
        }
        lazy[v] = 0;
    }
    if(l > b || r < a)
        return 0;
    if(l >= a && r <= b)
        return seg[v];
 
    int mid = (l+r)/2;
    return query(2*v, l, mid, a, b) | query(2*v+1, mid+1, r, a, b);
}
int DFS(int node, int pr)
{
    id[node] = ++TT;
    sub[node] = 1;
    for(int i : tree[node])
        if(i != pr)
            sub[node] += DFS(i, node);
    return sub[node];
}
int main()
{
    _upgrade;
    cin>>n>>q;
    FOR(i, 1, n+1)
        cin>>temp[i];
 
    FOR(i, 0, n-1)
    {
        int a, b;
        cin>>a>>b;
        tree[a].pb(b);
        tree[b].pb(a);
    }
    DFS(1, -1);
    FOR(i, 1, n+1)
        c[id[i]] = temp[i];
    build();
    while(q--)
    {
        int type;
        cin>>type;
        if(type == 1)
        {
            int v, col;
            cin>>v>>col;
            up(1, 1, n, id[v], id[v] + sub[v]-1, col);
        }
        else
        {
            int v;
            cin>>v;
 
            cout<<__builtin_popcountll(query(1, 1, n, id[v], id[v] + sub[v]-1))<<"\n";
        }
    }
}
