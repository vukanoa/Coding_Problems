/*
    ============
    === EASY ===
    ============

    ===============================
    1995) Count Special Quadruplets
    ===============================

    ============
    Description:
    ============


    Given a 0-indexed integer array nums, return the number of distinct
    quadruplets (a, b, c, d) such that:

        + nums[a] + nums[b] + nums[c] == nums[d], and
        + a < b < c < d

    ==================================================
    FUNCTION: int countQuadruplets(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,6]
    Output: 1
    Explanation: The only quadruplet that satisfies the requirement is (0, 1,
                 2, 3) because 1 + 2 + 3 == 6.

    --- Example 2 ---
    Input: nums = [3,3,6,4,5]
    Output: 0
    Explanation: There are no such quadruplets in [3,3,6,4,5].

    --- Example 3 ---
    Input: nums = [1,1,1,3,5]
    Output: 4
    Explanation: The 4 quadruplets that satisfy the requirement are:
    - (0, 1, 2, 3): 1 + 1 + 1 == 3
    - (0, 1, 3, 4): 1 + 1 + 3 == 5
    - (0, 2, 3, 4): 1 + 1 + 3 == 5
    - (1, 2, 3, 4): 1 + 1 + 3 == 5


    *** Constraints ***
    4 <= nums.length <= 50
    1 <= nums[i] <= 100

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Similar to Two-Sum.

*/

/* Time  Beats: 59.51% */
/* Space Beats: 26.09% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int countQuadruplets(vector<int>& nums)
    {
        const auto N = nums.size();
        size_t result = 0;

        unordered_map<int, int> freq;
        freq[nums[N - 1]] = 1;

        for (int i = N-2; i > 1; i--)
        {
            for (int j = i-1; j > 0; j--)
            {
                for (int k = j-1; k >= 0; k--)
                {
                    if (freq.count(nums[i] + nums[j] + nums[k]))
                        result += freq[nums[i] + nums[j] + nums[k]];
                }
            }

            freq[nums[i]]++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Small "trick" to reduce the Time Complexity by an order of 'N'.

*/

/* Time  Beats: 59.51% */
/* Space Beats: 13.86% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution_N_Squared {
public:
    int countQuadruplets(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;
        
        unordered_map<int, int> freq;
        freq[nums[N-1] - nums[N-2]] = 1;
        
        for (int i = N-3; i >= 1; i--)
        {
            for (int j = i-1; j >= 0; j--)
                result += freq[nums[j] + nums[i]];
            
            for (int x = N-1; x > i; x--)
                freq[nums[x] - nums[i]]++;
        }

        return result;
    }
};
