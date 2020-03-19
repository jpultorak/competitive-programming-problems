#include <bits/stdc++.h>


#define FOR(i, a, b) for(int i = a; i<b; ++i)
#define FR(i, a, b) for(int i = a; i>=b; --i)
#define _upgrade cin.tie(0); ios_base::sync_with_stdio(0)
#define pb push_back
#define mp make_pair
#define INF 1e9

using namespace std;

typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef pair<int, int> iPair;


const int MAX = 5e4 +2;
const int MOD = 1e9 +7;

ll n, total;
int sub[MAX], dist[MAX];
vector<int> tree[MAX], primes;
bool dead[MAX], sieve[MAX];

void solve(int node, int pr, ll len)
{
    if(!sieve[len])
        total++;

    for(auto p : primes)
    {
        if(p <= len)continue;
        if(!dist[p-len] || p > n)break;
        total += dist[p-len];
    }
    for(int i : tree[node])
        if(i != pr && !dead[i])
            solve(i, node, len+1);
}
void upd(int node, int pr, ll len)
{
    dist[len]++;
    for(auto i : tree[node])
        if(i != pr && !dead[i])
            upd(i, node, len+1);
}
int get_size(int node, int pr)
{
    sub[node] = 1;
    for(int i : tree[node])
        if(!dead[i] && i != pr)
            sub[node] += get_size(i, node);
    return sub[node];
}
int find_centroid(int node, int pr, int sz)
{
    for(int i : tree[node])
        if(i != pr && !dead[i] && sub[i] > sz/2)
            return find_centroid(i, node, sz);
    return node;
}
void decompose(int x)
{
    int sz = get_size(x, -1), v = find_centroid(x, -1, sz);
    FOR(i, 1, n+1)
    {
        if(!dist[i])break;
        dist[i] = 0;
    }

    dead[v] = true;

    for(int i : tree[v])
        if(!dead[i])
        {
            solve(i, -1, 1);
            upd(i, -1, 1);
        }
    for(int i : tree[v])
        if(!dead[i])
            decompose(i);
}

int main()
{
    _upgrade;
    sieve[0] = sieve[1] = true;
    for(int i = 2; i*i< MAX; ++i)
        if(!sieve[i])
            for(int j = i*i; j<MAX; j += i)
                sieve[j] = 1;
    FOR(i, 2, MAX)
        if(!sieve[i])
            primes.pb(i);

   /* for(auto p : primes)
        cout<<p<<" ";*/

    cin>>n;
    FOR(i, 0, n-1)
    {
        int a, b;
        cin>>a>>b;
        tree[a].pb(b);
        tree[b].pb(a);
    }
    decompose(1);
    double p = total, q = n*(n-1)/2;
    //output p/q
    cout<<setprecision(7)<<p/q<<"\n";
}
