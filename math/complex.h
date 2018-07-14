#ifndef COMPLEX_H
#define COMPLEX_H
class Complex{
public:
  Complex(double real);
  Complex(double real, double imaginary);
  Complex(const Complex c&);
  Complex operator*(const Complex& c) const;
  Complex operator*(double c) const;
  Complex operator+(const Complex& c) const;
  Complex operator+(double c) const;
  double i();
  double r();
private:
  double imaginary;
  double real;

};

#endif
