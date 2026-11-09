/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3927) Minimize Array Sum Using Divisible Replacements
    =====================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    You can perform the following operation any number of times:

        + Choose two indices a and b such that nums[a] % nums[b] == 0.
        + Replace nums[a] with nums[b].

    Return the minimum possible sum of the array after performing any number of
    operations.

    ===================================================
    FUNCTION: long long minArraySum(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,6,2]
    Output: 7
    Explanation:
        Choose a = 1, b = 2, where nums[a] = 6 and nums[b] = 2. Since 6 % 2 == 0, replace nums[1] with nums[2].
        The array becomes [3, 2, 2].
        No further operation reduces the sum. Thus, the final sum is 3 + 2 + 2 = 7.

    --- Example 2 ---
    Input: nums = [4,2,8,3]
    Output: 9
    Explanation:
        Choose a = 0, b = 1, where nums[a] = 4 and nums[b] = 2. Since 4 % 2 == 0, replace nums[0] with nums[1].
        Choose a = 2, b = 1, where nums[a] = 8 and nums[b] = 2. Since 8 % 2 == 0, replace nums[2] with nums[1].
        The array becomes [2, 2, 2, 3].
        No further operation reduces the sum. Thus, the final sum is 2 + 2 + 2 + 3 = 9.

    --- Example 3 ---
    Input: nums = [7,5,9]
    Output: 21
    Explanation:
        There is no pair (a, b) such that nums[a] % nums[b] == 0.
        Hence, no operation can be performed. The sum remains 7 + 5 + 9 = 21.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <unordered_set>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    For each number, go through all of its factors--there are exactly
    sqrt(nums[i]) of them--and if some factor exists in "nums" then check if
    that's the minimal present factor. If it is, simply add it to the result.

    In other words--For each nums[i], out of ALL of ITS factors that are
    PRESENT in vector "nums", take the smallest one and add it to the result.
    (if none of its factors are present, add nums[i] itself)

*/

/* Time  Beats: 26.86% */
/* Space Beats: 41.78% */

/* Time  Complexity: O(N * sqrt(M)) */ // Where 'M' is max nums[i] in nums
/* Space Complexity: O(N)           */
class Solution {
public:
    long long minArraySum(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        unordered_set<int> uset(nums.begin(), nums.end());

        for (const int& num : nums)
        {
            long long candidate = 1LL * num;

            for (int f = 1; f * f <= num; f++)
            {
                if (num % f == 0)
                {
                    if (uset.find(f) != uset.end())
                        candidate = min(candidate, 1LL * f);

                    if (uset.find(num / f) != uset.end())
                        candidate = min(candidate, 1LL * num / f);
                }
            }

            result += candidate;
        }

        return result;
    }
};
