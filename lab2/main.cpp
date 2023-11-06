#include "number.h"

int main()
{
    Number num1, num2, mod, *result;
    num1 = 21;
    num2 = 4;

    mod = num1.mod(num2, &result);

    std::cout << num1.toString() << std::endl;
    std::cout << num2.toString() << std::endl;
    std::cout << mod.toString() << std::endl;
    std::cout << (*result).toString() << std::endl;

    return 0;
}
