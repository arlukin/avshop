#include "boost/lexical_cast.hpp"
using boost::lexical_cast;

#include "Money.h"

std::set<string> Money::_allowedCurrencies;

Money::Money()
        : _amount(0), _currency("")
{
	_initAllowedCurrencies();
}

Money::Money( double amount, string currency_ ) throw(IncompatibleMoneyError)
        : _amount( amount ), _currency( currency_ )
{
    _initAllowedCurrencies();
    if (!_isValidCurrency(currency_))
        throw IncompatibleMoneyError("Not valid currency.");
}

Money::Money( const Money& other_ )
{
	_initAllowedCurrencies();

    _amount = other_.amount();
    _currency = other_.currency();
}

void Money::_initAllowedCurrencies()
{
	if (_allowedCurrencies.size() == 0)
	{
		_allowedCurrencies.insert("SEK");
		_allowedCurrencies.insert("USD");
		_allowedCurrencies.insert("EUR");
	}
}
double Money::amount() const
{
    return _amount;
}

string Money::currency() const
{
    return _currency;
}

string Money::amountFmt() const
{    
    return lexical_cast<std::string>(amount()) + " " + currency();
}

bool Money::operator ==( const Money& other_ ) const
{
    return _amount == other_._amount  &&
           _currency == other_._currency;
}

bool Money::operator !=( const Money& other_ ) const
{
    return !(*this == other_);
}

Money &Money::operator +=( const Money& other_ ) throw(IncompatibleMoneyError)
{
    _setCurrencyIfEmpty(other_);

    _amount += other_._amount;
    return *this;
}

Money &Money::operator -=( const Money& other_ ) throw(IncompatibleMoneyError)
{
    _setCurrencyIfEmpty(other_);

    _amount -= other_._amount;
    return *this;
}

Money &Money::operator *=( const Money& other_ ) throw(IncompatibleMoneyError)
{
    _setCurrencyIfEmpty(other_);

   _amount *= other_._amount;
    return *this;
}

Money &Money::operator /=( const Money& other_ ) throw(IncompatibleMoneyError)
{
    _setCurrencyIfEmpty(other_);

    _amount /= other_._amount;
    return *this;
}

Money Money::operator+(const Money &other_) const throw(IncompatibleMoneyError)
{
    Money money(*this);
    money += other_;
    return money;
}

Money Money::operator-(const Money &other_) const throw(IncompatibleMoneyError)
{
    Money money(*this);
    money -= other_;
    return money;
}

Money Money::operator*(const Money &other_) const throw(IncompatibleMoneyError)
{
    Money money(*this);
    money *= other_;
    return money;
}

Money Money::operator/(const Money &other_) const throw(IncompatibleMoneyError)
{
    Money money(*this);
    money /= other_;
    return money;
}

Money &Money::operator *=( const int other_ )
{
    _amount *= other_;
    return *this;
}

const Money Money::operator*(const int &other_) const
{
    return Money(*this) *= other_;
}

bool Money::_isValidCurrency(const string& currency_) const
{
    if (_allowedCurrencies.count(currency_) > 0)
    {
      return true;
    }
    else
    {
      return false;
    }
}

void Money::_setCurrencyIfEmpty(const Money &other_)
{
    if (_currency == "")
    {
        _currency = other_.currency();
    }
    else if (!_isValidCurrency(other_.currency()))
    {
        throw IncompatibleMoneyError("Invalid currency, " + other_.currency());
    }
    else if ( _currency != other_._currency )
    {
        throw IncompatibleMoneyError("Not mathing currencies.");
    }
}
