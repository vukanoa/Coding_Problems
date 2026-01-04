/*
    ============
    === EASY ===
    ============

    ===========================
    14) Longest Common Prefix
    ===========================

    ============
    Description:
    ============

    Write a function to find the longest common prefix string amongst
    an array of strings.

    If there is no common prefix, return an empty string "".

    ===========================================================
    FUNCTION: string longestCommonPrefix(vector<string>& strs);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  strs = ["flower", "flow", "flight"]
    Output: "fl"

    --- Example 2 ---
    Input:  strs = ["dog", "racecar", "car"]
    Output: ""
    Explanation: There is no common prefix among the input stringsn.

    *** Constraints ***
    1 <= strs.length() <= 200
    0 <= strs[i].length() <= 200
    strs[i] consists of only lowercase English letters.
*/

/*
    ------------
    --- IDEA ---
    ------------

    The most logical approach.

    We MUST stop if the i-th character is out of bounds for the given word,
    therefore it doesn't matter up to which length are we going to iterate
    our 'i' variable.

    If we ever go out of bounds with the letter_idx of current word, then we
    MUST immediately return constructed string up to this point, NOT INCLUDING
    this one.

    
    This can be implemented in three different ways in C++:
        1. Using repeated operator+= to append characters has amortized O(1)
           time per append, resulting in total O(L) time for L appended
           characters. This complexity does not rely on Small String
           Optimization; SSO is implementation-defined and only affects
           constant factors.

        2. Using strs[0].substr(0, letter_idx);

        3. Using "ostringstream", however it has a huge overheard, so it should
           be avoided for smaller string concatenations.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/* Time  Complexity: O(L * N) */ // L <==> longest_common_prefix length
/* Space Complexity: O(1)     */ // Result isn't EXTRA
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs)
    {
        if (strs.size() == 1) // Then return immediately
            return strs[0];

        const int N = strs.size();
        string longest_common_prefix = "";

        for (int letter_idx = 0; letter_idx < strs[0].size(); letter_idx++)
        {
            for (int i = 1; i < N; i++)
            {
                if (letter_idx >= static_cast<int>(strs[i].size()))
                    return longest_common_prefix;

                if (strs[0][letter_idx] != strs[i][letter_idx])
                    return longest_common_prefix;
            }

            longest_common_prefix += strs[0][letter_idx];
        }

        return longest_common_prefix;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The big brained concept here seems to be this:

    If the array is sorted alphabetically then you can assume that the first
    element of the array and the last element of the array will have most
    different prefixes of all comparisons that could be made between strings in
    the array. If this is true, you only have to compare these two strings.

    I know this seems unintuitive, and I also know that you're trying to think
    of some example where first and last elements are similar, but the middle
    one is completely different.

        ["preheat", "oven", "prehistoric"] // UNSorted

    However, after sorting this, it becomes:

        ["preheat", "prehistoric", "oven"] // Sorted

    And thus we've successfully eliminated this imaginary problem.



    Also, it helps to consider these examples:

        ["flower", "hat", "something", "zebra"] // Sorted

        ["flower", "flp", "flq", "flzzz"]       // Sorted

        ["fl", "flower", "flp", "flq", "flzzz"] // Sorted

*/

/* Time  Beats:   100% */
/* Space Beats: 61.24% */

/* Time  Complexity: O(L * N * logN) */ // L <==> longest_common_prefix length
/* Space Complexity: O(logN)         */ // Space Complexity of C++'s IntroSort
class Solution_Sort_Alphabetically {
public:
    string longestCommonPrefix(vector<string>& strs)
    {
        const int N = strs.size();
        string longest_common_prefix = "";

        // Sort lexicographically
        sort(strs.begin(), strs.end());

        string first = strs[0];
        string last  = strs[N-1];

        int SHORTER_STR_LEN = min(first.size(), last.size());
        for (int letter_idx = 0; letter_idx < SHORTER_STR_LEN; letter_idx++)
        {
            if (first[letter_idx] != last[letter_idx])
                return longest_common_prefix;

            longest_common_prefix += first[letter_idx];
        }

        return longest_common_prefix;
    }
};
