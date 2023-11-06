#pragma once
#include <iostream>
#include <string>

const int SYSTEM_BASE = 10;

class Number {
public:
    // Constructors
    Number();
    Number(const Number& other);
    Number(int value);
    Number(int value, int length);
    // Destructor
    ~Number();
    // Getters
    int get_trailing_zeroes() const;
    // Setters
    void set_num_length(int length);
    // Number operators
    void operator=(int value);
    void operator=(const Number& other);
    Number operator+(Number& other);
    Number operator-(Number& other);
    Number operator*(Number& other);
    Number operator/(Number& other);
    Number operator%(Number& other);
    bool operator==(Number& other) const;
    bool operator!=(Number& other) const;
    // Int operators
    Number operator+(int other);
    Number operator-(int other);
    Number operator*(int other);
    Number operator/(int other);
    Number operator%(int other);
    bool operator==(int other) const;
    bool operator!=(int other) const;
    // Other
    int toInt() const;
    std::string toString() const;
    Number mod(Number& other, Number** result);

private:
    // Fields
    int num_length;
    int tab_length;
    int* tab_ptr;
    bool is_negative;

    // Helper methods
    void copyFrom(const Number& other);
    void assignValue(int value, int min_length);

    friend Number addition(Number& num1, Number& num2);
    friend Number subtraction(Number& num1, Number& num2, bool& change_sign);
    friend Number multiplication(Number& num1, Number& num2);
    friend Number division(Number& num1, Number& num2);
    friend Number mod_division(Number& num1, Number& num2, Number& mod);
    friend Number simpleMod(Number& num1, Number& num2);
    friend int abs_comp(Number& num1, Number& num2);

    // Left hand side operators
    friend Number operator+(int lhs, Number& rhs);
    friend Number operator-(int lhs, Number& rhs);
    friend Number operator*(int lhs, Number& rhs);
    friend Number operator/(int lhs, Number& rhs);
    friend bool operator==(int lhs, Number& rhs);
    friend bool operator!=(int lhs, Number& rhs);
};
