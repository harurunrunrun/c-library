vector<ll> topological_sort(vector<vector<ll>>& G){
    vector<ll> res;
    ll N=G.size();
    res.reserve(N);
    vector<ll> indegree(N);
    for(ll i=0;i<N;i++){
        for(const ll& to:G[i]){
            indegree[to]++;
        }
    }
    queue<ll> que;
    for(ll i=0;i<N;i++){
        if(indegree[i]==0){
            que.push(i);
        }
    }
    while(!que.empty()){
        ll now=que.front();
        que.pop();
        res.push_back(now);
        for(const ll& to:G[now]){
            indegree[to]--;
            if(indegree[to]==0){
                que.push(to);
            }
        }
    }
    return res;
}
