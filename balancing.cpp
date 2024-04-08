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

// Check class begins
Check::Check(int checkNumber, long dollars, int cents, bool isCashed)
    : checkNumber(checkNumber), amount(Money(dollars, cents)),
      isCashed(isCashed) {}

Check::Check(int checkNumber, long dollars, bool isCashed)
    : checkNumber(checkNumber), amount(Money(dollars)), isCashed(isCashed) {}

Check::Check() : checkNumber(0), amount(Money()), isCashed(false) {}

int Check::getNumber() const { return checkNumber; }

Money Check::getAmount() const { return amount; }

bool Check::getIsCashed() const { return isCashed; }

void Check::setNumber(int checkNumber) { this->checkNumber = checkNumber; }

void Check::setAmount(const Money &amount) { this->amount = amount; }

void Check::setIsCashed(bool isCashed) { this->isCashed = isCashed; }

bool operator<(const Check &lhs, const Check &rhs) {
  return lhs.checkNumber < rhs.checkNumber;
}

istream &operator>>(istream &ins, Check &check) {
  bool isCashed;
  ins >> check.checkNumber >> check.amount >> isCashed;

  if (isCashed == 1) {
    check.isCashed = true;
  } else if (isCashed == 0) {
    check.isCashed = false;
  } else {
    cout << "Remember cashed = 1 and not cashed = 0, Try again!\n";
    exit(1);
  }
  return ins;
}

ostream &operator<<(ostream &outs, const Check &check) {
  outs << "Check number: " << check.checkNumber
       << " with amount: " << check.amount << ' ';
  return outs;
}
// check class ends

int main() {
  int numOfChecks, numOfDeposits;
  Money priorBalance, cashedAmount, unCashedAmount, depositAmount, bankBalance, customerBalance;
  cout << "Please enter the check number, amount on the check(in the form "
          "$##.##), and whether or not ";
  cout << "the check has been cashed or not (by typing 1 for YES and 0 for "
          "NO): \n";
  cout << endl;
  cout << "\t Example input: 12 for check number, $40.00 for amount and 1 for "
          "cashed ";
  cout << "(12 $40.00 1) \n";
  cout << endl;
  cout << "How many checks would you like to enter? \n";
  cin >> numOfChecks;
  cout << "Enter the check number, amount, and if it is cashed or not" << endl;
  cout << "eg. '12 $549.00 1' or '9 $54.04 0'" << endl;
  cout << "Every check information must be in separate lines: \n";

  //Input the checks from the user
  Check *checks = new Check[numOfChecks];
  int count = 0;
  while (count < numOfChecks) {
    cin >> checks[count];
    ++count;
  }

  //calculate sums
  for(int i = 0; i < numOfChecks; ++i) {
    if(checks[i].getIsCashed()) {
      cashedAmount += checks[i].getAmount();
    } else {
      unCashedAmount += checks[i].getAmount();
    }
  }
  cout << "The sum of the cashed checks is: " << cashedAmount << endl;
  cout << "The sum of the un-cashed checks is: " << unCashedAmount << endl;
  cout << endl;
  
  //Input the deposits from the user 
  cout << "How many deposits would you like to enter? \n";
  cin >> numOfDeposits;
  cout << "Enter your deposit amounts in separate lines: (example format: "
          "$40.00 or $44.44) \n";
  Money *deposits = new Money[numOfDeposits];
  int i = 0;
  while (i < numOfDeposits) {
    cin >> deposits[i];
    ++i;
  }

  // Calculate deposits sum
  for(int i = 0; i < numOfDeposits; ++i) {
    depositAmount += deposits[i];
  }
  cout << "The sum of the deposits is: " << depositAmount << endl;
  cout << endl;
  
  // take the acc balance from user
  cout << "Please enter the prior balance amount ($##.##): ";
  cin >> priorBalance;
  cout << endl;
  
  customerBalance = priorBalance - (cashedAmount + unCashedAmount) + depositAmount;
  bankBalance = priorBalance - cashedAmount + depositAmount;
  
  cout << "The new balance amount according to the account holder: "
       << customerBalance << endl;
  cout << "The balance according to the bank which includes only cleared "
          "checks is: "
       << bankBalance << endl;
  cout << "The difference between the account holder's balance of "
       << customerBalance << " and " << endl;
  cout << "bank balance of " << bankBalance << " is: " << unCashedAmount << endl;
  cout << endl;

  sort(checks, checks + numOfChecks);
  //print all checks
  cout << "The cashed checks are: " << endl;
  for(int i = 0; i < numOfChecks; ++i) {
    if (checks[i].getIsCashed()) {
      cout << checks[i] << endl;
    }
  }
  cout << "\nThe uncashed checks are: " << endl;
  for(int i = 0; i < numOfChecks; ++i) {
    if (!(checks[i].getIsCashed())) {
      cout << checks[i] << endl;
    }
  }

  return 0;
}