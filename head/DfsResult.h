#pragma once
#include <list>
#include "Vertex.h"

template <typename K, typename T>
class DfsResult {
public:
    DfsResult() : tree_(0), back_(0), forward_(0), cross_(0), numTrees_(0) {}

    void incTree() { ++tree_; }
    void incBack() { ++back_; }
    void incForward() { ++forward_; }
    void incCross() { ++cross_; }
    void incNumTrees() { ++numTrees_; }
    int getNumTrees() const { return numTrees_; }

    int treeEdges() const { return tree_; }
    int backEdges() const { return back_; }
    int forwardEdges() const { return forward_; }
    int crossEdges() const { return cross_; }

    bool hasCycle() const { return back_ > 0; }

    void onFinish(Vertex<K, T>* v) {
        // TBD: complete
        topo_.push_front(v);
    }

    std::list<Vertex<K, T>*> topologicalOrderOrEmpty() const {
        // TBD: complete
        if (hasCycle()) return std::list<Vertex<K, T>*>();
        return topo_;
    }

private:
    int tree_, back_, forward_, cross_;
    std::list<Vertex<K, T>*> topo_;
    int numTrees_ = 0;
};
