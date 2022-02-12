#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    const double inputVal = strtof(argv[1], nullptr);

    const double result = sqrt(inputVal);
    std::cout << "The square root of " << argv[1] << " is " << result
              << std::endl;
    
    return 0;
}