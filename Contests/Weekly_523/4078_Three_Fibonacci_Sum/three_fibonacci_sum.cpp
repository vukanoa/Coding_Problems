/*
    ============
    === EASY ===
    ============

    ===========================
    4078) Three Fibonacci Sum
    ===========================

    ============
    Description:
    ============

    You are given an integer n.

    The Fibonacci sequence starts with 0 and 1, and each subsequent number is
    the sum of the previous two numbers. Its first few terms are 0, 1, 1, 2, 3,
    5, 8, 13, ....

    Return true if n can be expressed as the sum of three consecutive terms in
    the Fibonacci sequence, and false otherwise.
   

    ========================================
    FUNCTION: bool threeFibonacciSum(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 16
    Output: true
    Explanation:
    The three consecutive terms 3, 5, and 8 have a sum of 3 + 5 + 8 = 16.

    --- Example 2 ---
    Input: n = 8
    Output: false
    Explanation:
    Although 1 + 2 + 5 = 8, these terms are not consecutive in the Fibonacci
    sequence. No three consecutive terms have a sum of 8.

    --- Example 3 ---
    Input: n = 2
    Output: true
    Explanation:
    The first three terms have a sum of 0 + 1 + 1 = 2.


    *** Constraints ***
    1 <= n <= 10^9

*/

#include <cmath>

/*
    ------------
    --- IDEA ---
    ------------

    The only "trick" here is to realize that even if 'n' is a 10^9, since we
    are increasing the steps by next fibonacci number, the total number of
    executions of the while-loop will NOT exceed 45.

    Therefore it's safe to do a "Brute Force".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  81.27% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution {
public:
    bool threeFibonacciSum(int n)
    {
        long long a = 0;
        long long b = 1;
        long long c = 1;

        // The while loop will exectue AT MOST 45 times for n=1e9
        while (a + b + c < n)
        {
            a = b;
            b = c;
            c = a + b;
        }

        return a + b + c == n;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We know that c is EQUAL to a + b, therefore:

        a + b + c ==> c + c ==> 2*c

    That means that ANY 3 CONSECUTIVE terms ALWAYS sum to TWICE the largest
    one term, i.e. twice the 'c' term.

        0 + 1 + 1 = 2
        1 + 1 + 2 = 4
        3 + 5 + 8 = 16
        ...

    That means this whole problem can be turned into two questions:

        1) Is n an EVEN number? (It MUST be, otherwise the answer is false)
        2) Is n/2 a FIBONACCI number?


    For the question 2), there is a classic test:

    Number X is a Fibonaci number IF AND ONLY IF:

        1) 5 * X^2 + 4
        2) 5 * X^2 - 4

    is a PERFECT square.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.74% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Fibonacci_classic_test {
public:
    bool threeFibonacciSum(int n)
    {
        if (n & 1) // If n is an ODD number--Return false
            return false;

        long long x = n / 2;

        return is_square(5 * x * x + 4) || is_square(5 * x * x - 4);
    }

private:
    bool is_square(long long num)
    {
        long long rounded_sqrt_num = llround(sqrt(1.0 * num));

        return rounded_sqrt_num * rounded_sqrt_num == num;
    }
};
