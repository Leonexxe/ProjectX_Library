#pragma once

/**
 * @brief calculations and number names provided by https://wolframalpha.com
 */
namespace sizes
{
    //large
        /** error: integer literal is too large to be represented in any integer type
        /** @brief 10^30 (31 decimal digits)/
        const unsigned long nonillion  = 1000000000000000000000000000000;
        /** @brief 10^27 (28 decimal digits)/
        const unsigned long octillion  = 1000000000000000000000000000;
        /** @brief 10^24 (yotta)(25 decimal digits)/
        const unsigned long septillion = 1000000000000000000000000;
        /** @brief 10^21 (zetta)(22 decimal digits)/
        const unsigned long sextillion = 1000000000000000000000;
        */
    /** @brief 10^18 (exa)(19 decimal digits)*/
    const unsigned long quintillion= 1000000000000000000;
    /** @brief 10^15 (peta)(16 decimal digits)*/
    const unsigned long quadrillion= 1000000000000000;
    /** @brief 10^12 (tera)(13 decimal digits)*/
    const unsigned long trillion   = 1000000000000;
    /** @brief 10^9 (giga)(10 decimal digits)*/
    const unsigned long billion    = 1000000000;
    /** @brief 10^6 (mega)(7 decimal digits)*/
    const unsigned long million    = 1000000;
    /** @brief 10^3 (kilo)(4 decimal digits)*/
    const unsigned long thousand   = 1000;

    //small
    /** @brief 10^-3 (milli)*/
    const double milli = 0.001;
    /** @brief 10^-6 (micro)*/
    const double micro = 0.000001;
    /** @brief 10^-9 (nano)*/
    const double nano = 0.000000001;
    /** @brief 10^-12 (pico) */
    const double pico = 0.000000000001;
    /** @brief 10^-15 (femto) */
    const double femto = 0.000000000000001;
}