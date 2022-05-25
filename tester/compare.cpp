#include "inc.hpp"

void    print_table()
{
    std::string n[TEST_SIZE + 1] = {"Do All", "Constructor", "Push back", "Max size", "Resize", "Assign", "At", "Back"
    , "Clear", "Erase", "Front", "Get Allocator", "Insert", "Pop Back", "Reserve", "Swap" , "Operators"};
    std::cout << " " << std::string(51, '*') << "\n";
    int helper = 0;
    for (size_t i = 0; i < TEST_SIZE + 1; i++)
    {
        if (i == 10)
            helper = 1;
	    std::cout << "*" << std::string(51, ' ') << "*\n";
	    std::cout << "*\t\t" << i <<". Vector " << n[i] << std::string(26 - n[i].size() - helper, ' ') << "*\n"; 
    }
	std::cout << "*" << std::string(51, ' ') << "*\n" << " " << std::string(51, '*') << "\n";
}

void    vector_test()
{
    void (*fn[TEST_SIZE])() = {&constructor_test, &push_back_test, &max_size_test, &resize_test,  &assign_test,  &at_test,
    &back_test,  &clear_test,  &erase_test,  &front_test,  &get_allocator_test,  &insert_test,  &pop_back_test, &reserve_test,
    &swap_test, &op_test};

	system("clear");
    print_table();
    std::string answer;
    std::cout << "Enter a number to choose option: ";
    std::getline(std::cin, answer);
    std::cout << std::endl;
    if (answer == "0")
    {
        for (int i = 0; i < TEST_SIZE; i++)
            fn[i]();
    }
    else
        fn[atoi(answer.c_str()) - 1]();

    std::cout << "Do you want to do another test? ";
    std::getline(std::cin, answer);
    std::for_each(answer.begin(), answer.end(), tolower);
    
    if (answer == "y" || answer == "yes" || answer.empty())
        vector_test();

}

int main()
{
	system("clear");
	std::cout << "\nWhich STL you want to test?\n\n\t0. Vector\n\t1. Map\n\n";
    std::cout << "Enter a number to choose option: ";
    std::string answer;
    std::getline(std::cin, answer);

    if (answer == "0")
    {
        vector_test();
    }
	// 	std::cout << GREEN << "[OK]" << RESET << std::endl;

}
