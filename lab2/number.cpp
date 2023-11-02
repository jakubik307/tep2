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

Number::Number(const Number& other)
{
    copyFrom(other);
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
    delete[] tab_ptr;
}

void Number::set_num_length(int length)
{
    if (length <= 0) {
        length = 1;
    }
    num_length = length;
}

void Number::operator=(const int value)
{
    // Delete previous tab allocation
    delete[] tab_ptr;

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
    if (this != &other) {
        delete[] tab_ptr;
        copyFrom(other);
    }
}

Number Number::operator+(Number& other)
{
    Number result;

    if (this->is_negative == other.is_negative) {
        result = addition(*this, other);
        result.is_negative = this->is_negative;
    } else {
        bool change_sign;
        result = subtraction(*this, other, change_sign);
        result.is_negative = change_sign ? other.is_negative : this->is_negative;
    }

    return result;
}

Number Number::operator-(Number& other)
{
    Number result;
    bool change_sign;
    if (this->is_negative == other.is_negative) {
        result = subtraction(*this, other, change_sign);
        result.is_negative = change_sign;
    } else {
        result = addition(*this, other);
        result.is_negative = abs_comp(*this, other) == -1;
    }

    return result;
}

Number Number::operator*(Number& other)
{
    Number result;
    result = multiplication(*this, other);
    result.is_negative = this->is_negative != other.is_negative;

    return result;
}

Number Number::operator/(Number& other)
{
    Number result;
    result = division(*this, other);
    result.is_negative = this->is_negative != other.is_negative;

    return result;
}

Number Number::operator%(Number& other)
{
    Number result;
    result = modulo(*this, other);

    return result;
}

bool Number::operator==(Number& other)
{
    if (this->num_length != other.num_length) {
        return false;
    }
    if (this->is_negative != other.is_negative) {
        return false;
    }
    for (int i = 0; i < this->num_length; i++) {
        if (this->tab_ptr[i] != other.tab_ptr[i]) {
            return false;
        }
    }
    return true;
}

bool Number::operator!=(Number& other)
{
    return !(*this == other);
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

Number Number::operator%(int other)
{
    Number other_number;
    other_number = other;
    return (*this % other_number);
}

bool Number::operator==(int other)
{
    Number other_number;
    other_number = other;
    return (*this == other_number);
}

bool Number::operator!=(int other)
{
    Number other_number;
    other_number = other;
    return (*this != other_number);
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

int Number::toInt()
{
    int result = 0;

    for (int i = num_length - 1; i >= 0; i--) {
        result *= SYSTEM_BASE;
        result += tab_ptr[i];
    }

    return result;
}

Number addition(Number& num1, Number& num2)
{
    Number result(std::max(num1.num_length, num2.num_length) + 1);
    int carry = 0;

    for (int i = 0; i < result.tab_length - 1; i++) {
        int part_sum = 0;

        if (num1.num_length > i) {
            part_sum += num1.tab_ptr[i];
        }
        if (num2.num_length > i) {
            part_sum += num2.tab_ptr[i];
        }
        part_sum += carry;
        carry = 0;

        if (part_sum >= SYSTEM_BASE) {
            carry = 1;
            part_sum -= SYSTEM_BASE;
        }

        result.tab_ptr[i] = part_sum;
    }

    if (carry == 1) {
        result.tab_ptr[result.tab_length - 1] = 1;
        result.set_num_length(result.tab_length);
    } else {
        result.set_num_length(result.tab_length - 1);
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

    result = Number(minuend.num_length);

    for (int i = 0; i < minuend.num_length; i++) {
        int diff = minuend.tab_ptr[i] - borrow;
        if (subtrahend.num_length > i) {
            diff -= subtrahend.tab_ptr[i];
        }
        if (diff < 0) {
            diff += SYSTEM_BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.tab_ptr[i] = diff;
    }

    result.set_num_length(result.tab_length - result.get_trailing_zeroes());
    return result;
}

Number multiplication(Number& num1, Number& num2)
{
    int result_length = num1.num_length + num2.num_length;
    Number result(result_length);
    Number temp;
    Number carry;
    Number product;

    for (int i = 0; i < num1.num_length; i++) {
        carry = 0;
        for (int j = 0; j < num2.num_length || !(carry.num_length == 1 && carry.tab_ptr[0] == 0); j++) {
            product = result.tab_ptr[i + j] + (i < num1.num_length ? num1.tab_ptr[i] : 0) * (j < num2.num_length ? num2.tab_ptr[j] : 0);
            product = product + carry;

            result.tab_ptr[i + j] = (product % SYSTEM_BASE).toInt();
            carry = product / SYSTEM_BASE;
        }
    }

    result.set_num_length(result.tab_length - result.get_trailing_zeroes());
    return result;
}

Number division(Number& num1, Number& num2)
{
    Number result;
    Number dividend;
    Number divisor;
    divisor = num2;
    divisor.is_negative = false;

    // Division by 0 case
    if (num2.num_length == 1 && num2.tab_ptr[0] == 0) {
        return result;
    }

    // Result equal 0 case
    if (abs_comp(num1, num2) == -1) {
        return result;
    }

    // Result equal 1 case
    if (abs_comp(num1, num2) == 0) {
        result = 1;
        return result;
    }

    result = Number(num1.num_length);

    for (int i = num1.num_length - 1; i >= 0; i--) {
        dividend = dividend * SYSTEM_BASE + num1.tab_ptr[i];
        int quotient_digit = 0;
        while (abs_comp(dividend, num2) != -1) {
            dividend = dividend - divisor;
            quotient_digit++;
        }
        result.tab_ptr[i] = quotient_digit;
    }

    result.set_num_length(result.tab_length - result.get_trailing_zeroes());
    return result;
}

Number modulo(Number& num1, Number& num2)
{
    Number result(1);
    Number dividend;
    dividend = num1;
    dividend.is_negative = false;

    // Division by 0 case
    if (num2.num_length == 1 && num2.tab_ptr[0] == 0) {
        return result;
    }

    // Result equal dividend case
    if (abs_comp(num1, num2) == -1) {
        result = dividend;
        return result;
    }

    // Result equal 0 case
    if (abs_comp(num1, num2) == 0) {
        return result;
    }

    while (abs_comp(dividend, num2) != -1) {
        dividend = dividend - num2;
    }

    result = dividend;
    result.set_num_length(result.tab_length - result.get_trailing_zeroes());
    return result;
}

int abs_comp(Number& num1, Number& num2)
{
    if (num1.num_length != num2.num_length) {
        return (num1.num_length > num2.num_length ? 1 : -1);
    }

    for (int i = num1.num_length - 1; i >= 0; i--) {
        if (num1.tab_ptr[i] != num2.tab_ptr[i]) {
            return (num1.tab_ptr[i] > num2.tab_ptr[i] ? 1 : -1);
        }
    }

    return 0;
}

void Number::copyFrom(const Number& other)
{
    this->num_length = other.num_length;
    this->tab_length = other.tab_length;
    this->is_negative = other.is_negative;
    this->tab_ptr = new int[other.tab_length];
    for (int i = 0; i < other.tab_length; i++) {
        this->tab_ptr[i] = other.tab_ptr[i];
    }
}

Number operator+(int lhs, Number& rhs)
{
    Number lhsNumber;
    lhsNumber = lhs;
    return lhsNumber + rhs;
}

Number operator-(int lhs, Number& rhs)
{
    Number lhsNumber;
    lhsNumber = lhs;
    return lhsNumber - rhs;
}

Number operator*(int lhs, Number& rhs)
{
    Number lhsNumber;
    lhsNumber = lhs;
    return lhsNumber * rhs;
}

Number operator/(int lhs, Number& rhs)
{
    Number lhsNumber;
    lhsNumber = lhs;
    return lhsNumber / rhs;
}
