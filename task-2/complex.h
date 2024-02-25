#pragma once
#include <cmath>
#include <string>

class Complex {
private:
	double real;
	double imag;

public:
	
	Complex(double real, double imag);

	double Real();
	
	double Imag();
	
	double Mod();
	
	double Arg();
	
	std::string toString();
	
	Complex operator-();
};

Complex operator+(const Complex& left, const Complex& right);
Complex operator-(const Complex& left, const Complex& right);
Complex operator*(const Complex& left, const Complex& right);
Complex operator/(const Complex& left, const Complex& right);