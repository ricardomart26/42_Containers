#include "inc.hpp"

void    print_table()
{
    std::string n[] = {"Constructor", "Push_back"};
    std::cout << " " << std::string(51, '*') << "\n";
    for (size_t i = 0; i < 2; i++)
    {
	    std::cout << "*" << std::string(51, ' ') << "*\n";
	    std::cout << "*\t\t" << i <<". Vector " << n[i] << std::string(26 - n[i].size(), ' ') << "*\n"; 
    }
	std::cout << "*" << std::string(51, ' ') << "*\n" << " " << std::string(51, '*') << "\n";
}

void    vector_test()
{
    void (*fn[10])() = {&constructor_test, &push_back_test};

	system("clear");
    print_table();

    std::string answer;
    std::cout << "Enter a number to choose option: ";
    std::getline(std::cin, answer);
    std::cout << std::endl;
    fn[atoi(answer.c_str())]();
}

int main()
{
	system("clear");
	std::cout << "\nWhich STL you want to test?\n\n\t0. vector\n\t1.  map\n\n";
    std::string answer;
    std::cout << "Enter a number to choose option: ";
    std::getline(std::cin, answer);

    if (answer == "0")
    {
        vector_test();
    }
	// 	std::cout << GREEN << "[OK]" << RESET << std::endl;

}
