#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    740) Delete and Earn
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums. You want to maximize the number of
    points you get by performing the following operation any number of times:

        Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you
        must delete every element equal to nums[i] - 1 and every element equal
        to nums[i] + 1.

    Return the maximum number of points you can earn by applying the above
    operation some number of times.

    ===============================================
    FUNCTION: int deleteAndEarn(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,4,2]
    Output: 6
    Explanation: You can perform the following operations:
    - Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
    - Delete 2 to earn 2 points. nums = [].
    You earn a total of 6 points.


    --- Example 2 ---
    Input: nums = [2,2,3,3,3,4]
    Output: 9
    Explanation: You can perform the following operations:
    - Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums = [3,3].
    - Delete a 3 again to earn 3 points. nums = [3].
    - Delete a 3 once more to earn 3 points. nums = [].
    You earn a total of 9 points.


    *** Constraints ***
    1 <= nums.length <= 2 * 10^4
    1 <= nums[i] <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 86.75% */
/* Space Beats: 65.74% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution{
public:
    int deleteAndEarn(std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return nums[0];

        // Sort
        std::sort(nums.begin(), nums.end());

        // Remove duplicates and count occurrences
        std::vector<int> nums_no_dup;
        nums_no_dup.push_back(nums[0]);

        std::unordered_map<int, int> umap;
        umap.insert({nums[0], 1});

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] == nums[i - 1])
                umap[nums[i]]++;
            else
            {
                umap.insert({nums[i], 1});
                nums_no_dup.push_back(nums[i]);
            }
        }

        // Meat of the Solution
        int prev = 0;
        int curr = nums[0] * umap[nums[0]];

        for (int i = 1; i < nums_no_dup.size(); i++)
        {
            int val = nums_no_dup[i] * umap[nums_no_dup[i]];

            int tmp;
            if (nums_no_dup[i - 1] + 1 == nums_no_dup[i])
                tmp = std::max(prev + val, curr);
            else
                tmp = std::max(prev + val, curr + val);

            prev = curr;
            curr = tmp;
        }

        return std::max(prev, curr);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing.

*/

/* Time  Beats: 86.85% */
/* Space Beats: 58.94% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution{
public:
    int deleteAndEarn(std::vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];

        // Hash Map
        std::unordered_map<int, int> occurrences;

        // Fill the Hash Map
        for (int& num : nums)
            occurrences[num]++;

        // New vector without size of unique numbers in "nums"
        std::vector<int> new_nums(occurrences.size());

        // Fill new vector with unique values form "nums"
        int i = 0;
        for (auto& entry : occurrences)
            new_nums[i++] = entry.first;

        std::sort(new_nums.begin(), new_nums.end());

        // The most important part of the Solution
        int prev = 0;
        int curr = new_nums[0] * occurrences[new_nums[0]];
        for (int i = 1; i < new_nums.size(); i++)
        {
            int tmp;
            if (new_nums[i] - 1 == new_nums[i - 1])
                tmp = std::max(curr, new_nums[i] * occurrences[new_nums[i]] + prev);
            else
                tmp = new_nums[i] * occurrences[new_nums[i]] + std::max(curr, prev);

            prev = curr;
            curr = tmp;
        }

        return curr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Good example:
    nums = [1, 1, 1, 2, 4, 5, 5, 5, 6]

    The important part of this example is when we are on the number 4.
    Number 2 is at i-1, however, 3 1's is more than one 2, therefore we must
    have this line:

        if (i-1 >= 0 && uniq_nums[i-1] + 1 == uniq_nums[i])
            dp[i] = std::max(dp[i], dp[i-1]);

*/

/* Time  Beats: 85.77% */
/* Space Beats: 59.71% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Messy {
public:
    int deleteAndEarn(vector<int>& nums)
    {
        std::map<int, int> map;

        for (int& num : nums)
            map[num]++;

        std::vector<int> uniq_nums;
        for (auto& entry : map)
            uniq_nums.push_back(entry.first);

        //std::vector<int> dp(uniq_nums.size());
        int dp[uniq_nums.size()];

        int max = 0;
        for (int i = 0; i < uniq_nums.size(); i++)
        {
            dp[i] = map[uniq_nums[i]] * uniq_nums[i];

            int tmp = 0;
            if (i-1 >= 0 && uniq_nums[i-1] + 1 != uniq_nums[i])
                tmp = dp[i-1];

            if (i-2 >= 0)
                tmp = std::max(tmp, dp[i - 2]);

            dp[i] += tmp;

            if (i-1 >= 0 && uniq_nums[i-1] + 1 == uniq_nums[i])
                dp[i] = std::max(dp[i], dp[i-1]);

            max = std::max(max, dp[i]);
        }

        return max;
    }
};
