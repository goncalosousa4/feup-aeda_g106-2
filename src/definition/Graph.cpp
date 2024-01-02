#include <set>
#include "../header/Graph.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>

/****************** Vertex Implementation ********************/

Vertex::Vertex(const std::string& code) : visited(false), processing(false), indegree({}), num(0), low(0), airport(code, "", "", "", 0.0, 0.0){}


bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(bool v) {
    visited = v;
}


std::vector<Vertex*> Vertex::getIndegree() const {
    return indegree;
}

void Vertex::setIndegree(Vertex* v) {
    indegree.push_back(v);
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

Edge* Graph::findEdgeByDest(const std::string dest) const {
    for (auto e: edgeSet){
        if (e->getDest()==findVertex(dest)){
            return e;
        }
    }
    return nullptr;
}

Vertex* Graph::findVertexByName(const std::string& name) const {
    for (auto v : vertexSet)
        if (v->getAirport().getName() == name)
            return v;
    return nullptr;
}

Vertex* Graph::findVertex(const std::string& code) const {
    for (auto v : vertexSet)
        if (v->getAirport().getCode() == code)
            return v;
    return nullptr;
}
std::set<std::string> Graph::findVertexCity(const std::string &city) const {
    std::set<std::string> vertexes;
    for (auto v : vertexSet)
        if (v->getAirport().getCity() == city)
            vertexes.insert(v->getAirport().getCode());
    return vertexes;
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
    v2->setIndegree(v1);
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

void Graph::makeUndirected() {

    std::vector<Edge*> edgesCopy = edgeSet;

    for (const Edge* directedEdge : edgesCopy) {
        Vertex* src = directedEdge->getSrc();
        Vertex* dest = directedEdge->getDest();
        double weight = directedEdge->getWeight();
        std::string airline = directedEdge->getAirline();


        Edge* undirectedEdge = new Edge(src, dest, weight, airline);
        src->addEdge(src, dest, weight, airline);
        edgeSet.push_back(undirectedEdge);


        if (src != dest) {
            undirectedEdge = new Edge(dest, src, weight, airline);
            dest->addEdge(dest, src, weight, airline);
            edgeSet.push_back(undirectedEdge);
        }
    }
}

void Graph::findArticulationPointsUtil(Vertex* v, std::unordered_map<Vertex*, int>& disc, std::unordered_map<Vertex*, int>& low,
                                       std::unordered_map<Vertex*, Vertex*>& parent,
                                       std::unordered_set<Vertex*>& articulationPoints) {
    static int time = 0;
    int children = 0;

    v->setVisited(true);
    disc[v] = low[v] = ++time;

    for (const Edge& e : v->getAdj()) {
        Vertex* adjV = e.getDest();
        if (!adjV->isVisited()) {
            children++;
            parent[adjV] = v;
            findArticulationPointsUtil(adjV, disc, low, parent, articulationPoints);

            low[v] = std::min(low[v], low[adjV]);

            if (parent[v] == nullptr && children > 1)
                articulationPoints.insert(v);
            if (parent[v] != nullptr && low[adjV] >= disc[v])
                articulationPoints.insert(v);
        }
        else if (adjV != parent[v])
            low[v] = std::min(low[v], disc[adjV]);
    }
}

void Graph::findArticulationPoints() {
    int contador = 0;
    std::unordered_map<Vertex*, int> disc;
    std::unordered_map<Vertex*, int> low;
    std::unordered_map<Vertex*, Vertex*> parent;
    std::unordered_set<Vertex*> articulationPoints;

    for (Vertex* v : vertexSet) {
        if (!v->isVisited())
            findArticulationPointsUtil(v, disc, low, parent, articulationPoints);
    }

    for (Vertex* ap : articulationPoints) {
        std::cout << ap->getAirport().getCode() << " | ";
        contador++;
    }

    if (contador > 0) {
        std::cout << std::endl << "There are " << contador << " airports essential to the network's circulation capability." << std::endl;
    } else {
        std::cout << "No airports essential to the network's circulation capability found." << std::endl;
    }
}


std::vector<std::vector<Vertex*>> Graph::findFlightsWithFilters(const std::string& source, const std::string& destination, const std::vector<std::string>& preferredAirlines, bool minimizeAirlineChanges) {
    std::vector<std::vector<Vertex*>> result;
    std::unordered_map<Vertex*, Vertex*> prev;
    std::queue<std::pair<Vertex*, std::string>> q; // Queue of vertex and last airline used
    std::unordered_set<Vertex*> visited;

    Vertex* sourceVertex = findVertex(source);
    Vertex* destinationVertex = findVertex(destination);
    if (sourceVertex == nullptr || destinationVertex == nullptr) return result;

    q.push({sourceVertex, ""});
    visited.insert(sourceVertex);

    while (!q.empty()) {
        Vertex* current = q.front().first;
        std::string lastAirline = q.front().second;
        q.pop();

        if (current == destinationVertex) {
            // Construct path
            std::vector<Vertex*> path;
            for (Vertex* v = current; v != nullptr; v = prev[v]) {
                path.insert(path.begin(), v);
            }
            result.push_back(path);
            continue;
        }

        for (const Edge& edge : current->getAdj()) {
            Vertex* next = edge.getDest();
            std::string airline = edge.getAirline();
            auto it = std::find_if(preferredAirlines.begin(), preferredAirlines.end(), [&airline](const std::string& preferred) { return airline == preferred; });
            if (visited.find(next) == visited.end() && (preferredAirlines.empty() || it != preferredAirlines.end())) {
                if (!minimizeAirlineChanges || lastAirline.empty() || airline == lastAirline) {
                    visited.insert(next);
                    prev[next] = current;
                    q.push({next, airline});
                }
            }
        }
    }

    return result;
}

void Graph::findAllFlightsUtil(Vertex* current, Vertex* destination, std::vector<Vertex*>& path, std::vector<std::vector<Vertex*>>& allPaths, std::unordered_set<Vertex*>& visited) {
    visited.insert(current);
    path.push_back(current);

    if (current == destination) {
        // If destination is reached, add the current path to allPaths
        allPaths.push_back(path);
    } else {
        // Explore adjacent vertices
        for (const Edge& edge : current->getAdj()) {
            Vertex* next = edge.getDest();
            if (visited.find(next) == visited.end()) {
                findAllFlightsUtil(next, destination, path, allPaths, visited);
            }
        }
    }

    // Backtrack
    path.pop_back();
    visited.erase(current);
}

std::vector<std::vector<Vertex*>> Graph::findAllFlights(const std::string& source, const std::string& destination) {
    std::vector<std::vector<Vertex*>> allFlights;
    std::vector<Vertex*> path;
    std::unordered_set<Vertex*> visited;
    Vertex* sourceVertex = findVertex(source);
    Vertex* destVertex = findVertex(destination);

    if (sourceVertex && destVertex) {
        findAllFlightsUtil(sourceVertex, destVertex, path, allFlights, visited);
    }

    return allFlights;
}
