#include "map.hpp" 
#include <iostream>
#include <string>

int main( void )
{
    ft::map<std::string, int> map_test;
    std::pair<int, int> p(10, 2); 
    map_test.insert(p);
}