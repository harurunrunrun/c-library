#include <vector>
#include <algorithm>
#include <stack>
#include <utility>

/*
reference:
https://nyaannyaan.github.io/library/data-structure/rollback-union-find.hpp.html
https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
*/

struct RollbackDsu{
  private:
    std::vector<int> data;
    std::stack<std::pair<int,int>> history;
    int snap=0;
  public:
    RollbackDsu(int sz){
      data.resize(sz,-1);
    }

    int leader(int x){
      if(data[x]<0){
        return x;
      }
      return leader(data[x]);
    }

    bool merge(int x,int y){
      x=leader(x);
      y=leader(y);
      if(x==y){
        return false;
      }
      history.emplace(x,data[x]);
      history.emplace(y,data[y]);
      if(data[x]>data[y]){
        std::swap(x,y);
      }
      data[x]+=data[y];
      data[y]=x;
      return true;
    }
    
    bool same(int x,int y){
      return leader(x)==leader(y);
    }

    int size(int x){
      return -data[leader(x)];
    }

    void undo(){
      data[history.top().first]=history.top().second;
      history.pop();
      data[history.top().first]=history.top().second;
      history.pop();
    }

    int get_state(){
      return history.size()>>1;
    }

    void snapshot(){
      snap=get_state();
    }

    void rollback(int state=-1){
      if(state==-1){
        state=snap;
      }
      state<<=1;
      while(state<history.size()){
        undo();
      }
    }

    std::vector<std::vector<int>> groups() {
      std::vector<int> leader_buf(data.size()), group_size(data.size());
      for(int i=0;i<data.size();i++){
        leader_buf[i]=leader(i);
        group_size[leader_buf[i]]++;
      }
      std::vector<std::vector<int>> result(data.size());
      for(int i=0;i<data.size();i++){
        result[i].reserve(group_size[i]);
      }
      for(int i=0;i<data.size();i++){
        result[leader_buf[i]].push_back(i);
      }
      result.erase(
        std::remove_if(result.begin(),result.end(),
          [&](const std::vector<int>& v){ return v.empty();}),
            result.end());
      return result;
    }

};
