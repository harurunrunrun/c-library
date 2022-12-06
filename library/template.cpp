#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <string>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <stack>
#include <random>
#include <complex>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif
#if __has_include(<boost/multiprecision/cpp_int.hpp>)
#include <boost/multiprecision/cpp_int.hpp>
using cpp_int=boost::multiprecision::cpp_int;
#endif
#if __has_include(<boost/multiprecision/cpp_dec_float.hpp>)
#include <boost/multiprecision/cpp_dec_float.hpp>
using cpp_float=boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1024>>;
#endif
using namespace std;
using ll=long long;
#define read(x) cin>>(x);
#define readll(x) ll (x);cin>>(x);
#define readS(x) string (x);cin>>(x);
#define readvll(x,N) vector<ll> (x)((N));for(int i=0;i<(N);i++){cin>>(x)[i];}
#define rep(i,N) for(ll (i)=0;(i)<(N);(i)++)
#define rep2d(i,j,H,W) for(ll (i)=0;(i)<(H);(i)++)for(ll (j)=0;(j)<(W);j++)
#define is_in(x,y) (0<=(x) && (x)<H && 0<=(y) && (y)<W)
#define yn {cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}
#define double_out(x) fixed << setprecision(x)
template<class T> inline void erase_duplicate(vector<T>& A){sort(A.begin(),A.end());A.erase(unique(A.begin(),A.end()),A.end());}
inline ll powll(ll x,ll n){ll r=1;while(n>0){if(n&1){r*=x;};x*=x;n>>=1;};return r;}


int main(){
  
}
