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

istream &operator>>(istream &ins, Money &amount) {
  char one_char, decimal_point, digit1, digit2;
  long dollars;
  int cents;
  bool negative;

  ins >> one_char;

  if (one_char == '-') {
    negative = true;
    ins >> one_char; // read '$'
  } else {
    negative = false;
  }

  ins >> dollars >> decimal_point >> digit1 >> digit2;

  if (one_char != '$' || decimal_point != '.' || !isdigit(digit1) ||
      !isdigit(digit2)) {
    cout << "Error illegal form for money input\n";
    exit(1);
  }

  cents = digits_to_int(digit1) * 10 + digits_to_int(digit2);
  amount.all_cents = dollars * 100 + cents;

  if (negative) {
    amount.all_cents = -amount.all_cents;
  }

  return ins;
}

ostream &operator<<(ostream &outs, const Money &amount) {
  long positive_cents, dollars, cents;
  positive_cents = labs(amount.all_cents);
  dollars = positive_cents / 100;
  cents = positive_cents % 100;

  if (amount.all_cents < 0) {
    outs << "-$" << dollars << '.';
  } else {
    outs << '$' << dollars << '.';
  }

  if (cents < 10) {
    outs << '0';
  }

  outs << cents;

  return outs;
}
// Money Class ends

int digits_to_int(char c) {
  return static_cast<int>(c) - static_cast<int>('0');
}

// Check Class
class Check {
public:
  Check(); // default
  Check(int checkNumber, long dollars, int cents, bool isCashed);
  Check(int checkNumber, long dollars, bool isCashed);
  int getNumber() const;           
  Money getAmount() const;          
  bool getIsCashed() const;           
  void setNumber(int checkNumber);     
  void setAmount(const Money &amount); 
  void setIsCashed(bool isCashed);     
  friend bool
  operator<(const Check &lhs, const Check &rhs); 
  friend istream &operator>>(istream &ins, Check &check);
  friend ostream &operator<<(ostream &outs, const Check &check); 

private:
  int checkNumber;
  Money amount;
  bool isCashed;
};