# Numbers

These are the type of numbers treated by star:

- i(8|16|32|64): Represent the signed integers of each size
- u(8|16|32|64): Represent the unsigned integers of each size
- f(32|64): Represent the IEEE-754 float point numbers, the float and double

## Treatment

Now star treats numbers the dummiest way possible, only accepts+ operands and operation of same type, without any treatment, but, a `NumericDispatcher` is planned (detais [here](##NumericDispatcher))

### Numeric-Dispatcher

What is planned for the numeric dispatcher, 4 operations, `promote`, `demote`, `truncate` and `try_cast`:

- `promote`: promotes a number of same category, signed, unsigned and float, for types of bigger size
- `demote`: demotes a number of same category for types of smaller size, fails if the original type exceeds the limits of the target type
- `truncate`: demotes a number of same category for types of smaller size, but discard the higher words
- `try_cast`: tries to cast a number for different categories, fails if limit of the target is out of range