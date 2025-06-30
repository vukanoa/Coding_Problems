/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3599) Partition Array to Minimize XOR
    =====================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    Your task is to partition nums into k non-empty subarrays. For each
    subarray, compute the bitwise XOR of all its elements.

    Return the minimum possible value of the maximum XOR among these k
    subarrays.

    ===============================================
    FUNCTION: int minXor(vector<int>& nums, int k);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3], k = 2
    Output: 1
    Explanation:
    The optimal partition is [1] and [2, 3].
        XOR of the first subarray is 1.
        XOR of the second subarray is 2 XOR 3 = 1.
    The maximum XOR among the subarrays is 1, which is the minimum possible.

    --- Example 2 ---
    Input: nums = [2,3,3,2], k = 3
    Output: 2
    Explanation:
    The optimal partition is [2], [3, 3], and [2].
        XOR of the first subarray is 2.
        XOR of the second subarray is 3 XOR 3 = 0.
        XOR of the third subarray is 2.
    The maximum XOR among the subarrays is 2, which is the minimum possible.

    --- Example 3 ---
    Input: nums = [1,1,2,3,1], k = 2
    Output: 0
    Explanation:
    The optimal partition is [1, 1] and [2, 3, 1].
        XOR of the first subarray is 1 XOR 1 = 0.
        XOR of the second subarray is 2 XOR 3 XOR 1 = 0.
    The maximum XOR among the subarrays is 0, which is the minimum possible.


    *** Constraints ***
    1 <= nums.length <= 250
    1 <= nums[i] <= 109
    1 <= k <= n

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Pretty standard Memoization-problem.

    The only thing that you needed here additionaly is to realize that you need
    a "xor_till_end" vector because the once you're left with k=1, you need to
    quickly have an answer instead of iterating through the remaining elements
    to determine the total XOR value.

*/

/* Time  Complexity: O(N^2 * k) */ // Since N=250, it's essentially O(k)
/* Space Complexity: O(N^2 * k) */ // Since N=250, it's essentially O(k)
class Solution {
private:
    int memo[251][251];
public:
    int minXor(vector<int>& nums, int k)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, 0x7f, sizeof(memo));

        vector<int> xor_till_end(N, 0);
        xor_till_end[N-1] = nums.back();

        for (int i = N-2; i >= 0; i--)
        {
            xor_till_end[i] = nums[i] ^ xor_till_end[i+1];
        }

        return solve(0, k, 0, nums, xor_till_end);
    }

private:
    int solve(int start, int k, int curr_xor, vector<int>& nums, vector<int>& xor_till_end)
    {
        const int N = nums.size();

        if (k == 1)
            return memo[start][k] = xor_till_end[start];

        if (memo[start][k] != 0x7f7f7f7f)
            return memo[start][k];

        int result = 0x7f7f7f7f;
        for (int i = start; i <= N - k; i++)
        {
            curr_xor ^= nums[i];
            int min_max = solve(i+1, k-1, 0, nums, xor_till_end);

            result = min(result, max(curr_xor, min_max));
        }

        return memo[start][k] = result;
    }
};
