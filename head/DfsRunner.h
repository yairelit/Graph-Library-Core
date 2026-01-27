#pragma once
#include "Graph.h"
#include "Vertex.h"
#include "DfsResult.h"

class DfsRunner {
public:
    template <typename K, typename T>
    static DfsResult<K, T> DFS(Graph<K, T>& g) {
        DfsResult<K, T> res;
        int time = 0;

        // Step 1: Initialize all vertices (Reset colors and parents)
        // Note: Assuming Graph has a public method 'getVertices()' returning the list
        for (Vertex<K, T>* v : g.getVertices()) {
            v->setColor(WHITE);
            v->setParent(nullptr);
            v->setDiscoverTime(0);
            v->setFinishTime(0);
        }

        // Step 2: Iterate over all vertices to handle disconnected graphs (DFS Forest)
        for (Vertex<K, T>* v : g.getVertices()) {
            if (v->getColor() == WHITE) {
                res.incNumTrees();
                DFSVisit(v, time, res);
            }
        }

        return res;
    }

private:

    // Recursive helper function for DFS traversal
    template <typename K, typename T>
    static void DFSVisit(Vertex<K, T>* u, int& time, DfsResult<K, T>& res) {
        // 1. Mark as discovered (GRAY) and set discovery time
        u->setColor(GRAY);
        u->setDiscoverTime(++time);

        // 2. Iterate over all neighbors
        for (Vertex<K, T>* v : u->neighbors()) {
            if (v->getColor() == WHITE) {
                // Tree Edge: Visiting a new vertex
                res.incTree();
                v->setParent(u);
                DFSVisit(v, time, res);
            }
            else if (v->getColor() == GRAY) {
                // Back Edge: Cycle detected (pointing to an ancestor)
                res.incBack();
            }
            else { // v is BLACK
                // Check if it's Forward or Cross edge based on discovery times
                if (u->getDiscoverTime() < v->getDiscoverTime()) {
                    res.incForward(); // Pointing to a descendant
                }
                else {
                    res.incCross();   // Pointing to a different branch
                }
            }
        }

        // 3. Mark as finished (BLACK), set finish time, and add to topological sort
        u->setColor(BLACK);
        u->setFinishTime(++time);
        res.onFinish(u);
    }
};