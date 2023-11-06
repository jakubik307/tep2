#include "number.h"

int main()
{
    Number num1, num2;
    num1 = 42;
    num2 = 0;

    std::cout << num1.toString() << std::endl;
    std::cout << num2.toString() << std::endl;

    std::cout << (num1 / num2).toString() << std::endl;
    return 0;
}
