# min heap (二分木ヒープ)

[コードへのリンク](https://github.com/harurunrunrun/c-library/blob/main/library/min_heap.c)


### 注意

参照渡しをするとき main関数側からは `&` をつける


## 初期化

```
min_heap heap;
```

min_heap内で
```
#define Type T
// T: 型名 (int ,ll, double 等) char*は未対応
```
と定義する


## ヒープ化

```
void heapify(min_heap*,Type* hoge,int size);
// main関数内では heapify(&heap,hoge,size); と使う
```
O((size)log(size))


## 容量の確保

```
void reserve(min_heap*,int size);
```
O(size)

再確保の時間を軽減する


## 追加

```
void push(min_heap*,Type val);
```
O(log(size))


## 最小値の取得

```
Type top(min_heap*);
```
O(1)


## 最小値の削除&取得

```
Type pop(min_heap*);
```
O(log(size))


## メモリの解放

```
void delete(min_heap*);
```


## デバッグ出力用

```
void print_heap(min_heap*);
```
O(size)


