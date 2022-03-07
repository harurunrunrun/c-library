# Tree (static)

[コードへのリンク](https://github.com/harurunrunrun/c-library/blob/main/library/Tree.hpp)

<br>

```
int V    : 頂点数
int E    : 辺数
int root : 根
```

このライブラリは 0-indexed です。

<br>

## コンストラクタ

```
Tree tree(int V,int root=0);
```

- V 頂点 0 辺の木グラフを作成します。

- 計算量 O(V)

```
Tree tree(std::vector<std::vector<int>> Graph,int root=0);
```

- V 頂点 E 辺、各辺のコストが 1 の木グラフを作成します。

- 計算量 O(V+E)

```
Tree tree(std::vector<std::vector<std::pair<int,long long>>> Graph,int root=0);
```

- V 頂点 E 辺、各辺のコストは Graph\[i]\[j].second の木グラフを作成します。

- 計算量 O(V+E)

<br>

## 辺の追加

```
void add_edge(int s,int t,long long c=1);
```

- 頂点 s と頂点 t を結ぶコスト c の辺を追加します。

- 計算量 O(1)

<br>

## 親、深さ、根からのコストの計算

```
void search_parent_and_depth_and_distance();
```

- 木グラフが静的であると仮定して計算します。

- 計算量 O(V)

<br>

## 最近共通祖先(LCA)

```
long long LCA(int u,int v);
```

- 頂点 u と頂点 v の最近共通祖先を求めます。

- 計算量

  - 1回目の呼び出しの場合 
  
    O(Vlog(V))

  - 2回目以降の呼び出しの場合 
  
    O(log(V))
    
- 2回目以降は 木グラフが変更されていないと仮定して求めます。

<br>

## 2頂点間距離

```
inline long long get_distance(int u,int v);
```

- 頂点 u と頂点 v の距離を求めます。

- 計算量

  - <code>void search_parent_and_depth_and_distance()</code> を 以前に呼び出しており、u もしくは v が 根の場合 
    
    O(1)

  - LCAの前計算がされている場合 
  
    O(log(V))

  - LCAの前計算がされていない場合 
  
    O(Vlog(V))
    
    (このときにLCAの前計算も行われます)

<br>

## パス上の頂点存在判定

```
inline bool is_on_path(int u,int v,int p);
```

- 頂点 u と頂点 v の最短パス上に 頂点 p が存在するかを判定します。

- 計算量
  
  - LCAの前計算が行われている場合

    O(log(V)^3)

  - LCAの前計算が行われていない場合

    O(VlogV+log(V)^3)

    (このときにLCAの前計算も行われます)
  
<br>

## 木の直径

```
long long calculate_diameter();
```

- 木グラフの直径を求めます。

- 計算量 O(V)


  


