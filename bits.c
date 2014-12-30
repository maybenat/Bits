/* 
 * CS:APP Data Lab 
 * 
 * <Natalie McMullen, U0409117>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
    //Tells whether the int is < 0, will contain
    //a11 1's if it is < 0.
    int sign = x >> 31;
    //XOR will flip the bits where 1 is set, leaving positive
    //numbers alone
    int newX = x ^ sign;
    //If the number is negative the sign mask will turn the
    //number positive, otherwise it is equivalent to a no-op.
    //Way to implement subtraction
    int subX = (1+(~sign));
    return newX + subX;
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
    //Here we will use an all odd number in order
    //to mask x and determine if all bits are even.
    //Since we have a size constraint we need to a 32 bit number
    int large = (0xAA << 8 | 0XAA) | (0xAA << 8 | 0XAA) << 16;
    //Or the large odd with the input
    int all = large | x;
    //Invert the bits, it will contain all 0's if it had even bits.
    return !(~all);
    
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    //All 1's for < 0
    int check1 = x >> 31;
    int negate = (~x+1);
    //All 0's for < 0
    int check2 = (negate >> 31);
    //Will contain all 0's if x = 0
    int check3 = (check1 | check2);
    //If check3 contains all 0's adding 1, gives the desired result
    return check3 + 1;
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    //Simply flip the bits and OR them
    int or1 = (~x | ~y);
    //To get the AND result flip the bits
    return ~or1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    //Reference used for the method used: http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
    //I will use the numbers described from the link:
    //0x55, 0x33, 0x0F, 00ff.., 0000ffff in order to figure out where bits
    //are set
    //First I must make them large enough to compare, that all numbers
    //input will work.

    int patternf = (0x0F << 8 | 0x0F) | (0x0F << 8 | 0x0F) << 16;
    int pattern3 = (0x33 << 8 | 0x33) | (0x33 << 8 | 0x33) << 16;
    int pattern5 = (0x55 << 8 | 0x55) | (0x55 << 8 | 0x55) << 16;
    int patternf2 = 0xff | (0xff << 16);
    int patternf3 = 0xff | (0xff << 8);
    
    //Invert and add one is the same as x-1
    //This is where we go through and add up the number
    //of set bits
    x = x + ~((x>>1) & pattern5)+1;
    //By adding each pair, has the number of set bits
    x = (x&pattern3) + ((x>>2)&pattern3);
    x = (x + (x >> 4)) & patternf;
    x = (x + (x>>8)) & patternf2;
    //MSB contains the number required.
    x = (x + (x >>16)) & patternf3;
    return x;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*If x is non zero than y is evaulated
    otherwise z is evaulated */
    //Logical NOT (!) of a number that is non zero is 0(F)
    int xNonZero = !(!x);
    //Negates the number (flip bits & add 1), this will leave all bits set or all 0
    int xTrue = ~(xNonZero)+1;
    //Opposite used if x is false
    int xFalse = ~xTrue;
    //Bitwise & leaves us with the value needed to return
    return (xTrue & y) | (xFalse & z);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int xSign = x >> 31;
    //We will make use of bias to deal with rounding
    //(~1+1) will give us negative 1
    //We only want to execute if >0
    int masking = (1 << n) + (~1+1);
    int bias = xSign & masking;
    return (x+bias) >> n;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  return 2;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  return 2;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //All 0's if < 0
    int xSign = x >> 31;
    int ySign = y >> 31;
    //Signs not equal, y is positive and x is negative
    int yPositive = (xSign & !ySign);
    //Equivalency check XOR returns 1 if either bit is 1 for all bits
    int equivalent = xSign ^ ySign;
    //Check if y < x. If x is smaller we will have a 1
    int smaller = (x + ~y) >> 31;
    //If yPositive then x is negative return T, otherwise check that they
    //aren't equivalent and if x < y.
    return yPositive | ((!equivalent) & smaller);

}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
    //If x is less than 0, >>(signed shift) fills with 1's
    int signCheck = x >> 31;
    //Invert the bits + 1 to negate
    int negCheck = ~(signCheck) + 1;
    return negCheck;

}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
    int signCheck = x >> 31;
    int negCheck = ~(signCheck) + 1;
    //Invert the result from isNegative check.
    return !(negCheck);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
    //In binary a number is a power of 2 if it has only 1 bit set to 1
    //First check negative or not.
    int xSign = x >> 31;
    //Convert to two's complement
    int twoComp = (~x+1);
    //Two's complement | flipped bits will be all 1's if it is a power of 2
    int check = ~(twoComp | ~x);
    //The !!x is a check for when 0 is input
    return (!xSign & !check) & (!!x);
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    //First if x is the max, this will cause us to go to tMin which is 1 + the max
    int tMax = (x+1);
    //Flip the bits of x + the hypothetical max value, which if tMax will contain all 0's
    int flipped = ~(x+tMax);
    //will become 0 if contains tMax, and we not the value to return 1.
    tMax = !tMax;
    return !(tMax|flipped);
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  //Simple logical not indicates whether x is 0 or not
  return !x;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
    //Negative value of x
    int negate = (~x+1);
    //The negative will only share 1 bit with x, the least bit
    return x & negate;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    //Perform the necessary shift
    int shift = (x>>n);
    //Puts ones in the bits leading up to n, needed to handle negative numbers
    //Failure on negative numbers if not used
    int rightOne = (1 << 31);
    int masked = (rightOne>>n)<<1;
    //Simple reversal of the bits used to extract the necessary information
    masked = ~(masked);
    return (masked) & (shift);
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  //Simple way of getting negative one
  return (~0);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    //Makes use of the well known formula for
    //two's complement negation
    //Invert the bits and add 1.
    return (~x)+1;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
    return 2;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
    //Get the sign
    int sign = x >> 31;
    //Change x into a boolean value to test for zero
    //We have to do it twice to get the correct value
    //Will only return true if there is a 0.
    int zero = !!x;
    return sign | zero;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //Two's complement 32 bits on the smallest number shifted 31 times
  //will give the minimum two's complement integer, 0x80000000.
  return (1<<31);
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
    //(x+1 << n) -1 formula from the book
    //We need to use a logical not here to handle the value of n=0
    int masked = ((~1+1) & (!n+(~0)));
    //Use the mask to shift the full value to the correctly padded value
    masked = masked << (32+(~n+1));
    return masked;
}
