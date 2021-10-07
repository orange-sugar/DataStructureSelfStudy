#ifndef GRAPH_H
#define GRAPH_H

#include "../_share/utils.h" // for INT_MAX ...
#include "../stack_vector/stack_vector.h"
#include "../queue_list/queue_list.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

template <typename Tv, typename Te>
class Graph {
private:
    void reset() {
        for (int i = 0; i < n; i++) {
            status ( i ) = UNDISCOVERED; dTime ( i ) = fTime ( i ) = -1; //状态，时间标签
            parent ( i ) = -1; priority ( i ) = _INT_MAX_; //（在遍历树中的）父节点，优先级数
            for ( int j = 0; j < n; j++ ) //所有边的
                if ( exists ( i, j ) ) type ( i, j ) = UNDETERMINED; //类型
        }
    }
    void BFS ( int, int& ); //（连通域）广度优先搜索算法
    void DFS ( int, int& ); //（连通域）深度优先搜索算法
    void BCC ( int, int&, Stack<int>& ); //（连通域）基于DFS的双连通分量分解算法
    bool TSort ( int, int&, Stack<Tv>* ); //（连通域）基于DFS的拓扑排序算法
    template <typename PU> void PFS ( int, PU ); //（连通域）优先级搜索框架

public: 
// 顶点
    int n; //顶点总数
    virtual int insert ( Tv const& ) = 0; //插入顶点，返回编号
    virtual Tv remove ( int ) = 0; //删除顶点及其关联边，返回该顶点信息
    virtual Tv& vertex ( int ) = 0; //顶点v的数据（该顶点的确存在）
    virtual int inDegree ( int ) = 0; //顶点v的入度（该顶点的确存在）
    virtual int outDegree ( int ) = 0; //顶点v的出度（该顶点的确存在）
    virtual int firstNbr ( int ) = 0; //顶点v的首个邻接顶点
    virtual int nextNbr ( int, int ) = 0; //顶点v的（相对于顶点j的）下一邻接顶点
    virtual VStatus& status ( int ) = 0; //顶点v的状态
    virtual int& dTime ( int ) = 0; //顶点v的时间标签dTime
    virtual int& fTime ( int ) = 0; //顶点v的时间标签fTime
    virtual int& parent ( int ) = 0; //顶点v在遍历树中的父亲
    virtual int& priority ( int ) = 0; //顶点v在遍历树中的优先级数
// 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
    int e; //边总数
    virtual bool exists ( int, int ) = 0; //边(v, u)是否存在
    virtual void insert ( Te const&, int, int, int ) = 0; //在顶点v和u之间插入权重为w的边e
    virtual Te remove ( int, int ) = 0; //删除顶点v和u之间的边e，返回该边信息
    virtual EType & type ( int, int ) = 0; //边(v, u)的类型
    virtual Te& edge ( int, int ) = 0; //边(v, u)的数据（该边的确存在）
    virtual int& weight ( int, int ) = 0; //边(v, u)的权重
// 算法
    void bfs ( int ); //广度优先搜索算法
    void dfs ( int ); //深度优先搜索算法
    void bcc ( int ); //基于DFS的双连通分量分解算法
    Stack<Tv>* tSort ( int ); //基于DFS的拓扑排序算法
    void prim ( int ); //最小支撑树Prim算法
    void dijkstra ( int ); //最短路径Dijkstra算法
    template <typename PU> void pfs ( int, PU ); //优先级搜索框架
};

// bfs for whole graph
template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs (int s) {
    reset(); int clock = 0; int v = s;
    do
        if (UNDISCOVERED == status(v))
            BFS(v, clock);
    while (s != (v = (++v % n)));
    
}

// bfs for single connected domain
template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS (int v, int& clock) {
   Queue<int> Q;
   status(v) = DISCOVERED; Q.enqueue(v);
   while (!Q.empty()) {
      int v = Q.dequeue(); dTime(v) = ++clock;
      for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
         if (UNDISCOVERED == status(u)) {
            status(u) = DISCOVERED; Q.enqueue(u);
            type(v, u) = TREE; parent(u) = v;
         }
         else type(v, u) = CROSS;
      status(v) = VISITED;
   }
}

// dfs for whole graph
template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs (int s) {
    reset(); int clock = 0; int v = s;
    do
        if (UNDISCOVERED == status(v))
            DFS(v, clock);
    while (s != (v = (++v % n)));
}

// dfs for single graph
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock) {
    dTime(v) = ++clock; status(v) = DISCOVERED;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
        switch (status(u)) {
        case UNDISCOVERED:
            type(v, u) = TREE; parent(u) = v; DFS(u, clock); break;
        case DISCOVERED:
            type(v, u) = BACKWARD; break;
        default:
            type(v, u) = (dTime(v) < dTime(u) ? FORWARD : CROSS); break;
        }
    status(v) = VISITED; fTime(v) = ++clock;
}

#endif