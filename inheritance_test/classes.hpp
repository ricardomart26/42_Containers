#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <iostream>

class father
{

    public:

        father()
        {
            std::cout << "I'm daddy\n";
        }
        
        ~father()
        {
            std::cout << "daddy died\n";
        }

        father(const father &copy)
        {
            std::cout << "Copied father\n";
        }
        
        father  &operator=(const father &copy)
        {
            std::cout << "Assigned father\n";
            return (*this);
        }

    private:

        std::string name;
        int         age;

};

class son1 : public father
{
    public:

        son1() : myfather()
        {
            std::cout << "I'm an orphan son\n";
        }
        
        son1(const father &dad) : myfather()
        {
            std::cout << "I'm son with a dad\n";
        }

        ~son1()
        {
            std::cout << "son dead\n";
        }
        son1(const son1 &copy)
        {
            std::cout << "Copied son\n";
        }

        son1    &operator=(const son1 &copy)
        {
            std::cout << "Assigned son\n";
            return (*this);

        }

    private:

        std::string name;
        int         age;
        father      myfather;
};


#endif