#include "equal.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../vector/vector.hpp"

bool    predict(int x, int y) {return (x >= y);}

int main(void)
{
    ft::vector<int> vec;
    ft::vector<int> vec2;

    std::vector<int> std_vec;
    std::vector<int> std_vec2;

    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i);
        vec2.push_back(i);
        std_vec.push_back(i);
        std_vec2.push_back(i);
    }

    // vec.push_back(20);
    vec2.push_back(20);

    if (ft::equal(vec.begin(), vec.end(), vec2.begin()))
        std::cout << "they are equal\n";
    else
        std::cout << "they are not equal\n";


    if (ft::equal(vec.begin(), vec.end(), vec2.begin()))
        std::cout << "they are equal\n";
    else
        std::cout << "they are not equal\n";



    if (ft::equal(vec.begin(), vec.end(), vec2.begin(), predict))
        std::cout << "they are equal\n";
    else
        std::cout << "they are not equal\n";


    // Segfaul dont know why?

    // std_vec.push_back(20);
    std_vec2.push_back(20);

    if (std::equal(std_vec.begin(), std_vec.end(), std_vec2.begin()))
        std::cout << "they are equal\n";
    else
        std::cout << "they are not equal\n";

    if (std::equal(std_vec.begin(), std_vec.end(), std_vec2.begin(), predict))
        std::cout << "they are equal\n";
    else
        std::cout << "they are not equal\n";
    return (0);
}