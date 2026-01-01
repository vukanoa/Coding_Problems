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

/* Time  Beats: 85.56% */
/* Space Beats: 66.01% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    int deleteAndEarn(std::vector<int>& nums)
    {
        /* Hash Map */
        std::unordered_map<int, int> occurrences;

        /* Fill Hash Map */
        for (int& num : nums)
            occurrences[num]++;

        /* Create new vector with unique elements */
        std::vector<int> uniq_nums(occurrences.size());

        /* Fill new vector with unique values from "nums" */
        int i = 0;
        for (auto& entry : occurrences)
            uniq_nums[i++] = entry.first;

        /* Sort */
        std::sort(uniq_nums.begin(), uniq_nums.end());

        /*
           The most important part of the Solution
           It uses only two variables instead of the whole vector "dp"
        */
        int prev = 0;
        int curr = uniq_nums[0] * occurrences[uniq_nums[0]];
        for (int i = 1; i < uniq_nums.size(); i++)
        {
            int tmp;

            if (uniq_nums[i - 1] + 1 == uniq_nums[i])
                tmp = std::max(curr, uniq_nums[i] * occurrences[uniq_nums[i]] + prev);
            else
                tmp = uniq_nums[i] * occurrences[uniq_nums[i]] + std::max(curr, prev);

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

    Same idea sa abov, implemented a bit differently. This one isn't Space
    optimized, however it is much easier for reading and understanding how this
    approach works.

    Therefore, I'll leave it here for didactic purposes.

*/

/* Time  Beats: 64.74% */
/* Space Beats: 45.29% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    int deleteAndEarn(std::vector<int>& nums)
    {
        /* Hash Map */
        std::unordered_map<int, int> umap;

        /* Fill Hash Map */
        for (const int& num : nums)
            umap[num]++;

        /* Create new vector with unique elements */
        std::vector<int> uniq;
        for (const auto& entry : umap)
            uniq.push_back(entry.first);

        /* Sort */
        std::sort(uniq.begin(), uniq.end());

        /* DP vector */
        std::vector<int> dp(uniq.size(), 0);
        dp[0] = umap[uniq[0]] * uniq[0]; // Solve for 0-th index

        for (int i = 1; i < uniq.size(); i++) // Start from 1
        {
            dp[i] = umap[uniq[i]] * uniq[i];

            if (i-1 >= 0 && uniq[i-1]+1 != uniq[i])
                dp[i] += dp[i-1];
            else if (i-2 >= 0)
                dp[i] += dp[i-2];

            dp[i] = std::max(dp[i], dp[i-1]);
        }

        return dp[uniq.size() - 1];
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
        // Red Black Tree
        std::map<int, int> map;

        for (int& num : nums)
            map[num]++;

        std::vector<int> uniq_nums;
        for (auto& entry : map)
            uniq_nums.push_back(entry.first);

        // std::vector<int> dp(uniq_nums.size());
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




/*
    ------------
    --- IDEA ---
    ------------

    This Solution doesn't use std::sort, instead it sorts elements using a
    std::map aka "Red and Black Tree", therefore the Time Complexity is the
    same, but I wanted to show another way of implementing this.

*/

/* Time  Beats: 53.65% */
/* Space Beats: 61.38% */

/* Time  Complexity: O(N * log N) */
/* Space Complexity: O(N) */
class Solution_Without_Using_Sort_Function { // Uses Red and Black Tree instead
public:
    int deleteAndEarn(std::vector<int>& nums)
    {
        // Red Black tree(Insertion time O(log N))
        std::map<int, int> map;

        // If there are N different numbers, there will be N insertions and
        // every insertion is O(log N) therefore the total Time Complexity of
        // this piece of code is: O(N * log N)
        for (int& num : nums)
        {
            if (map.find(num) == map.end()) // Doesn't exist yet
                map.insert( {num, 1} );
            else
                map[num]++;
        }

        // O(M), where M is the number of distinct numbers in "nums".
        // 1 <= M <= N
        // M, in the worst case, is the same as N
        // Therefore we can say, the Time Complexity is:
        // O(N)
        std::vector<int> uniq_nums;
        for (auto& entry : map)
            uniq_nums.push_back(entry.first);

        std::vector<int> dp(uniq_nums.size(), 0);
        dp[0] = uniq_nums[0] * map[uniq_nums[0]];

        // O(M), i.e O(N)
        for (int i = 1; i < uniq_nums.size(); i++)
        {
            int tmp = uniq_nums[i] * map[uniq_nums[i]];

            if (uniq_nums[i-1] == uniq_nums[i]-1)
            {
                if (i-2 >= 0)
                    dp[i] = std::max(dp[i-2] + tmp, dp[i-1]);
                else
                    dp[i] = std::max(tmp, dp[i-1]);
            }
            else
                dp[i] = tmp + dp[i-1];
        }

        return dp[uniq_nums.size() - 1];
    }
};
