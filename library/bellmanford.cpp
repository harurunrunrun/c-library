#include <iostream>
#include <vector>
using namespace std;

typedef struct edge{
  int from,to,cost;
}Edges;

long long INF=1000000000000000000;
int V;
vector<Edges> G;
vector<long long> d(1000000,INF);

bool bell(int start){
  int size=G.size();
  bool f;
  d[start]=0;
  for(int i=0;i<V;i++){
    f=true;
    for(int j=0;j<size;j++){
      Edges e=G.at(j);
      if(d.at(e.to)>d.at(e.from)+e.cost){
        d.at(e.to)=d.at(e.from)+e.cost;
        f=false;
      }
    }
    if(f)break;
    if(i==V-1)return false;
  }
  return true;
}

int main(){
  int E,start,from,to,cost;
  cin>>V>>E>>start;
  for(int i=0;i<E;i++){
    cin>>from>>to>>cost;
    G.push_back({from,to,cost});
  }
  return 0;
}
