#include "pair.hpp"
#include <iostream>



int main(void)
{


    {
        std::cout << "\n\t--------------------------------------\n";
        std::cout << "\t\t      make_pair \n";
        std::cout << "\t--------------------------------------\n\n";
        ft::pair <int,int> foo;
        ft::pair <int,int> bar;

        foo = ft::make_pair (10,20);
        bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

        std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
        std::cout << "bar: " << bar.first << ", " << bar.second << '\n';

        return 0;
    }
    {
        std::cout << "\n\t--------------------------------------\n";
        std::cout << "\t\t Overload operator\n";
        std::cout << "\t--------------------------------------\n\n";

        ft::pair<int,char> foo (10,'z');
        ft::pair<int,char> bar (90,'a');

        if (foo==bar) std::cout << "foo and bar are equal\n";
        if (foo!=bar) std::cout << "foo and bar are not equal\n";
        if (foo< bar) std::cout << "foo is less than bar\n";
        if (foo> bar) std::cout << "foo is greater than bar\n";
        if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
        if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

        return 0;
    }
    #if 0 

    {
        int lhs_first = 3;
        int rhs_first = 5;
        int lhs_second = 3;
        int rhs_second = 5;

        if (lhs_first < rhs_first || (rhs_first == lhs_first && lhs_second < rhs_second))
            std::cout << "MEU: Verdadeiro\n";
        else
            std::cout << "MEU: Falso\n";

        if (lhs_first < rhs_first || (!(rhs_first < lhs_first) && lhs_second < rhs_second))
            std::cout << "DEFAULT: Verdadeiro\n";
        else
            std::cout << "DEFAULT: Falso\n";

        lhs_first = 5;
        rhs_first = 3;
        lhs_second = 5;
        rhs_second = 3;

        if (lhs_first < rhs_first || (rhs_first == lhs_first && lhs_second < rhs_second))
            std::cout << "MEU: Verdadeiro\n";
        else
            std::cout << "MEU: Falso\n";

        if (lhs_first < rhs_first || (!(rhs_first < lhs_first) && lhs_second < rhs_second))
            std::cout << "DEFAULT: Verdadeiro\n";
        else
            std::cout << "DEFAULT: Falso\n";
        
        lhs_first = 5;
        rhs_first = 5;
        lhs_second = 3;
        rhs_second = 5;

        if (lhs_first < rhs_first || (rhs_first == lhs_first && lhs_second < rhs_second))
            std::cout << "MEU: Verdadeiro\n";
        else
            std::cout << "MEU: Falso\n";

        if (lhs_first < rhs_first || (!(rhs_first < lhs_first) && lhs_second < rhs_second))
            std::cout << "DEFAULT: Verdadeiro\n";
        else
            std::cout << "DEFAULT: Falso\n";
        
        
        lhs_first = 5;
        rhs_first = 3;
        lhs_second = 5;
        rhs_second = 5;

        if (lhs_first < rhs_first || (rhs_first == lhs_first && lhs_second < rhs_second))
            std::cout << "MEU: Verdadeiro\n";
        else
            std::cout << "MEU: Falso\n";

        if (lhs_first < rhs_first || (!(rhs_first < lhs_first) && lhs_second < rhs_second))
            std::cout << "DEFAULT: Verdadeiro\n";
        else
            std::cout << "DEFAULT: Falso\n";
        

        lhs_first = 2;
        rhs_first = 5;
        lhs_second = 5;
        rhs_second = 5;

        if (lhs_first < rhs_first || (rhs_first == lhs_first && lhs_second < rhs_second))
            std::cout << "MEU: Verdadeiro\n";
        else
            std::cout << "MEU: Falso\n";

        if (lhs_first < rhs_first || (!(rhs_first < lhs_first) && lhs_second < rhs_second))
            std::cout << "DEFAULT: Verdadeiro\n";
        else
            std::cout << "DEFAULT: Falso\n";
        

        return (0);

    }
    #endif
}
