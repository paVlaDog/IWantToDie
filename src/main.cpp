#include "SplayTree.h"

#include <iostream>

int main()
{
    SplayTree tree;
    for (int i = 0; i < 10000000; ++i) {
        tree.insert(i);
        //std::cout << "Insert:" << tree.insert(i) << '\n';
    }
    std::cout << tree.size();
    std::cout << "Insert:" << tree.insert(1) << '\n';
    std::cout << "Insert:" << tree.insert(2) << '\n';
    std::cout << "Insert:" << tree.insert(3) << '\n';
    std::cout << "Insert:" << tree.insert(4) << '\n';
    std::cout << "Insert:" << tree.insert(9999999) << '\n';
    std::cout << "Contains:" << tree.contains(5000000) << '\n';
    std::cout << "Contains:" << tree.contains(9999999) << '\n';
    std::cout << "Contains:" << tree.contains(10000000) << '\n';
    std::cout << "Contains:" << tree.contains(-1) << '\n';
    std::cout << "Contains:" << tree.contains(1) << '\n';
    std::cout << tree.size();
}
