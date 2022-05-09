#include <algorithm>
#include<vector>
template<class T>
std::vector<T> zaatsu(const vector<T>& A){
  std::vector<T> B=A;
  std::sort(B.begin(),B.end());
  B.erase(std::unique(B.begin(),B.end()),B.end());
  std::vector<T> res(A.size());
  for(int i=0;i<(int)A.size();i++){
    res[i]=std::lower_bound(B.begin(),B.end(),A[i])-B.begin();
  }
  return res;
}
