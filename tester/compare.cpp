#include "inc.hpp"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>

char    get_keys() 
{

    struct termios old;

    tcgetattr(0, &old);
    struct termios save = old;
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &old);

    char answer = getchar();

    old = save;
    tcsetattr(0, TCSANOW, &save);

    system("clear");
    return (answer);
}

int    print_table()
{
    int counter = 0;

    while (1) 
    {
        static std::string n[TEST_SIZE + 1] = {"Do All", "Constructor", "Push back", "Max size", "Resize", "Assign", "At", "Back"
        , "Clear", "Erase", "Front", "Get Allocator", "Insert", "Pop Back", "Reserve", "Swap" , "Operators"};

        std::cout <<  RED<< "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << RESET <<  "\n";
        std::cout << RED << "█" << YELLOW << std::string(23, ' ') <<  "VECTOR" << std::string(23, ' ') << RED<< "█\n";
        std::cout << RED << "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" <<  "\n";
        if (counter < 0)
            counter = 16;
        for (size_t i = 0; i < TEST_SIZE + 1; i++)
        {
            if (counter % 17 == i)
            {
                if (counter % 17 != 16 && i != 0)
                {
                    std::cout << RED << "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << "\n";
                    std::cout << "█\t" << RESET << RED << i << ".\t|\t" << YELLOW << n[i] << std::string(29 - n[i].size(), ' ') << RESET << RED<< "█\n" << RESET;
                    std::cout << RED << "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << "\n";
                } 
                else if (i != 0)
                {
                    std::cout << RED << "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << "\n";
                    std::cout << "█\t" << RESET << RED << i << ".\t|\t" << YELLOW << n[i] << std::string(29 - n[i].size(), ' ') << RESET << RED<< "█\n" << RESET;
                } 
                else
                {
                    std::cout << "█\t" << RESET << RED << i << ".\t|\t" << YELLOW << n[i] << std::string(29 - n[i].size(), ' ') << RESET << RED<< "█\n" << RESET;
                    std::cout << RED << "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << "\n";
                }
            }
            else
            {
                if (counter % 17 == i - 1)
                    std::cout << "█\t" << RESET << i << ".\t|\t" << n[i] << std::string(29 - n[i].size(), ' ') << RED<< "█\n" << RESET;
                else
                {
                    if (i != 0)
                        std::cout << RED << "█" << RESET << std::string(52, '-') << RED<< "█\n";
                    else
                    {
                    }
                    std::cout << "█\t" << RESET << i << ".\t|\t" << n[i] << std::string(29 - n[i].size(), ' ') << RED<< "█\n" << RESET;
                        // std::cout << "█" << std::string(50, ' ') << "█\n";
                }
            }
        }
	    std::cout <<  RED<< "█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << RESET <<  "\n";

        char answer = get_keys();

        if (answer == 's')
            counter++;
        else if (answer == 'w')
            counter--;

        if (answer == 10)
            return (counter % 17);
    }
}


void    vector_test()
{
    // void (*fn[TEST_SIZE])() = {&constructor_test, &push_back_test, &max_size_test, &resize_test,  &assign_test,  &at_test,
    // &back_test,  &clear_test,  &erase_test,  &front_test,  &get_allocator_test,  &insert_test,  &pop_back_test, &reserve_test,
    // &swap_test, &op_test};

    // int answer = 
    print_table();
    // if (answer % 17 == 0)
    //     for (int i = 0; i < TEST_SIZE; i++)
    //         fn[i]();
    // else
    //     fn[answer % 17]();

    std::cout << "Do you want to do another test? ";
    std::string line;
    std::getline(std::cin, line);
    std::for_each(line.begin(), line.end(), tolower);
    if (line == "y" || line == "yes" || line.empty())
        vector_test();
}

int main()
{
    system("clear");
    int counter = 0;
    while (1) 
    {
        std::cout << "\nWhich STL you want to test?\n";

        if (counter % 2 == 0)
            std::cout << YELLOW <<"\n\t ➾ Vector " << RESET << "\n\tMap\n\n";
        else
            std::cout << "\n\tVector " << YELLOW << "\n\t ➾ Map\n\n" RESET;

        char answer = get_keys();

        if (answer == 's')
            counter++;
        else if (answer == 'w')
            counter--;

        if (answer == 10)
        {
            if (counter % 2 == 0)
                vector_test();
            else
                std::cout << "Map not done Yet" << std::endl;
        }
    }
}
