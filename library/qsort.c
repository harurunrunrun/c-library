//a-b:昇順 b-a:降順
int cmp(const void* a,const void* b){
  return *(int*)a-*(int*)b;
}
/*
qsort(a,N,sizeof(int),cmp);
*/
