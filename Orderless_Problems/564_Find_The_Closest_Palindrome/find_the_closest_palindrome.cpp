#include <iostream>

/*
    ============
    === HARD ===
    ============

    ================================
    564) Find The Closest Palindrome
    ================================

    ============
    Description:
    ============

    Given a string n representing an integer, return the closest integer (not
    including itself), which is a palindrome. If there is a tie, return the
    smaller one.

    The closest is defined as the absolute difference minimized between two
    integers.

    ==============================================
    FUNCTION: string nearestPalindromic(string n); 
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = "123"
    Output: "121"

    --- Example 2 ---
    Input: n = "1"
    Output: "0"
    Explanation: 0 and 2 are the closest palindromes but we return the smallest
                 which is 0.


    *** Constraints ***
    1 <= n.length <= 18
    n consists of only digits.
    n does not have leading zeros.
    n is representing an integer in the range [1, 10^18 - 1].

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.74% */
/* Space Beats: 5.96% */

/* Time  Complexity: O(logn * logn) */
/* Space Complexity: O(logn)        */
class Solution {
public:
    string nearestPalindromic(string n)
    {
        int len = n.size();

        long long num = stoll(n);
        long long a = max_binary_search(num);
        long long b = min_binary_search(num);

        if (abs(a - num) <= abs(b - num))
            return to_string(a);

        return to_string(b);
    }

private:

    // abcde -> abcba, abde -> abba
    long long convert(long long& num)
    {
        string s = to_string(num);

        const int n = s.length();

        int left  = (n - 1) / 2;
        int right = n / 2;

        while (left >= 0)
            s[right++] = s[left--];

        return stoll(s);
    }

    long long max_binary_search(long long num)
    {
        long long left  = 0;
        long long right = num;

        long long result = INT_MIN;

        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            long long palindrome = convert(mid);

            if (palindrome < num)
            {
                result = palindrome;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return result;
    }

    long long min_binary_search(long long num)
    {
        long long left = num, right = 1e18;
        long long result = INT_MIN;

        while (left <= right)
        {
            long long mid = (right - left) / 2 + left;
            long long palindrome = convert(mid);

            if (palindrome > num)
            {
                result = palindrome;
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return result;
    }
};
