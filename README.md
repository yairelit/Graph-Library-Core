# Graph Algorithms Implementation (C++)

A robust and efficient C++ implementation of graph data structures and fundamental traversal algorithms. This project focuses on clean code, Object-Oriented Programming (OOP) principles, and optimal algorithmic performance.

## 🚀 Overview
This repository provides a framework for building and manipulating graphs (both directed and undirected). It features the two most essential search algorithms in computer science:

* **BFS (Breadth-First Search):** Used for level-order traversal and finding the shortest path in unweighted graphs.
* **DFS (Depth-First Search):** Used for exhaustive pathfinding, cycle detection, and topological sorting.



## 🛠 Key Features
* **Adjacency List Representation:** Implemented using `std::vector` for memory efficiency in sparse graphs.
* **Performance:** Algorithms are optimized with a time complexity of $O(V + E)$ and space complexity of $O(V)$.
* **Modular Design:** Separated interface (`.hpp`) and implementation (`.cpp`) for better maintainability.

## 📁 Project Structure
* `include/`: Header files defining the Graph and Algorithm classes.
* `src/`: Source files containing the logic for graph manipulation and traversals.
* `main.cpp`: A demonstration file showcasing graph creation and algorithm execution.

## 💻 Getting Started

### Prerequisites
* A C++ compiler (e.g., `g++` or `clang`) supporting C++11 or higher.

### Installation & Execution
1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/your-username/Graph-Algorithms-Cpp.git](https://github.com/your-username/Graph-Algorithms-Cpp.git)
    ```
2.  **Navigate to the project folder:**
    ```bash
    cd Graph-Algorithms-Cpp
    ```
3.  **Compile the project:**
    ```bash
    g++ -I include src/*.cpp -o graph_app
    ```
4.  **Run the application:**
    ```bash
    ./graph_app
    ```

## 📜 License
This project is licensed under the MIT License.
