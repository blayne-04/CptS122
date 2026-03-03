#include "Complex.hpp"

double Complex::getReal() const {
	return real;
}

double Complex::getImag() const {
	return imag;
}

void Complex::setReal(double r) {
	real = r;
}

void Complex::setImag(double i) {
	imag = i;
}

Complex Complex::add(Complex &rhs) {
	this->real = this->getReal() + rhs.getReal();
	this->imag = this->getImag() + rhs.getImag();
	return *this;
}

Complex add(Complex& lhs, Complex& rhs) {
	Complex r;
	r.setReal(lhs.getReal() + rhs.getReal());
	r.setImag(lhs.getImag() + rhs.getImag());
	return r;
}

Complex operator+ (const Complex& lhs, Complex& rhs) {
	Complex r;
	r.setReal(lhs.getReal() + rhs.getReal());
	r.setImag(lhs.getImag() + rhs.getImag());
	return r;
}

Complex subtract(Complex& lhs, Complex& rhs) {
	Complex r;
	r.setReal(lhs.getReal() - rhs.getReal());
	r.setImag(lhs.getImag() - lhs.getImag());
}

void read() {
	std::string buffer;
	std::cin << 
}