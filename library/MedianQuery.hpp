#pragma once
#include <set>
#include <vector>
#include <assert.h>
#include <iostream>

template <typename T> class MedianQuery{
  private:
    int _size;
    double _median;
    std::multiset<T> small;
    std::multiset<T> large;
  public:
    MedianQuery(){
      _size=0;
    }
    
    MedianQuery(std::vector<T> vec){
      _size=vec.size();
      for(const T& v:vec){
        add(v);
      }
    }
    
    ~MedianQuery(){
      _size=0;
      small.clear();
      large.clear();
    }

    void add(T x){
      if(_size==0){
        _median=x;
      }else if(_size&1==1){
        if(_median<x){
          small.insert(_median);
          large.insert(x);
        }else{
          small.insert(x);
          large.insert(_median);
        }
      }else{
        T small_max=*small.rbegin();
        T large_min=*large.begin();
        if(small_max<=x && x<=large_min){
          _median=x;
        }else if(x<small_max){
          _median=small_max;
          small.erase(small_max);
          small.insert(x);
        }else{
          _median=large_min;
          large.erase(large_min);
          large.insert(x);
        }
      }
      ++_size;
      return;
    }

    void update(std::vector<T> vec){
      for(const T& v: vec){
        add(v);
      }
      return;
    }
    
    double get(){
      assert(_size>0);
      if(_size&1==1){
        return _median;
      }else{
        return ((double)(*small.rbegin())+(double)(*large.begin()))/2.0;
      }
    }

    void erase(T x){
      assert(_size>0);
      if(_size&1==1){
        if(_median==x){
          --_size;
        }else if(_median>x){
          assert(small.find(x)!=small.end());
          --_size;
          small.erase(x);
          small.insert(_median);
        }else{
          assert(large.find(x)!=large.end());
          --_size;
          large.erase(x);
          large.insert(_median);
        }
      }else{
        T small_max=*small.rbegin();
        T large_min=*large.begin();
        assert(x<=small_max || large_min<=x);
        if(x<=small_max){
          assert(small.find(x)!=small.end());
          --_size;
          small.erase(x);
          _median=large_min;
          large.erase(large_min);
        }else if(x>=large_min){
          assert(large.find(x)!=large.end());
          --_size;
          large.erase(x);
          _median=small_max;
          small.erase(small_max);
        }
      }
      return;
    }

    void debug(){
      std::cout<<"small\n";
      for(auto i:small){
        std::cout<<i<<" ";
      }
      std::cout<<"\nlarge\n";
      for(auto i:large){
        std::cout<<i<<" ";
      }
      std::cout<<"\n";
    }
};
