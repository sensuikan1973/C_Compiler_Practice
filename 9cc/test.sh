#!/bin/bash
assert()  {
    expected="$1"
    input="$2"

    ./9cc "$input" > tmp.s
    gcc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

assert 0 "0;"
assert 42 "42;"
assert 255 "1 - 2;"
assert 21 '5+20-4;'
assert 41 " 12 + 34 - 5;"
assert 47 '5+6*7;'
assert 15 '5*(9-6);'
assert 4 '(3+5)/2;'
assert 10 '-10+20;'
assert 3 '5+(-2);'
assert 8 '+(-(-3)) + 5;'

assert 1 '1 == 1;'
assert 0 '1 == 2;'
assert 1 '1 != 0;'
assert 0 '1 != 1;'

assert 1 '2 > 1;'
assert 1 '2 >= 1;'
assert 1 '0 > -1;'
assert 1 '1 >= 1;'
assert 0 '0 >= 1;'
assert 0 '-2 >= -1;'

assert 1 '1 < 2;'
assert 1 '1 <= 2;'
assert 1 '-1 < 0;'
assert 1 '1 <= 1;'
assert 0 '1 <= 0;'
assert 0 '-1 <= -2;'

assert 0 'a = 0;'
assert 255 'b = 255;'
assert 1 'z  =    1;'
assert 1 'z=1;'
assert 123 'x=y=z=123;'

assert 2 'xy = 2;'
assert 2 'x_y_zabc = 2;'
assert 123 'a3_bcd = 123;'

assert 2 'return 2;'
assert 3 'var = 1 + 2; return var;'
assert 3 'var = 1 + 2;return var;'

echo ok
