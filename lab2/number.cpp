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
    if (tab_length <= 0) {
        tab_length = DEFAULT_LENGTH;
    }
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

    // Set sign and value
    int value_copy;
    if (value < 0) {
        is_negative = true;
        value_copy = value * -1;
    } else {
        is_negative = false;
        value_copy = value;
    }

    int digits = 1;

    // Get number of digits in the value
    while (value_copy >= SYSTEM_BASE) {
        value_copy /= SYSTEM_BASE;
        digits++;
    }

    tab_length = digits;
    num_length = digits;
    tab_ptr = new int[tab_length];

    // Copy values digits to tab
    if (value < 0) {
        value_copy = value * -1;
    } else {
        value_copy = value;
    }

    for (int i = 0; i < tab_length; i++) {
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
    Number result;

    if (this->is_negative == other.is_negative) {
        result = addition(*this, other);
        result.set_is_negative(this->is_negative);
    } else {
        bool change_sign;
        result = subtraction(*this, other, change_sign);
        if (!change_sign) {
            result.set_is_negative(this->is_negative);
        } else {
            result.set_is_negative(other.is_negative);
        }
    }

    return result;
}

Number Number::operator-(Number& other)
{
    Number result;
    bool change_sign;
    if (this->is_negative == other.is_negative) {
        result = subtraction(*this, other, change_sign);
        result.set_is_negative(change_sign);
    } else {
        result = addition(*this, other);
        result.set_is_negative(abs_comp(other, *this));
    }

    return result;
}

Number Number::operator*(Number& other)
{
    // TODO
    return Number();
}

Number Number::operator/(Number& other)
{
    // TODO
    return Number();
}

Number Number::operator+(int other) {
    Number other_number;
    other_number = other;
    return (*this + other_number);
}

Number Number::operator-(int other)
{
    Number other_number;
    other_number = other;
    return (*this - other_number);
}

Number Number::operator*(int other)
{
    Number other_number;
    other_number = other;
    return (*this * other_number);
}

Number Number::operator/(int other)
{
    // TODO
    return Number();
}

int Number::get_trailing_zeroes()
{
    int trailing_zeroes = 0;
    for (int i = tab_length - 1; i >= 0; i--) {
        if (tab_ptr[i] != 0) {
            return trailing_zeroes;
        }
        trailing_zeroes++;
    }
    return trailing_zeroes;
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

void Number::set_is_negative(bool sign)
{
    is_negative = sign;
}

Number addition(Number& num1, Number& num2)
{
    Number result(std::max(num1.get_num_length(), num2.get_num_length()) + 1);

    int carry = 0;

    for (int i = 0; i < result.get_tab_length() - 1; i++) {
        int part_sum = 0;

        if (num1.get_num_length() > i) {
            part_sum += num1.get_tab_ptr()[i];
        }
        if (num2.get_num_length() > i) {
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

Number subtraction(Number& num1, Number& num2, bool& change_sign)
{
    Number minuend;
    Number subtrahend;
    int borrow = 0;

    if (abs_comp(num1, num2)) {
        minuend = num1;
        subtrahend = num2;
        change_sign = false;
    } else {
        minuend = num2;
        subtrahend = num1;
        change_sign = true;
    }

    Number result(minuend.get_num_length());

    for (int i = 0; i < minuend.get_num_length(); i++) {
        int diff = minuend.get_tab_ptr()[i] - borrow;
        if (subtrahend.get_num_length() > i) {
            diff -= subtrahend.get_tab_ptr()[i];
        }
        if (diff < 0) {
            diff += SYSTEM_BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.get_tab_ptr()[i] = diff;
    }

    result.set_num_length(result.get_tab_length() - result.get_trailing_zeroes());

    return result;
}

Number multiplication(Number& num1, Number& num2)
{
    // TODO
    return Number();
}

Number division(Number& num1, Number& num2)
{
    // TODO
    return Number();
}

bool abs_comp(Number& num1, Number& num2)
{
    if (num1.get_num_length() != num2.get_num_length()) {
        return num1.get_num_length() > num2.get_num_length();
    }

    for (int i = num1.get_num_length() - 1; i >= 0; i--) {
        if (num1.get_tab_ptr()[i] != num2.get_tab_ptr()[i]) {
            return num1.get_tab_ptr()[i] > num2.get_tab_ptr()[i];
        }
    }

    return true;
}
