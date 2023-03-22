// ref:https://tookunn.hatenablog.com/entry/2016/07/13/211148

#include <vector>
template<class S,S (*op)(S,S)>
struct Sparse_Table{
  private:
    std::vector<S> _A;
    std::vector<std::size_t> _logT;
    std::vector<std::vector<std::size_t>> _table;
    std::size_t _NN;
  public:
    Sparse_Table(){}
    Sparse_Table(const std::vector<S>& A):_A(A){
      _NN=A.size();
      _logT.resize(_NN+1);
      for(std::size_t i=2;i<_NN+1;i++){
        _logT[i]=_logT[i>>1]+1;
      }
      _table=std::vector<std::vector<std::size_t>>(_NN,std::vector<std::size_t>(_logT[_NN]+1));
      for(std::size_t i=0;i<_NN;i++){
        _table[i][0]=i;
      }
      for(std::size_t k=1;(1<<k)<=_NN;k++){
        for(std::size_t i=0;i+(1<<k)<=_NN;i++){
          std::size_t first=_table[i][k-1];
          std::size_t second=_table[i+(1<<(k-1))][k-1];
          if(op(_A[first],_A[second])==_A[first]){
            _table[i][k]=first;
          }else{
            _table[i][k]=second;
          }
        }
      }
    }
    inline S query(std::size_t s, std::size_t t){
      std::size_t k=_logT[t-s+1];
      return op(_A[_table[s][k]],_A[_table[t-(1<<k)+1][k]]);
    }
};
