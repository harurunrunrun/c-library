#pragma once
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#define Type int
typedef struct min_heap_t{
  Type* _heap;
  int _size;
  int _cap;
}min_heap;

void print_heap(min_heap* mh){
  printf("size = %d\n", mh->_size);
  for(int i=0;i<mh->_size;i++){
    printf("%d ",mh->_heap[i]);
  }
  printf("\n");
  return;
}

Type pop(min_heap* mh){
  assert(mh->_size>=1);
  Type res=mh->_heap[0];
  mh->_heap[0]=mh->_heap[mh->_size-1];
  mh->_size--;
  int j=(int)log2(mh->_size+1)+1,i,k;
  Type tmp;
  while(j>0){
    i=((mh->_size)>>j)-1;
    k=((mh->_size)>>(j-1))-1;
    if(i>=0 && i<mh->_size && mh->_heap[i]>mh->_heap[k]){
      tmp=mh->_heap[i];
      mh->_heap[i]=mh->_heap[k];
      mh->_heap[k]=tmp;
    }
    j--;
  }
  return res;
}

Type top(min_heap* mh){
  assert(mh->_size>=1);
  return mh->_heap[0];
}

void reserve(min_heap* mh,int size){
  assert(size>=mh->_size);
  mh->_cap=size;
  Type* new_heap=(Type*)malloc(sizeof(Type)*size);
  for(int i=0;i<mh->_size;i++){
    new_heap[i]=mh->_heap[i];
  }
  free(mh->_heap);
  mh->_heap=new_heap;
  return;
}

void push(min_heap* mh,Type val){
  if(mh->_size+1>mh->_cap){
    reserve(mh,(mh->_cap+1)*2);
  }
  int j=(int)log2(mh->_size+1),i;
  Type tmp;
  while(j>=0){
    i=((mh->_size)>>j)-1;
    if(i>=0 && i<(mh->_size) && (mh->_heap[i])>val){
      tmp=mh->_heap[i];
      mh->_heap[i]=val;
      val=tmp;
    }
    j--;
  }
  mh->_size++;
  mh->_heap[mh->_size-1]=val;
  return;
}

void heapify(min_heap* mh,Type* data,int size){
  mh->_heap=(Type*)malloc(sizeof(Type)*size);
  assert(mh->_heap!=NULL);
  mh->_cap=size;
  mh->_size=0;
  for(int i=0;i<size;i++){
    push(mh,data[i]);
  }
  return;
}

void delete(min_heap* mh){
  free(mh->_heap);
  mh->_size=0;
  mh->_cap=0;
  return;
}




