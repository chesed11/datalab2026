/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    x = ~x;
    y = ~y;
    return ~(x | y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    int a = ~(~x & ~y);
    int b = ~(x & y);
    return a & b;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!(x && y))          /* 至少有一个是 0 */
        return !x & !y;     /* 两个都是 0 才为 1 */
    return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int b;
    b = (v > 0xFFFF) << 4;
    v = v >> b;
    r = r | b;
    b = (v > 0xFF) << 3;
    v = v >> b;
    r = r | b;
    b = (v > 0xF) << 2;
    v = v >> b;
    r = r | b;
    b = (v > 0x3) << 1;
    v = v >> b;
    r = r | b;
    r = r | (v > 1);
    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nb = n << 3;
    int mb = m << 3;
    int bn = (x >> nb) & 0xFF;
    int bm = (x >> mb) & 0xFF;
    int mask = (0xFF << nb) | (0xFF << mb);
    x = x & ~mask;
    x = x | (bm << nb) | (bn << mb);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned r = 0;
    int i = 32;
    for (; i; i = i - 1) {
        r = r << 1;
        r = r | (v & 1);
        v = v >> 1;
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    return (x >> n) & ~((~0x7FFFFFFF >> n) << 1);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y = ~x;                 /* 数 y 的前导零 = 数 x 的左侧连续 1 */
    int c = 0;
    int t;
    t = !(y >> 16);
    c = c + (t << 4);
    y = y << (t << 4);
    t = !(y >> 24);
    c = c + (t << 3);
    y = y << (t << 3);
    t = !(y >> 28);
    c = c + (t << 2);
    y = y << (t << 2);
    t = !(y >> 30);
    c = c + (t << 1);
    y = y << (t << 1);
    t = !(y >> 31);
    c = c + t;
    y = y << t;
    c = c + !y;                 /* y 全零时补上最后一位 */
    return c;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned a;
    unsigned frac;
    unsigned rnd;
    int e = 0;

    if (x == 0) return 0;
    if (x < 0) {
        sign = 0x80000000;
        a = -x;
    } else {
        a = x;
    }

    while (!(a & 0x80000000)) {     /* 归一化：把最高位 1 移到 bit31 */
        a = a << 1;
        e = e + 1;
    }

    frac = (a >> 8) & 0x7FFFFF;     /* 隐含位之后的 23 位尾数 */
    rnd = a & 0xFF;                 /* 被舍掉的 8 位 */

    if (rnd > 0x80) {
        frac = frac + 1;            /* 超过一半，进位 */
    } else if (rnd == 0x80) {
        if (frac & 1) frac = frac + 1;  /* 正好一半：向偶数舍入 */
    }

    if (frac == 0x800000) {         /* 进位溢出到隐含位 */
        frac = 0;
        e = e - 1;
    }

    return sign | ((158 - e) << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned sign = uf & 0x80000000;

    if (exp == 0xFF) return uf;             /* Inf / NaN 原样返回 */
    if (exp == 0) return sign | (uf << 1);  /* 非规格化：尾数左移一位 */
    if (exp == 0xFE) return sign | 0x7F800000;   /* 指数溢出成 Inf */
    return uf + 0x800000;                   /* 指数加 1 */
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    int e = exp - 1023;
    unsigned h;
    int r;

    if (exp >= 0x7FF) return 0x80000000;    /* Inf / NaN */
    if (!exp) return 0;                     /* 零 / 非规格化：过小 */
    if (e < 0) return 0;                    /* |值| < 1 */
    if (e > 30) return 0x80000000;          /* 超出 int 范围 */

    /* h = 完整 53 位尾数(隐含 1 打头)的高 32 位，即 m >> 21 */
    h = 0x80000000 | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);
    r = h >> (31 - e);                      /* 截断取整数部分（向零取整） */
    if (sign) r = -r;
    return r;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127) return 0x7F800000;         /* 太大：+Inf */
    if (x >= -126) return (x + 127) << 23;  /* 规格化数 */
    if (x >= -149) return 1 << (x + 149);   /* 非规格化数 */
    return 0;                               /* 太小：0 */
}
