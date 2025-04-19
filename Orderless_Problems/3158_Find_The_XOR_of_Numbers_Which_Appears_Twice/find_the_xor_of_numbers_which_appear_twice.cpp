/*
    ============
    === EASY ===
    ============

    ================================================
    3158) Find the XOR of Numbers Which Appear Twice
    ================================================

    ============
    Description:
    ============

    You are given an array nums, where each number in the array appears either
    once or twice.

    Return the bitwise XOR of all the numbers that appear twice in the array,
    or 0 if no number appears twice.

    =====================================================
    FUNCTION: int duplicateNumbersXOR(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,3]
    Output: 1
    Explanation:
    The only number that appears twice in nums is 1.

    --- Example 2 ---
    Input: nums = [1,2,3]
    Output: 0
    Explanation:
    No number appears twice in nums.

    --- Example 3 ---
    Input: nums = [1,2,2,1]
    Output: 3
    Explanation:
    Numbers 1 and 2 appeared twice. 1 XOR 2 == 3.


    *** Constraints ***
    1 <= nums.length <= 50
    1 <= nums[i] <= 50
    Each number in nums appears either once or twice.

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.23% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int duplicateNumbersXOR(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        unordered_map<int,int> umap;

        for (int i = 0; i < N; i++)
            umap[nums[i]]++;

        int xor_num = 0;
        for (const auto& entry : umap)
        {
            if (entry.second == 2)
                xor_num ^= entry.first;
        }

        return xor_num;
    }
};
