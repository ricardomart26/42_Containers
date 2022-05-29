#include "binary_search_tree.hpp"
#include <map>
int main(void) {
    bst<>   tree;

    std::cout << "../\n";
    tree.add_node(std::make_pair("random2", 4));
    std::cout << "../\n";
    tree.add_node(std::make_pair("rando", 5));
    std::cout << "../\n";
    tree.add_node(std::make_pair("rand", 3));
    std::cout << "../\n";
    tree.add_node(std::make_pair("ran", 2));
    std::cout << "../\n";
    // tree.add_node(std::make_pair("ra", 1));
    // tree.add_node(std::make_pair("r", 0));
    tree.add_node(std::make_pair("random22", 6));
    // tree.add_node(, std::make_pair("random222", 7));
    // tree.print_bst();

    return (0);
}