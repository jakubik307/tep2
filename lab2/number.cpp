#include "number.h"

Number::Number()
{
    num_length = 1;
    tab_length = 1;
    tab_ptr = new int[tab_length];
    is_negative = false;

    for (int i = 0; i < tab_length; i++) {
        tab_ptr[i] = 0;
    }
}

Number::Number(int tab_length)
{
    if (tab_length <= 0) {
        tab_length = 1;
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
        if (change_sign) {
            result.set_is_negative(other.is_negative);
        } else {
            result.set_is_negative(this->is_negative);
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
        result.set_is_negative(abs_comp(*this, other) == -1);
    }

    return result;
}

Number Number::operator*(Number& other)
{
    Number result;
    result = multiplication(*this, other);
    result.set_is_negative(this->is_negative != other.is_negative);

    return result;
}

Number Number::operator/(Number& other)
{
    Number result;
    result = division(*this, other);
    result.set_is_negative(this->is_negative != other.is_negative);

    return result;
}

Number Number::operator+(int other)
{
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
    Number other_number;
    other_number = other;
    return (*this / other_number);
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
    Number result;
    Number minuend;
    Number subtrahend;
    int borrow = 0;

    if (abs_comp(num1, num2) == 0) {
        return result;
    } else if (abs_comp(num1, num2) == 1) {
        minuend = num1;
        subtrahend = num2;
        change_sign = false;
    } else {
        minuend = num2;
        subtrahend = num1;
        change_sign = true;
    }

    result = Number(minuend.get_num_length());

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
    int result_length = num1.get_num_length() + num2.get_num_length();
    Number result(result_length);

    for (int i = 0; i < num1.get_num_length(); i++) {
        long long carry = 0;
        for (int j = 0; j < num2.get_num_length() || carry; j++) {
            long long product = static_cast<long long>(num1.get_tab_ptr()[i]) * (j < num2.get_num_length() ? num2.get_tab_ptr()[j] : 0);
            long long temp = static_cast<long long>(result.get_tab_ptr()[i + j]) + product + carry;
            result.get_tab_ptr()[i + j] = static_cast<int>(temp % SYSTEM_BASE);
            carry = temp / SYSTEM_BASE;
        }
    }

    result.set_num_length(result.get_tab_length() - result.get_trailing_zeroes());
    return result;
}

Number division(Number& num1, Number& num2)
{
    Number result(num1.get_num_length());
    Number dividend;
    Number divisor;
    divisor = num2;
    divisor.set_is_negative(false);

    // Division by 0 case
    if (num2.get_num_length() == 1 && num2.get_tab_ptr()[0] == 0) {
        return result;
    }

    // Result equal 1 case
    if (abs_comp(num1, num2) == -1) {
        return result;
    }

    // Result equal 1 case
    if (abs_comp(num1, num2) == 0) {
        result = 1;
        return result;
    }

    for (int i = num1.get_num_length() - 1; i >= 0; i--) {
        dividend = dividend * SYSTEM_BASE + num1.get_tab_ptr()[i];
        int quotient_digit = 0;
        while (abs_comp(dividend, num2) != -1) {
            dividend = dividend - divisor;
            quotient_digit++;
        }
        result.get_tab_ptr()[i] = quotient_digit;
    }

    result.set_num_length(result.get_tab_length() - result.get_trailing_zeroes());
    return result;
}

int abs_comp(Number& num1, Number& num2)
{
    if (num1.get_num_length() != num2.get_num_length()) {
        return (num1.get_num_length() > num2.get_num_length() ? 1 : -1);
    }

    for (int i = num1.get_num_length() - 1; i >= 0; i--) {
        if (num1.get_tab_ptr()[i] != num2.get_tab_ptr()[i]) {
            return (num1.get_tab_ptr()[i] > num2.get_tab_ptr()[i] ? 1 : -1);
        }
    }

    return 0;
}
