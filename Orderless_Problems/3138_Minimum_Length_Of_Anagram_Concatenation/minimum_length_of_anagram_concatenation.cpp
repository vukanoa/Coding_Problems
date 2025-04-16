/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3138) Minimum Length of Anagram Concatenation
    =============================================

    ============
    Description:
    ============

    You are given a string s, which is known to be a concatenation of anagrams
    of some string t.

    Return the minimum possible length of the string t.

    An anagram is formed by rearranging the letters of a string. For example:
    "aab", "aba", and, "baa" are anagrams of "aab".

    =========================================
    FUNCTION: int minAnagramLength(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abba"
    Output: 2
    Explanation:
    One possible string t could be "ba".

    --- Example 2 ---
    Input: s = "cdef"
    Output: 4
    Explanation:
    One possible string t could be "cdef", notice that t can be equal to s.

    --- Example 3 ---
    Input: s = "abcbcacabbaccba"
    Output: 3


    *** Constraints ***
    1 <= s.length <= 10^5
    s consist only of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 36.68% */
/* Space Beats: 74.53% */

/*
    Theoretical: Time Complexity: O(N^2 * logN)
    Parctical:   Time Complexity: O(D * N * logK)

    Where:
        D is the number of divisors of N(~128 for N = 1e5)
        K is the current candidate size (<= N/2)

        and early break DRASTICALLY reduces work

*/
/* Space Complexity: O(N)          */
class Solution {
public:
    int minAnagramLength(string s)
    {
        const int N = s.length();
        int result = 0;


        for (int size = 1; size <= N/2; size++)
        {
            if (N % size != 0)
                continue;

            string str = s.substr(0, size);
            sort(str.begin(), str.end());

            unordered_map<string,int> counter;
            counter[str]++;

            for (int x = size; x < N; x += size)
            {
                string substr = s.substr(x, size);
                sort(substr.begin(), substr.end());

                counter[substr]++;

                if (counter.size() > 1)
                    break;
            }

            if (counter.size() == 1)
                return size;
        }

        return N;
    }
};
