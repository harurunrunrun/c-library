#include <vector>
#include <utility>
#include <algorithm>
class Tree{
  private:
    struct Edge{
      int to;
      long long cost;
      Edge(int to,long long cost):to(to),cost(cost){}
    };
    // Nomal data
    int _V;
    int _root;
    std::vector<std::vector<Edge>> _Graph;
    // other data
    std::vector<int> _parent;
    std::vector<int> _depth;
    std::vector<long long> _distance;
    std::vector<std::vector<long long>> _doubling_parent;
    // flags
    bool is_searched_parent_and_depth_and_distance=false;
    bool is_init_lca=false;
    // private functions
    void _parent_and_depth_and_distance(int v,int par,int dep,long long cost){
      _parent[v]=par;
      _depth[v]=dep;
      _distance[v]=cost;
      for(Edge e:_Graph[v]){
        if(e.to!=par){
          _parent_and_depth_and_distance(e.to,v,dep+1,cost+e.cost);
        }
      }
    }
    void _LCA_init(){
      if(is_init_lca){
        return;
      }
      is_init_lca=true;
      search_parent_and_depth_and_distance();
      int K=1;
      while((1<<K)<_V){
        K++;
      }
      _doubling_parent.resize(K,std::vector<long long>(_V,-1));
      for(int v=0;v<_V;v++){
        _doubling_parent[0][v]=_parent[v];
      }
      for(int k=0;k<K-1;k++){
        for(int v=0;v<_V;v++){
          if(_doubling_parent[k][v]<0){
            _doubling_parent[k+1][v]=-1;
          }else{
            _doubling_parent[k+1][v]=_doubling_parent[k][_doubling_parent[k][v]];
          }
        }
      }
    }
  public:
    Tree(){}
    Tree(int V,int root=0):_V(V),_root(root){
      _Graph.resize(_V);
    }
    Tree(const std::vector<std::vector<int>>& Graph,int root=0):_V(Graph.size()),_root(root){
      _Graph.resize(_V);
      for(int v=0;v<_V;v++){
        _Graph.reserve(Graph[v].size());
        for(int to:Graph[v]){
          _Graph[v].emplace_back(Edge(to,1));
        }
      }
    }
    Tree(const std::vector<std::vector<std::pair<int,long long>>>& Graph,int root=0):_V(Graph.size()),_root(root){
      _Graph.resize(_V);
      for(int v=0;v<_V;v++){
        _Graph.reserve(Graph[v].size());
        for(std::pair<int,long long> e:Graph[v]){
          _Graph[v].emplace_back(Edge(e.first,e.second));
        }
      }
    }
    void add_edge(int s,int t,long long c=1){
      _Graph[s].emplace_back(Edge(t,c));
      _Graph[t].emplace_back(Edge(s,c));
    }
    void search_parent_and_depth_and_distance(){
      if(is_searched_parent_and_depth_and_distance){
        return;
      }
      is_searched_parent_and_depth_and_distance=true;
      _parent.resize(_V);
      _depth.resize(_V);
      _distance.resize(_V);
      _parent_and_depth_and_distance(_root,-1,0,0);
    }
    long long LCA(int u,int v){
      if(!is_init_lca){
        _LCA_init();
      }
      if(_depth[u]<_depth[v]){
        std::swap(u,v);
      }
      int K=_doubling_parent.size();
      for(int k=0;k<K;k++){
        if((_depth[u]-_depth[v])>>k&1){
          u=_doubling_parent[k][u];
        }
      }
      if(u==v){
        return u;
      }
      for(int k=K-1;k>=0;k--){
        if(_doubling_parent[k][u]!=_doubling_parent[k][v]){
          u=_doubling_parent[k][u];
          v=_doubling_parent[k][v];
        }
      }
      return _doubling_parent[0][u];
    }
    long long get_distance(int u,int v){
      if(!is_init_lca){
        _LCA_init();
      }
      return _distance[u]+_distance[v]-2*_distance[LCA(u,v)];
    }
    bool is_on_path(int u,int v,int p){
      if(!is_init_lca){
        _LCA_init();
      }
      return get_distance(u,p)+get_distance(v,p)==get_distance(u,v);
    }
};
