/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    398) Random Pick Index
    ===========================

    ============
    Description:
    ============


    Given an integer array nums with possible duplicates, randomly output the
    index of a given target number. You can assume that the given target number
    must exist in the array.

    Implement the Solution class:

        + Solution(int[] nums) Initializes the object with the array nums.

        + int pick(int target) Picks a random index i from nums where
          nums[i] == target. If there are multiple valid i's, then each index
          should have an equal probability of returning.

    ===============================
    CLASS:
    class Solution {
    public:
        Solution(vector<int>& nums) {
            
        }
        
        int pick(int target) {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["Solution", "pick", "pick", "pick"]
    [[[1, 2, 3, 3, 3]], [3], [1], [3]]
    Output
    [null, 4, 0, 2]

    Explanation
    Solution solution = new Solution([1, 2, 3, 3, 3]);
    solution.pick(3); // It should return either index 2, 3, or 4 randomly.
                      // Each index should have equal probability of returning.

    solution.pick(1); // It should return 0. Since in the array only nums[0] is
                      // equal to 1.

    solution.pick(3); // It should return either index 2, 3, or 4 randomly.
                      // Each index should have equal probability of returning.

    *** Constraints ***
    1 <= nums.length <= 2 * 10^4
    -2^31 <= nums[i] <= 2^31 - 1
    target is an integer from nums.
    At most 104 calls will be made to pick.

*/

#include <vector>
#include <random>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  5.14% */
/* Space Beats: 68.86% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    vector<int> nums;
    mt19937 rng; // Random Generator

public:
    Solution(vector<int>& nums)
    {
        this->nums = nums;

        random_device random_device;
        rng = mt19937(random_device());
    }

    int pick(int target)
    {
        int result = -1;
        int count = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != target)
                continue;

            count++;
            uniform_int_distribution<int> dist(0, count - 1);
            if (dist(rng) == 0)
                result = i;
        }

        return result;
    }
};
