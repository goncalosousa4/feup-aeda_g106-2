#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <stack>
#include <list>
#include "Airport.h"

class Edge;

/****************** Provided structures  ********************/

class Vertex {
    std::vector<Edge> adj;  // list of outgoing edges
    bool visited;
    bool processing;
    int indegree;
    int num;               // auxiliary field
    int low;               // auxiliary field
    Airport airport;

public:
    Vertex(const std::string& code);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    int getIndegree() const;
    void setIndegree(int indegree);
    const std::vector<Edge>& getAdj() const;
    void setAdj(const std::vector<Edge>& adj);
    const Airport& getAirport() const;
    void setAirport(const Airport& airport);

    void addEdge(Vertex* dest, double w);
    bool removeEdgeTo(Vertex* dest);
};

class Edge {
    Vertex* dest;      // destination vertex
    double weight;         // edge weight

public:
    Edge(Vertex* d, double w);
    Vertex* getDest() const;
    void setDest(Vertex* dest);
    double getWeight() const;
    void setWeight(double weight);
};

class Graph {
    std::vector<Vertex*> vertexSet;      // vertex set
    void dfsVisit(Vertex* v, std::vector<std::string>& res);

public:
    Vertex* findVertex(const std::string& code) const;
    int getNumVertex() const;
    bool addVertex(const std::string& code);
    bool removeVertex(const std::string& code);
    bool addEdge(const std::string& sourc, const std::string& dest, double w);
    bool removeEdge(const std::string& source, const std::string& dest);
    std::vector<Vertex*> getVertexSet() const;
    std::vector<std::string> dfs();
    std::vector<std::string> dfs(const std::string& source);
    std::vector<std::string> bfs(const std::string& source) const;
    bool isDAG() const;
};

/****************** Vertex Implementation ********************/

Vertex::Vertex(const std::string& code) : visited(false), processing(false), indegree(0), num(0), low(0), airport(code, "", "", 0.0, 0.0) {}

bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(bool v) {
    visited = v;
}

bool Vertex::isProcessing() const {
    return processing;
}

void Vertex::setProcessing(bool p) {
    processing = p;
}

int Vertex::getIndegree() const {
    return indegree;
}

void Vertex::setIndegree(int indegree) {
    this->indegree = indegree;
}

const std::vector<Edge>& Vertex::getAdj() const {
    return adj;
}

void Vertex::setAdj(const std::vector<Edge>& adj) {
    this->adj = adj;
}

const Airport& Vertex::getAirport() const {
    return airport;
}

void Vertex::setAirport(const Airport& airport) {
    this->airport = airport;
}

void Vertex::addEdge(Vertex* dest, double w) {
    adj.push_back(Edge(dest, w));
}

bool Vertex::removeEdgeTo(Vertex* dest) {
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        if (it->getDest() == dest) {
            adj.erase(it);
            return true;
        }
    }
    return false;
}

/****************** Edge Implementation ********************/

Edge::Edge(Vertex* d, double w) : dest(d), weight(w) {}

Vertex* Edge::getDest() const {
    return dest;
}

void Edge::setDest(Vertex* d) {
    dest = d;
}

double Edge::getWeight() const {
    return weight;
}

void Edge::setWeight(double w) {
    weight = w;
}

/****************** Graph Implementation ********************/

Vertex* Graph::findVertex(const std::string& code) const {
    for (auto v : vertexSet)
        if (v->getAirport().getCode() == code)
            return v;
    return nullptr;
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

bool Graph::addVertex(const std::string& code) {
    if (findVertex(code) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(code));
    return true;
}

bool Graph::removeVertex(const std::string& code) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); ++it) {
        if ((*it)->getAirport().getCode() == code) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    }
    return false;
}

bool Graph::addEdge(const std::string& sourc, const std::string& dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::removeEdge(const std::string& sourc, const std::string& dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    return v1->removeEdgeTo(v2);
}

std::vector<Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

std::vector<std::string> Graph::dfs() {
    std::vector<std::string> res;
    for (auto v : vertexSet)
        v->setVisited(false);
    for (auto v : vertexSet)
        if (!v->isVisited())
            dfsVisit(v, res);
    return res;
}

void Graph::dfsVisit(Vertex* v, std::vector<std::string>& res) {
    v->setVisited(true);
    res.push_back(v->getAirport().getCode());
    for (auto& e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited())
            dfsVisit(w, res);
    }
}

std::vector<std::string> Graph::dfs(const std::string& source) {
    std::vector<std::string> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->setVisited(false);

    dfsVisit(s, res);
    return res;
}

std::vector<std::string> Graph::bfs(const std::string& source) const {
    std::vector<std::string> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    std::queue<Vertex*> q;
    for (auto v : vertexSet)
        v->setVisited(false);

    q.push(s);
    s->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getAirport().getCode());

        for (auto& e : v->getAdj()) {
            auto w = e.getDest();
            if (!w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }

    return res;
}

#endif /* GRAPH_H_ */
