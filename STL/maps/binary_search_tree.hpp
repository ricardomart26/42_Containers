#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <utility>
#include <string>
#include <iostream>
#include <memory>

template <typename key, typename T, typename allocator = std::allocator<std::pair<key, T> > >
class bst {
    
    public:

        typedef std::pair<std::string, int> value_type;
		typedef allocator			        allocator_type;
        
        typedef struct s_node
        {
            public:

                s_node(value_type type) {
                    _data = type;
                    _left = NULL;
                    _right = NULL;
                };

                friend std::ostream &operator<<(std::ostream &out, const struct s_node &node)
                {
                    out << "data: " << "[" << node._data.first << "] [" << node._data.second << "]\n";
                    return (out); 
                }

                value_type _data;
                struct s_node *_left;
                struct s_node *_right;
                allocator_type _alloc;

        } t_node;

    
        typedef std::allocator<t_node>      allocator_node;

        bool    compare(const value_type &elem, const value_type &toAdd)
        {
            return (elem.first < toAdd.first);
        }
        
        bst() : _head(NULL) cmp_ptr() {}

        ~bst() {};

        void    wrapper_add_node(t_node *node, const value_type &type)
        {
            if (!compare(node->_data, type)) {
                if (node->_left == NULL) {
                    node->_left = _alloc_node.allocate(1);
                    _alloc_node.construct(node->_left, t_node(type));
                    return ;
                }
                wrapper_add_node(node->_left, type);
            } 
            else {
                if (node->_right == NULL) {
                    node->_right = _alloc_node.allocate(1);
                    _alloc_node.construct(node->_right, t_node(type));
                    return ;
                }
                wrapper_add_node(node->_right, type);
            }
        }

        void    add_node(const value_type &type)
        {  
            if (_head == NULL)
            {
                _head = _alloc_node.allocate(1);
                _alloc_node.construct(_head, t_node(type));
            }
            else
                wrapper_add_node(getHead(), type);
        }

        // int find_width(t_node *node, int w)
        // {
        //     static int ret = 0;
        //     int save_ret;

        //     if (w > ret)
        //         ret = w;
        //     if (node->_left != NULL)
        //         if ((save_ret = find_width(node->_left, ++w)) > ret)
        //             ret = save_ret;
        //     if (node->_right != NULL)
        //         if ((save_ret = find_width(node->_right, ++w)) > ret)
        //             ret = save_ret;

        //     if (node == _head)
        //         return (ret - 1);
        //     return (w);
        // }

        // void    print_bst(t_node *node) {
        //     static size_t nv = 1;
        //     static t_node *my_node = head;
        //     size_t width = find_width(head, 0);
        //     static size_t size = 71;

        //     if (nv == 1) 
        //         std::cout << "\t\t" << _head->_data.first << "\t\t\n";

        //     static t_node *myLeft = _head->_left;
        //     static t_node *myRight = _head->_right;
        //     for (size_t i = 0; i < nv; i++)
        //     {
        //         if (myLeft != NULL)
        //             std::cout << std::string(width / 65, ' ') << myLeft->_data.first << "\t";
        //         if (myRight != NULL)
        //             std::cout << "\t" << myRight->_data.first << "\t";
        //         i++;
        //         if (i == nv)
        //             std::cout << "\n";
        //     }
        //     nv++;
        //     // my_node = myLeft;
        //     if (!myLeft && !myRight)
        //         return ;
        //     print_bst();
        // }

        t_node *getHead() const { return (_head); }

    private:

        allocator_type _alloc;
        allocator_node _alloc_node;
        t_node *_head;
        bool    (*cmp_ptr)(const value_type&, const value_type&);    
};

#endif
