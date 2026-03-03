#pragma once
#include <iostream>
#include <string>

class Complex {
public:
	Complex();
	~Complex();

	double getReal() const;
	double getImag() const;

	void setReal(double r);
	void setImag(double i);

	Complex add(Complex &rhs);
	Complex sub(Complex &lhs, Complex &rhs);

	void read();

private:
	double real;
	double imag;
};

Complex add(Complex& lhs, Complex& rhs);
Complex operator+ (const Complex& lhs, Complex& rhs);

std::ostream& operator<< (std::ostream& lhs, const Complex& rhs);