/*
    ============
    === EASY ===
    ============

    =================================================
    4065) Rearrange Array by Removing Distinct Values
    =================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    You start with an empty array ans. Repeat the following operation until
    nums is empty:

        + Identify all distinct values currently present in nums.

        + Remove one occurrence of every distinct value currently in nums, and
          append those values to ans in ascending order.

    Return the array ans.

    ========================================================
    FUNCTION: vector<int> rearrangeArray(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,3,2,1,3]
    Output: [1,2,3,1,3,3]

    --- Example 2 ---
    Input: nums = [7,7,4,4,4]
    Output: [4,7,4,7,4]


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 83.26% */
/* Space Beats: 97.28% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(M)     */
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result;
        result.reserve(N); // To prevent repeated reallocations

        int freq[101] = {};
        for (const int& num : nums)
            ++freq[num];

        int remaining = N;
        while (remaining > 0)
        {
            for (int i = 0; i <= 100; i++)
            {
                if (freq[i] > 0)
                {
                    --freq[i];
                    --remaining;
    
                    result.push_back(i);
                }
            }           
        }


        return result;
    }
};
