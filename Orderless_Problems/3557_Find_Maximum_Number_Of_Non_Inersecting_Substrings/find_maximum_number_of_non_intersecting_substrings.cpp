/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3556) Find Maximum Number of Non Intersecting Substrings
    ========================================================

    ============
    Description:
    ============

    You are given a string word.

    Return the maximum number of non-intersecting of word that are at least
    four characters long and start and end with the same letter.

    =========================================
    FUNCTION: int maxSubstrings(string word);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "abcdeafdef"
    Output: 2
    Explanation:
    The two substrings are "abcdea" and "fdef".

    --- Example 2 ---
    Input: word = "bcdaaaab"
    Output: 1
    Explanation:
    The only substring is "aaaa". Note that we cannot also choose "bcdaaaab"
    since it intersects with the other substring.


    *** Constraints ***
    1 <= word.length <= 2 * 10^5
    word consists only of lowercase English letters.

*/

#include <algorithm>
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

/* Time  Beats:  9.30% */
/* Space Beats: 61.33% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int maxSubstrings(string word)
    {
        const int N = word.length();
        int result = 0;

        unordered_map<char, vector<int>> umap;

        for (int i = 0; i < N; i++)
        {
            char chr = word[i];
            umap[chr].push_back(i);
        }

        // O(N * logN)
        for (auto& [chr, vec] : umap)
            sort(vec.begin(), vec.end());


        vector<int> dp(N + 1, 0);
        for (int i = N-4; i >= 0; i--)
        {
            char chr = word[i];

            auto it = lower_bound(umap[chr].begin(), umap[chr].end(), i);
            int idx = it - umap[chr].begin();

            int remaining = umap[chr].size() - (idx + 1);

            if (remaining == 0)
            {
                dp[i] = dp[i+1];
            }
            else
            {
                int target = umap[chr][idx] + 2;
                auto it2 = upper_bound(umap[chr].begin() + idx + 1, umap[chr].end(), target);
                int idx2 = it2 - umap[chr].begin();

                if (it2 != umap[chr].end())
                {
                    dp[i] = max(dp[i+1], 1 + dp[umap[chr][idx2] + 1]);
                }
                else
                    dp[i] = dp[i+1];
            }
        }

        return dp[0];
    }
};
