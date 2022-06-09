#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include "map.hpp"
#include "map_iterator.hpp"

namespace ft 
{
	template <typename value_type>
	struct t_node 
	{
		public:
			typedef typename value_type::first_type		key_type;
			typedef typename value_type::second_type	mapped_type;

			t_node(value_type &type) 
			{
				_data = type;
				_left = NULL;
				_right = NULL;
				_parent = NULL;
			};

			friend std::ostream &operator<<(std::ostream &out, const struct t_node &node)
			{
				out << "data: " << "[" << node._data.first << "] [" << node._data.second << "]\n";
				return (out); 
			}

			key_type	&getKey() const  { return (_data.first); }

			mapped_type	&getMapped() const { return (_data.second); }

			value_type _data;
			t_node<value_type> *_left;
			t_node<value_type> *_right;
			t_node<value_type> *_parent;
	};

	// template <typename key, typename T, typename compare = std::less<key>, typename allocator = std::allocator<std::pair<key, T> > >
	template <typename value_type, typename compare>
	class bst {

		public:

			typedef typename value_type::first_type		key_type;
			typedef typename value_type::second_type	mapped_type;
			typedef t_node<value_type>					node;
			typedef value_type*							pointer;
			typedef std::allocator<node>				allocator_node;
			typedef bst_iterator<value_type, compare>	iterator;

			bst(const compare comp = compare()) : _head(NULL), _comp(comp), _size(0) {}

			~bst() 
			{
				if (_head != NULL)
					delete (_head);
				else
					return ;
				if (_head->_left != NULL)
					delete (_head->_left);
				if (_head->_right != NULL)
					delete (_head->_right);

			}

			node	*_wrapper_add_node_(node *n, const value_type &val)
			{
				if (n == NULL)
				{
					n = _alloc_node.allocate(1);
					_alloc_node.construct(n, node(val));
					_size++;
					return n;
				}
				if (n->_data.first == val.first)
					return NULL;
				if (!_comp(n->_data, val))
				{
					if (n->_left == NULL)
					{
						n->_left = _alloc_node.allocate(1);
						_alloc_node.construct(n->_left, node(val));
						n->_left->_parent = n;
						_size++;
						return n;
					}
					_wrapper_add_node(n->left, val);
				} 
				else 
				{
					if (n->_right == NULL) 
					{
						n->_right = _alloc_node.allocate(1);
						_alloc_node.construct(n->_right, node(val));
						n->_right->_parent = n;
						_size++;
						return n;
					}
					_wrapper_add_node(n->right, val);
				}
			}

			ft::map_iterator    add_node(const value_type &val)
			{
				ft::map_iterator it = _wrapper_add_node_(getHead(), val);
				return (it);
			}

			mapped_type	_wrapper_search_node_(const node *node, const key_type &find) const 
			{
				if (node->getKey() == find)
					return (node->getMapped());
				if (!_comp(node->getKey(), find)) {
					if (node->_left == NULL)
						_wrapper_search_node_(node->_left, find); // Ver se os lados estão certos
				} else {
					_wrapper_search_node_(node->_right, find); // Ver se os lados estão certos
				}
			}

			pointer	find_max() const 
			{
				node *temp = _head;
				while (temp != NULL)
					temp = temp->_right;
				return (temp);
			}

			pointer	find_min() const 
			{
				node *temp = _head;
				while (temp != NULL)
					temp = temp->_left;
				return (temp);
			}

			mapped_type   &search_node(const key_type &find) const
			{
				if (_head->getKey() == find)
					return (_head->getMapped());
				return (_wrapper_search_node_(getHead(), find));
			}

			node *getHead() const { return (_head); }

		protected:

			allocator_node  _alloc_node;
			node			*_head;
			compare         _comp;
			size_t			_size;
			// bool    (*cmp_ptr)(const value_type&, const value_type&);    
	};

	template <typename value_type, typename compare>
	class bst_iterator
	{
		public:

			typedef value_type* pointer;

			bst_iterator() : _ptr(NULL) {}

			bst_iterator(const pointer ptr) : _ptr(ptr) {}

			

		private:
			pointer _ptr;
	};
}

#endif
