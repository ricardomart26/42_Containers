#include "../inc.hpp"

void	push_back_test()
{

        ft::vector<int> vecA(10);
        ft::vector<int> vecB(10);
        ft::vector<int> vecC(10);
        ft::vector<int> vecD(10);

        for (int i = 0; i < 10; i++)
            vecA.push_back(i);

        int i = 0;
        for (ft::vector<int>::iterator it = vecA.begin(); it != vecA.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        
        std::cout << "\n<<<<<<<<<<<  Push back  >>>>>>>>>>>>\n";
        vecA.push_back(20);
        i = 0;
        for (ft::vector<int>::iterator it = vecA.begin(); it != vecA.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "last element: " << vecA[vecA.size() - 1] << "\n";
        std::cout << "size: " << vecA.size() << "\n";
}
