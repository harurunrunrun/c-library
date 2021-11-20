#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <assert.h>
#include <atcoder/segtree>

std::pair<int,int> _max(std::pair<int,int> a,std::pair<int,int> b){
  return a > b ? a : b;
}

std::pair<int,int> _e(){
  return std::make_pair(-1,-1);
}

class RangePriorityQueue{
  private:
    std::vector<std::priority_queue<int>> _vec;
    atcoder::segtree<std::pair<int,int>,_max,_e> _seg;
    // val,index
  public:
    ContinuousPriorityQueue(int maxsize=200000){
      _seg=atcoder::segtree<std::pair<int,int>,_max,_e>(maxsize);
      _vec.reserve(maxsize);
    }
    int top(int l,int r){
      assert(0<=l && l<_vec.size() && 0<=r && r<=_vec.size());
      return _seg.prod(l,r).first;
    }
    int pop(int l,int r){
      assert(0<=l && l<_vec.size() && 0<r && r<=_vec.size());
      std::pair<int,int> max_p=_seg.prod(l,r);
      if(max_p==_e()){
        return -1;
      }
      int res=max_p.first;
      _vec[max_p.second].pop();
      if(_vec[max_p.second].empty()){
        _seg.set(max_p.second,_e());
      }else{
        _seg.set(max_p.second,std::make_pair(_vec[max_p.second].top(),max_p.second));
      }
      return res;
    }
    void add(int index,int val){
      assert(0<=index && index<_vec.size());
      _vec[index].push(val);
      _seg.set(index,std::make_pair(_vec[index].top(),index));
      return;
    }
    void add_back(int val){
      assert(!_vec.empty());
      _vec.back().push(val);
      _seg.set(_vec.size()-1,std::make_pair(_vec.back().top(),_vec.size()-1));
      return;
    }
    void push_back(){
      _vec.push_back(std::priority_queue<int>());
      return;
    }
    int size(){
      return _vec.size();
    }
    bool empty(int index){
      return _vec[index].empty();
    }
    bool range_empty(int l,int r){
      return _seg.prod(l,r)==_e();
    }
    void _print(){
      for(int i=0;i<_vec.size();i++){
        priority_queue<int> pq=_vec[i];
        while(!pq.empty()){
          cerr<<pq.top()<<" ";
          pq.pop();
        }cerr<<endl;
      }
    }
};
