#include <set>
#include "../header/Graph.h"
#include <iostream>

/****************** Vertex Implementation ********************/

Vertex::Vertex(const std::string& code) : visited(false), processing(false), indegree(0), num(0), low(0), airport(code, "", "", "", 0.0, 0.0) {}

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

const Airport& Vertex::getAirport() const {
    return airport;
}

void Vertex::setAirport(const Airport& airport) {
    this->airport = airport;
}

void Vertex::addEdge(Vertex* src, Vertex* dest, double w, std::string airline) {
    adj.push_back(Edge(src, dest, w, airline));
}


/****************** Edge Implementation ********************/

Edge::Edge(Vertex* s, Vertex* d, double w, std::string airline) : src(s), dest(d), weight(w), airline(airline) {}

Vertex* Edge::getDest() const {
    return dest;
}
Vertex* Edge::getSrc() const {
    return src;
}

void Edge::setDest(Vertex* d) {
    dest = d;
}

double Edge::getWeight() const {
    return weight;
}
std::string Edge::getAirline() const{
    return airline;
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
int Graph::getNumEdges() const {
    return edgeSet.size();
}

bool Graph::addVertex(const std::string& code) {
    if (findVertex(code) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(code));
    return true;
}


bool Graph::addEdge(const std::string& sourc, const std::string& dest, const std::string airline, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v1, v2, w, airline);
    edgeSet.push_back(new Edge(v1, v2, w, airline));
    return true;

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

const std::set<std::string> Graph::bfs(const std::string& source) const {
    std::set<std::string> res;
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
        res.insert(v->getAirport().getCode());

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

void Graph::recursiveBfs(Vertex* s, std::unordered_map<std::string, int>& airportLayovers) {
    for (const auto& edge : s->getAdj()) {
        if (!edge.getDest()->isVisited()) {
            edge.getDest()->setVisited(true);

            // Increment the layovers for the destination airport
            airportLayovers[edge.getDest()->getAirport().getCode()] = airportLayovers[edge.getSrc()->getAirport().getCode()] + 1;

            recursiveBfs(edge.getDest(), airportLayovers);
        }
    }
}

std::unordered_map<std::string, int> Graph::bfsLayOver(std::string airportCode) {
    auto s = findVertex(airportCode);
    findVertex(airportCode)->setVisited(true);
    std::set<std::string> reachableDestinations = bfs(airportCode);
    std::unordered_map<std::string, int> airportLayovers;

    for (const auto& dest : reachableDestinations) {
        auto air = findVertex(dest);
        if (air != nullptr && dest!=airportCode) {
            air->setVisited(false);

            // Initialize layovers to -1 for all destinations except the source airport
            airportLayovers.insert({dest, -1});

        }
        recursiveBfs(s, airportLayovers);
    }


    for (const auto& l: airportLayovers){
        std::cout << "Airport " << l.first << " - " << l.second << std::endl;
    }
    return airportLayovers;
}

