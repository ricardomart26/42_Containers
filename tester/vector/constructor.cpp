
#include "../inc.hpp"

#ifndef FT
    #define FT 1
#endif

// #if FT==1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
//     // #include "../STL/vector/vector.hpp"
// #endif


template <typename T>
void    print_vec_info(ft::vector<T> vec)
{
    std::cout << "\n";
    if (vec.empty())
        std::cout << "Empty: YES\n";
    else
        std::cout << "Empty: NO\n";
    
    std::cout << "SIZE: " << vec.size() << std::endl;
    std::cout << "CAPACITY: " << vec.capacity() << std::endl;
    
    ft::vector<int>::iterator it = vec.begin();
    std::cout << "ELEMENTS: [ ";
    for (; it != vec.end(); it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << "\\0 ]\n\n";
}

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

void	constructor_test()
{
    {
        std::cout << "<<<<<<<<<<<  Default constructor  >>>>>>>>>>>>" << std::endl;
        ft::vector<int> vecA;
        print_vec_info(vecA);
    }

    {
        std::cout << "<<<<<<<<<<<  Constructor with size  >>>>>>>>>>>>" << std::endl;
        ft::vector<int> vecA(10);
        ft::vector<int> vecB(0);
        try {
            ft::vector<int> vecC(-10);
            print_vec_info(vecC);
        } catch (const std::exception &e) {
            e.what();
        }
        print_vec_info(vecA);
        print_vec_info(vecB);
    }

    {
        // std::cout << "<<<<<<<<<<<    >>>>>>>>>>>>" << std::endl;
    }
    // std::cout << "" << std::endl;
	// ft::vector<int> vecB(10);
    // std::cout << "" << std::endl;
	// ft::vector<int> vecC(10);
    
}



int main(int ac, char **av)
{
	std::map<size_t, std::map<std::string, void (*fn[10])()> > categories;
	
	
	void	(*fn[10])() = { &constructor_test, &push_back_test};
	// void	(*fn)() = &constructor_test;

	(void)av;
	std::cout << "\nWhich STL you want to test?\n\n\t0. vector\n";
	if (ac == 2)
	{
	
		std::cout << GREEN << "[OK]" << RESET << std::endl;
	}

}
