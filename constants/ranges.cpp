#pragma once
namespace px
{
    namespace ranges
    {
        namespace _unsigned
        {
            /** @brief 1 byte */
            unsigned char UCHAR = 255;
            /** @brief 4 bytes */
            unsigned int UINT = 4294967295;
            /** @brief 2 bytes */
            unsigned short USHORT = 65535;
            /** @brief 8 bytes */
            unsigned long ULONG = 4294967295;
            /** @brief 8 bytes */
            unsigned long long ULONG_LONG = 18446744073709551615;
        }
        namespace max
        {
            /** @brief 1 byte */
            char CHAR = 127;
            /** @brief 4 bytes */
            int INT = 2147483647;
            /** @brief 2 bytes */
            short SHORT = 32767;
            /** @brief 8 bytes */
            long LONG = 2147483647;
            /** @brief 8 bytes */
            long long LONG_LONG = 9223372036854775807;
        }

        namespace min
        {
            /** @brief 1 bytes */
            char CHAR = -127;
            /** @brief 4 bytes */
            int INT = -2147483648;
            /** @brief 2 bytes */
            short SHORT = -32768;
            /** @brief 8 bytes */
            long LONG = -2147483648;
            /** @brief 8 bytes */
            long long LONG_LONG = -9223372036854775808;
        }
    }
}
