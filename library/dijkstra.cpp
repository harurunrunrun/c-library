//蟻本より
#include <vector>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;


typedef struct edge{
	int to;
	int cost;
}Edge;
typedef pair<int,int> P;

long long INF=1000000000000000000;
int V;
vector<Edge> G[100000];
long long d[100000];

void dijkstra(int s){
  priority_queue<P,vector<P>,greater<P>> que;
	fill(d,d+V,INF);
	d[s]=0;
	que.push(P(0,s));
	while(!que.empty()){
		P p=que.top();que.pop();
		int v=p.second;
		if(d[v]<p.first)continue;
		for(unsigned int i=0;i<G[v].size();i++){
		  Edge e=G[v][i];
			if(d[e.to]>d[v]+e.cost){
			  d[e.to]=d[v]+e.cost;
				que.push(P(d[e.to],e.to));
			}
		}
	}
}


int main(){
  int E,s,st,t,w;
	cin>>V>>E>>s;
	for(int i=0;i<E;i++){
	  cin>>st>>t>>w;
		G[st].push_back({t,k});
		//G[t].push_back({st,k});//有向のときはいれない。
	}
	dijkstra(s);
	for(int i=0;i<V;i++){
		if(d[i]==INF)cout<<"INF"<<endl;
		else cout<<d[i]<<endl;
	}
	return 0;
}
