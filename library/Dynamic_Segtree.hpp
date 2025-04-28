#ifndef ATCODER_DYNAMIC_SEGTREE_HPP
#define ATCODER_DYNAMIC_SEGTREE_HPP 1

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
#include <iostream>


namespace atcoder {

#if __cplusplus >= 201703L

template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");

#else

template <class S, S (*op)(S, S), S (*e)()> struct segtree {

#endif
  private:
    struct Node;
  public:
    explicit segtree(long long n) : _n(n) {
        size = 1;
        while(size<_n){
            size <<= 1;
        }
        root = new Node(size/2);
    }

    void set(long long p, S x) {
        assert(0 <= p && p < _n);
        Node* cur = access(p);
        cur->val = x;
        if(cur->parent == nullptr){
            return;
        }
        cur = cur->parent; 
        while (cur->parent != nullptr){
            update(cur);
            cur = cur->parent;
        }
        update(cur);
    }

    S get(long long p) {
        assert(0 <= p && p < _n);
        Node* cur = access(p);
        return cur->val;
    }

    S prod(long long l, long long r) {
        assert(0 <= l && l <= r && r <= _n);
        if(l == r){
            return e();
        }
        if(l+1 == r){
            return get(l);
        }
        Node* cur = root;
        long long left = 0, right = size;
        while(1){
            if(r <= cur->index){
                if(cur->left == nullptr){
                    return e();
                }
                right = cur->index;
                cur = cur->left;
            }else if(cur->index <= l){
                if(cur->right == nullptr){
                    return e();
                }
                left = cur->index;
                cur  = cur->right;
            }else{
                break;
            }
        }
        S sm = e();
        // [l,index)
        if(cur->left != nullptr){
            Node* tmpl = access(l);
            sm = op(sm, tmpl->val);
            tmpl = tmpl->parent;
            while(tmpl != cur){
                if(l < tmpl->index){
                    if(tmpl->right != nullptr){
                        sm = op(sm, tmpl->right->val);
                    }
                }
                tmpl = tmpl->parent;
            }
        }
        // [index,r)
        if(cur->right != nullptr){
            Node* tmpr = cur->right;
            Node* endr = access(r-1);
            while(tmpr != endr){
                if(tmpr->index <= r - 1){
                    if(tmpr->left != nullptr){
                        sm = op(sm, tmpr->left->val);
                        // std::cerr<<tmpr->left->val<<std::endl;
                    }
                    if(tmpr->right != nullptr){
                        tmpr = tmpr->right;
                    }
                }else if(tmpr->left != nullptr){
                    tmpr = tmpr->left;
                }else{
                    break;
                }
            }
            sm = op(sm, endr->val);
        }
        return sm;
    }

    S all_prod() { return root->val; }

    void debug(){
        debug(root);
    }
    void debug(Node* node){
        if(node->left != nullptr || node->right != nullptr){
            std::cerr<<node->index<<" "<<node->val<<std::endl;
        }
        if(node->left != nullptr){
            debug(node->left);
        }
        if(node->right != nullptr){
            debug(node->right);
        }
    }

  private:
    int _n, size;
    struct Node{
        S val;
        long long index;
        Node* left;
        Node* right;
        Node* parent;
        Node(long long index):index(index),left(nullptr),right(nullptr),parent(nullptr),val(e()){}
    };
    Node* root;
    Node* access(long long p){
        long long left = 0;
        long long right = size;
        Node* cur = root;
        while(right - left > 1){
            if(p < cur->index){
                right = cur->index;
                if(cur->left == nullptr){
                    cur->left = new Node((left + right) / 2);
                    cur->left->parent = cur;
                }
                cur = cur->left;
            }else{
                left = cur->index;
                if(cur->right == nullptr){
                    cur->right = new Node((left + right) / 2);
                    cur->right->parent = cur;
                }
                cur = cur->right;
            }
        }
        return cur;
    }
    void update(Node* cur) { 
        if(cur == nullptr){
            return;
        }
        assert(cur->left != nullptr || cur->right != nullptr);
        if(cur->left != nullptr && cur->right != nullptr){
            cur->val = op(cur->left->val, cur->right->val);
        }else if(cur->left != nullptr){
            cur->val = cur->left->val;
        }else if(cur->right != nullptr){
            cur->val = cur->right->val;
        }
    }
};

}  // namespace atcoder

#endif  // ATCODER_DYNAMIC_SEGTREE_HPP
