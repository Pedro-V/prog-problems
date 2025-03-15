
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))                    

typedef long long ll;                            
typedef vector<ll> vll;
typedef vector<int> vi;

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

    ll rsq(int j) {                                
      ll sum = 0;
      for (; j; j -= LSOne(j))
        sum += ft[j];
      return sum;
    }

    ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } 


    void update(int i, ll v) {
      for (; i < (int)ft.size(); i += LSOne(i))
        ft[i] += v;
    }

    int select(ll k) {                             
      int p = 1;
      while (p*2 < (int)ft.size()) p *= 2;
      int i = 0;
      while (p) {
        if (k > ft[i+p]) {
          k -= ft[i+p];
          i += p;
        }
        p /= 2;
      }
      return i+1;
    }
};

class RUPQ {                                     
  private:
    FenwickTree ft;                                
  public:
    RUPQ(int m) : ft(FenwickTree(m)) {}
    void range_update(int ui, int uj, ll v) {
      ft.update(ui, v);                            
      ft.update(uj+1, -v);                         
    }                                              
    ll point_query(int i) { return ft.rsq(i); }    
};

class RURQ  {                                    
  private:                                         
    RUPQ rupq;                                     
    FenwickTree purq;                              
  public:
    RURQ(int m) : rupq(RUPQ(m)), purq(FenwickTree(m)) {} 
    void range_update(int ui, int uj, ll v) {
      rupq.range_update(ui, uj, v);                
      purq.update(ui, v*(ui-1));                   
      purq.update(uj+1, -v*uj);                    
    }
    ll rsq(int j) {
      return rupq.point_query(j)*j -               
        purq.rsq(j);                          
    }
    ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } 
};

int main() {
  int tc, n, c, i, p, q, v;
  char op;

  cin >> tc;
  while (tc--) {
    cin >> n >> c;
    RURQ rurq(n);

    for (i = 0; i < c; i++) {
      cin >> op;
      if (op == '0') {
        cin >> p >> q >> v;
        rurq.range_update(p, q, v);
      }
      else {
        cin >> p >> q;
        cout << rurq.rsq(p, q) << '\n';
      }
    }
  }
}

