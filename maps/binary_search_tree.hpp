#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <utility>

class bst {
    
    public:

        typedef std::pair<std::string, int> value_type;
        
        bst()
        {
            head = this;
            head = new bst;
            head->_data = std::make_pair("random", 3);
            head->_left = NULL;
            head->_right = NULL;
        }

        bool    compare(const value_type& elem, const value_type& toAdd)
        {
            return (elem.first() < toAdd.first());
        }

        ~bst();

        void    add_node(const value_type& type)
        {
            static bst *temp = head;
            if (compare(temp->_data, type)) {
                if (temp->_left == NULL) {
                    temp->_left = new bst;
                    temp->_left->_data = type;
                    return ;
                } else {
                    temp = _left;
                    add_node(type);
                }
            } else {
                if (_right == NULL) {
                    temp->_right = new bst;
                    temp->_right->_data = type;
                    return ;
                } else {
                    temp = _right;
                    add_node(type);
                }
            }
            return ;
        }
    
    private:

        value_type _data;
        bst *head;
        bst *_left;
        bst *_right;
};

#endif
