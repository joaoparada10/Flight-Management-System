/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include "Airline.h"
#include <string>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int distance;

    void addEdge(Vertex<T> *dest, std::string w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    void setDistance(int d);
    int getDistance() const;
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
    std::string weight;// edge information ( this case flight distance)
public:
	Edge(Vertex<T> *d, std::string w);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    std::string getWeight() const;
    void setWeight(std::string weight);
    friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
	bool addVertex(T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, std::string w);
	bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
	vector<T> dfs() const;
	vector<T> dfs(const T & source) const;
	vector<T> bfs(const T &source) const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, std::string w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}
template<class T>
int Vertex<T>::getDistance() const {
    return distance;
}
template<class T>
void Vertex<T>::setDistance(int d) {
    Vertex::distance = d;
}

template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
std::string Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(std::string weight) {
    Edge::weight = weight;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, std::string w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, w);
    return true;
}


/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, std::string w) {
	adj.push_back(Edge<T>(d, w));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	for (auto it = adj.begin(); it != adj.end(); it++)
		if (it->dest  == d) {
			adj.erase(it);
			return true;
		}
	return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
		if ((*it)->info  == in) {
			auto v = *it;
			vertexSet.erase(it);
			for (auto u : vertexSet)
				u->removeEdgeTo(v);
			delete v;
			return true;
		}
	return false;
}


//=============================================================================
// Exercise 1.1: Depth First Search
//=============================================================================
// Subexercise 1.1.1: Depth First Search (Graph Traversal)
//=============================================================================
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 */
// TODO
template <class T>
vector<T> Graph<T>::dfs() const {
    for(auto vx : vertexSet) vx->setVisited(false);
    vector<T> res;
    for (auto it = this->vertexSet.begin(); it != this->vertexSet.end(); it++){
        auto vx = *it;
        if(!vx->isVisited()) dfsVisit(vx,res);
    }
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
// TODO
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->setVisited(true);
    vector<Edge<T>> edges = v->getAdj();
    res.push_back(v->getInfo());
    for(auto ed : edges){
        if(!ed.getDest()->isVisited()) dfsVisit(ed.getDest(), res);
    }
}

//=============================================================================
// Subexercise 1.1.2: Depth First Search (From a source node)
//=============================================================================
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
// TODO
template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;
    for(auto vx : this->vertexSet) vx->setVisited(false);
    auto srcVx = this->findVertex(source);
    dfsVisit(srcVx,res);
    return res;
}


//=============================================================================
// Exercise 2: Breadth-First Search
//=============================================================================
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
// TODO
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    Vertex<T>* srcVx = findVertex(source);
    if (srcVx == nullptr) return res;
    for (Vertex<T>* vx : this->vertexSet){
        vx->setVisited(false);
    }
    queue<Vertex<T>*> tempQ;
    tempQ.push(srcVx);
    srcVx->setVisited(true);
    while (!tempQ.empty()){
        Vertex<T>* u = tempQ.front();
        tempQ.pop();
        res.push_back(u->getInfo());
        for (Edge<T> edge : u->getAdj()){
            Vertex<T>* w = edge.getDest();
            if (!w->isVisited()){
                tempQ.push(w);
                w->setVisited(true);
            }
        }
    }
	return res;
}

#endif /* GRAPH_H_ */
