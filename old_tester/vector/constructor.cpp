
#include "../inc.hpp"

void	constructor_test()
{

    std::string filename(VECTOR_OUTPUT_DIR + std::string("constructor.txt"));
    std::cout << filename << std::endl;
    std::ofstream file(filename.c_str());

    if (file.bad())
    {
        std::cerr << "Error creating file\n";
        return ;
    }
    
        file << "<<<<<<<<<<<  Default constructor  >>>>>>>>>>>>" << std::endl;
        ft::vector<int> vecA;
        print_vec_info(vecA, file);

    {
        file << "<<<<<<<<<<<  Constructor with size  >>>>>>>>>>>>" << std::endl;
        ft::vector<int> vecA(10);
        ft::vector<int> vecB(0);
        try {
            ft::vector<int> vecC(-10);
            print_vec_info(vecC, file);
        } catch (const std::exception &e) {
            e.what();
        }
        print_vec_info(vecA, file);
        print_vec_info(vecB, file);
    }

    {
        // file << "<<<<<<<<<<<    >>>>>>>>>>>>" << std::endl;
    }
   
   
    // file << "" << std::endl;
	// ft::vector<int> vecB(10);
    // std::cout << "" << std::endl;
	// ft::vector<int> vecC(10);
    file.close();
}

