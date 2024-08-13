#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    525) Contiguous Array
    ===========================

    ============
    Description:
    ============

    Given a binary array nums, return the maximum length of a contiguous
    subarray with an equal number of 0 and 1.

    ===============================================
    FUNCTION: int findMaxLength(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---


    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Very cool idea. Lol, I sound like Trump.)

*/

/* Time  Beats: 98.42% */
/* Space Beats: 14.59% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findMaxLength(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int zero = 0;
        int one  = 0;

        unordered_map<int, int> umap;
        umap.insert( {0, -1} ); // This is important!

        int result = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
                zero++;
            else
                one++;

            int difference = one - zero;
            if (umap.find(difference) == umap.end()) // Doesn't exist
                umap.insert( {difference, i} );

            result = max(result, i - umap[difference]);
        }

        return result;
    }
};
