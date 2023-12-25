#include "../header/Graph.h"

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

/*void Vertex::setAdj(const std::vector<Edge>& adj) {
    this->adj = adj;
}*/

const Airport& Vertex::getAirport() const {
    return airport;
}

void Vertex::setAirport(const Airport& airport) {
    this->airport = airport;
}

void Vertex::addEdge(Vertex* dest, double w, std::string airline) {
    adj.push_back(Edge(dest, w, airline));
}


/****************** Edge Implementation ********************/

Edge::Edge(Vertex* d, double w, std::string airline) : dest(d), weight(w), airline(airline) {}

Vertex* Edge::getDest() const {
    return dest;
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
    v1->addEdge(v2, w, airline);
    edgeSet.push_back(new Edge(v2, w, airline));
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