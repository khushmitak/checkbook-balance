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