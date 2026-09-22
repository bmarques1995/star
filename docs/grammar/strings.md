# Strings

Star supports two types of string declaration:

## RawString

Is the simplest string definitions, the string begins and ends with `"`.

Example:

- `"Hello there"`

## Template String

This is the more elaborated string, where you can use expressions inside the string and output the result to it:

- `` ` ``: defines the beginning and the end of the template string
- `${`:  defines the beginning of an expression
- `}$`:  defines the end of an expression
- `@{`: defines the beginning of a format, must be right after an end of expression
- `}@`: defines the end of a format

Examples:

- ``` `Hello there, I'm here to teach you star` ``` :white_check_mark:
- ``` `Hello there, I'm ${55}$ years old` ``` :white_check_mark:
- ``` `Hello there, I'm ${name}$` ``` :white_check_mark:
- ``` `Hello there, my CPU has ${5.2}$@{:.1f}@GHz of clock` ``` :white_check_mark:
- ``` `Hello there, my CPU has ${5.4}$ @{:.1f}@GHz of clock` ``` :x:
- ``` `Hello there, my CPU has @{:.1f}@GHz of clock` ``` :x:

The formats used are the same used by fmtlib, as is it that processes the formats, more details [here](https://en.cppreference.com/cpp/utility/format/spec)