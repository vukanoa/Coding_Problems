/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2429) Minimize XOR
    ===========================

    ============
    Description:
    ============

    Given two positive integers num1 and num2, find the positive integer x such
    that:

        x has the same number of set bits as num2, and

        The value x XOR num1 is minimal.

    Note that XOR is the bitwise XOR operation.

    Return the integer x. The test cases are generated such that x is uniquely
    determined.

    The number of set bits of an integer is the number of 1's in its binary
    representation.

    ==============================================
    FUNCTION: int minimizeXor(int num1, int num2);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num1 = 3, num2 = 5
    Output: 3
    Explanation:
    The binary representations of num1 and num2 are 0011 and 0101, respectively.
    The integer 3 has the same number of set bits as num2, and the value
    3 XOR 3 = 0 is minimal.

    --- Example 2 ---
    Input: num1 = 1, num2 = 12
    Output: 3
    Explanation:
    The binary representations of num1 and num2 are 0001 and 1100, respectively
    The integer 3 has the same number of set bits as num2, and the value
    3 XOR 1 = 2 is minimal.


    *** Constraints ***
    1 <= num1, num2 <= 10^9

*/

#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Standard Binary Manipulation. There are some things you should know from
    this Solution:

        1. __builtin_popcount(number) // Counts set-bits from an integer
        2. How to convert an integer to ts BinaryString representation

    Once you know that, now let's reason.

    If we have the SAME amount of set-bits in both num1 and num2, then, since
    we would like to minimize the output of XOR-ing num1 with 'x', it makes
    sense that once x == num1, then XOR-ing those two variables will gives us
    the minimal result, i.e. zero.

    (If you didn't know - XOR-ing a value with itself gives ZERO)

    Since we want to MINIMIZE the result of XOR-ing num1 with 'x', the best
    possible option would be to have 'x' be equal to num1.

    For example:
        num1 = 11   num2 = 19
               ~~          ~~
               ^           ^
               |           |
               |           |
             01011       10011


    From num2 we see that there are 3 set-bits.

    We also see that there are 3 set-bits in num1. Since that is the case, what
    would be the best "XOR-ing partner" for num1, so that the output is
    MINIMIZED?

    Surely, it must be num1.

            num1
        XOR num1
            ----
              0


            01011
        XOR 01011
            -----
            00000



    However, what happens if the amount of set-bits is NOT the same?
    Then, it's a bit more complicated than this, but also not difficult.

    Since we are asked to MINIMIZE the Output, we OUGHT flip the MSBs(Most
    Significant Bit)s first.

    There are two possitilibites now:
        1) There are MORE set-bits in num1 than in num2
        2) There are LESS set-bits in num1 than in num2




    1) If we had MORE set-bits in num1 than in num2:

            num1 = 30     num2 = 64
                   ~~            ~~
                   ^             ^
                   |             |
                   |             |
               0011110        1000000
            (4 set-bits)      (1 set-bit)

    There is ONLY ONE set-bit in num2, therefore we're allowed to have ONLY
    ONE set-bit in our 'x' varible.

    So which value of x, in decimal, ought to give us the MINIMAL value when
    XOR-ed with num1?


    It's the value where we'll flip the MostSignificant set-bit in num1.

        num1 =   0  0  1  1  1  1  0
                64 32 16  8  4  2  1


    We would MINIMIZE this value up above if we were to flip its
    MostSignificant set-bit, in this case that's a set-bit that represents 16.

    Therefore, since we're allowed to use ONLY ONE set-bit for our 'x' value,
    the best option for it is to be equal to 16.

    Now if we XOR x=16 with num=30, we'll get 14.

            001 1110 -> 30
       XOR  001 0000 -> 16
            --------
            000 1110 -> 14




    2) If we had LESS set-bits in num1 than in num2:

            num1 = 4     num2 = 19
                   ~            ~~
                   ^            ^
                   |            |
                   |            |
                 000100       010011
              (1 set-bit)    (3 set-bits)


        Here we have 3 set-bits in num2, but we ONLY have 1 set-bit in num1.

        So, does that mean we must flip some 0s in num1 to become 1s?
        Yes! We must do that!


        It's a reverse logic from the previous example.
        Since we want to, again, MINIMIZE the output of num1 XOR-ed with x and
        since we know we'll neutralize ALL set-bits in num1, i.e. all set-bits
        will become 0, what should we do with setbits that we're left off with?

        Since we MUST use them, unfortunately, then we should flip 0s to 1s in
        num1 as to increase the output for the LEAST POSSIBLE AMOUNT.

        Imagine this:

            You have: 00000..000 // Zero

            You must XOR it with a value that has ONLY ONE set-bit. Which value
            will guarantee the MINIMAL output when XOR-ed with 0?

            Surely it's 1.

                00...0000 -> 0
            XOR 00...0001 -> 1
                ---------
                00...0001 -> 1


        This way, we did indeed increase ZERO value, but we've increasing it
        AS LITTLE AS POSSIBLE by fliping LSBs (Least Significant Bit)s FIRST,
        until we've used all of set-bits from num2.


    There's only a small caveat in the Implementation below.
    First, how does the Implementation works?

        1. Check if the number of set-bits between num1 and num2 are equal.
           If they are, then return num1 as the result. (XOR-ing num1 with
           itself would gives us 0, remember?)

        2. Count the number of set-bits in num2 and store it in "set_bits".

        3. Convert num1 to its binary string representation with 32 characters.

        4. Create a 32 characters string "str_x" with all '0's.

        5. Iterate through the Binary String representation of num1 from MSB
           to LSB.

        6. If we find set-bit in num1, then, str_x[i] becomes 1, and we
           decrement set_bits.

           If there are no more set_bits, we break the loop and return the
           decimal value of the binary string representation of str_x.



    However, there's a small caveat. It's this condition:

        if ((31 - i) < set_bits)
        {
            ...
        }

    What it does is, if we have MORE set-bits left to set in str_x, but we are
    at the LOWER index(looking from the RIGHT of the binary string), then all
    the remaining characters in str_x ought to be '1's.

    For example:

            num1 = 1     num2 = 12
                   ~            ~~
                   ^            ^
                   |            |
                   |            |
                 000001       001100
              (1 set-bit)    (2 set-bits)

    For must use 2 set-bits for 'x', since there are 2 set-bits in num2.

    Let's represent num1 as a Binary String.

        0  0  0  ... 0  0  0  0  1
       .. .. ..     16  8  4  2  1

    However, INDICES FROM THE RIGHT, would be like this:

        0  0  0  ... 0  0  0  0  1
       .. .. ..     16  8  4  2  1
       31 30 29  ... 4  3  2  1  0 // Indices


    Since we need to set 2 set-bits, we will come up to index 1(FROM THE RIGHT)
    at bit that represents 2 and now look at this:

        Its index, from the right, is 1, but we need to put TWO more set-bits,
        that indicates all the remaining bits, until the end, OUGHT to be 1s.

    This is just a way of checking if that's the case.
*/

/* Time  Beats:  7.01% */
/* Space Beats:  5.14% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimizeXor(int num1, int num2)
    {
        if (__builtin_popcount(num1) == __builtin_popcount(num2))
            return num1; // Because XOR-ing num1 with itself gives 0

        int set_bits = __builtin_popcount(num2);

        ostringstream out;
        for (int i = 31; i >= 0; i--)
        {
            if (num1 & (1 << i))
                out << 1;
            else
                out << 0;
        }
        string str_num1 = out.str();

        string str_x(32, '0');
        for (int i = 0; i < 32; i++)
        {
            if ((31 - i) < set_bits || str_num1[i] == '1')
            {
                str_x[i] = '1';
                set_bits--;

                if (set_bits == 0)
                    break;
            }
        }

        return stoi(str_x, nullptr, 2);
    }
};
