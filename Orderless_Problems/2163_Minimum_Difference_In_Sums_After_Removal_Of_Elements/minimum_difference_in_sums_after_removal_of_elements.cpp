/*
    ============
    === HARD ===
    ============

    ==========================================================
    2163) Minimum Difference In Sums After Removal of Elements
    ==========================================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums consisting of 3 * n elements.

    You are allowed to remove any subsequence of elements of size exactly n
    from nums. The remaining 2 * n elements will be divided into two equal
    parts:

        + The first n elements belonging to the first part and their sum is
          sumfirst.

        + The next n elements belonging to the second part and their sum is
          sumsecond.

    The difference in sums of the two parts is denoted as sumfirst - sumsecond.

        For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
        Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.

    Return the minimum difference possible between the sums of the two parts
    after the removal of n elements.

    =========================================================
    FUNCTION: long long minimumDifference(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,2]
    Output: -1
    Explanation: Here, nums has 3 elements, so n = 1. 
    Thus we have to remove 1 element from nums and divide the array into two equal parts.
    - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
    - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
    - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
    The minimum difference between sums of the two parts is min(-1,1,2) = -1. 

    --- Example 2 ---
    Input: nums = [7,9,5,8,1,3]
    Output: 1
    Explanation: Here n = 2. So we must remove 2 elements and divide the remaining array into two parts containing two elements each.
    If we remove nums[2] = 5 and nums[3] = 8, the resultant array will be [7,9,1,3]. The difference in sums will be (7+9) - (1+3) = 12.
    To obtain the minimum difference, we should remove nums[1] = 9 and nums[4] = 1. The resultant array becomes [7,5,8,3].
    The difference in sums of the two parts is (7+5) - (8+3) = 1.
    It can be shown that it is not possible to obtain a difference smaller than 1.


    *** Constraints ***
    nums.length == 3 * n
    1 <= n <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.86% */
/* Space Beats: 95.95% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long minimumDifference(vector<int>& nums)
    {
        const int THREE_N = nums.size();
        const int N = THREE_N / 3;

        long long sum = 0;

        vector<long long> part_1(N + 1);
        priority_queue<int> left_max_heap;
        for (int i = 0; i < N; ++i)
        {
            sum += nums[i];
            left_max_heap.push(nums[i]);
        }

        part_1[0] = sum;
        for (int i = N; i < N * 2; i++)
        {
            sum += nums[i];
            left_max_heap.push(nums[i]);
            sum -= left_max_heap.top();
            left_max_heap.pop();

            part_1[i - (N - 1)] = sum;
        }

        long long part_2 = 0;
        priority_queue<int, vector<int>, greater<int>> right_min_heap;
        for (int i = N * 3 - 1; i >= N * 2; i--)
        {
            part_2 += nums[i];
            right_min_heap.push(nums[i]);
        }

        long long result = part_1[N] - part_2;
        for (int i = N * 2 - 1; i >= N; i--)
        {
            part_2 += nums[i];
            right_min_heap.push(nums[i]);

            part_2 -= right_min_heap.top();
            right_min_heap.pop();

            result = min(result, part_1[i - N] - part_2);
        }

        return result;
    }
};
