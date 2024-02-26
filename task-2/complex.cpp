#pragma once
#include "cmath"
#include "numeric"
#include "complex.h"

#define PI 3.1415926
#define PI_2 1.570796

double Complex::Real() { return this->real; }

double Complex::Imag() { return this->imag; }

Complex::Complex(double real, double imag) {
	this->real = real;
	this->imag = imag;
}

double Complex::Mod() {
	return std::sqrt((this->real * this->real) + (this->imag * this->imag));
}

double Complex::Arg() {
	bool firstQuarter = this->real > 0 && this->imag > 0;
	bool secondQuarter = this->real < 0 && this->imag > 0;
	bool thirdQuarter = this->real < 0 && this->imag < 0;
	bool fourthQuarter = this->real > 0 && this->imag < 0;

	bool positiveReal = this->real > 0 && this->imag == 0;
	bool negativeReal = this->real < 0 && this->imag == 0;
	bool positiveImag = this->real == 0 && this->imag > 0;
	bool negativeImag = this->real == 0 && this->imag < 0;

	double module = std::atan(this->imag / this->real);

	if (firstQuarter) return module;
	else if (secondQuarter) return -module;
	else if (thirdQuarter) return PI - module;
	else if (fourthQuarter) return module - PI;

	else if (positiveImag) return PI_2;
	else if (negativeImag) return -PI_2;
	else if (positiveReal) return 0;
	else if (negativeReal) return PI;

	else return std::numeric_limits<double>::signaling_NaN();
}

Complex operator+(const Complex& left, const Complex& right) {
	double real = ((Complex)left).Real() + ((Complex)right).Real();
	double imag = ((Complex)left).Imag() + ((Complex)right).Imag();
	return Complex{ real, imag };
}

Complex operator-(const Complex& left, const Complex& right) {
	double real = ((Complex)left).Real() - ((Complex)right).Real();
	double imag = ((Complex)left).Imag() - ((Complex)right).Imag();
	return Complex{ real, imag };
}

Complex operator*(const Complex& left, const Complex& right) {
	double leftReal = ((Complex)left).Real();
	double leftImag = ((Complex)left).Imag();
	double rightReal = ((Complex)right).Real();
	double rightImag = ((Complex)right).Imag();
	double real = (leftReal * rightReal) - (leftImag * rightImag);
	double imag = (leftReal * rightImag) + (leftImag * rightReal);
	return Complex{ real, imag };
}

Complex operator/(const Complex& left, const Complex& right) {
	double leftReal = ((Complex)left).Real();
	double leftImag = ((Complex)left).Imag();
	double rightReal = ((Complex)right).Real();
	double rightImag = ((Complex)right).Imag();
	double numeratorReal = (leftReal * rightReal) + (leftImag * rightImag);
	double numeratorImag = (rightReal * leftImag) + (leftReal * rightImag);
	double denominator = (rightReal * rightReal) + (rightImag * rightImag);
	double real = numeratorReal / denominator;
	double imag = numeratorImag / denominator;
	return Complex{ real, imag };
}
