#include "number.h"

using namespace std;

int main()
{
    Number num1, num2;
    num1 = 5;
    num2 = -12;

    std::cout << num1.toString() << std::endl;
    std::cout << num2.toString() << std::endl;

//    num1 = num2;
//
//    std::cout << num1.toString() << std::endl;
//    std::cout << num2.toString() << std::endl;

    Number num3;
    num3 = num1 - num2;


    std::cout << num3.toString() << std::endl;
    return 0;
}
