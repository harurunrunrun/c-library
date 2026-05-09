#include <vector>
#include <set>
#include <algorithm>
#include <concepts>
#include <iterator>

// v の中で x 以上の最初のイテレータを返す
template<class T, class internal>
auto find_geq(T& v, const internal& x)->decltype(v.begin()){
    if constexpr (requires {v.lower_bound(x);}){
        return v.lower_bound(x);
    }else{
        return std::lower_bound(v.begin(),v.end(),x);
    }
}

// v の中で xより大きい最初のイテレータを返す
template<class T, class internal>
auto find_greater(T& v, const internal& x)->decltype(v.begin()){
    if constexpr (requires {v.upper_bound(x);}){
        return v.upper_bound(x);
    }else{
        return std::upper_bound(v.begin(),v.end(),x);
    }
}

// v の中で x 以下の最後のイテレータを返す
template<class T, class internal>
auto find_leq(T& v, const internal& x)->decltype(v.begin()){
    auto it=[&]{
        if constexpr (requires {v.upper_bound(x);}){
            return v.upper_bound(x);
        }else{
            return std::upper_bound(v.begin(),v.end(),x);
        }
    }();
    if(it==v.begin()){
        return v.end();
    }else{
        return std::prev(it);
    }
}

// v の中で x 未満の最後のイテレータを返す
template<class T, class internal>
auto find_less(T& v, const internal& x)->decltype(v.begin()){
    auto it=[&]{
        if constexpr (requires {v.lower_bound(x);}){
            return v.lower_bound(x);
        }else{
            return std::lower_bound(v.begin(),v.end(),x);
        }
    }();
    if(it==v.begin()){
        return v.end();
    }else{
        return std::prev(it);
    }
}

