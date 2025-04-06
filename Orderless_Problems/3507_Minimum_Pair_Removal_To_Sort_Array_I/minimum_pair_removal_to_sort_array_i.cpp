/*
    ============
    === EASY ===
    ============

    ==========================================
    3507) Minimum Pair Removal to Sort Array I
    ==========================================

    ============
    Description:
    ============

    Given an array nums, you can perform the following operation any number of
    times:

        + Select the adjacent pair with the minimum sum in nums. If multiple
          such pairs exist, choose the leftmost one.

        + Replace the pair with their sum.

    Return the minimum number of operations needed to make the array
    non-decreasing.

    An array is said to be non-decreasing if each element is greater than or
    equal to its previous element (if it exists).

    =====
    Note: Please do not copy the description during the contest to maintain the
          integrity of your submissions.©leetcode
    =====

    ====================================================
    FUNCTION: int minimumPairRemoval(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,2,3,1]
    Output: 2
    Explanation:
        The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
        The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
    The array nums became non-decreasing in two operations.
    Note: Please do not copy the description during the contest to maintain the
    integrity of your submissions.©leetcode


    --- Example 2 ---
    Input: nums = [1,2,2]
    Output: 0
    Explanation:
    The array nums is already sorted.©leetcode


    *** Constraints ***
    1 <= nums.length <= 50
    -1000 <= nums[i] <= 1000

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums)
    {
        int result = 0;

        while ( ! is_sorted(nums) && nums.size() > 1)
        {
            int min_sum = INT_MAX;
            for (int i = 1; i < nums.size(); i++)
                min_sum = min(min_sum, nums[i-1] + nums[i]);

            vector<int> tmp = {nums[0]};

            for (int i = 1; i < nums.size(); i++)
            {
                if (nums[i-1] + nums[i] == min_sum)
                {
                    tmp.pop_back();
                    tmp.push_back(min_sum);

                    if (i + 1 < nums.size())
                        tmp.insert(tmp.end(), nums.begin() + i + 1, nums.end());

                    break;
                }
                else
                    tmp.push_back(nums[i]);
            }

            nums.clear();
            nums = tmp;

            result++;
        }

        return result;
    }

private:
    bool is_sorted(vector<int>& nums)
    {
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i - 1] > nums[i])
                return false;
        }

        return true;
    }
};
