#ifndef FIXED_POINT_MATH_H
#define FIXED_POINT_MATH_H

// There is no standard Fixed Point Math library
// so we are going to use our own based on that found
// in Boost, FreeType and other fixed point implementations
// We concentrate on 16.16 format which is what we need
// for Fonts.

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cmath>


namespace OpenType {


    // ideally we want to constrain integral+decimals <= 32
    template<int integral_bits=16, int decimal_bits=16>
    class Fixed {
    public:
        // this is the number 1 in this representation
        static int32_t const FIXED_ONE;
        // this is the smallest change in this representation
        static int32_t const EPSILON;
        // bounds on this number can hold
        // 0x7FFFFFFFL is the last positive value of a signed integer
        static int32_t const FIXED_MAX;
        // 0x80000000L is the unsigned value that equates to
        // -2147483648 in a 32-bit integer
        static int32_t const FIXED_MIN;
        static double DBL_BIT_SHIFT;




        Fixed() {
        }

        Fixed( int16_t hi, int16_t lo ) {
            value_ = 0;
            value_ = int32_t(hi) << decimal_bits;
            value_ = value_ | int32_t(lo);
        }


        Fixed( int value ) {
             set( value );
        }



        Fixed( double value ) {
            set( value );
        }


        Fixed<integral_bits, decimal_bits>& set( int value ) {
            value_ = int32_t(uint32_t(value) << decimal_bits);
            return *this;
        }


        Fixed<integral_bits, decimal_bits>& set( double value ) {
            // we cannot bit shift on a double so need
            // to calculate the value
            value_ = (int32_t) (value * DBL_BIT_SHIFT + 0.5);
            return *this;
        }

        /**
         * Convert Fixed Point value to int, essentially removing the fractional part
         * @return int
         */

         int toInt() {
            return (int32_t) ( ( (uint32_t)(value_) & 0xFFFF0000UL ) >> decimal_bits );
        }


        double to_double() const {
            // take the high bits shift them back down
            int32_t number = (int32_t) ( ( (uint32_t)(value_) & 0xFFFF0000UL ) >> decimal_bits );
            int32_t lo = (uint32_t)(value_) & 0x0000FFFFUL;
            double fractional = double( lo ) / ( DBL_BIT_SHIFT );
            return number = double(number) + fractional ;
        }

        // Fixed<integral,decimals abs() {
        //     if ( value_ < 0 ) {
        //         negative();
        //     } else {
        //         value_;
        //     }
        // }
        //

        /**
         * Gets the fixed part only
         * @return [description]
         */

        int32_t integral() {
            int32_t x = (int32_t) ( (uint32_t)(value_) & 0xFFFF0000UL );
            return x;
        }

        /**
         * Gets the decimal bits only
         * @return [description]
         */

        int32_t fractional() {
            return value_ - integral();
        }


        void print(std::ostream& out) const {
            out << "fx(0x" << std::hex << std::setfill('0') << std::setw(8) << value_ << ",";
            out << std::dec << to_double() << ")";
        }

        /**
         * Get raw INT32 value
         * @return int32    raw representation of fixed value
         */

        int32_t get() const {
           return value_;
        }

    private:
        int32_t value_;
    };


    // this is the number 1 in this representation
    template<int integral_bits, int decimal_bits> int32_t const Fixed<integral_bits,decimal_bits>::FIXED_ONE = 1 << decimal_bits;
    // this is the smallest change in this representation
    template<int integral_bits, int decimal_bits> int32_t const Fixed<integral_bits,decimal_bits>::EPSILON = 0x1;
    // bounds on this number can hold
    // 0x7FFFFFFFL is the last positive value of a signed integer
    template<int integral_bits, int decimal_bits> int32_t const Fixed<integral_bits,decimal_bits>::FIXED_MAX = pow( 2, integral_bits+decimal_bits-1)-1;
    // 0x80000000L is the unsigned value that equates to
    // -2147483648 in a 32-bit integer
    template<int integral_bits, int decimal_bits> int32_t const Fixed<integral_bits,decimal_bits>::FIXED_MIN = pow( 2, integral_bits+decimal_bits-1) * -1;
    template<int integral_bits, int decimal_bits> double Fixed<integral_bits,decimal_bits>::DBL_BIT_SHIFT = double((2 << (decimal_bits-1)));

    // comparison
    template<int integral_bits, int decimal_bits>
    bool operator==( Fixed<integral_bits, decimal_bits> const & lhs, Fixed<integral_bits, decimal_bits> const & rhs ) {
        return lhs.get() == rhs.get();
    }
    template<int integral_bits, int decimal_bits>
    bool operator==( Fixed<integral_bits, decimal_bits> const & lhs, int32_t const & rhs ) {
        auto f = Fixed<integral_bits,decimal_bits>(rhs);
        return lhs.get() == f;
    }
    template<int integral_bits, int decimal_bits>
    bool operator==( int32_t const & lhs, Fixed<integral_bits, decimal_bits> const & rhs ) {
        auto f = Fixed<integral_bits,decimal_bits>(lhs);
        return f.get() == rhs.get();
    }

    // double will be truncated in this example
    template<int integral_bits, int decimal_bits>
    bool operator==( Fixed<integral_bits, decimal_bits> const & lhs, double const & rhs ) {
        auto f = Fixed<integral_bits,decimal_bits>(rhs);
        return lhs.get() == f;
    }
    template<int integral_bits, int decimal_bits>
    bool operator==( double const & lhs, Fixed<integral_bits, decimal_bits> const & rhs ) {
        auto f = Fixed<integral_bits,decimal_bits>(lhs);
        return f.get() == rhs.get();
    }



    // streams
    template<int integral_bits, int decimal_bits>
    std::ostream& operator<< ( std::ostream& out, Fixed<integral_bits, decimal_bits> const & number ) {
        number.print(out);
        return out;
    }

    template<int integral_bits, int decimal_bits>
    std::istream& operator>> ( std::istream& in, Fixed<integral_bits, decimal_bits>& number ) {
        double x;
        in >> x;
        number.set(x);
        return in;
    }

    using FP_16DOT16 = Fixed<16,16>;
    //using FP_FRACTION = Fixed<2,30>;
}



#endif // FIXED_POINT_MATH_H
