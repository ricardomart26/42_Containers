#include "map.hpp" 
#include <iostream>
#include <string>

int main( void )
{
    ft::map<std::string, int> map_test;
    map_test.insert(ft::pair<const std::string, int>("random", 2));
    
}