#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <utility>
#include <assert.h>
#include <tuple>
#include <algorithm>

long long NODE_NO=0;
enum {
    NOTFOUND = 0xFFFFFFFFFFFFFFFFLLU
};
class Node{
  public:
    long long no;
    long long num;
    long long ones;
    Node *left;
    Node *right;
    long long balance;

    long long bits;
    long long bits_size;

    bool is_leaf;

    Node(long long bits,long long bits_size,bool is_leaf):
      no(NODE_NO++),num(0),ones(0),bits(bits),is_leaf(is_leaf),left(nullptr),right(nullptr),balance(0){}
    
    bool is_valid_node(){
      if(is_leaf){
        if(num!=0 || ones!=0 || left!=nullptr || right!=nullptr){
          return false;
        }
      }else if(num==0 || left==nullptr || right==nullptr || bits!=0 || bits_size!=0 || ones>num){
        return false;
      }
      return true;
    }
  std::string info(){
    std::stringstream ss;
    ss<<"No:"<<std::to_string(this->no)<<"\n";
    if(is_leaf){
      ss<<"size:"<<std::to_string(this->bits_size)<<"\n";
      for(long long i=0;i<bits_size;i++){
        ss<<std::to_string((bits>>i)&1LL);
      }
    }else{
      ss<<"num:"<<std::to_string(this->num)<<"ones:"<<std::to_string(this->ones)<<"\n";
    }
    return ss.str();
  }
};

class DynamicBitvector{
  public:
    Node* root;
    long long size;
    long long num_one;
    const long long bits_size_limit=32;

    DynamicBitvector():root(nullptr),size(0),num_one(0){}

    DynamicBitvector(std::vector<long long>& v):root(nullptr),size(0),num_one(0){
      if(v.size()==0){
        return;
      }
      std::deque<std::pair<Node*,long long>> leaves;
      for(int i=0;i<v.size();i+=this->bits_size_limit){
        long long bits=0;
        const long long bits_size=std::min(this->bits_size_limit,v.size()-i);
        for(long long j=0;j<bits;j++){
          assert(v.at(i+j)==0 || v.at(i+j)==1);
          if(v.at(i+j)==1){
            bits|=1<<j;
          }
        }
        leaves.emplace_back(std::make_pair(new Node(bits,bits_size,true),bits_size));
      }

      std::deque<std::tuple<Node*,long long,long long,long long>> nodes;
      while(!leaves.empty()){
        const auto node=leaves.front().first;
        const auto bits_size=leaves.front().second;
        leaves.pop_front();
        nodes.emplace_back(std::make_tuple(node,bits_size,popCount(node->this),0));
      }
      
      while(nodes.size()>1){
        std::deque<std::tuple<Node*,long long,long long,long long>> next_nodes;
        while(!nodes.empty()){
          if(nodes.size()==1){
            nodes.emplace_back(next_nodes.back());
            next_nodes.pop_back();
          }
          Node *left_node;
          long long left_num,left_ones,left_height;
          std::tie(left_node,left_num,left_ones,left_height)=nodes.front();
          nodes.pop_front();

          Node *right_node;
          long long right_num,right_ones,right_height;
          std::tie(right_node,right_num,right_ones,right)=nodes.front();
          nodes.pop_front();

          const auto internal_node=new Node(0,0,false);
          internal_node->num=left_num;
          internal_node->ones=left_ones;
          internal_node->left=left_node;
          internal_node->right=right_node;
          internal_node->balance=right_height-left_height;

          next_nodes.emplace_back(std::make_tuple(internal_node,left_num+right_num,left_ones+right_ones,std::max(left_height,right_height)+1));
        }
        nodes=next_nodes;
      }
      long long height;
      std::tie(this->root,this->size,this->num_one,height)=nodes.front();
      nodes.pop_front();
      assert(this->size==v.size());
    }

    long long access(long long pos){
      assert(pos<this->size);
      return access(this->root,pos);
    }

    long long rank(long long bit,long long pos){
      assert(bit==0 || bit==1);
      assert(pos<=this->size);
      if(bit){
        return rank1(this->root,pos,0);
      }else{
        return pos-rank1(this->root,pos,0);
      }
    }

    long long select(long long bit,long long rank){
      assert(bit==0 || bit==1);
      assert(rank>0);
      if(bit==0 && rank>this->size-this->num_one){
        return NOTFOUND;
      }
      if(bit==1 && rank>this->num_one){
        return NOTFOUND;
      }
      if(bit){
        return select1(this->root,0,rank);
      }else{
        return select0(this->root,0,rank);
      }
    }

    void insert(long long pos,long long bit){
      assert(bit==0 || bit==1);
      assert(pos<=this->size);
      if(root==nullptr){
        root=new Node(bit,1,true);
      }else{
        insert(this->root,nullptr,bit,pos,this->size);
      }
      this->size++;
      this->num_one+=(bit==1);
      return;
    }

    void push_back(long long bit){
      assert(bit==0 || bit==1);
      this->insert(this->size,bit);
      return;
    }

    void erase(long long pos){
      assert(pos<this->size);
      long long bit=this->remove(this->root,nullptr,pos,this->size,0,true).first;
      this->size--;
      this->num_one-=(bit==1);
      return;
    }
    
    void update(long long pos,long long bit){
      assert(bit==0 || bit==1);
      assert(pos<this->size);
      if(bit==1){
        this->bitset(pos);
      }else{
        this->bitclear(pos);
      }
      return;
    }
    
    void bitset(long long pos){
      assert(pos<this->size);
      bool flip=bitset(this->root,pos);
      this->num_one+=flip
      return;
    }

    void bitclear(long long pos){
      assert(pos<this->size);
      bool flip=bitset(this->root,pos);
      this->num_one-=flip;
      return;
    }

  private:
    long long access(const Node *node,long long pos){
      if(node->is_leaf){
        assert(pos<=2*this->bits_size_limit);
        return (node->bits>>pos)&1LL;
      }
      if(pos<node->num){
        return this->access(node->left,pos);
      }else{
        return this->access(node->right,pos-node->num);
      }
    }

    long long rank1(const Node *node,long long pos,long long ones){
      if(node->is_leaf){
        assert(node->bits_size>=pos);
        const long long mask=(1LL<<pos)-1;
        return ones+popCount(node->bits&mask);
      }
      if(pos<node->num){
        return this->rank1(node->left,pos,ones);
      }else{
        return this->rank1(node->right,pos-node->num,ones+node->ones);
      }
    }

    long long select1(const Node *node,long long pos,long long rank){
      if(node->is_leaf){
        return pos+this->selectInBlock(node->bits,rank)+1;
      }
      if(rank<=node->ones){
        return this->select1(node->left,pos,rank);
      }else{
        return this->select1(node->right,pos+node->num,rank-node->ones);
      }
    }

    long long select0(const Node *node,long long pos,long long rank){
      if(node->is_leaf){
        return pos+this->selectInBlock(node->bits,rank)+1;
      }
      if(rank<=(node->num-node->ones)){
        return this->select0(node->left,pos,rank);
      }else{
        return this->select0(node->right,pos+node->num,rank-(node->num-node->ones));
      }
    }

    long long selectInBlock(long long bits,long long rank){
      const long long x1=bits-((bits&0xAAAAAAAAAAAAAAAALLU)>>1LL);
      const long long x2=(x1&0x3333333333333333LLU)+((x1>>2LL)&0x3333333333333333LLU);
      const long long x3=(x2+(x2>>4LL))&0x0F0F0F0F0F0F0F0FLLU;

      long long pos=0;
      for(;;pos+=8){
        const long long rank_next=(x3>>pos)&0xFFLLU;
        if(rank<=rank_next){
          break;
        }
        rank-=rank_next;
      }
      const long long v2=(x2>>pos)&0xFLLU;
      if(rank>v2){
        rank-=v2;
        pos+=4;
      }
      const long long v1=(x1>>pos)&0x3LLU;
      if(rank>v1){
        rank-=v1;
        pos+=2;
      }
      const long long v0=(bits>>pos)&0x1LLU;
      if(v0<rank){
        pos+=1;
      }
      return pos;
    }
    
    long long insert(Node *node, Node *parent, long long bit, long long pos, long long len) {
      assert(bit==0||bit==1);
      if(node->is_leaf) {
        assert(pos <= 2 * this->bits_size_limit);
        const long long up_mask = (((long long)1 << (len - pos)) - 1) << pos;
        const long long up = (node->bits & up_mask);
        const long long down_mask = ((long long)1 << pos) - 1;
        const long long down = node->bits & down_mask;
        node->bits = (up << (long long)1) | (bit << pos) | down;
        node->bits_size++;
        assert(node->bits_size == len + 1);
        if (len + 1 >= 2 * bits_size_limit) {
          this->splitNode(node, len + 1); 
          return 1;
        }
        return 0;
      }
      if (pos < node->num) {
        const long long diff = this->insert(node->left, node, bit, pos, node->num);
        node->num += 1;
        node->ones += (bit == 1);
        return achieveBalance(parent, node, diff, 0);
      } else {
        const long long diff = this->insert(node->right, node, bit, pos - node->num, len - node->num);
        return achieveBalance(parent, node, 0, diff);
      }
    }
    
    std::pair<long long, long long> remove(Node *node, Node *parent, long long pos, long long len, long long ones, bool allow_under_flow) {
      if (node->is_leaf) {
        if (node != this->root && len <= bits_size_limit / 2 && not allow_under_flow) {
          return std::make_pair(NOTFOUND, 0);
        }
        assert(pos <= 2 * this->bits_size_limit);
        assert(pos < len);
        const long long bit = (node->bits >> pos) & (long long)1;
        const long long up_mask = (((long long)1 << (len - pos - 1)) - 1) << (pos + 1);
        const long long up = (node->bits & up_mask);
        const long long down_mask = ((long long)1 << pos) - 1;
        const long long down = node->bits & down_mask;
        node->bits = (up >> (long long)1) | down;
        node->bits_size--;
        assert(node->bits_size == len - 1);
        return std::make_pair(bit, 0);
      }
      if (pos < node->num) {
        const auto bit_diff = this->remove(node->left, node, pos, node->num, node->ones, allow_under_flow);
        if (bit_diff.first == NOTFOUND) {
          return bit_diff;
        }
        node->ones -= (bit_diff.first == 1);
        if (node->num == bits_size_limit / 2) {
          const auto b_d = remove(node->right, node, 0, len - bits_size_limit / 2, 0, false);
          if (b_d.first == NOTFOUND) {
            assert(node->left->is_leaf);
            assert(node->left->bits_size == bits_size_limit / 2 - 1);
            mergeNodes(node->right, 0, len - bits_size_limit / 2, node->left->bits, bits_size_limit / 2 - 1, node->ones, true);
            this->replace(parent, node, node->right);
            return std::make_pair(bit_diff.first, -1);
          }
          assert(node->left->bits_size == bits_size_limit / 2 - 1);
          insert(node->left, node, b_d.first, bits_size_limit / 2 - 1, bits_size_limit / 2 - 1);
          node->ones += (b_d.first == 1);
        }else{
          node->num -= 1;
        }
        const long long diff = achieveBalance(parent, node, bit_diff.second, 0);
        return std::make_pair(bit_diff.first, diff);
      } else {
        const auto bit_diff = this->remove(node->right, node, pos - node->num, len - node->num, ones - node->ones, allow_under_flow);
        if (bit_diff.first == NOTFOUND) {
          return bit_diff;
        }
        ones -= (bit_diff.first == 1);
        if ((len - node->num) == bits_size_limit / 2) {
          const auto b_d = remove(node->left, node, node->num - 1, node->num, 0, false);
          if (b_d.first == NOTFOUND) {
            assert(node->right->is_leaf);
            assert(node->right->bits_size == bits_size_limit / 2 - 1);
            mergeNodes(node->left, node->num, node->num, node->right->bits, bits_size_limit / 2 - 1, ones - node->ones, false);
            this->replace(parent, node, node->left);
            return std::make_pair(bit_diff.first, -1);
          }
          insert(node->right, node, b_d.first, 0, bits_size_limit / 2 - 1);
          node->num -= 1;
          node->ones -= (b_d.first == 1);
        }
        const long long diff = achieveBalance(parent, node, 0, bit_diff.second);
        return std::make_pair(bit_diff.first, diff);
      }
    }
    
    bool bitset(Node *node, long long pos) {
      if (node->is_leaf) {
        assert(pos <= 2 * this->bits_size_limit);
        const long long bit = (node->bits >> pos) & 1;
        if (bit == 1) {
          return false;
        }
        node->bits |= ((long long)1 << pos);
          return true;
      }
      if (pos < node->num) {
        bool flip = this->bitset(node->left, pos);
        node->ones += flip;
        return flip;
      } else {
        return this->bitset(node->right, pos - node->num);
      }
    }
    
    bool bitclear(Node *node, long long pos) {
      if (node->is_leaf) {
        assert(pos <= 2 * this->bits_size_limit);
        const long long bit = (node->bits >> pos) & 1;
        if (bit == 0) {
          return false;
        }
        node->bits &= ~((long long)1 << pos);
        return true;
      }
      if (pos < node->num) {
        const bool flip = this->bitclear(node->left, pos);
        node->ones -= flip;
        return flip;
      } else {
        return this->bitclear(node->right, pos - node->num);
      }
    }
    
    void splitNode(Node *node, long long len) {
      assert(node->is_leaf);
      assert(node->bits_size == len);
      const long long left_size = len / 2;
      const long long left_bits = node->bits & (((long long)1 << left_size) - 1);
      node->left = new Node(left_bits, left_size, true);
      const long long right_size = len - left_size;
      const long long right_bits = node->bits >> left_size;
      node->right = new Node(right_bits, right_size, true);
      node->is_leaf = false;
      node->num = left_size;
      node->ones = this->popCount(left_bits);
      node->bits = 0;
      node->bits_size = 0;
    }
    
    void mergeNodes(Node *node, long long pos, long long len, long long bits, long long s, long long ones, bool left) {
      if (node->is_leaf) {
        if (left) {
          node->bits = (node->bits << s) | bits;
        }else {
          assert(len == node->bits_size);
          node->bits = node->bits | (bits << len);
        }
        node->bits_size += s;
        return;
      }
      if (pos < node->num) {
        node->num += s;
        node->ones += ones;
        mergeNodes(node->left, pos, node->num, bits, s, ones, left);
      }else {
        mergeNodes(node->right, pos, len - node->num, bits, s, ones, left);
      }
    }
    
    long long achieveBalance(Node *parent, Node *node, long long leftHeightDiff, long long rightHeightDiff) {
      assert(-1 <= node->balance && node->balance <= 1);
      assert(-1 <= leftHeightDiff && leftHeightDiff <= 1);
      assert(-1 <= rightHeightDiff && rightHeightDiff <= 1);
      if (leftHeightDiff == 0 && rightHeightDiff == 0) {
        return 0;
      }
      long long heightDiff = 0;
      if ((node->balance <= 0 && leftHeightDiff > 0) || (node->balance >= 0 && rightHeightDiff > 0)) {
        ++heightDiff;
      }
      if ((node->balance < 0 && leftHeightDiff < 0) || (node->balance > 0 && rightHeightDiff < 0)) {
        --heightDiff;
      }
      node->balance += -leftHeightDiff + rightHeightDiff;
      assert(-2 <= node->balance && node->balance <= 2);
      if (node->balance == -2) {
        assert(-1 <= node->left->balance && node->left->balance <= 1);
        if (node->left->balance != 0) {
          heightDiff--;
        }
        if (node->left->balance == 1) {
          replace(node, node->left, rotateLeft(node->left));
        }
        replace(parent, node, rotateRight(node));
      }else if (node->balance == 2) {
        assert(-1 <= node->right->balance && node->right->balance <= 1);
        if (node->right->balance != 0) {
          heightDiff--;
        }
        if (node->right->balance == -1) {
          replace(node, node->right, rotateRight(node->right));
        }
        replace(parent, node, rotateLeft(node));
      }
      return heightDiff;
    }

    Node *rotateLeft(Node *B) {
      Node *D = B->right;
      const long long heightC = 0;
      const long long heightE = heightC + D->balance;
      const long long heightA = std::max(heightC, heightE) + 1 - B->balance;
      B->right = D->left;
      D->left = B;
      B->balance = heightC - heightA;
      D->num += B->num;
      D->ones += B->ones;
      D->balance = heightE - (std::max(heightA, heightC) + 1);
      assert(-2 <= B->balance && B->balance <= 2);
      assert(-2 <= D->balance && D->balance <= 2);
      return D;
    }

    Node *rotateRight(Node *D) {
      Node *B = D->left;
      const long long heightC = 0;
      const long long heightA = heightC - B->balance;
      const long long heightE = std::max(heightA, heightC) + 1 + D->balance;
      D->left = B->right;
      B->right = D;
      D->num -= B->num;
      D->ones -= B->ones;
      D->balance = heightE - heightC;
      B->balance = std::max(heightC, heightE) + 1 - heightA;
      assert(-2 <= B->balance && B->balance <= 2);
      assert(-2 <= D->balance && D->balance <= 2);
      return B;
    }

    void replace(Node *parent, Node *oldNode, Node *newNode) {
      if (parent == nullptr) {
        this->root = newNode;
        return;
      }
      if (parent->left == oldNode) {
        parent->left = newNode;
      }else if (parent->right == oldNode) {
        parent->right = newNode;
      }else {
        throw "old node is not child";
      }
    }

    long long popCount(long long x) {
      x = (x & 0x5555555555555555ULL) + ((x >> (long long)1) & 0x5555555555555555ULL);
      x = (x & 0x3333333333333333ULL) + ((x >> (long long)2) & 0x3333333333333333ULL);
      x = (x + (x >> (long long)4)) & 0x0f0f0f0f0f0f0f0fULL;
      x = x + (x >>  (long long)8);
      x = x + (x >> (long long)16);
      x = x + (x >> (long long)32);
      return x & 0x7FLLU;
    }

    long long get_height(Node *node, std::map<long long, long long> &height) {
      if (node->is_leaf) {
        return 0;
      }
      if (height.find(node->no) != height.end()) {
        return height[node->no];
      }
      auto left_height = get_height(node->left, height);
      auto right_height = get_height(node->right, height);
      return height[node->no] = std::max(left_height, right_height) + 1;
    }

};

class DynamicWaveletMatrix {
  public:
    std::vector<DynamicBitvector> bit_arrays;
    std::vector<long long> begin_one;

    long long size;
    long long maximum_element;
    long long bit_size;

  public:
    DynamicWaveletMatrix (long long maximum_element) : size(0), maximum_element(maximum_element + 1) {
      this->bit_size = this->get_num_of_bit(maximum_element);
      if (bit_size == 0) {
        bit_size = 1;
      }
      this->begin_one.resize(bit_size);
      for (long long i = 0; i < bit_size; ++i) {
        DynamicBitvector sv;
        bit_arrays.push_back(sv);
      }
    }

    DynamicWaveletMatrix (long long num_of_alphabet, const std::vector<long long> &array) : size(0), maximum_element(num_of_alphabet + 1) {
      this->bit_size = this->get_num_of_bit(num_of_alphabet);
      if (bit_size == 0) {
        bit_size = 1;
      }
      this->begin_one.resize(bit_size);
      if (array.empty()) {
        for (long long i = 0; i < bit_size; ++i) {
          DynamicBitvector sv;
          bit_arrays.push_back(sv);
        }
        return;
      }
      size = array.size();
      std::vector<long long> v(array), b(array.size(), 0);
      for (long long i = 0; i < bit_size; ++i) {
        std::vector<long long> temp;
        for (long long j = 0; j < v.size(); ++j) {
          long long c = v.at(j);
          long long bit = (c >> (bit_size - i - 1)) & 1;
          if (bit == 0) {
            temp.push_back(c);
              b[j] = 0;
          }
        }
        this->begin_one.at(i) = temp.size();
        for (long long j = 0; j < v.size(); ++j) {
          long long c = v.at(j);
          long long bit = (c >> (bit_size - i - 1)) & 1;  //　上からi番目のbit
          if (bit == 1) {
            temp.push_back(c);
            b[j] = 1;
          }
        }

        DynamicBitvector dbv(b);
        bit_arrays.emplace_back(dbv);
        v = temp;
      }
    }

    long long access(long long pos) {
      if (pos >= this->size) {
         return NOTFOUND;
      }
      long long c = 0;
      for (long long i = 0; i < bit_arrays.size(); ++i) {
        long long bit = bit_arrays.at(i).access(pos);   // もとの数値がのi番目のbit
        c = (c <<= 1) | bit;
        pos = bit_arrays.at(i).rank(bit, pos);
        if (bit) {
          pos += this->begin_one.at(i);
        }
      }
      return c;
    }

    long long rank(long long c, long long pos) {
      assert(pos <= size);
      if (c >= maximum_element) {
        return 0;
      }

    long long left = 0, right = pos;
      for (long long i = 0; i < bit_size; ++i) {
        const long long bit = (c >> (bit_size - i - 1)) & 1;  
          left = bit_arrays.at(i).rank(bit, left);             
          right = bit_arrays.at(i).rank(bit, right);           
          if (bit) {
            left += this->begin_one.at(i);
            right += this->begin_one.at(i);
          }
        }
      return right - left;
    }

    long long select(long long c, long long rank) {
      assert(rank > 0);
      if (c >= maximum_element) {
        return NOTFOUND;
      }

    long long left = 0;
      for (long long i = 0; i < bit_size; ++i) {
        const long long bit = (c >> (bit_size - i - 1)) & 1;  
        left = bit_arrays.at(i).rank(bit, left);              
        if (bit) {
          left += this->begin_one.at(i);
        }
      }
      long long index = left + rank;
      for (long long i = 0; i < bit_arrays.size(); ++i){
        long long bit = ((c >> i) & 1);
        if (bit == 1) {
          index -= this->begin_one.at(bit_size - i - 1);
        }
        index = this->bit_arrays.at(bit_size - i - 1).select(bit, index);
      }
      return index;
    }

    void insert(long long pos, long long c) {
      assert(pos <= this->size);
      for (long long i = 0; i < bit_arrays.size(); ++i) {
        const long long bit = (c >> (bit_size - i - 1)) & 1;
        bit_arrays.at(i).insert(pos, bit);
        pos = bit_arrays.at(i).rank(bit, pos);
        if (bit) {
          pos += this->begin_one.at(i);
        }else {
          this->begin_one.at(i)++;
        }
      }
      this->size++;
    }
   
    void push_back(long long c) {
      this->insert(this->size, c);
    }

    void erase(long long pos) {
      assert(pos < this->size);
      if (pos >= this->size) {
        throw "Segmentation fault";
      }
      for (long long i = 0; i < bit_arrays.size(); ++i) {
        long long bit = bit_arrays.at(i).access(pos);
        auto next_pos = bit_arrays.at(i).rank(bit, pos);
        bit_arrays.at(i).erase(pos);
        if (bit) {
          next_pos += this->begin_one.at(i);
        }else {
          this->begin_one.at(i)--;
        }
        pos = next_pos;
      }
      this->size--;
    }

    void update(long long pos, long long c) {
      assert(pos < this->size);
      this->erase(pos);
      this->insert(pos, c);
    }

  private:
    long long get_num_of_bit(long long x) {
      if (x == 0) return 0;
      x--;
      long long bit_num = 0;
      while (x >> bit_num) {
          ++bit_num;
      }
      return bit_num;
    }
};

