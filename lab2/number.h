#pragma once
#include <iostream>
#include <string>

const int DEFAULT_LENGTH = 4;
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
    // Setters
    void set_num_length(int length);
    // Operators
    void operator=(const int value);
    void operator=(const Number& other);
    Number operator+(Number& other);
    Number operator-(Number& other);
    Number operator*(Number& other);
    Number operator/(Number& other);
    // Other
    std::string toString();

private:
    int num_length;
    int tab_length;
    int* tab_ptr;
    bool is_negative; 
};

Number addition(Number& number1, Number& number2);
Number subtraction(Number& number1, Number& number2);
