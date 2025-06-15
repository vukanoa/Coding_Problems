/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    3583) Count Special Triplets
    ============================

    ============
    Description:
    ============

    You are given an integer array nums.

    A special triplet is defined as a triplet of indices (i, j, k) such that:

        + 0 <= i < j < k < n, where n = nums.length
        + nums[i] == nums[j] * 2
        + nums[k] == nums[j] * 2

    Return the total number of special triplets in the array.

    Since the answer may be large, return it modulo 10^9 + 7.

    =================================================
    FUNCTION: int specialTriplets(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [6,3,6]
    Output: 1
    Explanation:
    The only special triplet is (i, j, k) = (0, 1, 2), where:
        nums[0] = 6, nums[1] = 3, nums[2] = 6
        nums[0] = nums[1] * 2 = 3 * 2 = 6
        nums[2] = nums[1] * 2 = 3 * 2 = 6


    --- Example 2 ---
    Input: nums = [0,1,0,0]
    Output: 1
    Explanation:
    The only special triplet is (i, j, k) = (0, 2, 3), where:
        nums[0] = 0, nums[2] = 0, nums[3] = 0
        nums[0] = nums[2] * 2 = 0 * 2 = 0
        nums[3] = nums[2] * 2 = 0 * 2 = 0


    --- Example 3 ---
    Input: nums = [8,4,2,8,4]
    Output: 2
    Explanation:
    There are exactly two special triplets:

        (i, j, k) = (0, 1, 3)
            nums[0] = 8, nums[1] = 4, nums[3] = 8
            nums[0] = nums[1] * 2 = 4 * 2 = 8
            nums[3] = nums[1] * 2 = 4 * 2 = 8
        (i, j, k) = (1, 2, 4)
            nums[1] = 4, nums[2] = 2, nums[4] = 4
            nums[1] = nums[2] * 2 = 2 * 2 = 4
            nums[4] = nums[2] * 2 = 2 * 2 = 4


    *** Constraints ***
    3 <= n == nums.length <= 10^5
    0 <= nums[i] <= 10^5

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Have "left" and "right" unordered HashMaps where we'll have elements and
    its frequency in it.

    At the beginning put only nums[0] in "left" HashMap, and put everything
    from [1, n-1] in "right" HashMap.

    Then begin iterating from j=1, j <= n-2 because we need at least one left
    and right from the current j-th element.

    Then once we're at 'j' index, we REMOVE that from the "right" HashMap and
    simply seach in both "left" and "right HashMap for: (nums[j] * 2).

    Since we can have more than one on both sides, we multiply them because
    that gives us the number of combinations, i.e. the number of different
    unique "triplet of indices".

    At the end of a insgle iteration we now MUST put current nums[j] in "left"
    HashMap, since next 'j' index will be able to use the current 'j' index.


    Also in C++, one caveat: When you have to MOD and ADD, you do it like this:

        result = (result + mul) % MOD;

    and NOT(!!!!!) like this:

        result += mul % MOD;

    The second one will not produce correct result.

*/

/* Time  Beats: 84.89% */
/* Space Beats: 63.64% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int specialTriplets(vector<int>& nums)
    {
        const int N = nums.size();
        const int MOD = 1e9 + 7;
        int result = 0;

        unordered_map<int, int> umap_left;
        unordered_map<int, int> umap_right;

        // Left
        umap_left[nums[0]]++;

        // Right
        for (int i = 1; i < N; i++)
            umap_right[nums[i]]++;


        for (int i = 1; i < N-1; i++)
        {
            int target = nums[i] * 2LL;

            umap_right[nums[i]]--;
            if (umap_right[nums[i]] == 0)
                umap_right.erase(nums[i]);

            if (umap_left.find(target)  != umap_left.end() &&
                umap_right.find(target) != umap_right.end())
            {
                long long mul = (1LL * umap_left[target] * umap_right[target]) % MOD;
                result = (result + mul) % MOD;
            }

            umap_left[nums[i]]++;
        }

        return result % MOD;
    }
};
