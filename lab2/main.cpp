#include "number.h"

int main()
{
    Number num1, num2;
    num1 = -2137;
    num2 = -69;

    std::cout << num1.toString() << std::endl;
    std::cout << num2.toString() << std::endl;
//    Number num3 = num1 / num2;
    Number num4 = num1 % num2;

//    std::cout << num3.toString() << std::endl;
    std::cout << num4.toString() << std::endl;
    std::cout << num1.toInt() % num2.toInt() << std::endl;

//    Number num4 = num3;
//
//    std::cout << num4.toString() << std::endl;
//    std::cout << (21 == num3) << std::endl;
    return 0;
}
