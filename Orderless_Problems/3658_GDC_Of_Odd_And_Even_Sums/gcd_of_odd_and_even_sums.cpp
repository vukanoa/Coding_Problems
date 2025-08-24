/*
    ============
    === EASY ===
    ============

    ==============================
    3658) GCD of Odd and Even Sums
    ==============================

    ============
    Description:
    ============

    You are given an integer n. Your task is to compute the GCD (greatest
    common divisor) of two values:

        + sumOdd:  the sum of the first n odd numbers.
        + sumEven: the sum of the first n even numbers.

    Return the GCD of sumOdd and sumEven.

    ======================================
    FUNCTION: int gcdOfOddEvenSums(int n);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4
    Output: 4
    Explanation:
        Sum of the first 4 odd numbers sumOdd = 1 + 3 + 5 + 7 = 16
        Sum of the first 4 even numbers sumEven = 2 + 4 + 6 + 8 = 20
    Hence, GCD(sumOdd, sumEven) = GCD(16, 20) = 4.

    --- Example 2 ---
    Input: n = 5
    Output: 5
    Explanation:
        Sum of the first 5 odd numbers sumOdd = 1 + 3 + 5 + 7 + 9 = 25
        Sum of the first 5 even numbers sumEven = 2 + 4 + 6 + 8 + 10 = 30
    Hence, GCD(sumOdd, sumEven) = GCD(25, 30) = 5.


    *** Constraints ***
    1 <= n <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int gcdOfOddEvenSums(int n)
    {
        int sumOdd = 0;
        int sumEven = 0;

        for (int i = 1; i <= 2*n; i++)
        {
            if (i & 1)
                sumOdd += i;
            else
                sumEven += i;
        }
        
        return gcd(sumOdd, sumEven);
    }

private:
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_You_Can_Actually_Just_Return_N_LOL {
public:
    int gcdOfOddEvenSums(int n)
    {
        return n;
    }
};
