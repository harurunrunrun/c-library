#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
struct Dijkstra{
  private:
    long long INF=1000000000000000000LL;
    std::vector<std::vector<std::pair<long long,long long>>> G;
    int V;
    inline void _add(long long s,long long t,long long c){
      G[s].emplace_back(std::make_pair(t,c));
    }
  public:
    Dijkstra(int N):V(N) {
      G.resize(V);
    }
    void add1(long long s,long long t,long long c){
      _add(s,t,c);
    }
    void add2(long long s,long long t,long long c){
      _add(s,t,c);
      _add(t,s,c);
    }
    std::vector<long long> run(long long s){
      std::vector<long long> res(V,INF);
      std::priority_queue<std::pair<long long,long long>,std::vector<std::pair<long long,long long>>,std::greater<std::pair<long long,long long>>> que;
      res[s]=0;
      que.push(std::make_pair(0,s));
      while(!que.empty()){
        std::pair<long long,long long> p=que.top();
        que.pop();
        long long v=p.second;
        if(res[v]<p.first){
          continue;
        }
        for(const std::pair<long long,long long>& e:G[v]){
          if(res[e.first]>res[v]+e.second){
            res[e.first]=res[v]+e.second;
            que.push(std::make_pair(res[e.first],e.first));
          }
        }
      }
      return res;
    }
};
