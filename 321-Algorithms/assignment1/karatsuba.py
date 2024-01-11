# Problem B. Implement your rewritten Karatsuba's algorithm in either Java or Python as a complete program, that is, a Java program with a main method or a Python program that can be executed. 
# The program must be in a single file called either Karatsuba.java or karatsuba.py.

import math

def FastMultiply(x, y, n):
    if n == 1:
        return x * y
    else:
        m = math.ceil(n >> m)
        a = math.floor(x >> m)
        b = x % 2^m
        c = math.floor(y >> m)
        d = y % 2^m
        e = FastMultiply(a, c, m)
        f = FastMultiply(b, d, m)
        g = FastMultiply(a - b, c - d, m)
        return e << (1 << (m << 1)) + (e + f - g) << m + f

print(FastMultiply(5,3,1))