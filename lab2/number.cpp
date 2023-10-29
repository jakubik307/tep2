#include "number.h"

Number::Number()
{
    num_length = 1;
    tab_length = DEFAULT_LENGTH;
    tab_ptr = new int[tab_length];
    is_negative = false;

    for (int i = 0; i < tab_length; i++) {
        tab_ptr[i] = 0;
    }
}

Number::Number(int tab_length)
{
    num_length = 1;
    this->tab_length = tab_length;
    tab_ptr = new int[tab_length];
    is_negative = false;

    for (int i = 0; i < tab_length; i++) {
        tab_ptr[i] = 0;
    }
}

Number::~Number()
{
    delete tab_ptr;
}

int Number::get_num_length()
{
    return num_length;
}

int Number::get_tab_length()
{
    return tab_length;
}

int* Number::get_tab_ptr()
{
    return tab_ptr;
}

bool Number::get_is_negative()
{
    return is_negative;
}

void Number::set_num_length(int length)
{
    num_length = length;
}

void Number::operator=(const int value)
{
    // Delete previous tab allocation
    delete tab_ptr;

    int digits = 1;

    // Set sign and value
    int value_copy;
    if (value < 0) {
        is_negative = true;
        value_copy = value * -1;
    } else {
        is_negative = false;
        value_copy = value;
    }

    // Get number of digits in the value
    while (value_copy >= SYSTEM_BASE) {
        value_copy /= SYSTEM_BASE;
        digits++;
    }

    tab_length = digits;
    num_length = digits;
    tab_ptr = new int[tab_length];

    // Copy values digits to tab
    value_copy = value;
    for (int i = 0; i <= tab_length; i++) {
        tab_ptr[i] = value_copy % SYSTEM_BASE;
        value_copy /= SYSTEM_BASE;
    }
}

void Number::operator=(const Number& other)
{
    // Delete previous tab allocation
    delete tab_ptr;
    num_length = other.num_length;
    tab_length = other.tab_length;
    is_negative = other.is_negative;
    tab_ptr = new int[tab_length];
    for (int i = 0; i < tab_length; i++) {
        tab_ptr[i] = other.tab_ptr[i];
    }
}

Number Number::operator+(Number& other)
{
    return addition(*this, other);
}

Number Number::operator-(Number& other)
{
    return Number();
}

Number Number::operator*(Number& other)
{
    return Number();
}

Number Number::operator/(Number& other)
{
    return Number();
}

std::string Number::toString()
{
    std::string result;
    if (is_negative) {
        result += "-";
    }
    for (int i = num_length - 1; i >= 0; i--) {
        result += std::to_string(tab_ptr[i]);
    }
    return result;
}

Number addition(Number& num1, Number& num2)
{
    Number result(std::max(num1.get_num_length(), num2.get_num_length()) + 1);

    int carry = 0;

    for (int i = 0; i < result.get_tab_length() - 1; i++) {
        int part_sum = 0;

        if (num1.get_num_length() >= i) {
            part_sum += num1.get_tab_ptr()[i];
        }
        if (num2.get_num_length() >= i) {
            part_sum += num2.get_tab_ptr()[i];
        }
        part_sum += carry;
        carry = 0;

        if (part_sum >= SYSTEM_BASE) {
            carry = 1;
            part_sum -= SYSTEM_BASE;
        }

        result.get_tab_ptr()[i] = part_sum;
    }

    if (carry == 1) {
        result.get_tab_ptr()[result.get_tab_length() - 1] = 1;
        result.set_num_length(result.get_tab_length());
    } else {
        result.set_num_length(result.get_tab_length() - 1);
    }

    return result;
}

Number subtraction(Number& number1, Number& number2)
{
    return Number();
}
