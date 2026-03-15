#include <vector>
#include <iostream>
#include <utility>
#include <numeric>
#include <limits>

struct Range_Edge_Graph{
    private:
    int _n;
    int size;
    int _log;
    std::vector<std::vector<std::pair<int, long long>>> G;
    constexpr unsigned bitceil(unsigned x){
        if(x<=1){
            return 1;
        }
        x--;
        for(int shift=1;shift<std::numeric_limits<unsigned>::digits;shift<<=1){
            x|=(x>>shift);
        }
        return x+1;
    }
    constexpr int countr_zero(unsigned x){
        if(x==0){
            return std::numeric_limits<unsigned>::digits;
        }
        int count=0;
        while((x&1)==0){
            count++;
            x>>=1;
        }
        return count;
    }
    public:
    Range_Edge_Graph(int N):_n(N){
        size=(int)bitceil((unsigned)N);
        _log=countr_zero(size);
        G.resize(3*size);
        for(int i=1;2*i+1<size;i++){
            G[size+i].push_back(std::make_pair(size+2*i,0));
            G[size+i].push_back(std::make_pair(size+2*i+1,0));
            G[2*size+2*i].push_back(std::make_pair(2*size+i,0));
            G[2*size+2*i+1].push_back(std::make_pair(2*size+i,0));
        }
        if(size>1){
            for(int i=size>>1;i<size;i++){
                G[size+i].push_back(std::make_pair(2*i-size,0));
                G[size+i].push_back(std::make_pair(2*i+1-size,0));
                G[2*i-size].push_back(std::make_pair(2*size+i,0));
                G[2*i+1-size].push_back(std::make_pair(2*size+i,0));
            }
        }
    }
    void add_edge(int from, int to, long long weight){
        G[from].push_back(std::make_pair(to,weight));
    }
    void add_range_edge(int from, int l_to, int r_to, long long weight){
        l_to+=size;
        r_to+=size;
        if(l_to&1){
            G[from].push_back(std::make_pair(l_to-size,weight));
            l_to++;
        }
        if(r_to&1){
            r_to--;
            G[from].push_back(std::make_pair(r_to-size,weight));
        }
        l_to>>=1;
        r_to>>=1;
        while(l_to<r_to){
            if(l_to&1){
                G[from].push_back(std::make_pair(size+l_to,weight));
                l_to++;
            }
            if(r_to&1){
                r_to--;
                G[from].push_back(std::make_pair(size+r_to,weight));
            }
            l_to>>=1;
            r_to>>=1;
        }
    }
    void add_range_edge_reverse(int l_from, int r_from, int to, long long weight){
        l_from+=size;
        r_from+=size;
        if(l_from&1){
            G[l_from-size].push_back(std::make_pair(to,weight));
            l_from++;
        }
        if(r_from&1){
            r_from--;
            G[r_from-size].push_back(std::make_pair(to,weight));
        }
        l_from>>=1;
        r_from>>=1;
        while(l_from<r_from){
            if(l_from&1){
                G[2*size+l_from].push_back(std::make_pair(to,weight));
                l_from++;
            }
            if(r_from&1){
                r_from--;
                G[2*size+r_from].push_back(std::make_pair(to,weight));
            }
            l_from>>=1;
            r_from>>=1;
        }
    }
    void add_range_edge_both(int l_from, int r_from, int l_to, int r_to, long long weight){
        int hub1=G.size();
        int hub2=hub1+1;
        G.push_back(std::vector<std::pair<int,long long>>());
        G.push_back(std::vector<std::pair<int,long long>>());
        add_range_edge(hub2,l_to,r_to,0);
        add_range_edge_reverse(l_from,r_from,hub1,0);
        add_edge(hub1,hub2,weight);
    }
    std::vector<std::vector<std::pair<int,long long>>> build(){
        return G;
    }
};
