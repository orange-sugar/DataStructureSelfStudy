#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include "Graph.h"
#include "../Vector/Vector.h"

// Vertex struct
template <typename Tv> class Vertex {
public:
    Tv data; int inDegree; int outDegree;
    VStatus status; // time label
    int dTime, fTime;
    int parent; int priority;
    Vertex(Tv const & d = (Tv) 0): 
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(_INT_MAX_) {}
};

// Edge struct
template <typename Te> class Edge {
public:
    Te data; int weight; EType type;
    Edge (Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};

// vector-based Graph implemented by adjacency matrix
template <typename Tv, typename Te> 
class GraphMatrix: public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;
    Vector<Vector<Edge<Te> *>> E;
public:
    GraphMatrix() { this->n = this->e = 0; }
    ~GraphMatrix() {
        for (int j = 0; j < this->n; j++) 
            for (int k = 0; k < this->n; k++)
                delete E[j][k];
    }

// operations of vertex
    virtual Tv & vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    virtual VStatus & status(int i) { return V[i].status; }
    virtual int & dTime(int i) { return V[i].dTime; }
    virtual int & fTime(int i) { return V[i].fTime; }
    virtual int & parent(int i) { return V[i].parent; }
    virtual int & priority(int i) { return V[i].priority; }

    virtual int nextNbr(int i, int j) { while((-1<j)&&!exists(i, --j)); return j; }
    virtual int firstNbr(int i) { return nextNbr(i, this->n); }
// dynamic op of vertex
    virtual int insert (Tv const & vertex) {
        for (int j = 0; j < this->n; j++) E[j].insert(nullptr); this->n++;
        E.insert(Vector<Edge<Te>*> (this->n, this->n, (Edge<Te> *) nullptr));
        return V.insert(Vertex<Tv> (vertex));
    }
    virtual Tv remove(int i) {
        for (int j = 0; j < this->n; j++) 
            if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; this->e--; }
        E.remove(i); this->n--;
        Tv vBak = vertex(i); V.remove(i);
        for (int j = 0; j < this->n; j++) 
            if (Edge<Te>* x = E[j].remove(i)) {delete x; V[j].outDegree--; this->e--;}
        return vBak;
    }
// operations of edge
    virtual bool exists(int i, int j) 
    { return (0 <= i) && (i <= this->n) && (0 <= j) && (j < this->n) && E[i][j] != nullptr; }
    virtual int& weight(int i, int j) { return E[i][j]->weight; }
    virtual EType & type ( int i, int j ) { return E[i][j]->type; }
    virtual Te& edge(int i, int j) { return E[i][j]->data; }
    virtual void insert(Te const & edge, int w, int i, int j) {
        if (exists(i, j)) return;
        E[i][j] = new Edge<Te> (edge, w);
        this->e++; V[i].outDegree++; V[j].inDegree++;
    }
    virtual Te remove(int i, int j) {
        Te eBak = edge(i, j); delete E[i][j]; E[i][j] = nullptr;
        this->e--; V[i].outDegree--; V[j].inDegree--;
        return eBak;
    }


};

#endif