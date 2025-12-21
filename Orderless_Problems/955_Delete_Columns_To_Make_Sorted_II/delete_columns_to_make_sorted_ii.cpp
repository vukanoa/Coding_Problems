/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    955) Delete Columns to Make Sorted II
    =====================================

    ============
    Description:
    ============

    You are given an array of n strings strs, all of the same length.

    We may choose any deletion indices, and we delete all the characters in
    those indices for each string.

    For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0,
    2, 3}, then the final array after deletions is ["bef", "vyz"].

    Suppose we chose a set of deletion indices answer such that after
    deletions, the final array has its elements in lexicographic order (i.e.,
    strs[0] <= strs[1] <= strs[2] <= ... <= strs[n - 1]). Return the minimum
    possible value of answer.length.

    ====================================================
    FUNCTION: int minDeletionSize(vector<string>& strs);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: strs = ["ca","bb","ac"]
    Output: 1
    Explanation: 
    After deleting the first column, strs = ["a", "b", "c"].
    Now strs is in lexicographic order (ie. strs[0] <= strs[1] <= strs[2]).
    We require at least 1 deletion since initially strs was not in
    lexicographic order, so the answer is 1.

    --- Example 2 ---
    Input: strs = ["xc","yb","za"]
    Output: 0
    Explanation: 
    strs is already in lexicographic order, so we do not need to delete
    anything. Note that the rows of strs are not necessarily in lexicographic
    order: i.e., it is NOT necessarily true that (strs[0][0] <= strs[0][1] <=
    ...)

    --- Example 3 ---
    Input: strs = ["zyx","wvu","tsr"]
    Output: 3
    Explanation: We have to delete every column.


    *** Constraints ***
    n == strs.length
    1 <= n <= 100
    1 <= strs[i].length <= 100
    strs[i] consists of lowercase English letters.

*/

#include <climits>
#include <string>
#include <vector>

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 20.79% */
/* Space Beats: 87.08% */

/* Time  Complexity: O(N * LEN) */
/* Space Complexity: O(N)       */
using namespace std;
class Solution {
public:
    int minDeletionSize(vector<string>& strs)
    {
        const int N   = strs.size();
        const int LEN = strs[0].size();
        int result = 0;

        vector<bool> sorted(N-1, false);

        for (int chr_idx = 0; chr_idx < LEN; chr_idx++)
        {
            bool need_delete = false;

            for (int i = 0; i < N-1; i++)
            {
                if ( ! sorted[i] && strs[i][chr_idx] > strs[i+1][chr_idx])
                {
                    need_delete = true;
                    break;
                }
            }

            if (need_delete)
            {
                result++;
                continue;
            }

            for (int i = 0; i < N-1; i++)
            {
                if ( ! sorted[i] && strs[i][chr_idx] < strs[i+1][chr_idx])
                    sorted[i] = true;
            }

            bool all_sorted = true;
            for (int i = 0; i < N-1; i++)
            {
                if ( ! sorted[i])
                {
                    all_sorted = false;
                    break;
                }
            }

            if (all_sorted)
                break;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.92% */

/* Time  Complexity: O(N * LEN) */
/* Space Complexity: O(N)       */
class Solution_2 {
public:
    using uint128_t = unsigned __int128;

    int minDeletionSize(vector<string>& strs)
    {
        const int N   = strs.size();
        const int LEN = strs[0].size();

        uint128_t is_sorted = 0;
        uint128_t remove = 0;

        for (int chr_idx = 0; chr_idx < LEN; chr_idx++)
        {
            bool need_remove = false;

            for (int i = 0; i < N-1; i++)
            {
                if (((is_sorted >> i) & 1) == 0 && strs[i][chr_idx] > strs[i+1][chr_idx])
                {
                    remove |= ((uint128_t)1 << chr_idx);
                    need_remove = true;
                    break;
                }
            }

            if (need_remove)
                continue;

            for (int i = 0; i < N-1; i++)
            {
                if (((is_sorted >> i) & 1) == 0 && strs[i][chr_idx] < strs[i+1][chr_idx])
                    is_sorted |= ((uint128_t)1 << i);
            }
        }

        // Count set bits in remove (low 64 + high 64)
        return __builtin_popcountll((unsigned long long)(remove & ULLONG_MAX))
             + __builtin_popcountll((unsigned long long)(remove >> 64));
    }
};
