#pragma once
#include <list>

enum Color { WHITE, GRAY, BLACK };

template <typename K, typename T>
class Vertex {
public:
    Vertex(const K& key, const T& data)
        : key_(key), data_(data), color_(WHITE), parent_(nullptr), dist_(-1),
          discoverTime_(-1), finishTime_(-1) {}

    const K& getKey() const { return key_; }
    T& getData() { return data_; }
    const T& getData() const { return data_; }

    void addNeighbor(Vertex* v) { neighbors_.push_back(v); }
    const std::list<Vertex*>& neighbors() const { return neighbors_; }

    Color getColor() const { return color_; }
    void setColor(Color c) { color_ = c; }

    Vertex* getParent() const { return parent_; }
    void setParent(Vertex* p) { parent_ = p; }

    int getDist() const { return dist_; }
    void setDist(int d) { dist_ = d; }

    int getDiscoverTime() const { return discoverTime_; }
    void setDiscoverTime(int t) { discoverTime_ = t; }

    int getFinishTime() const { return finishTime_; }
    void setFinishTime(int t) { finishTime_ = t; }

private:
    K key_;
    T data_;
    std::list<Vertex*> neighbors_;

    Color color_;
    Vertex* parent_;
    int dist_;
    int discoverTime_;
    int finishTime_;
};
