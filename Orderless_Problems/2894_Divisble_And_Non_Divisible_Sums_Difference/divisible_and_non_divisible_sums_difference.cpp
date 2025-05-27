/*
    ============
    === EASY ===
    ============

    =================================================
    2894) Divisible and Non-divisible Sums Difference
    =================================================

    ============
    Description:
    ============

    You are given positive integers n and m.

    Define two integers as follows:

        num1: The sum of all integers in the range [1, n] (both inclusive) that
              are not divisible by m.

        num2: The sum of all integers in the range [1, n] (both inclusive) that
              are divisible by m.

    Return the integer num1 - num2.

    =============================================
    FUNCTION: int differenceOfSums(int n, int m);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10, m = 3
    Output: 19
    Explanation: In the given example:
    - Integers in the range [1, 10] that are not divisible by 3 are
      [1,2,4,5,7,8,10], num1 is the sum of those integers = 37.

    - Integers in the range [1, 10] that are divisible by 3 are [3,6,9], num2
      is the sum of those integers = 18.

    We return 37 - 18 = 19 as the answer.


    --- Example 2 ---
    Input: n = 5, m = 6
    Output: 15
    Explanation: In the given example:
    - Integers in the range [1, 5] that are not divisible by 6 are [1,2,3,4,5],
      num1 is the sum of those integers = 15.

    - Integers in the range [1, 5] that are divisible by 6 are [], num2 is the
      sum of those integers = 0.

    We return 15 - 0 = 15 as the answer.


    --- Example 3 ---
    Input: n = 5, m = 1
    Output: -15
    Explanation: In the given example:
    - Integers in the range [1, 5] that are not divisible by 1 are [], num1 is
      the sum of those integers = 0.

    - Integers in the range [1, 5] that are divisible by 1 are [1,2,3,4,5],
      num2 is the sum of those integers = 15.

    We return 0 - 15 = -15 as the answer.


    *** Constraints ***
    1 <= n, m <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats:  8.39% */
/* Space Beats: 36.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int differenceOfSums(int n, int m)
    {
        int num1 = 0;
        int num2 = 0;

        for (int i = 1; i <= n; i++)
        {
            if (i % m != 0)
                num1 += i;
            else
                num2 += i;
        }

        return num1 - num2;
    }
};




/*

    ------------
    --- IDEA ---
    ------------

    We need to find:

        sum_of_divisible - sum_of_non_divisibles


    But what numbers will be divisibles of m?
    
        m + 2m + 3m + 4m... multiples of m


    For example:
        n = 11 and m = 2:

    So the numbers divisible by 2 here are:

        1  2  3  4  5  6  7  8  9  10  11
           ^     ^     ^     ^     ^^

    As we can see all the numbers divisible by m are in form:
        
        m + 2m + 3m + 4m + ...  <==> (1 + 2 + 3 + 4 + ...) * m


    That means we only need to find the sum of multiples of m.
    Now for the "sum_of_non_divisibles" we can simply use:

        total_sum = sum_of_divisibles + sum_of_non_divisibles

    ==> sum_of_non_divisibles = total_sum - sum_of_divisibles


    Therefore the final equation that we get is:

        total_sum = sum_of_divisibles + sum_of_non_divisibles
    ==> sum_of_non_divisibles = total_sum - sum_of_divisibles


        sum_of_non_divisibles - sum_of_divisibles
    ==> total_sum - sum_of__divisibles - sum_of_divisibles
    ==> total_sum - 2 * sum_of_divisibles



    So the formula for the sum of first n natural numbers is:
        n * (n+1) / 2

    And the formula for the sum of first n multiples of a number m is:

        m * (k * (k+1) / 2), where k=n/m (number of multiples in [1...n])

    So we get the equation as:
        (n * (n+1) / 2) - (2 * m * (k * (k+1) / 2))

    We remove the 2 from the numerator and denominater from the second term as
    its both multipled as well as divided and we're now left with:

    Final Answer: 
        
        n * (n+1) / 2 - m * (k * (k+1))

*/

/* Time  Beats: 100.00% */
/* Space Beats:  36.04% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Math {
public:
    int differenceOfSums(int n, int m)
    {
        int total_sum     = n * (n + 1) / 2;
        int divisible_sum = m * (n / m) * (n / m + 1);

        return total_sum - divisible_sum;
    }
};
