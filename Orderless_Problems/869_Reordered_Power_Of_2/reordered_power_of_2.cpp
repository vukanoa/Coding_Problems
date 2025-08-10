/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    869) Reordered Power of 2
    ===========================

    ============
    Description:
    ============

    You are given an integer n. We reorder the digits in any order
    (including the original order) such that the leading digit is not zero.

    Return true if and only if we can do this so that the resulting number is a
    power of two.

    ========================================
    FUNCTION: bool reorderedPowerOf2(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: true

    --- Example 2 ---
    Input: n = 10
    Output: false


    *** Constraints ***
    1 <= n <= 10^9

*/

#include <algorithm>
#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Given the constraints, i.e. "1 <= n <= 10^9", we can consider this Solution
    constant in both Space and Time.

    2^30 is GREATER than 10^9, therefore we'll need to take care of only 30
    numbers(2^0 included, that's why it's 30 and not 29).


    Since 30 is very low, we can generate all of those 30 powers of two and
    stores them as a string in a HashSet.

    However, since we're asked if we can "rearrange the digits", before storing
    the string in HashSet, we SORT the STRING itself.

    Then convert our 'n' to a string and SORT that string as well.

    At the end we simply check if n_str is present in our HashSet of "Powers of
    Two".

    That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  25.37% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool reorderedPowerOf2(int n)
    {
        unordered_set<string> powers(30);

        for (int i = 0; i < 30; i++) // Because 2^30 is GREATER than 10^9
        {
            long long num     = 1 << i; // <==> pow(2, i)
            string    num_str = to_string(num);

            /* Sort */
            sort(num_str.begin(), num_str.end());

            powers.insert(num_str);
        }

        string n_str = "";
        while (n > 0)
        {
            int digit = n % 10;
            n /= 10;

            n_str += to_string(digit);
        }

        /* Sort */
        sort(n_str.begin(), n_str.end());

        return powers.count(n_str);
    }
};
