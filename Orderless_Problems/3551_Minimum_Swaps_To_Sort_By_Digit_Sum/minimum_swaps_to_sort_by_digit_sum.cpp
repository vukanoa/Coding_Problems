/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    3551) Minimum Swaps to Sort by Digit Sum
    ========================================

    ============
    Description:
    ============

    You are given an array nums of distinct positive integers. You need to sort
    the array in increasing order based on the sum of the digits of each number

    If two numbers have the same digit sum, the smaller number appears first in
    the sorted order.

    Return the minimum number of swaps required to rearrange nums into this
    sorted order.

    A swap is defined as exchanging the values at two distinct positions in the
    array.

    ==========================================
    FUNCTION: int minSwaps(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [37,100]
    Output: 1
    Explanation:
        Compute the digit sum for each integer: [3 + 7 = 10, 1 + 0 + 0 = 1] → [10, 1]
        Sort the integers based on digit sum: [100, 37]. Swap 37 with 100 to obtain the sorted order.
        Thus, the minimum number of swaps required to rearrange nums is 1.


    --- Example 2 ---
    Input: nums = [22,14,33,7]
    Output: 0
    Explanation:
        Compute the digit sum for each integer: [2 + 2 = 4, 1 + 4 = 5, 3 + 3 = 6, 7 = 7] → [4, 5, 6, 7]
        Sort the integers based on digit sum: [22, 14, 33, 7]. The array is already sorted.
        Thus, the minimum number of swaps required to rearrange nums is 0.


    --- Example 3 ---
    Input: nums = [18,43,34,16]
    Output: 2
    Explanation:
        Compute the digit sum for each integer: [1 + 8 = 9, 4 + 3 = 7, 3 + 4 = 7, 1 + 6 = 7] → [9, 7, 7, 7]
        Sort the integers based on digit sum: [16, 34, 43, 18]. Swap 18 with 16, and swap 43 with 34 to obtain the sorted order.
        Thus, the minimum number of swaps required to rearrange nums is 2.



    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    nums consists of distinct positive integers.

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 32.23% */
/* Space Beats: 47.35% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minSwaps(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        vector<int> should = nums;

        sort(should.begin(), should.end(), [&](int a, int b) {
            int sum_a = find_sum(a);
            int sum_b = find_sum(b);

            if (sum_a == sum_b)
                return a < b;

            return sum_a < sum_b;
        });

        unordered_map<int, int> num_to_idx;
        for (int idx = 0; idx < N; idx++)
            num_to_idx[nums[idx]] = idx;

        vector<bool> visited(N, false);

        for (int i = 0; i < N; ++i)
        {
            if (visited[i] || should[i] == nums[i])
                continue;

            int cycle_size = 0;
            int idx = i;

            while ( ! visited[idx])
            {
                visited[idx] = true;

                idx = num_to_idx[should[idx]];
                cycle_size++;
            }

            if (cycle_size >= 1)
                result += (cycle_size - 1);
        }

        return result;
    }

private:
    int find_sum(int n)
    {
        int sum = 0;
        while (n > 0)
        {
            sum += n % 10;
            n /= 10;
        }

        return sum;
    }
};
