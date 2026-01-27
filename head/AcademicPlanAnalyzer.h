#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <map>
#include <list>
#include <algorithm> // for std::replace, std::all_of
#include <sstream>   // for std::istringstream
#include <locale>    // for std::locale

#include "Graph.h"
#include "Vertex.h"
#include "DfsResult.h"
#include "DfsRunner.h"
#include "CourseData.h"

class AcademicPlanAnalyzer {
public:
    // Constructor: Loads the graph from the file
    AcademicPlanAnalyzer(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file " + path);
        }

        int numCourses = 0;
        if (!(file >> numCourses)) {
            throw std::runtime_error("Error: Failed to read number of courses.");
        }

        // 1. Load Courses (Vertices)
        for (int i = 0; i < numCourses; ++i) {
            std::string name;
            std::string creditsStr;

            // Read as string to avoid locale crashes
            file >> name >> creditsStr;

            // Handle comma/dot decimal separator manually
            std::replace(creditsStr.begin(), creditsStr.end(), ',', '.');
            double credits = 0.0;
            try {
                std::istringstream iss(creditsStr);
                iss.imbue(std::locale::classic());
                iss >> credits;
            }
            catch (...) { credits = 0.0; }

            CourseData data(name, credits);
            g_.addVertex(name, data);
        }

        // 2. Universal Edge Loader (Handles explicit count, no count, or headers)
        std::string token;
        while (file >> token) {
            // Check if the token is a purely numeric count
            bool isNumber = !token.empty() && std::all_of(token.begin(), token.end(), ::isdigit);

            if (isNumber) {
                // Scenario A: It's the number of edges (standard format)
                int numPrereqs = std::stoi(token);
                for (int i = 0; i < numPrereqs; ++i) {
                    std::string uKey, vKey;
                    file >> uKey >> vKey;

                    Vertex<std::string, CourseData>* u = g_.getVertex(uKey);
                    Vertex<std::string, CourseData>* v = g_.getVertex(vKey);
                    if (u && v) {
                        g_.addEdge(u, v);
                    }
                }
                // If we found the count and finished the loop, we assume we are done or format is consistent
                // Continue to read just in case there are more blocks, or break if that's standard.
                // Safest is to break if we strictly expect one block of edges.
                break;
            }
            else {
                // Scenario B: It's NOT a number (maybe a header "Prerequisites" or a course name)
                // If it's a known course, treat 'token' as the first part of an edge.
                Vertex<std::string, CourseData>* u = g_.getVertex(token);
                if (u != nullptr) {
                    // It's a valid course! Must be an edge pair without a count.
                    std::string vKey;
                    file >> vKey; // Read the second part
                    Vertex<std::string, CourseData>* v = g_.getVertex(vKey);
                    if (v) {
                        g_.addEdge(u, v);
                    }
                }
                // If u is nullptr, it might be a header like "Prerequisites:", so we just ignore 'token' and loop again.
            }
        }

        file.close();
    }

    ~AcademicPlanAnalyzer() = default;

    bool hasCycle() {
        runDfsIfNeeded();
        return dfsResult_.hasCycle();
    }

    int minimalSemesters() {
        if (hasCycle()) {
            return -1;
        }

        std::list<Vertex<std::string, CourseData>*> topoOrder = dfsResult_.topologicalOrderOrEmpty();
        std::map<std::string, int> semesterMap;
        int globalMaxSemesters = 0;

        for (Vertex<std::string, CourseData>* u : topoOrder) {
            std::string uKey = u->getKey();

            if (semesterMap.find(uKey) == semesterMap.end()) {
                semesterMap[uKey] = 1;
            }

            if (semesterMap[uKey] > globalMaxSemesters) {
                globalMaxSemesters = semesterMap[uKey];
            }

            for (Vertex<std::string, CourseData>* v : u->neighbors()) {
                std::string vKey = v->getKey();
                if (semesterMap[vKey] < semesterMap[uKey] + 1) {
                    semesterMap[vKey] = semesterMap[uKey] + 1;
                }
            }
        }

        if (globalMaxSemesters == 0 && !topoOrder.empty()) return 1;
        return globalMaxSemesters;
    }

private:
    Graph<std::string, CourseData> g_;
    bool hasDfs_ = false;
    DfsResult<std::string, CourseData> dfsResult_;

    void runDfsIfNeeded() {
        if (!hasDfs_) {
            dfsResult_ = DfsRunner::DFS(g_);
            hasDfs_ = true;

            std::cout << "DFS completed, found "
                << dfsResult_.getNumTrees() << " trees, "
                << dfsResult_.treeEdges() << " tree edges, "
                << dfsResult_.backEdges() << " back edges, "
                << dfsResult_.forwardEdges() << " forward edges, "
                << dfsResult_.crossEdges() << " cross edges"
                << std::endl;
        }
    }
};