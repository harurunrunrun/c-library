// 1~Nまでのkbit目が立っている数
ll sum_bit_N(ll N,ll k){
  return N/(1LL<<(k+1))*(1LL<<k)+(((N>>k)&1)?1+N%(1LL<<k):0);
}
