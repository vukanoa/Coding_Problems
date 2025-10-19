/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    1625) Lexicographically Smallest String After Applying Operations
    =================================================================

    ============
    Description:
    ============

    You are given a string s of even length consisting of digits from 0 to 9,
    and two integers a and b.

    You can apply either of the following two operations any number of times
    and in any order on s:

        + Add a to all odd indices of s (0-indexed). Digits post 9 are cycled
          back to 0. For example, if s = "3456" and a = 5, s becomes "3951".

        + Rotate s to the right by b positions. For example, if s = "3456" and
          b = 1, s becomes "6345".

    Return the lexicographically smallest string you can obtain by applying the
    above operations any number of times on s.

    A string a is lexicographically smaller than a string b
    (of the same length) if in the first position where a and b differ, string
    a has a letter that appears earlier in the alphabet than the corresponding
    letter in b. For example, "0158" is lexicographically smaller than "0190"
    because the first position they differ is at the third letter, and '5'
    comes before '9'.

    ===============================================================
    FUNCTION: string findLexSmallestString(string s, int a, int b);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "5525", a = 9, b = 2
    Output: "2050"
    Explanation: We can apply the following operations:
    Start:  "5525"
    Rotate: "2555"
    Add:    "2454"
    Add:    "2353"
    Rotate: "5323"
    Add:    "5222"
    Add:    "5121"
    Rotate: "2151"
    Add:    "2050"​​​​​
    There is no way to obtain a string that is lexicographically smaller than
    "2050".

    --- Example 2 ---
    Input: s = "74", a = 5, b = 1
    Output: "24"
    Explanation: We can apply the following operations:
    Start:  "74"
    Rotate: "47"
    "42"
    "24"
    There is no way to obtain a string that is lexicographically smaller than
    "24".

    --- Example 3 ---
    Input: s = "0011", a = 4, b = 2
    Output: "0011"
    Explanation: There are no sequence of operations that will give us a
                 lexicographically smaller string than "0011".

    *** Constraints ***
    2 <= s.length <= 100
    s.length is even.
    s consists of digits from 0 to 9 only.
    1 <= a <= 9
    1 <= b <= s.length - 1

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  84.38% */

/* Time  Complexity: O(N^2 * d^2) */
/* Space Complexity: O(N)         */
class Solution {
public:
    string findLexSmallestString(string s, int a, int b)
    {
        const int n = s.size();

        string result = s;
        string doubled_s = s + s;

        int gcd_val = my_gcd(b, n);

        for (int i = 0; i < n; i += gcd_val)
        {
            string candidate = doubled_s.substr(i, n);
            add_to_digits(candidate, a, 1);

            if (b % 2 != 0)
            {
                add_to_digits(candidate, a, 0);
            }

            if (candidate < result)
            {
                result = candidate;
            }
        }

        return result;
    }

private:
    int my_gcd(int a, int b)
    {
        return b == 0 ? a : my_gcd(b, a % b);
    }

    void add_to_digits(string& s, int a, int start_index)
    {
        const int N = s.size();
        int min_digit = 10;
        int min_times = 0;

        for (int i = 0; i < 10; i++)
        {
            int added = ((s[start_index] - '0') + i * a) % 10;
            if (added < min_digit)
            {
                min_digit = added;
                min_times = i;
            }
        }

        for (int i = start_index; i < N; i += 2)
        {
            s[i] = '0' + ((s[i] - '0') + min_times * a) % 10;
        }
    }
};
