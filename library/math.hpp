#pragma once
#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>

long long pow(long long x,long long n){
  long long res=1;
  while(n>0){
    if(n&1){
      res*=x;
    }
    x*=x;
    n>>=1;
  }
  return res;
}

long long pow_mod(long long x,long long n,long long mod){
  long long res=1;
  while(n>0){
    if(n&1){
      res*=x;
      res%=mod;
    }
    x*=x;
    x%=mod;
    n>>=1;
  }
  return res;
}

long long gcd(long long x,long long y){
  long long tmp;
  while(y!=0){
    tmp=y;
    y=x%y;
    x=tmp;
  }
  return x;
}

long long lcm(long long x,long long y){
  return x/gcd(x,y)*y;
}

bool is_prime(long long x){
  for(long long i=1;i*i<=x;i++){
    if(x%i==0LL){
      return false;
    }
  }
  return x!=1LL;
}

std::vector<long long> divisor(long long n){
  std::vector<long long> res;
  for(long long i=1;i*i<=n;i++){
    if(n%i==0){
      res.push_back(i);
      if(n/i!=i){
        res.push_back(n/i);
      }
    }
  }
  return res;
}

std::vector<std::pair<long long,long long>> prime_factor(long long n){
  std::vector<std::pair<long long,long long>> res;
  long long tmp;
  for(long long i=1;i*i<=n;i++){
    tmp=0;
    while(n%i==0){
      tmp++;
      n/=i;
    }
    if(tmp!=0){
      res.push_back(std::make_pair(i,tmp));
    }
  }
  if(n!=1){
    res.push_back(std::make_pair(n,1LL));
  }
  return res;
}

std::vector<long long> sieve(long long n){
  std::vector<long long> res;
  std::vector<bool> prime(n,true);
  prime.at(0)=false;
  prime.at(1)=false;
  for(long long i=2;i<=n;i++){
    if(prime.at(i)){
      res.push_back(i);
      for(long long j=2*i;j<=n;j+=i){
        prime.at(j)=false;
      }
    }
  }
  return res;
}

std::vector<long long> segment_sieve(long long a,long long b){
  std::vector<long long> res;
  std::vector<bool> prime((int)sqrt(b)+2,true),small(b-a+1,true);
  for(long long i=2;i*i<=b;i++){
    if(small.at(i)){
      for(long long j=2*i;j*j<b;j+=i){
        small.at(j)=false;
      }
      for(long long j=std::max(2LL,(a+i-1)/i)*i;j<b;j+=i){
        prime.at(j-a)=false;
      }
    }
  }
  for(long long i=a;i<=b;i++){
    if(prime.at(i-a)){
      res.push_back(i);
    }
  }
  return res;
}
