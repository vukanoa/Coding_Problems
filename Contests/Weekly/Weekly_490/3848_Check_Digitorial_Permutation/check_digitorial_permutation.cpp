/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3848) Check Digitorial Permutation
    ==================================

    ============
    Description:
    ============


    You are given an integer n.

    A number is called digitorial if the sum of the factorials of its digits is
    equal to the number itself.

    Determine whether any permutation of n (including the original order) forms
    a digitorial number.

    Return true if such a permutation exists, otherwise return false.

    =====
    Note: The factorial of a non-negative integer x, denoted as x!, is the
          product of all positive integers less than or equal to x, and 0! = 1.

          A permutation is a rearrangement of all the digits of a number that
          does not start with zero. Any arrangement starting with zero is
          invalid.
    =====

    ==============================================
    FUNCTION: bool isDigitorialPermutation(int n);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 145
    Output: true
    Explanation:
    The number 145 itself is digitorial since 1! + 4! + 5! = 1 + 24 + 120 =
    145. Thus, the answer is true.


    --- Example 2 ---
    Input: n = 10
    Output: false
    Explanation:
    10 is not digitorial since 1! + 0! = 2 is not equal to 10, and the
    permutation "01" is invalid because it starts with zero.



    *** Constraints ***
    1 <= n <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.49% */
/* Space Beats: 74.12% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(logN) */
class Solution {
public:
    bool isDigitorialPermutation(int n)
    {
        int factorial[10] = {};
        factorial[0] = 1;
        factorial[1] = 1;
        factorial[2] = 2;
        factorial[3] = 6;
        factorial[4] = 24;
        factorial[5] = 120;
        factorial[6] = 720;
        factorial[7] = 5040;
        factorial[8] = 40320;
        factorial[9] = 362880;

        vector<int> freq_orig(10, 0);
        vector<int> freq_sum (10, 0);

        int sum  = 0;
        int copy = n;
        while (copy > 0)
        {
            int digit = copy % 10;
            
            sum += factorial[digit];
            ++freq_orig[digit];
            
            copy /= 10;
        }

        copy = sum;
        while (copy > 0)
        {
            int digit = copy % 10;

            ++freq_sum[digit];

            copy /= 10;
        }

        return freq_orig == freq_sum;
    }
};
