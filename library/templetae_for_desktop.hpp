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
#include <bitset>
#include <tuple>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <atcoder/all>
#if __has_include(<boost/multiprecision/cpp_int.hpp>)
#include <boost/multiprecision/cpp_int.hpp>
using cpp_int=boost::multiprecision::cpp_int;
#endif
#if __has_include(<boost/multiprecision/cpp_dec_float.hpp>)
#include <boost/multiprecision/cpp_dec_float.hpp>
template<unsigned size>using cpp_float=boost::multiprecision::number<boost::multiprecision::cpp_dec_float<size>>;
template<unsigned size>using cpp_double=boost::multiprecision::number<boost::multiprecision::cpp_dec_float<size,long long>>;
#endif

#ifndef ONLINE_JUDGE
#include "header.hpp"
#else
#include <bits/stdc++.h>
#include <atcoder/all>
#include <boost/multiprecision/cpp_int.hpp>
using cpp_int=boost::multiprecision::cpp_int;
#include <boost/multiprecision/cpp_dec_float.hpp>
template<unsigned size>using cpp_float=boost::multiprecision::number<boost::multiprecision::cpp_dec_float<size>>;
template<unsigned size>using cpp_double=boost::multiprecision::number<boost::multiprecision::cpp_dec_float<size,long long>>;
#endif

using namespace std;
using ll=long long;
inline void yn(bool x){if(x){cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}}
#define double_out(x) fixed << setprecision(x)
template<class T> inline void erase_duplicate(vector<T>& A){sort(A.begin(),A.end());A.erase(unique(A.begin(),A.end()),A.end());}
inline ll powll(ll x,ll n){ll r=1;while(n>0){if(n&1){r*=x;};x*=x;n>>=1;};return r;}


int main(){
    
}


