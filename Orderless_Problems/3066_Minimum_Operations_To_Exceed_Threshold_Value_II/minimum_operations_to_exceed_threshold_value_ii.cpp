/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3066) Minimum Operations to Exceed Threshold Value II
    =====================================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums, and an integer k.

    In one operation, you will:

        Take the two smallest integers x and y in nums.
        Remove x and y from nums.
        Add min(x, y) * 2 + max(x, y) anywhere in the array.

    Note that you can only apply the described operation if nums contains at
    least two elements.

    Return the minimum number of operations needed so that all elements of the
    array are greater than or equal to k.

    ======================================================
    FUNCTION: int minOperations(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,11,10,1,3], k = 10
    Output: 2
    Explanation: In the first operation, we remove elements 1 and 2, then add
    1 * 2 + 2 to nums. nums becomes equal to [4, 11, 10, 3].
    In the second operation, we remove elements 3 and 4, then add 3 * 2 + 4 to
    nums. nums becomes equal to [10, 11, 10].
    At this stage, all the elements of nums are greater than or equal to 10 so
    we can stop.
    It can be shown that 2 is the minimum number of operations needed so that
    all elements of the array are greater than or equal to 10.


    --- Example 2 ---
    Input: nums = [1,1,2,4,9], k = 20
    Output: 4
    Explanation: After one operation, nums becomes equal to [2, 4, 9, 3].
    After two operations, nums becomes equal to [7, 4, 9].
    After three operations, nums becomes equal to [15, 9].
    After four operations, nums becomes equal to [33].
    At this stage, all the elements of nums are greater than 20 so we can stop.
    It can be shown that 4 is the minimum number of operations needed so that
    all elements of the array are greater than or equal to 20.


    *** Constraints ***
    2 <= nums.length <= 2 * 10^5
    1 <= nums[i] <= 10^9
    1 <= k <= 10^9
    The input is generated such that an answer always exists. That is, there
    exists some sequence of operations after which all elements of the array
    are greater than or equal to k.

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you know about the Heap data structure, that's it.

    Unfortunately, we cannot use: make_heap, pop_heap, push_heap
    functionalities from standard library because we can't change the type of
    vector "nums", which is "int", but we need "long" at least given these
    Constraints.

*/

/* Time  Beats:  5.57% */
/* Space Beats: 16.98% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minOperations(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = 0;

        priority_queue<long, vector<long>, greater<long>> min_heap;

        int less_than_k = 0;
        for (int i = 0; i < N; i++)
        {
            less_than_k += nums[i] < k ? 1 : 0;
            min_heap.push(nums[i]);
        }

        while (less_than_k > 0 && nums.size() > 1)
        {
            long one = min_heap.top();
            min_heap.pop();

            long two = min_heap.top();
            min_heap.pop();

            less_than_k -= one < k ? 1 : 0;
            less_than_k -= two < k ? 1 : 0;

            long new_elem = min(one, two) * 2 + max(one, two);
            min_heap.push(new_elem);

            less_than_k += new_elem < k ? 1 : 0;

            result++; // Count
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however we don't actually need to keep track of how many
    elements in "nums" are less than k. Also, this way of initializing Heap is
    much more elegant as well.

*/

/* Time  Beats: 74.27% */
/* Space Beats: 90.45% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Elegant {
public:
    int minOperations(vector<int>& nums, int k)
    {
        int result = 0;

        priority_queue<long,
                       vector<long>,
                       greater<long>> min_heap(nums.begin(), nums.end());

        while (min_heap.top() < k)
        {
            long x = min_heap.top();
            min_heap.pop();

            long y = min_heap.top();
            min_heap.pop();

            min_heap.push(x * 2 + y);
            result++;
        }

        return result;
    }
};
