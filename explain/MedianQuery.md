# MedianQuery

[コードへのリンク](https://github.com/harurunrunrun/c-library/blob/main/library/MedianQuery.hpp)

<br>

## 宣言

```
MedianQuery<Type> MQ;
```
計算量 O(1)

<br>

```
MedianQuery<Type> MQ(std::vector<Type> v);
```
計算量 O(|v|log(|v|))

<br>

## 追加

```
void add(Type x);
```
計算量 O(log(n))

(n :今まで追加した要素数)

<br>

## 複数追加

```
void update(std::vector<Type> v);
```
計算量 O(|v|log(n))

<br>

## 中央値の取得

```
double get();
```
計算量 O(1)

<br>

## 削除

```
void erase(Type x);
```

x が存在しない場合は例外が発生します。

計算量 O(log(n))


