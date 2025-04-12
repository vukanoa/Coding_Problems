/*
    ============
    === HARD ===
    ============

    =====================================
    3272) Find the Count of Good Integers
    =====================================

    ============
    Description:
    ============

    You are given two positive integers n and k.

    An integer x is called k-palindromic if:

        + x is a palindrome
        + x is divisible by k.

    An integer is called good if its digits can be rearranged to form a
    k-palindromic integer. For example, for k = 2, 2020 can be rearranged to
    form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to
    form a k-palindromic integer.

    Return the count of good integers containing n digits.

    =====
    Note: that any integer must not have leading zeros, neither before nor
          after rearrangement. For example, 1010 cannot be rearranged to form
          101.
    =====

    ====================================================
    FUNCTION: long long countGoodIntegers(int n, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, k = 5
    Output: 27
    Explanation:
    Some of the good integers are:
        551 because it can be rearranged to form 515.
        525 because it is already k-palindromic.

    --- Example 2 ---
    Input: n = 1, k = 4
    Output: 2
    Explanation:
    The two good integers are 4 and 8.

    --- Example 3 ---
    Input: n = 5, k = 6
    Output: 2468


    *** Constraints ***
    1 <= n <= 10
    1 <= k <= 9

*/

#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 55.17% */
/* Space Beats: 43.10% */

/* Time  Complexity: O(N * logN * 10^M) */
/* Space Complexity: O(N * 10^M)        */
class Solution {
public:
    long long countGoodIntegers(int n, int k)
    {
        long long result = 0;

        unordered_set<string> dict;
        int base = pow(10, (n - 1) / 2);
        int skip = n & 1;

        /* Enumerate the number of palindrome numbers of n digits */
        for (int i = base; i < base * 10; i++)
        {
            string s = to_string(i);

            s += string(s.rbegin() + skip, s.rend());

            long long palindromicInteger = stoll(s);
            /* If the current palindrome number is a k-palindromic integer */
            if (palindromicInteger % k == 0)
            {
                sort(s.begin(), s.end());
                dict.emplace(s);
            }
        }

        vector<long long> factorial(n + 1, 1);

        for (int i = 1; i <= n; i++)
            factorial[i] = factorial[i - 1] * i;

        for (const string &str : dict)
        {
            vector<int> count(10);

            for (const char& chr : str)
                count[chr - '0']++;

            /* Calculate permutations and combinations */
            long long total = (n - count[0]) * factorial[n - 1];

            for (int x : count)
                total /= factorial[x];

            result += total;
        }

        return result;
    }
};
