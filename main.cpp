//  ------------------------------------------------------------------------------
//
//  Converter
//     Copyright 2024 Matthew Rogers
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
//
//  ------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace
{

bool is_valid_roman(const std::string& num)
{
    std::unordered_map<char, int> roman_numerals = {
        { 'I',    1 },
        { 'V',    5 },
        { 'X',   10 },
        { 'L',   50 },
        { 'C',  100 },
        { 'D',  500 },
        { 'M', 1000 },
    };
    for (char c : num)
    {
        if (roman_numerals.find(c) == roman_numerals.end())
        {
            return false;
        }
    }
    return true;
}

bool is_valid_binary(const std::string& num)
{
    if (num.substr(0, 2) != "0b" && num.substr(0, 2) != "0B")
        return false;
    return std::ranges::all_of(num.substr(2), [](char c) { return c == '0' || c == '1'; });
}

bool is_valid_hex(const std::string& num)
{
    if (num.substr(0, 2) != "0x" && num.substr(0, 2) != "0X")
        return false;
    return std::ranges::all_of(num.substr(2), [](char c) { return std::isxdigit(c); });
}

bool is_valid_octal(const std::string& num)
{
    if (num.substr(0, 2) != "0o" && num.substr(0, 2) != "0O")
        return false;
    return std::ranges::all_of(num.substr(2), [](char c) { return c >= '0' && c <= '7'; });
}

char get_number_type(const std::string& num)
{
    if (is_valid_roman(num))
    {
        return 'R';
    } else if (is_valid_binary(num))
    {
        return 'B';
    } else if (is_valid_hex(num))
    {
        return 'H';
    } else if (is_valid_octal(num))
    {
        return 'O';
    }
    return 'D';
}

std::string convert_to_decimal(const std::string& number)
{
    char type    = get_number_type(number);
    int  decimal = 0;
    if (type == 'B')
    {
        int base = 1;
        for (int i = (int) number.length() - 1; i >= 2; --i)
        {
            if (number[i] == '1')
            {
                decimal += base;
            }
            base *= 2;
        }
    } else if (type == 'O')
    {
        int base = 1;
        for (int i = (int) number.length() - 1; i >= 2; --i)
        {
            decimal += (number[i] - '0') * base;
            base *= 8;
        }
    } else if (type == 'H')
    {
        int base = 1;
        for (int i = (int) number.length() - 1; i >= 2; --i)
        {
            if (number[i] >= '0' && number[i] <= '9')
            {
                decimal += (number[i] - '0') * base;
            } else
            {
                decimal += (std::toupper(number[i]) - 'A' + 10) * base;
            }
            base *= 16;
        }
    } else if (type == 'R')
    {
        std::unordered_map<char, int> roman_numerals = {
            { 'I',    1 },
            { 'V',    5 },
            { 'X',   10 },
            { 'L',   50 },
            { 'C',  100 },
            { 'D',  500 },
            { 'M', 1000 },
        };
        int i = 0;
        while (i < number.length())
        {
            int value = roman_numerals[(char) std::toupper(number[i])];
            if (i != number.length() - 1 && value < roman_numerals[(char) std::toupper(number[i + 1])])
            {
                decimal -= value;
            } else
            {
                decimal += value;
            }
            ++i;
        }
    } else
    {
        return number;
    }
    return std::to_string(decimal);
}

std::string convert_to_roman(const std::string& number)
{
    std::string result;
    char        type = get_number_type(number);
    if (type == 'R')
    {
        return number;
    } else
    {
        std::vector<std::pair<int, std::string>> numbers = {
            { 1000,  "M" },
            {  900, "CM" },
            {  500,  "D" },
            {  400, "CD" },
            {  100,  "C" },
            {   90, "XC" },
            {   50,  "L" },
            {   40, "XL" },
            {   10,  "X" },
            {    9, "IX" },
            {    5,  "V" },
            {    4, "IV" },
            {    1,  "I" },
        };
        int num = std::stoi(convert_to_decimal(number));
        for (const auto& pair : numbers)
        {
            while (num >= pair.first)
            {
                result += pair.second;
                num -= pair.first;
            }
        }
    }

    return result;
}


std::string convert_to_binary(const std::string& number)
{
    int         num = 0;
    std::string binary;
    char        type = get_number_type(number);
    if (type == 'B')
    {
        return number;
    } else
    {
        num = std::stoi(convert_to_decimal(number));
        while (num > 0)
        {
            binary = std::to_string(num % 2) + binary;
            num /= 2;
        }
    }

    return binary;
}

std::string convert_to_hex(const std::string& number)
{
    int         num = 0;
    std::string hex;
    char        type = get_number_type(number);
    if (type == 'H')
    {
        return number;
    } else
    {
        num = std::stoi(convert_to_decimal(number));
        while (num > 0)
        {
            int remainder = num % 16;
            if (remainder < 10)
            {
                hex = std::to_string(remainder) + hex;
            } else
            {
                hex = (char) ('A' + remainder - 10) + hex;
            }
            num /= 16;
        }
    }

    return hex;
}

std::string convert_to_octal(const std::string& number)
{
    char        type = get_number_type(number);
    std::string octal;
    if (type == 'O')
    {
        return number;
    } else
    {
        int dec = std::stoi(convert_to_decimal(number));
        while (dec > 0)
        {
            octal = std::to_string(dec % 8) + octal;
            dec /= 8;
        }
    }

    return octal;
}


} // anonymous namespace

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help" || std::string(argv[1]) == "help")
        {
            std::cout << "Usage: " << argv[0] << " <conversion_type> <number>" << std::endl;
            std::cout << "Conversion types: B (binary), H (hexadecimal), O (octal), D (decimal), R (roman)" << std::endl;
            std::cout << "Hex, binary, and octal numbers must have prefixes 0x, 0b, and 0o, respectively, or they will be "
                         "treated as either decimal or roman numeral by default"
                      << std::endl;
            std::cout << "Example: '" << argv[0] << " B 0x1A' will yield 11010" << std::endl;
            return 0;
        }
    }
    if (argc <= 2)
    {
        std::cout << "Usage: " << argv[0] << " <conversion_type> <number>" << std::endl;
        return 1;
    }
    char type = (char) std::toupper(argv[1][0]);
    switch (type)
    {
    case 'B': std::cout << argv[2] << " = " << convert_to_binary(argv[2]) << std::endl; return 0;
    case 'H': std::cout << argv[2] << " = " << convert_to_hex(argv[2]) << std::endl; return 0;
    case 'O': std::cout << argv[2] << " = " << convert_to_octal(argv[2]) << std::endl; return 0;
    case 'D': std::cout << argv[2] << " = " << convert_to_decimal(argv[2]) << std::endl; return 0;
    case 'R': std::cout << argv[2] << " = " << convert_to_roman(argv[2]) << std::endl; return 0;
    default: std::cerr << "Invalid conversion type. Choices are: B, H, O, D, R" << std::endl; return 1;
    }
}
