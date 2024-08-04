#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===========================
    1512) Number of Good Pairs
    ===========================

    ============
    Description:
    ============

    Given an array of integers nums, return the number of good pairs.

    A pair (i, j) is called good if nums[i] == nums[j] and i < j.

    ===================================================
    FUNCTION: int numIdenticalPairs(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,1,1,3]
    Output: 4
    Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.

    --- Example 2 ---
    Input: nums = [1,1,1,1]
    Output: 6
    Explanation: Each pair in the array are good.

    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: 0

    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you have X amount of same characters, how many different pairs is there?

        2 - 1
        3 - 3
        4 - 6
        5 - 10
        6 - 15
        7 - 21

        ...

    Formula is: num_of_pairs[i] = i-1 + num_of_pairs[i-1];

*/

/* Time  Beats: 100.00% */
/* Space Beats:   7.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums)
    {
        int result = 0;

        vector<int> num_of_pairs(101, 0);
        num_of_pairs[2] = 1;

        for (int i = 3; i < 101; i++)
            num_of_pairs[i] = i-1 + num_of_pairs[i-1];

        unordered_map<int, int> umap;
        for (const int& num : nums)
            umap[num]++;

        for (const auto& entry : umap)
        {
            int number = entry.first;
            int freq   = entry.second;

            if (freq > 1)
                result += num_of_pairs[freq];
        }

        return result;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    In the previous Solution we've been building a vector "num_of_pairs" to
    have precalculated number of pairs for each occurrence.

    However, is there a math formula that can do that thing immediately?

    Turns out there is and it is very simple.


    Imaigne that we have 4 1's:

        1 1 1 1

        To create PAIRS, we need 2 of 4.
        In a standard "permutations" formula we'd have:

        _ _
        4 3

        Which is: 4 * 3 = 12

        However, over here we aren't allowed to do that since we're told that
        i < j, i.e. if we take, say, 3rd 1(index 2) of out these 4, then for
        the second index in the pair, we don't actually have 3 choices. We have
        only one.

            0 1 2 3
            1 1 1 1
                |
            ____|
            |
            v
            _ _

        For the second index, we can ONLY take the very last 1, right?

        So, if we calculated 4 * 3, that'd be misleading since we'd be counting
        some of the pairs TWICE, which is now allowed.

        Meaning, we'd have pairs indices: (1, 3) and (3, 1), which is NOT
        allowed.

        Did you catch it?

        If we are counting every pair TWICE and one of them is NOT allowed, to
        remedy this, all we have to do is simply to divide by 2 and we are
        getting the correct result for our problem.

        Although, the Time and Space Complexities stay the same, this one is
        indeed more efficient.

        If we were to vastly increase "n", we'd be having a lot more efficient
        solution.

        At least the "wall time clock" one.

*/

/* Time  Beats: 36.79% */
/* Space Beats:  7.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Improve_Formula {
public:
    int numIdenticalPairs(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int result = 0;

        unordered_map<int, int> umap;
        for (const int& num : nums)
            umap[num]++;

        for (const auto& entry : umap)
        {
            int number = entry.first;
            int freq   = entry.second;

            if (freq > 1)
                result += freq * (freq-1) / 2;
        }

        return result;
    }
};
