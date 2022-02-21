#include <vector>
#include <algorithm>

bool warshall_floyd(std::vector<std::vector<long long>>& d){
  for(unsigned int k=0;k<d.size();k++){
    d[k][k]=0;
  }
  for(unsigned int k=0;k<d.size();k++){
    for(unsigned int i=0;i<d.size();i++){
      for(unsigned int j=0;j<d.size();j++){
        d[i][j]=std::min(d[i][j],d[i][k]+d[k][j]);
      }
    }
  }
  for(unsigned int k=0;k<d.size();k++){
    if(d[k][k]<0){
      return false;
    }
  }
  return true;
}
