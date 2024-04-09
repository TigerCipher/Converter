Converter
---
A simple command line tool to do number conversions. Currently whole integers only.
Supports the following conversions:
- Decimal to Binary
- Decimal to Octal
- Decimal to Hexadecimal
- Decimal to Roman Numeral
- Roman Numeral to Decimal
- Roman Numeral to Binary
- Roman Numeral to Octal
- Roman Numeral to Hexadecimal
- Binary to Octal
- Binary to Hexadecimal
- Binary to Roman Numeral
- Binary to Decimal
- Octal to Binary
- Octal to Hexadecimal
- Octal to Roman Numeral
- Octal to Decimal
- Hexadecimal to Binary
- Hexadecimal to Octal
- Hexadecimal to Roman Numeral
- Hexadecimal to Decimal

## Usage
```
converter <conversion> <number>
```
Where `<conversion>` is the conversion you want to do and `<number>` is the number you want to convert.
`<conversion>` can be any of the following:
- `D` `B` `H` `R` `O` for Decimal, Binary, Hexadecimal, Roman Numeral, Octal respectively.
    - Can also be lower-cased.
- `<number>` must be a valid number for the conversion you want to do.
    - Decimal: Any whole number
    - Binary: A string of 1s and 0s prefixed with `0b`
    - Octal: A string of numbers 0-7 prefixed with `0o`
    - Hexadecimal: A string of numbers 0-9 and letters A-F (or a-f) prefixed with `0x`
    - Roman Numeral: A string of valid Roman Numerals
        - Valid Roman Numerals currently supported: `I` `V` `X` `L` `C` `D` `M`
### Examples
```
converter B 0x1A
```
- yields `11010`

```
converter R 0b11010
```
- yields `XXVI`

```
converter D 0o123
```
- yields `83`

```
converter r 578
```
- yields `DLXXVIII`
