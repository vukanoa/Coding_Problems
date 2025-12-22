/*
    ============
    === HARD ===
    ============

    ===================================
    1655) Distribute Repeating Integers
    ===================================

    ============
    Description:
    ============

    You are given an array of n integers, nums, where there are at most 50
    unique values in the array. You are also given an array of m customer order
    quantities, quantity, where quantity[i] is the amount of integers the ith
    customer ordered. Determine if it is possible to distribute nums such that:

        + The ith customer gets exactly quantity[i] integers,
        + The integers the ith customer gets are all equal, and
        + Every customer is satisfied.

    Return true if it is possible to distribute nums according to the above
    conditions.

    =======================================================================
    FUNCTION: bool canDistribute(vector<int>& nums, vector<int>& quantity);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4], quantity = [2]
    Output: false
    Explanation: The 0th customer cannot be given two different integers.

    --- Example 2 ---
    Input: nums = [1,2,3,3], quantity = [2]
    Output: true
    Explanation: The 0th customer is given [3,3]. The integers [1,2] are not
                 used.

    --- Example 3 ---
    Input: nums = [1,1,2,2], quantity = [2,2]
    Output: true
    Explanation: The 0th customer is given [1,1], and the 1st customer is given
                 [2,2].


    *** Constraints ***
    n == nums.length
    1 <= n <= 10^5
    1 <= nums[i] <= 1000
    m == quantity.length
    1 <= m <= 10
    1 <= quantity[i] <= 10^5
    There are at most 50 unique values in nums.

*/

#include <cstring>
#include <map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  5.81% */
/* Space Beats: 41.07% */

/* Time  Complexity: O(N * 2^M * 2^M) */
/* Space Complexity: O(N * 2^M)       */
class Solution {
private:
    int memo[100][1 << 11];

public:
    bool canDistribute(vector<int>& nums, vector<int>& quantities)
    {
        map<int,int> count_map;
        for (const int& num : nums)
            count_map[num]++;

        vector<int> frequencies;
        for(const auto& [key, value] : count_map)
            frequencies.push_back(value);

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return distribute_from_position(frequencies, quantities, 0, 0);
    }

public:
    bool is_valid_subset(int prev_mask, int curr_mask, vector<int>& quantities, int available_freq)
    {
        if ((prev_mask & curr_mask) != 0)
            return false;

        int num_quantities = quantities.size();
        int sum_required = 0;

        for (int i = 0; i < num_quantities; i++)
        {
            if (curr_mask & (1 << i))
                sum_required += quantities[i];
        }

        return available_freq >= sum_required;
    }

    bool distribute_from_position(vector<int>& frequencies, vector<int>& quantities, int freq_idx, int mask)
    {
        int num_frequencies = frequencies.size();
        int num_quantities  = quantities.size();

        if (mask == (1 << num_quantities) - 1)
            return true;

        if (freq_idx >= num_frequencies)
            return false;

        if (memo[freq_idx][mask] != -1)
            return memo[freq_idx][mask];

        bool can_distribute = false;
        for (int subset_mask = 0; subset_mask < (1 << num_quantities); subset_mask++)
        {
            if (is_valid_subset(mask, subset_mask, quantities, frequencies[freq_idx]))
            {
                can_distribute |= distribute_from_position(frequencies, quantities, freq_idx + 1, mask | subset_mask);

                if (can_distribute)
                    return memo[freq_idx][mask] = true;
            }
        }

        return memo[freq_idx][mask] = can_distribute;
    }
};
