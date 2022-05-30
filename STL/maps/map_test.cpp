#include "map.hpp" 
#include "../vector/vector.hpp" 
#include <iostream>
#include <vector>
#include <string>
#include <map>

int main( void )
{
    ft::map<std::vector<int>, int> map_test;
    std::vector<int> vec;
    map_test.insert(ft::make_pair(vec,  2));    
}