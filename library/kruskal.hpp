#include <atcoder/dsu>
#include <vector>
#include <algorithm>

struct Edge_and_cost{
  long long start_point;
  long long last_point;
  long long cost;
  Edge_and_cost(){}
  Edge_and_cost(long long start_point, long long last_point,long long cost):start_point(start_point),last_point(last_point),cost(cost){}
  bool operator<(const Edge_and_cost& A){
    return cost < A.cost;
  }
};

// V: number of vertices, E: number of edges
long long kruskal(std::vector<Edge_and_cost> d,int V){
  std::sort(d.begin(),d.end());
  atcoder::dsu uf(V);
  long long res=0;
  for(const Edge_and_cost& i:d){
    if(!uf.same(i.start_point,i.last_point)){
      uf.merge(i.start_point,i.last_point);
      res+=i.cost;
    }
  }
  return res;
}
