
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

            			// void    new_add_node(const value_type &val)
			// { 
			// 	static t_node *node = _head;
			// 	if (_head == NULL)
			// 	{
			// 		_head = _alloc_node.allocate(1);
			// 		_alloc_node.construct(_head, t_node(val));
			// 	}
			// 	else 
			// 	{
			// 		if (node->_data.first == val.first)
			// 			return ;
			// 		if (!_comp(node->_data, val)) 
			// 		{
			// 			if (node->_left == NULL)
			// 			{
			// 				node->_left = _alloc_node.allocate(1);
			// 				_alloc_node.construct(node->_left, t_node(val));
			// 				node->_left->_parent = node;
			// 				return ;
			// 			}
			// 			std::cout << node << std::endl;
			// 			node = node->_left;
			// 			new_add_node(val);
			// 		} 
			// 		else 
			// 		{
			// 			if (node->_right == NULL) 
			// 			{
			// 				node->_right = _alloc_node.allocate(1);
			// 				_alloc_node.construct(node->_right, t_node(val));
			// 				node->_right->_parent = node;
			// 				return ;
			// 			}
			// 			std::cout << node << std::endl;
			// 			node = node->_right;
			// 			new_add_node(val);
			// 		}
			// 	}
			// }


			// bool    compare(const value_type &elem, const value_type &toAdd)
			// {
			//     return (elem.first < toAdd.first);
			// }