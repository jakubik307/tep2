#pragma once
#include <iostream>
#include <string>

const int SYSTEM_BASE = 10;

class Number {
public:
    // Constructors
    Number();
    Number(int tab_length);
    // Destructor
    ~Number();
    // Getters
    int get_num_length();
    int get_tab_length();
    int* get_tab_ptr();
    bool get_is_negative();
    int get_trailing_zeroes();
    // Setters
    void set_num_length(int length);
    void set_is_negative(bool sign);
    // Operators
    void operator=(const int value);
    void operator=(const Number& other);
    Number operator+(Number& other);
    Number operator-(Number& other);
    Number operator*(Number& other);
    Number operator/(Number& other);
    Number operator+(int other);
    Number operator-(int other);
    Number operator*(int other);
    Number operator/(int other);
    // Other
    std::string toString();

private:
    int num_length;
    int tab_length;
    int* tab_ptr;
    bool is_negative;
};

Number addition(Number& num1, Number& num2);
Number subtraction(Number& num1, Number& num2, bool& change_sign);
Number multiplication(Number& num1, Number& num2);
Number division(Number& num1, Number& num2);
bool abs_comp(Number& num1, Number& num2);
