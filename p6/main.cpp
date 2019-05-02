#include <iostream>
#include "bbtree.hpp"
#include "dni.hpp"

int main(void) {
    aeda::bbtree<int> tree;

    tree.insert(10);
    tree.insert(3);
    tree.insert(33);
    tree.insert(2);
    tree.insert(20);
    tree.insert(4);
    tree.insert(31);

    tree.remove(33);

    tree.printTree();
    return 0;
}
