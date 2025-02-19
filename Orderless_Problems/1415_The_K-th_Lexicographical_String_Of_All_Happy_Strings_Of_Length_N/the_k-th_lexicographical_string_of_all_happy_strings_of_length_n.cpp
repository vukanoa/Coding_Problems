/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================================
    1415) The k-th Lexicographical String of All Happy Strings of Length n
    ======================================================================

    ============
    Description:
    ============

    A happy string is a string that:

        + consists only of letters of the set ['a', 'b', 'c'].

        + s[i] != s[i + 1] for all values of i from 1 to s.length - 1
          (string is 1-indexed).

    For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy
    strings and strings "aa", "baa" and "ababbc" are not happy strings.

    Given two integers n and k, consider a list of all happy strings of length
    n sorted in lexicographical order.

    Return the kth string of this list or return an empty string if there are
    less than k happy strings of length n.

    ==============================================
    FUNCTION: string getHappyString(int n, int k);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1, k = 3
    Output: "c"
    Explanation: The list ["a", "b", "c"] contains all happy strings of length
    1. The third string is "c".

    --- Example 2 ---
    Input: n = 1, k = 4
    Output: ""
    Explanation: There are only 3 happy strings of length 1.

    --- Example 3 ---
    Input: n = 3, k = 9
    Output: "cab"
    Explanation: There are 12 different happy string of length 3
    ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac",
    "cba", "cbc"]. You will find the 9th string = "cab"

    *** Constraints ***
    1 <= n <= 10
    1 <= k <= 100

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute Force. Classic Backtracking.

    Given the Constraints of this problem, it is obvious that we can perform a
    basic Brute Force, i.e. Backtracking, and generate all of the possible
    strings and then simply sort them and take the "k-1"-th index.

*/

/* Time  Beats: 7.27% */
/* Space Beats: 6.32% */

/* Time  Complexity: O(3 * 2^(n-1) * log(3 * 2^(n-1))) ---> O(2^n * log(2^n)) --> O(2^n) */
/* Space Complexity: O(2^n * n)                                                          */
class Solution {
public:
    string getHappyString(int n, int k)
    {
        vector<string> happy_strings;

        backtracking(n, happy_strings, "");

        if (happy_strings.size() < k)
            return "";

        sort(happy_strings.begin(), happy_strings.end());

        return happy_strings[k-1];
    }

private:
    void backtracking(int n, vector<string>& uset_strings, string str)
    {
        if (str.length() == n)
        {
            uset_strings.push_back(str);
            return;
        }

        for (const char& chr : {'a','b','c'})
        {
            if (chr == str.back())
                continue;

            str += chr;
            backtracking(n, uset_strings, str);
            str.pop_back();
        }
    }
};
