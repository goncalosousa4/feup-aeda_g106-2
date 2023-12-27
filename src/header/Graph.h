#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <stack>
#include <list>
#include "Airport.h"
#include "Flight.h"
#include <set>
#include <unordered_map>

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
    const Airport& getAirport() const;
    void setAirport(const Airport& airport);

    void addEdge(Vertex* src, Vertex* dest, double w, std::string airline);
};

class Edge {
    Vertex* src;
    Vertex* dest;      // destination vertex
    double weight;         // edge weight
    std::string airline;


public:
    Edge(Vertex* src, Vertex* d, double w, std::string airline);
    Vertex* getDest() const;
    Vertex* getSrc() const;
    void setDest(Vertex* dest);
    double getWeight() const;
    std::string getAirline() const;


};

class Graph {
    std::vector<Vertex*> vertexSet;      // vertex set
    std::vector<Edge*> edgeSet;
    static void dfsVisit(Vertex* v, std::vector<std::string>& res);

public:
    Vertex* findVertex(const std::string& code) const;
    Vertex* findVertexCity(const std::string &city) const ;
    int getNumVertex() const;
    int getNumEdges() const;
    bool addVertex(const std::string& code);
    bool addEdge(const std::string& sourc, const std::string& dest, const std::string airline, double w);
    std::vector<Vertex*> getVertexSet() const;
    std::vector<std::string> dfs();
    std::vector<std::string> dfs(const std::string& source);
    const std::set<std::string> bfs(const std::string& source) const;
    bool isDAG() const;
};

#endif
