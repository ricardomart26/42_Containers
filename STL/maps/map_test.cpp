#include "map.hpp" 
#include "../vector/vector.hpp" 
#include <iostream>
#include <vector>
#include <string>
#include <map>

int main( void )
{
    ft::map<std::string, int> map_test;
    map_test.insert(ft::make_pair("random",  2));    
}