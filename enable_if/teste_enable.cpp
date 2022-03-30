#include <iostream>
#include "enable_if.hpp"

int main( void )
{
    ft::enable_if<(0 > 0), bool>::type should_be_bool;
    should_be_bool = true;
    if (should_be_bool)
        std::cout << "E boolean\n";
}