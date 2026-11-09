/*
    ============
    === EASY ===
    ============

    ================================================
    4038) Count Integers Appearing in a Single Block
    ================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    An integer x is special if all occurrences of x in nums appear in a single
    contiguous block.

    Return the number of distinct special integers in nums.

    ======================================================
    FUNCTION: int countSpecialIntegers(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2,1]
    Output: 1
    Explanation:
        1 appears at indices 0 and 3, forming two separate blocks, so it is not special.
        2 appears in a single contiguous block at indices [1, 2], so it is special.

    Therefore, there is one special integer.


    --- Example 2 ---
    Input: nums = [3,3,1,2,2,1]
    Output: 2
    Explanation:
        3 appears in a single contiguous block at indices [0, 1], so it is special.
        1 appears at indices 2 and 5, forming two separate blocks, so it is not special.
        2 appears in a single contiguous block at indices [3, 4], so it is special.
    Therefore, there are two special integers.



    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    There is a BETTER Solution down there, but it's always useful to see more
    approaches, as it can come in handy in other problems.

*/

/* Time  Beats: 24.71% */
/* Space Beats: 12.76% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Sorting__Inefficient {
public:
    int countSpecialIntegers(vector<int>& nums)
    {
        const int N = nums.size();
        unordered_set<int> special(nums.begin(), nums.end());

        vector<pair<int,int>> nums_w_idx;
        nums_w_idx.reserve(N);
        for (int i = 0; i < N; i++)
        {
            nums_w_idx.push_back( {nums[i], i} );
        }

        /* Sort */
        sort(nums_w_idx.begin(), nums_w_idx.end());

        for (int i = 1; i < N; i++)
        {
            if (nums_w_idx[i-1].first      == nums_w_idx[i].first &&
                nums_w_idx[i-1].second + 1 != nums_w_idx[i].second)
            {
                special.erase(nums_w_idx[i].first);
            }
        }

        return special.size();
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.88% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Efficient {
public:

    int countSpecialIntegers(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int block_freq[101] = {};
        for (int i = 0; i < N; i++)
        {
            if (i == 0 || nums[i-1] != nums[i]) // If it's a start of a block
                ++block_freq[nums[i]];
        }

        for (int contiguous_blocks : block_freq)
        {
            if (contiguous_blocks == 1)
                ++result;
        }

        return result;
    }
};
