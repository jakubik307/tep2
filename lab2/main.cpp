#include "number.h"

int main()
{
    Number num1, num2;
    num1 = 2137;
    num2 = 69;

    std::cout << num1.toString() << std::endl;
    std::cout << num2.toString() << std::endl;

    Number num3;
    num3 = num1 * num2;
    Number num4 = 147453;

    std::cout << num3.toString() << std::endl;
    std::cout << num4.toString() << std::endl;
    std::cout << (num3 == num4) << std::endl;
    return 0;
}
