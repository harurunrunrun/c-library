#include <stdlib.h>
#include <vector>
namespace Dice{
  struct Dice{
    int top,front,bottom,back,left,right;
    Dice(){
      top=1;
      front=3;
      bottom=6;
      back=4;
      left=2;
      right=5;
    }
  };
  Dice roll_right(const Dice& x){
    Dice res;
    res.top=x.left;
    res.front=x.front;
    res.bottom=x.right;
    res.back=x.back;
    res.left=x.bottom;
    res.right=x.top;
    return res;
  }

  Dice roll_left(const Dice& x){
    Dice res;
    res.top=x.right;
    res.front=x.front;
    res.bottom=x.left;
    res.back=x.back;
    res.left=x.top;
    res.right=x.bottom;
    return res;
  }

  Dice roll_front(const Dice& x){
    Dice res;
    res.top=x.back;
    res.front=x.top;
    res.bottom=x.front;
    res.back=x.bottom;
    res.left=x.left;
    res.right=x.right;
    return res;
  }

  Dice roll_back(const Dice& x){
    Dice res;
    res.top=x.front;
    res.front=x.bottom;
    res.bottom=x.back;
    res.back=x.top;
    res.left=x.left;
    res.right=x.right;
    return res;
  }

  Dice spin_right(const Dice& x){
    Dice res;
    res.top=x.top;
    res.front=x.right;
    res.bottom=x.bottom;
    res.back=x.left;
    res.left=x.front;
    res.right=x.back;
    return res;
  }

  Dice spin_left(const Dice& x){
    Dice res;
    res.top=x.top;
    res.front=x.left;
    res.bottom=x.bottom;
    res.back=x.right;
    res.left=x.back;
    res.right=x.front;
    return res;
  }

  Dice getDice(int _top,int _front){
    // 存在しない場合はtopが-1のダイスを返します
    Dice res;
    if(_top==1){
      if(_front==2){
        res=spin_left(res);
      }else if(_front==3){

      }else if(_front==4){
        res=spin_left(res);
        res=spin_left(res);
      }else if(_front==5){
        res=spin_right(res);
      }else{
        res.top=-1;
      }
    }else if(_top==2){
      res=roll_right(res);
      if(_front==1){
        res=spin_right(res);
      }else if(_front==3){

      }else if(_front==4){
        res=spin_right(res);
        res=spin_right(res);
      }else if(_front==6){
        res=spin_left(res);
      }else{
        res.top=-1;
      }
    }else if(_top==3){
      res=roll_back(res);
      if(_front==1){
        res=spin_left(res);
        res=spin_left(res);
      }else if(_front==2){
        res=spin_left(res);
      }else if(_front==5){
        res=spin_right(res);
      }else if(_front==6){

      }else{
        res.top=-1;
      }
    }else if(_top==4){
      res=roll_front(res);
      if(_front==1){

      }else if(_front==2){
        res=spin_left(res);
      }else if(_front==5){
        res=spin_right(res);
      }else if(_front==6){
        res=spin_left(res);
        res=spin_left(res);
      }else{
        res.top=-1;
      }
    }else if(_top==5){
      res=roll_left(res);
      if(_front==1){
        res=spin_left(res);
      }else if(_front==3){

      }else if(_front==4){
        res=spin_left(res);
        res=spin_left(res);
      }else if(_front==6){
        res=spin_right(res);
      }else{
        res.top=-1;
      }
    }else{
      res=roll_left(res);
      res=roll_left(res);
      if(_front==2){
        res=spin_right(res);
      }else if(_front==3){

      }else if(_front==4){
        res=spin_left(res);
        res=spin_left(res);
      }else if(_front==5){
        res=spin_left(res);
      }else{
        res.top=-1;
      }
    }
    return res;
  }
  bool is_same(std::vector<int>& dx,std::vector<int>& dy){
    auto strictly_same=[&](const Dice::Dice& x,const Dice::Dice& y){
      return dx[x.top-1]==dy[y.top-1] && dx[x.back-1]==dy[y.back-1] && dx[x.front-1]==dy[y.front-1] 
      && dx[x.bottom-1]==dy[y.bottom-1] && dx[x.right-1]==dy[y.right-1] && dx[x.left-1]==dy[y.left-1];
    };
    Dice x,y;
    for(int t=1;t<=6;t++){
      for(int f=1;f<=6;f++){
        y=getDice(t,f);
        if(y.top!=-1 && strictly_same(x,y)){
          return true;
        }
      }
    }
    return false;
  }
}
