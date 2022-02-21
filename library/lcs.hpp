#include <vector>
#include <string>
#include <algorithm>

template<typename Ty>
std::vector<Ty> Lcs(std::vector<Ty> S,std::vector<Ty> T){
  std::vector<std::vector<int>> dp(S.size()+1,std::vector<int>(T.size()+1));
  for(unsigned int i=1;i<S.size()+1;i++){
    for(unsigned int j=1;j<T.size()+1;j++){
      if(S[i-1]==T[j-1]){
        dp[i][j]=dp[i-1][j-1]+1;
      }else{
        dp[i][j]=std::max(dp[i-1][j],dp[i][j-1]);
      }
    }
  }
  int length=dp[S.size()][T.size()];
  int x=S.size();
  int y=T.size();
  std::vector<Ty> ans;
  ans.reserve(length);
  while(length>0){
    if(S[x-1]==T[y-1]){
      ans.emplace_back(S[x-1]);
      x--;
      y--;
      length--;
    }else if(dp[x][y]==dp[x-1][y]){
      x--;
    }else{
      y--;
    }
  }
  std::reverse(ans.begin(),ans.end());
  return ans;
}


std::string Lcs(std::string S,std::string T){
  std::vector<std::vector<int>> dp(S.size()+1,std::vector<int>(T.size()+1));
  for(unsigned int i=1;i<S.size()+1;i++){
    for(unsigned int j=1;j<T.size()+1;j++){
      if(S[i-1]==T[j-1]){
        dp[i][j]=dp[i-1][j-1]+1;
      }else{
        dp[i][j]=std::max(dp[i-1][j],dp[i][j-1]);
      }
    }
  }
  int length=dp[S.size()][T.size()];
  int x=S.size();
  int y=T.size();
  std::string ans;
  ans.reserve(length);
  while(length>0){
    if(S[x-1]==T[y-1]){
      ans.append(1,S[x-1]);
      x--;
      y--;
      length--;
    }else if(dp[x][y]==dp[x-1][y]){
      x--;
    }else{
      y--;
    }
  }
  std::reverse(ans.begin(),ans.end());
  return ans;
}
