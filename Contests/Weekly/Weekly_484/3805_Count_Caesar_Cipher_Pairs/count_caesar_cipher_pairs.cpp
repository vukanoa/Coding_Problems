/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    3805) Count Caesar Cipher Pairs
    ===============================

    ============
    Description:
    ============

    You are given an array words of n strings. Each string has length m and
    contains only lowercase English letters.

    Two strings s and t are similar if we can apply the following operation any
    number of times (possibly zero times) so that s and t become equal.

        + Choose either s or t.
        + Replace every letter in the chosen string with the next letter in the
          alphabet cyclically. The next letter after 'z' is 'a'.

    Count the number of pairs of indices (i, j) such that:

        i < j
        words[i] and words[j] are similar.

    Return an integer denoting the number of such pairs.

    ======================================================
    FUNCTION: long long countPairs(vector<string>& words);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["fusion","layout"]
    Output: 1
    Explanation:
    words[0] = "fusion" and words[1] = "layout" are similar because we can
    apply the operation to "fusion" 6 times. The string "fusion" changes as
    follows.
        "fusion"
        "gvtjpo"
        "hwukqp"
        "ixvlrq"
        "jywmsr"
        "kzxnts"
        "layout"

    --- Example 2 ---
    Input: words = ["ab","aa","za","aa"]
    Output: 2
    Explanation:
    words[0] = "ab" and words[2] = "za" are similar. words[1] = "aa" and
    words[3] = "aa" are similar.


    *** Constraints ***
    1 <= n == words.length <= 10^5
    1 <= m == words[i].length <= 10^5
    1 <= n * m <= 10^5
    words[i] consists only of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  8.78% */
/* Space Beats: 30.53% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution {
public:
    long long countPairs(vector<string>& words)
    {
        const int N = words.size();
        const int M = words[0].size();
        long long result = 0LL;

        unordered_map<string, int> umap;

        for (const string& word : words)
        {
            string str;
            str.reserve(N * M);

            for (int j = 0; j < M-1; j++)
            {
                int diff = (word[j] < word[j+1]) ? (word[j] + 26) - word[j+1] :
                                                   (word[j] +  0) - word[j+1];

                str += to_string(diff);
                str += '#';
            } 

            ++umap[str];
        }

        for (const auto& [string, count] : umap)
        {
            result += 1LL * count * (count-1) / 2;
        }

        return result;
    }
};
