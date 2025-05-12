// Solution idea: Just have X instances of PURQ Fenwick trees.

#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))                    

using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
using ii = pair<int, int>;

// PURQ Fenwick Tree
class FenwickTree {                              
  private:
    vll ft;                                        
  public:
    FenwickTree(int m) { ft.assign(m+1, 0); }      

    void build(const vll &f) {
      int m = (int)f.size()-1;                     
      ft.assign(m+1, 0);
      for (int i = 1; i <= m; ++i) {               
        ft[i] += f[i];                             
        if (i+LSOne(i) <= m)                       
          ft[i+LSOne(i)] += ft[i];                 
      }
    }

    FenwickTree(const vll &f) { build(f); }        

    FenwickTree(int m, const vi &s) {              
      vll f(m+1, 0);
      for (int i = 0; i < (int)s.size(); ++i)      
        ++f[s[i]];                                 
      build(f);                                    
    }

    ll rsq(int j) const {
      ll sum = 0;
      for (; j; j -= LSOne(j))
        sum += ft[j];
      return sum;
    }

    ll rsq(int i, int j) const { return rsq(j) - rsq(i-1); } 


    void update(int i, ll v) {
      for (; i < (int)ft.size(); i += LSOne(i))
        ft[i] += v;
    }
};

ll cost(const vector<FenwickTree>& fts, int p, ii A, ii B) {
  int min_x = min(A.first, B.first);
  int max_x = max(A.first, B.first);
  int min_y = min(A.second, B.second);
  int max_y = max(A.second, B.second);

  ll res = 0;
  for (int i = min_x; i <= max_x; i++) {
    res += fts[i].rsq(min_y, max_y);
  }

  return res * p;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, p, q, k, x, y, z, w, i;
  char op;

  while (true) {
    cin >> n >> m >> p;
    if (n == 0)
      break;

    cin >> q;
    FenwickTree ft(m);
    vector<FenwickTree> fts(n, ft);

    for (i = 0; i < q; i++) {
      cin >> op;
      if (op == 'A') {
        cin >> k >> x >> y;
        fts[x].update(y+1, k);
      } else {
        cin >> x >> y >> z >> w;
        cout << cost(fts, p, {x, y+1}, {z, w+1}) << '\n';
      }
    }
    cout << '\n';
  }
}
