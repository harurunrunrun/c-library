#include <vector>

struct Doubling{
    int _log=1;
    std::vector<std::vector<int>> doubling;
    Doubling(std::vector<int> next, int max_size){
        while((1<<(_log))<=max_size){
            _log++;
        }
        doubling=std::vector<std::vector<int>>(_log,std::vector<int>(next.size()));
        for(int i=0;i<(int)next.size();i++){
            doubling[0][i]=next[i];
        }
        for(int k=0;k<_log-1;k++){
            for(int i=0;i<(int)next.size();i++){
                doubling[k+1][i]=doubling[k][doubling[k][i]];
            }
        }
    }
    int query(int now, int c){
        for(int k=0;c>0;k++){
            if(c&1){
                now=doubling[k][now];
            }
            c>>=1;
        }
        return now;
    }
};
