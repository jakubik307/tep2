#pragma once
#include <iostream>
#include <string>

const int SYSTEM_BASE = 10;

class Number {
public:
    // Constructors
    Number();
    Number(const Number& other);
    Number(int tab_length);
    // Destructor
    ~Number();
    // Getters
    int get_trailing_zeroes();
    // Setters
    void set_num_length(int length);
    // Operators
    void operator=(const int value);
    void operator=(const Number& other);
    Number operator+(Number& other);
    Number operator-(Number& other);
    Number operator*(Number& other);
    Number operator/(Number& other);
    Number operator%(Number& other);
    Number operator+(int other);
    Number operator-(int other);
    Number operator*(int other);
    Number operator/(int other);
    Number operator%(int other);
    // Other
    int toInt();
    std::string toString();

private:
    int num_length;
    int tab_length;
    int* tab_ptr;
    bool is_negative;

    friend Number addition(Number& num1, Number& num2);
    friend Number subtraction(Number& num1, Number& num2, bool& change_sign);
    friend Number multiplication(Number& num1, Number& num2);
    friend Number division(Number& num1, Number& num2);
    friend Number modulo(Number& num1, Number& num2);
    friend int abs_comp(Number& num1, Number& num2);
};
