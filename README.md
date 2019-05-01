# SNOL (Simple Number-Oriented Language)

The Simple Number-Oriented Language (SNOL) is a programming language design based from the
Floating-Point Oriented Language (FLOPOL) design used for IS 214 (1st Sem, AY2014-2015) of the
UP Open University. SNOL deals with integer-type and float-type values only. This SNOL design is for
CMSC 124 implementation by BSCS students of UP Mindanao.

## Language Specifications

### 1. Formatting
- Whitespace
  - Spaces are used as delimiters – separate tokens (constructs) of the language.
  - Multiple spaces (horizontal, vertical) are irrelevant.
- SNOL is case-sensitive.

### 2. SNOL Coding
A valid SNOL code starts with the word SNOL, followed by all the “program
statements,” and ends with the word LONS.

### 3. Data Types
 There is no type declaration in SNOL. The type of a variable is determined by the
nature of the value it holds. There are only two types of values in SNOL:
- unsigned integer: *digit{digit}*
- unsigned floating-point: *digit{digit}.{digit}*

### 4. Variables
Variables are considered as simple expressions that evaluate to their corresponding values.
Naming a variable follows the format:
- *var_name → letter{(letter|digit)}*
- *letter → a|b|c|…|z|A|B|C|…|Z*
- *digit → 0|1|2|3|4|5|6|7|8|9*

### 5. Assignment, Input, and Output operations
An assignment operation takes the form where expr is an arithmetic operation, a
variable name, or a value:
```
INTO var_name IS expr
```
An input operation takes the form:
```
BEG var_name
```
An output operation takes the form where out is a variable name or a value:
```
PRINT out
```

### 6. Arithmetic Operations
SNOL uses the prefix notation and C’s precedence and associativity
rules. Nested form is not allowed. Note that each of the expressions (expr1, expr2) is a
variable name or a value.

| Operation | SNOL code | C code equivalen |
|---|---|---|
|Addition|ADD expr1 expr2| expr1 + expr2|
|Subtraction|SUB expr1 expr2| expr1 - expr2|
|Multiplication|MULT expr1 expr2| expr1 * expr2|
|Division|DIV expr1 expr2| expr1 / expr2|
|Modulo|MOD expr1 expr2| expr1 % expr2|

### 7. Sample SNOL Code
Source code:
```
SNOL
 INTO num IS 0
 INTO res IS 0
 BEG msg
 INTO num IS 5
 INTO res IS MULT num num
 PRINT res
 INTO res IS MULT res res
 INTO res IS MOD res num
 PRINT num
 PRINT res
 PRINT msg
LONS
```

Output:
```
Program starts…
… Set value of num to 0
… Set value of res to 0
INPUT (msg): Bye!!
… Set value of num to 5
… Evaluating MULT: result is 25
… Set value of res to 25
PRINT: 25
… Evaluating MULT: result is 625
… Set value of res to 625
… Evaluating MOD: result is 0
… Set value of res to 0
PRINT: 5
PRINT: 0
PRINT: Bye!!
Program terminates…
```
---
NOTE: Errors violate the language specifications. In lexical analysis, unknown words (lexemes) found in the program code will be treated as an error.
