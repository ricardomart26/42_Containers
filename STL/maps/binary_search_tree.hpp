#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <utility>
#include <string>
#include <iostream>

class bst {
    
    public:

        typedef std::pair<std::string, int> value_type;
        
        typedef struct s_node
        {
            value_type _data;
            struct s_node *_left;
            struct s_node *_right;
        } t_node;

        bst()
        {
            head = new t_node;
            head->_data = std::make_pair("random", 3);
            head->_left = NULL;
            head->_right = NULL;
        }

        bool    compare(const std::pair<std::string, int>& elem, const std::pair<std::string, int>& toAdd)
        {
            // random vs random2
            return (elem.first < toAdd.first);
        }

        ~bst() {};

        void    add_node(t_node *node, const std::pair<std::string, int>& type)
        {
            static int counter = 0;
            if (!compare(node->_data, type)) {
                // std::cout << "smaller\n";

                if (node->_left == NULL) {
                    node->_left = new t_node;
                    node->_left->_data = type;
                    // std::cout << counter++ << ": " << node->_left->_data.first << " (left) " << std::endl;
                } else {
                    // std::cout << "(left) no add\n";
                    add_node(node->_left, type);
                }
            } else {
                // std::cout << "bigger\n";
                if (node->_right == NULL) {
                    node->_right = new t_node;
                    node->_right->_data = type;
                    // std::cout << counter++ << ": " << node->_right->_data.first << " (right) " << std::endl;
                } else {
                    // std::cout << "(right) no add\n";
                    add_node(node->_right, type);
                }
            }
        }

        int find_width(t_node *node, int w)
        {
            static int ret = 0;
            int save_ret;

            if (w > ret)
                ret = w;
            if (node->_left != NULL)
                if ((save_ret = find_width(node->_left, ++w)) > ret)
                    ret = save_ret;
            if (node->_right != NULL)
                if ((save_ret = find_width(node->_right, ++w)) > ret)
                    ret = save_ret;

            if (node == head)
                return (ret - 1);
            return (w);
        }

        void    print_bst() {
            static int nv = 1;
            static t_node *my_node = head;
            int i = 0;
            int width = find_width(head, 0);
            std::cout << "width: " << width << std::endl;
            return;
            if (nv == 1) {
                std::cout << "\t\t" << head->_data.first << "\t\t\n";
            }
            static t_node *myLeft = head->_left;
            static t_node *myRight = head->_right;
            std::cout << "Chegou aqui!\n";
            while (i < nv)
            {
                if (myLeft != NULL)
                    std::cout << "\t" << myLeft->_data.first << "\t";
                if (myRight != NULL)
                    std::cout << "\t" << myRight->_data.first << "\t";
                i++;
                if (i == nv)
                    std::cout << "\n";
            }
            nv++;
            my_node = myLeft;
            if (!myLeft && !myRight)
                return ;
            print_bst();
        }

        t_node *getHead() const
        {
            return (head);
        }

    private:

        t_node *head;
};

#endif
