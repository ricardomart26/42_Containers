#include "binary_search_tree.hpp"

int main(void) {
    bst tree;

    std::cout << "../\n";
    tree.add_node(tree.getHead(), std::make_pair("random2", 4));
    tree.add_node(tree.getHead(), std::make_pair("rando", 5));
    tree.add_node(tree.getHead(), std::make_pair("rand", 3));
    tree.add_node(tree.getHead(), std::make_pair("ran", 2));
    // tree.add_node(tree.getHead(), std::make_pair("ra", 1));
    // tree.add_node(tree.getHead(), std::make_pair("r", 0));
    tree.add_node(tree.getHead(), std::make_pair("random22", 6));
    // tree.add_node(tree.getHead(), std::make_pair("random222", 7));
    tree.print_bst();
    if (std::string("teste") < std::string("teste2"))
        std::cout << "E menor amigos!\n";
    return (0);
}