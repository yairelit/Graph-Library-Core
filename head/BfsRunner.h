#pragma once
#include <queue> // Required for the queue data structure
#include "Graph.h"
#include "Vertex.h"

class BfsRunner {
public:
    template <typename K, typename T>
    static void BFS(Graph<K, T>& g, Vertex<K, T>* source) {

        //Reset the results of earlier searchs
        g.reset();

        // Initialize the queue for managing the frontier
        std::queue<Vertex<K, T>*> q;

        // Configure the source vertex
        source->setColor(GRAY);       // Mark as discovered
        source->setDist(0);           // Distance from itself is 0
        source->setParent(nullptr);   // Root has no parent

        q.push(source);

        // Main BFS loop
        while (!q.empty()) {
            // Dequeue the next vertex to process
            Vertex<K, T>* u = q.front();
            q.pop();

            // Iterate over all adjacent vertices (neighbors)
            for (Vertex<K, T>* v : u->neighbors()) {
                // If vertex is unvisited (WHITE), process it
                if (v->getColor() == WHITE) {
                    v->setColor(GRAY);            // Mark as discovered
                    v->setDist(u->getDist() + 1); // Update distance
                    v->setParent(u);              // Set parent for path reconstruction
                    q.push(v);                    // Enqueue for future processing
                }
            }

            // Mark the current vertex as fully processed (BLACK)
            u->setColor(BLACK);
        }
    }
};