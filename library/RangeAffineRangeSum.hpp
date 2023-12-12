using mint=atcoder::modint998244353;

struct S{
  mint val;
  ll size;
};
using F=pair<mint,mint>;

S op(S a,S b){
  return S{a.val+b.val,a.size+b.size};
}

S mapping(F f,S x){
  return S{f.first*x.val+f.second*x.size,x.size};
}

F composition(F f,F g){
  return F{f.first*g.first,f.second+f.first*g.second};
}

S e(){
  return S{0,0};
}

F id(){
  return F{1,0};
}
using RangeAffineRangeSum=atcoder::lazy_segtree<S,op,e,F,mapping,composition,id>;

/*
int main(){
  ll N,Q;
  cin>>N>>Q;
  vector<ll> A(N);
  for(ll i=0;i<N;i++){
    cin>>A[i];
  }
  RangeAffineRangeSum seg(N);
  for(ll i=0;i<N;i++){
    seg.set(i,S{A[i],1});
  }
  for(ll i=0;i<Q;i++){
    ll t;
    cin>>t;
    if(t==0){
      ll l,r,b,c;
      cin>>l>>r>>b>>c;
      seg.apply(l,r,F{b,c});
    }else{
      ll l,r;
      cin>>l>>r;
      cout<<seg.prod(l,r).val.val()<<endl;
    }
  }
}
*/
