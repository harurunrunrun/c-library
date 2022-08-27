#include <vector>
#include <deque>

template<class P>
std::vector<P> extract_cycle(const std::vector<std::vector<P>>& Graph){
  std::vector<int> deg(Graph.size());
  std::deque<P> degree1;
  int cut=0;
  for(unsigned i=0;i<Graph.size();i++){
    deg[i]=Graph[i].size();
    if(deg[i]==1){
      degree1.push_back(i);
      cut++;
    }
  }
  while(!degree1.empty()){
    P v=degree1.back();
    degree1.pop_back();
    for(P to:Graph[v]){
      if(deg[to]>1){
        deg[to]--;
        if(deg[to]==1){
          degree1.push_back(to);
          cut++;
        }
      }
    }
  }
  std::vector<P> res;
  res.reserve(Graph.size()-cut);
  for(unsigned i=0;i<Graph.size();i++){
    if(deg[i]>1){
      res.push_back(i);
    }
  }
  return res;
}

template<class P>
bool is_cycle(const std::vector<std::vector<P>>& Graph){
  return !extract_cycle(Graph).empty();
}

