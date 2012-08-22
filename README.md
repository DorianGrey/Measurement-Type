Measurement-Type
================

Measurement-Type is an attempt for compile-time measurement unit compatibilty checking. It uses templates to fix a numeric value beyond and a unit-type
that is generally defined. Both are used to create a value-struct that includes various functions, e.g. for integral scaling and assignments operations.
Since the real value is enclosed inside the struct, it cannot be accessed directly inadvertently. To define valid operations, free operator-functions are defined to declare which mathematical calculations are allowed.
Since this may appear a little bit confusing, consider the following example:
"value1" is a numeric value with logical type "watt", "value2" is another numeric value with logical type "seconds". Logically, one cannot calculate a sum or difference, i.e.
    
    value1+value2, value1-value2

is logically illegal. But the compiler does not know about is aspect, and thus cannot be of any help. On the other hand, watt and seconds can be multiplied and divided. I assumed that it would be useful to define which operations allowed, and thus get all others out of potential reach. In the end, if built up some framework-like code that allows to easily define those restrictions. As a result, considering the example mentioned above, a compiler is now able to detect that

    value1+value2

is illegal, since there is no definition of an operator-function. On the other hand,

    value1*value2

is tested and considered as legal code.

I know that this may occur a little bit abstract, but I suggest it can be useful in projects that heavily use measurement-types inside. I've created some basic stuff like a few measurement-types and some free-standing operator-functions to check if my attempt can work in any way, and it does.
There is an exemplary Main.cpp which shows the amount of code that has to be used once the allowed operations are defined, and I assume it's not too much in general. Even defining the operator-functions is quite easy, since the compatibility checks are performed using templates, the code inside the function is only about one single line.

Feel free to check out my code, have a look at it, comment or give suggestions - be sure I will read them.
There are a few things you should note before playing around with this code:
* The code requires a rather new compiler (especially supporting decltype() and std::initializer_list). I've tested it with GCC 4.7.1 on Windows and GCC 4.6.3 on Ubuntu.
* Code-documentation is not completed yet, and may still leave some questions. I will add it when I've enough time for it, feel free to ask if some things occur too strange to be understable.

