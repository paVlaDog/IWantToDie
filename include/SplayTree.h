#pragma once

#include <vector>

struct Node
{
    Node * left = nullptr;
    Node * right = nullptr;
    Node * parent = nullptr;
    int value = 0;
    Node(int v, Node * l, Node * r)
    {
        value = v;
        left = l;
        right = r;
    }
    ~Node()
    {
    }
};

class SplayTree
{
private:
    mutable Node * root = nullptr;
    std::size_t length = 0;

public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();
};
