/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    3862) Find the Smallest Balanced Index
    ======================================

    ============
    Description:
    ============

    You are given an integer array nums.

    An index i is balanced if the sum of elements strictly to the left of i
    equals the product of elements strictly to the right of i.

    If there are no elements to the left, the sum is considered as 0.
    Similarly, if there are no elements to the right, the product is considered
    as 1.

    Return an integer denoting the smallest balanced index. If no balanced
    index exists, return -1.

    =======================================================
    FUNCTION: int smallestBalancedIndex(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,2]
    Output: 1
    Explanation:
    For index i = 1:
        Left sum = nums[0] = 2
        Right product = nums[2] = 2
        Since the left sum equals the right product, index 1 is balanced.
    No smaller index satisfies the condition, so the answer is 1.

    --- Example 2 ---
    Input: nums = [2,8,2,2,5]
    Output: 2
    Explanation:
    For index i = 2:
        Left sum = 2 + 8 = 10
        Right product = 2 * 5 = 10
        Since the left sum equals the right product, index 2 is balanced.
    No smaller index satisfies the condition, so the answer is 2.

    --- Example 3 ---
    Input: nums = [1]
    Output: -1
    For index i = 0:
        The left side is empty, so the left sum is 0.
        The right side is empty, so the right product is 1.
        Since the left sum does not equal the right product, index 0 is not
        balanced.
    Therefore, no balanced index exists and the answer is -1.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one uses "unsigned __int128", otherwise we have to make our Solution
    a bit less readable and a bit less symmetrical.

*/

/* Time  Beats: 5.07% */
/* Space Beats: 5.07% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int smallestBalancedIndex(vector<int>& nums)
    {
        const int N = nums.size();

        vector<unsigned __int128> prefix_sum (N, 0);
        vector<unsigned __int128> suffix_prod(N, 1);

        for (int i = 1; i < N; i++)
        {
            prefix_sum[0    + i] = static_cast<unsigned __int128>(prefix_sum [0   + i - 1] + nums[0   + i - 1]);
            suffix_prod[N-1 - i] = static_cast<unsigned __int128>(suffix_prod[N-1 - i + 1] * nums[N-1 - i + 1]);
        }

        for (int i = 1; i < N; i++)
        {
            if (prefix_sum[i] == suffix_prod[i])
                return i;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 50.24% */
/* Space Beats: 22.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_unsigned_long_long {
public:
    int smallestBalancedIndex(vector<int>& nums)
    {
        const int N = nums.size();

        unsigned long long total_sum = accumulate(nums.begin(), nums.end(), 0ULL); 

        vector<unsigned long long> prefix_sum (N, 0LL);
        vector<unsigned long long> suffix_prod(N, 1LL);

        for (int i = 1; i < N; i++)
        {
            prefix_sum[i] = 1ULL * prefix_sum [i - 1] + nums[i - 1];

            if (suffix_prod[N-1 - i + 1] > total_sum / nums[N-1 - i + 1])
                suffix_prod[N-1 - i] = total_sum + 1;
            else
                suffix_prod[N-1 - i] = 1ULL * suffix_prod[N-1 - i + 1] * nums[N-1 - i + 1];
        }

        for (int i = 1; i < N; i++)
        {
            if (prefix_sum[i] == suffix_prod[i])
                return i;
        }

        return -1;
    }
};
