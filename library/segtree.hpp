#include <algorithm>
#include <vector>

template<class Type,Type (*op)(Type,Type),Type (*e)()>
class segtree{
  private:
    int _n,_size,_log;
    std::vector<Type> _d;
    void update(int k){
      _d.at(k)=op(_d.at(2*k),_d.at(2*k+1));
    }
    int ceil_pow2(int y){
      int x=0;
      while((1U<<x)<(unsigned int)(y)){
        x++;
      }
      return x;
    }
  public:
    segtree():segtree(0){}
    segtree(int n):segtree(std::vector<Type>(n,e())){}
    segtree(const std::vector<Type>& v):_n((int)v.size()){
      _log=ceil_pow2(_n);
      _size=1<<_log;
      _d=std::vector<Type>(2*_size,e());
      for(int i=0;i<_n;i++){
        _d.at(_size+i)=v.at(i);
      }
      for(int i=_size-1;i>=1;i--){
        update(i);
      }
    }

    void set(int p,Type x){
      p+=_size;
      _d.at(p)=x;
      for(int i=1;i<=_log;i++){
        update(p>>i);
      }      
    }

    Type get(int p)const{
      return _d.at(p+_size);
    }

    Type prod(int l,int r)const{
      Type sml=e(),smr=e();
      l+=_size;
      r+=_size;
      while(l<r){
        if(l&1){
          sml=op(sml,_d.at(l++));
        }
        if(r&1){
          smr=op(_d.at(--r),smr);
        }
        l>>=1;
        r>>=1;
      }
      return op(sml,smr);
    }

    Type all_prod()const{
      return _d.at(1);
    }

    template<bool (*f)(Type)>
    int max_right(int l)const{
      return max_right(l,[](Type x){return f(x);});
    }

    template<class F>
    int max_right(int l,F f)const{
      if(l==_n){
        return _n;
      }
      l+=_size;
      Type sm=e();
      do{
        while(l%2==0){
          l>>=1;
        }
        if(!f(op(sm,_d.at(l)))){
          while(l<_size){
            l=2*l;
            if(f(op(sm,_d.at(l)))){
              sm=op(sm,_d.at(l));
              l++;
            }
          }
          return l-_size;
        }
        sm=op(sm,_d.at(l));
        l++;
      }while((l&-l)!=l);
      return _n;
    }

    template<bool (*f)(Type)> int min_left(int r)const{
      return min_left(r,[](Type x){return f(x);});
    }
    template<class F>
    int min_left(int r,F f)const{
      if(r==0){
        return 0;
      }
      r+=_size;
      Type sm=e();
      do{
        r--;
        while(r>1 && (r%2)){
          r>>=1;
        }
        if(!f(op(_d.at(r),sm))){
          while(r<_size){
            r=2*r+1;
            if(f(op(_d.at(r),sm))){
              sm=op(_d.at(r),sm);
              r--;
            }
          }
          return r+1-_size;
        }
        sm=op(_d.at(r),sm);
      }while((r&-r)!=r);
      return 0;
    }
};

/*
コンストラクタ
segtree<Type,op,e> seg(int n)
segtree<Type,op,e> seg(std::vector<Type> v)
型 Type
二項演算 Type op(Type a,Type b)
単位元 Type e()
set O(log n)
void seg.set(int p,Type x)
a[p] <- x
get O(1)
Type seg.get(int p)
a[p] を取得
prod O(lon n)
Type seg.prod(int l,int r)
op(a[l], ..., a[r-1]) を取得
all_prod O(1)
Type seg.all_prod()
op(a[0],..,a[n-1]) を取得
max_right O(log n)
int seg.max_right<f>(int l)
int seg.max_right<F>(int l, F f)
関数 bool f(Type x)
segtree上で二分探索
f(op(a[l],...,a[r-1]))=true となる最大のr
min_left O(log n)
int seg.min_left<f>(int r)
int seg.min_left<F>(int r,F f)
関数 bool f(Type x)
segtree上で二分探索
f(op(a[l],...,a[r-1]))=true となる最小のl
*/
