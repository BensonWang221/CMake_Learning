// 这个文件是创建一个table, 应该在创建MathFunctions之前先run
// 所以应该把它加到cmake中作为构建的一部分
#include <cmath>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    std::ofstream fout(argv[1], std::ios::out);
    const bool fileOpen = fout.is_open();
    if (fileOpen)
    {
        fout << "double sqrtTable[] = {" << std::endl;
        for (int i = 0; i < 10; ++i) {
            fout << sqrt(static_cast<double>(i)) << "," << std::endl;
        }
        fout << "0};" << std::endl;
        fout.close();
    }
    return fileOpen ? 0 : 1;
}