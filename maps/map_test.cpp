#include <map>
#include <iostream>

int main( void )
{
    std::map<std::string, int> map_test;
    std::pair<int, int> p(10, 2); 
    map_test.insert(p);
}