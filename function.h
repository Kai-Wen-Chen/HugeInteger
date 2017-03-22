#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include <iostream>
#include <string>

class HugeInteger
{
   friend std::ostream &operator<<( std::ostream &, const HugeInteger & );
public:
   //static const size_t digits = 42; // maximum digits in a HugeInteger

   HugeInteger( ); // conversion/default constructor
   HugeInteger( const std::string & ); // conversion constructor

   HugeInteger operator+( const HugeInteger & ) const;// addition operator; HugeInteger + HugeInteger

   HugeInteger operator+( const std::string & ) const;// HugeInteger + string that represents large integer value

   HugeInteger operator-( const HugeInteger & ) const; // subtraction operator

   HugeInteger operator-( const std::string & ) const; // HugeInteger - string that represents large integer value

   HugeInteger operator*( const HugeInteger & ) const; // multiply two HugeIntegers

   HugeInteger operator*( const std::string & ) const;// HugeInteger * string that represents large integer value

   HugeInteger operator/( const HugeInteger & ) const; // divide two HugeIntegers

   HugeInteger operator/( const std::string & ) const;// HugeInteger / string that represents large integer value

   bool operator>( const HugeInteger & ) const; // greater than operator

private:
   short integer[ 42 ];
   int noOfDigits;

}; // end class HugeInteger
#endif

