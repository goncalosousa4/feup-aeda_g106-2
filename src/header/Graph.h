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

#endif /* GRAPH_H_ */
