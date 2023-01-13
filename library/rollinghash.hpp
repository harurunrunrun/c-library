/*
ref: https://ei1333.github.io/library/string/rolling-hash.hpp, https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
*/
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
#include <string>
#include <algorithm>

namespace Rollinghash{

struct Rhash{
  private:
    const unsigned long long mod=(1ull<<61ull)-1;
    std::vector<unsigned long long> power;
    const unsigned long long base=[&](){
      std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
      std::uniform_int_distribution<unsigned long long> rand(1,Rhash::mod-1);
      return rand(mt);
    }();
    inline unsigned long long safe_mod(unsigned long long x){
      x=(x>>61)+(x&((1ull<<61)-1));
      if(x>mod){
        x-=mod;
      }
      return x;
    }
    inline unsigned long long add(unsigned long long a, unsigned long long b){
      return safe_mod(a+b);
    }
    inline unsigned long long mul(unsigned long long a, unsigned long long b){
      unsigned long long au=a>>31;
      unsigned long long ad=a&((1ull<<31)-1);
      unsigned long long bu=b>>31;
      unsigned long long bd=b&((1ull<<31)-1);
      unsigned long long mid=ad*bu+au*bd;
      unsigned long long midu=mid>>30;
      unsigned long long midd=mid&((1ull<<30)-1);
      unsigned long long res=au*bu*2+midu+(midd<<31)+ad*bd;
      return safe_mod(res);
    }
    inline void expand(unsigned int sz){
      if(power.size()<sz+1){
        unsigned int pre_sz=power.size();
        power.resize(sz+1);
        for(unsigned int i=pre_sz-1;i<sz;i++){
          power[i+1]=mul(power[i],base);
        }
      }
    }
  public:
    explicit Rhash():power{1ull}{}
    template<class T> std::vector<unsigned long long> build(const std::vector<T>& s){
      unsigned int sz=s.size();
      std::vector<unsigned long long> hash(sz+1);
      for(unsigned i=0;i<sz;i++){
        hash[i+1]=add(mul(hash[i],base),s[i]);
      }
      return hash;
    }
    std::vector<unsigned long long> build(const std::string& s){
      return build(std::vector<char>(s.begin(),s.end()));
    }
    unsigned long long query(std::vector<unsigned long long>& hash, int l, int r){
      expand(r-l);
      return add(hash[r],mod-mul(hash[l],power[r-l]));
    }
    unsigned long long combine(unsigned long long h1, unsigned long long h2, unsigned int h2len){
      expand(h2len);
      return add(mul(h1,power[h2len]),h2);
    }
};

bool same(Rhash& R, std::vector<unsigned long long>& hash1, int l1, int r1, std::vector<unsigned long long>& hash2, int l2, int r2){
  return R.query(hash1,l1,r1)==R.query(hash2,l2,r2); 
}

int lcp(Rhash& R, std::vector<unsigned long long>& hash1, int l1, int r1, std::vector<unsigned long long>& hash2, int l2, int r2){
  int len=std::min(r1-l1,r2-l2);
  int low=0;
  int high=len+1;
  while(high-low>1){
    int mid=(low+high)/2;
    if(same(R,hash1,l1,l1+mid,hash2,l2,l2+mid)){
      low=mid;
    }else{
      high=mid;
    }
  }
  return low;
}

}
