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
    std::vector<long long> count_num;
    std::vector<long long> accum;
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
      count_num.resize(S.size());
      accum.resize(S.size()+1);
      tree[0].length=-1;
      tree[0].index=0;
      tree[1].length=0;
      tree[1].index=0;
      for(int i=0;i<(int)S.size();i++){
        _add(S[i]);
        count_num[i]=tree[mx].num;
        accum[i+1]=accum[i]+count_num[i];
      }
    }
    // Sに含まれる回文の個数
    // 1文字を除く場合は|S|を引けばよい
    long long count_all(){
      return accum[S.size()];
    }
    // S[pos] が最後尾となる回文の個数
    long long get(int pos){
      return count_num[pos];
    }
    // S[0~pos] が最後尾となる回文の個数
    long long get_accum(int pos){
      return accum[pos+1];
    }
};

