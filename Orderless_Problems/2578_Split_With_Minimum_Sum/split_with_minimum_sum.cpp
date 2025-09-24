/*
    ============
    === EASY ===
    ============

    ============================
    2578) Split with Minimum Sum
    ============================

    ============
    Description:
    ============


    Given a positive integer num, split it into two non-negative integers num1
    and num2 such that:

        + The concatenation of num1 and num2 is a permutation of num.
            + In other words, the sum of the number of occurrences of each
              digit in num1 and num2 is equal to the number of occurrences of
              that digit in num.

        + num1 and num2 can contain leading zeros.

    Return the minimum possible sum of num1 and num2.

    =====
    Note: It is guaranteed that num does not contain any leading zeros.
          The order of occurrence of the digits in num1 and num2 may differ
          from the order of occurrence of num.
    =====

    ===============================
    FUNCTION: int splitNum(int num);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 4325
    Output: 59
    Explanation: We can split 4325 so that num1 is 24 and num2 is 35, giving a
                 sum of 59. We can prove that 59 is indeed the minimal possible
                 sum.

    --- Example 2 ---
    Input: num = 687
    Output: 75
    Explanation: We can split 687 so that num1 is 68 and num2 is 7, which
                 would give an optimal sum of 75.


    *** Constraints ***
    10 <= num <= 10^9

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  25.06% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int splitNum(int num)
    {
        string str = to_string(num);

        /* Sort */
        sort(str.begin(), str.end());

        string one;
        string two;

        if (str.length() & 1) // Odd length
        {
            one = str[0];

            for (int i = 1; i < str.length(); i += 2)
            {
                one += str[i];
                two += str[i+1];
            }
        }
        else
        {
            for (int i = 0; i < str.length(); i += 2)
            {
                one += str[i];
                two += str[i+1];
            }
        }

        // Delete Leading zeroes
        // one.erase(0, one.find_first_not_of('0'));
        two.erase(0, two.find_first_not_of('0'));

        return stoi(one) + stoi(two);
    }
};
