#pragma once
#include <list>
#include <unordered_map>
#include "Vertex.h"
using namespace std;

template <typename K, typename T>
class Graph {
public:
    Graph() {};

    ~Graph() {

        for (Vertex<K, T>* v : vertices_) {
            delete v;
        }
    };

    Vertex<K, T>* getVertex(const K& key) {
        if (index_.find(key) != index_.end()) {
            return index_[key];
        }
        return nullptr;
    };

    const std::list<Vertex<K, T>*>& getVertices() const {
        return vertices_;
    };

    void addVertex(const K& key, const T& data) {
        // TBD: complete
        // Check if key already exists to prevent duplicates
        if (index_.find(key) != index_.end())
            return;

        // Allocate memory for the new vertex
        Vertex<K, T>* newVertex = new Vertex<K, T>(key, data);

        // Add to both the list and the lookup map
        vertices_.push_back(newVertex);
        index_[key] = newVertex;
    };



    void addEdge(Vertex<K, T>* from, Vertex<K, T>* to) {
        // Validate pointers before accessing
        if (from && to) {
            // Connect 'from' vertex to 'to' vertex
            from->addNeighbor(to);
        }
    };

    void addEdgeByKey(const K& fromKey, const K& toKey) {
        // Look up vertices in the index map
        auto fromIt = index_.find(fromKey);
        auto toIt = index_.find(toKey);

        // Proceed only if both keys exist in the graph
        if (fromIt != index_.end() && toIt != index_.end())
            // Reuse the pointer-based addEdge function
            addEdge(fromIt->second, toIt->second);
        else
            throw "Key not exist";
    };

    void reset() {
        for (Vertex<K, T>* v : vertices_) {
            v->setColor(WHITE);
            v->setDist(-1);
            v->setParent(nullptr);
            v->setDiscoverTime(-1);
            v->setFinishTime(-1);
        }
    };

private:
    std::list<Vertex<K, T>*> vertices_;
    unordered_map<K, Vertex<K, T>*> index_;
};
