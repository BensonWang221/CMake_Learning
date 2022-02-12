#include <cstdlib>
#include <iostream>
#include <string>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "MathFunctions.h"
#else
#include "cmath"
#endif

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << argv[0] << " version " << Tutorial_VERSION_MAJOR
                  << "." << Tutorial_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    const double inputVal = strtof(argv[1], nullptr);

    #ifdef USE_MYMATH
    std::cout << "Use my math" << std::endl;
    const double result = mysqrt(inputVal);
    #else
    std::cout << "use cmath" << std::endl;
    const double result = sqrt(inputVal);
    #endif
    std::cout << "The square root of " << argv[1] << " is " << result
              << std::endl;

    return 0;
}