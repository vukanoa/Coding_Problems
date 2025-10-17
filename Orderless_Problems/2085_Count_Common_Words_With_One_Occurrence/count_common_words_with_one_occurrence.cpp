/*
    ============
    === EASY ===
    ============

    ============================================
    2085) Count Common Words with One Occurrence
    ============================================

    ============
    Description:
    ============

    Given two string arrays words1 and words2, return the number of strings
    that appear exactly once in each of the two arrays.

    =========================================================================
    FUNCTION: int countWords(vector<string>& words1, vector<string>& words2);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words1 = ["leetcode","is","amazing","as","is"], words2 = ["amazing","leetcode","is"]
    Output: 2
    Explanation:
    - "leetcode" appears exactly once in each of the two arrays. We count this string.
    - "amazing" appears exactly once in each of the two arrays. We count this string.
    - "is" appears in each of the two arrays, but there are 2 occurrences of it in words1. We do not count this string.
    - "as" appears once in words1, but does not appear in words2. We do not count this string.
    Thus, there are 2 strings that appear exactly once in each of the two arrays.

    --- Example 2 ---
    Input: words1 = ["b","bb","bbb"], words2 = ["a","aa","aaa"]
    Output: 0
    Explanation: There are no strings that appear in each of the two arrays.

    --- Example 3 ---
    Input: words1 = ["a","ab"], words2 = ["a","a","a","ab"]
    Output: 1
    Explanation: The only string that appears exactly once in each of the two arrays is "ab".


    *** Constraints ***
    1 <= words1.length, words2.length <= 1000
    1 <= words1[i].length, words2[j].length <= 30
    words1[i] and words2[j] consists only of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.54% */
/* Space Beats: 71.30% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countWords(vector<string>& words1, vector<string>& words2)
    {
        unordered_map<string, int> umap1;
        unordered_map<string, int> umap2;

        for (const auto& str : words1)
            umap1[str]++;

        for (const auto& str : words2)
            umap2[str]++;

        unordered_set<string> uset;
        for (const auto& str : words1)
        {
            if (umap1.find(str) != umap1.end() && umap2.find(str) != umap2.end())
            {
                if (umap1[str] == 1 && umap2[str] == 1)
                    uset.insert(str);
            }
        }

        for (const auto& str : words2)
        {
            if (umap1.find(str) != umap1.end() && umap2.find(str) != umap2.end())
            {
                if (umap1[str] == 1 && umap2[str] == 1)
                    uset.insert(str);
            }
        }

        return uset.size();
    }
};
