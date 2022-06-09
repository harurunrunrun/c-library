#include <unordered_map>
#include <string>
#include <vector>
/*
thanks for https://miti-7.hatenablog.com/entry/2016/03/14/195721
*/
class PalindromicTree{
  private:
    struct Node{
      std::unordered_map<char,long long> next;
      long long length=0;
      long long index=0;
      long long num=0;
    };
    std::string S;
    std::vector<Node> tree;
    long long last=1;
    long long mx=1;
    bool _add(long long pos){
      char now=S[pos];
      long long A=mx;
      while(true){
        long long len=tree[A].length;
        if(pos-1-len>=0 && S[pos-1-len]==now){
          break;
        }
        A=tree[A].index;
      }
      if(tree[A].next[now]!=0){
        mx=tree[A].next[now];
        return false;
      }
      mx=++last;
      Node& node=tree[last];
      node.length=tree[A].length+2;
      tree[A].next[now]=last;
      if(node.length==1){
        node.index=1;
        node.num=1;
        return true;
      }
      long long B=A;
      while(true){
        B=tree[B].index;
        long long len=tree[B].length;
        if(pos-1-len>=0 && S[pos-1-len]==now){
          break;
        }
      }
      node.index=tree[B].next[now];
      node.now=tree[node.index].num+1;
      return true;
    }
  public:
    PalindromicTree(){}
    PalindromicTree(const string& str):S(str){
      tree.resize(S.size()+2);
      tree[0].length=-1;
      tree[0].index=0;
      tree[1].length=0;
      tree[1].index=0;
      for(int i=0;i<(int)S.size();i++){
        _add(S[i]);
      }
    }
    long long count_all(){
      long long res=0;
      for(int i=0;i<(int)S.size();i++){
        res+=tree[mx].num;
      }
      return res;
    }
    long long count_all_ignore_1(){
      return count_all()-S.size();
    }
    

};