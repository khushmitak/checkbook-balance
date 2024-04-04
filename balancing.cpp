#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
using namespace std;

int digits_to_int(char c);

// Money Class copied from the Book
class Money {
public:
  Money();
  Money(long dollars);
  Money(long dollars, int cents);
  double get_value() const;
  friend Money operator+(const Money &amount1, const Money &amount2);
  friend Money operator-(const Money &amount1, const Money &amount2);
  friend Money operator-(const Money &amount);
  friend bool operator==(const Money &amount1, const Money &amount2);
  Money &operator+=(const Money &rhs);
  friend istream &operator>>(istream &ins, Money &amount);
  friend ostream &operator<<(ostream &outs, const Money &amount);

private:
  long all_cents;
};

// Money class begin

Money::Money() : all_cents(0) {}

Money::Money(long dollars) : all_cents(dollars * 100) {}

Money::Money(long dollars, int cents) {
  if (dollars * cents < 0) {
    cout << "Illegal values for dollars and cents.\n";
    exit(1);
  }

  all_cents = dollars * 100 + cents;
}

double Money::get_value() const { return all_cents * 0.01; }

Money operator+(const Money &amount1, const Money &amount2) {
  Money temp;
  temp.all_cents = amount1.all_cents + amount2.all_cents;

  return temp;
}

Money operator-(const Money &amount1, const Money &amount2) {
  Money temp;
  temp.all_cents = amount1.all_cents - amount2.all_cents;

  return temp;
}

Money operator-(const Money &amount) {
  Money temp;
  temp.all_cents = -amount.all_cents;

  return temp;
}

bool operator==(const Money &amount1, const Money &amount2) {
  return amount1.all_cents == amount2.all_cents;
}

Money &Money::operator+=(const Money &rhs) {
  this->all_cents += rhs.all_cents;

  return *this;
}