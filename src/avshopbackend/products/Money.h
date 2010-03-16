#ifndef MONEY_H_INCLUDED
#define MONEY_H_INCLUDED

#include <string>
#include <set>
#include <stdexcept>

using std::string;

class IncompatibleMoneyError : public std::runtime_error
{
public:
    IncompatibleMoneyError( string errorText_) : std::runtime_error( errorText_ )
    {
    }
};

class Money
{
public:
    Money();
    Money( double amount_, string currency_ ) throw(IncompatibleMoneyError);
    Money( const Money& other_ );

    double amount() const;
    string currency() const;
    string amountFmt() const;

    bool operator ==( const Money& other_ ) const;
    bool operator !=( const Money& other_ ) const;

    Money &operator+=(const Money &other_) throw(IncompatibleMoneyError);
    Money &operator-=(const Money &other_) throw(IncompatibleMoneyError);
    Money &operator*=(const Money &other_) throw(IncompatibleMoneyError);
    Money &operator/=(const Money &other_) throw(IncompatibleMoneyError);

    Money operator+(const Money &other_) const throw(IncompatibleMoneyError);
    Money operator-(const Money &other_) const throw(IncompatibleMoneyError);
    Money operator*(const Money &other_) const throw(IncompatibleMoneyError);
    Money operator/(const Money &other_) const throw(IncompatibleMoneyError);

    Money &operator *=( const int other_ );
    const Money operator *(const int &other_) const;

private:
    void _initAllowedCurrencies();

    bool _isValidCurrency(const string& currency_) const;
    void _setCurrencyIfEmpty(const Money &other_);

    double _amount;
    string _currency;

    static std::set<string> _allowedCurrencies;
};


#endif // MONEY_H_INCLUDED
