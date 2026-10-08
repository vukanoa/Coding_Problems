/*
    ==============
    === MEDIUM ===
    ==============

    ================================================================
    4066) Maximum Equal Adjacent Pairs After at Most One Replacement
    ================================================================

    ============
    Description:
    ============

    You are given a 1-indexed integer array nums.

    You can choose two distinct values x and y and perform the following
    operation at most once:

        Replace every occurrence of x in nums with y.

    Return the maximum possible number of pairs of adjacent elements that are
    equal after performing the operation.

    =======================================================
    FUNCTION: int maxEqualAdjacentPairs(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,2]
    Output: 2
    Explanation:
        One optimal solution is to choose x = 3 and y = 2.
        The resulting array is [1, 2, 2, 2].
        There are 2 pairs of adjacent elements that are equal: (nums[2],
        nums[3]) and (nums[3], nums[4]). Therefore, the answer is 2.

    --- Example 2 ---
    Input: nums = [1,2,1,2,1]
    Output: 4
    Explanation:
        One optimal solution is to choose x = 1 and y = 2.
        The resulting array is [2, 2, 2, 2, 2].
        There are 4 pairs of adjacent elements that are equal: (nums[1],
        nums[2]), (nums[2], nums[3]), (nums[3], nums[4]), and (nums[4],
        nums[5]).
        Therefore, the answer is 4.

    --- Example 3 ---
    Input: nums = [1,1,1]
    Output: 2
    Explanation:
        One optimal solution is to perform no operation.
        Thus, the resulting array is [1, 1, 1].
        There are 2 pairs of adjacent elements that are equal: (nums[1],
        nums[2]) and (nums[2], nums[3]).
        Therefore, the answer is 2.


    *** Constraints ***
    2 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.59% */
/* Space Beats: 30.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxEqualAdjacentPairs(vector<int>& nums)
    {
        const int N = nums.size();
        unordered_map<long long, int> adjacent_pair_count;

        int curr_equal_pairs     = 0;
        int max_additional_pairs = 0;

        for (int i = 1; i < N; i++)
        {
            if (nums[i - 1] == nums[i])
            {
                ++curr_equal_pairs;
            }
            else
            {
                long long smaller_value = min(nums[i-1], nums[i]);
                long long larger_value  = max(nums[i-1], nums[i]);

                long long adjacent_pair = (larger_value << 32) | smaller_value;

                ++adjacent_pair_count[adjacent_pair];
            }
        }

        for (const auto& [adjacent_pair, count] : adjacent_pair_count)
            max_additional_pairs = max(max_additional_pairs, count);

        return curr_equal_pairs + max_additional_pairs;
    }
};
