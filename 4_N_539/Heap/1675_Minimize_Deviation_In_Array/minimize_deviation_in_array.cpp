#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    1675) Minimize Deviation In Array
    =================================

    ============
    Description:
    ============

    You are given an array nums of n positive integers.

    You can perform two types of operations on any element of the array any
    number of times:

        If the element is even, divide it by 2.  For example, if the array is
        [1,2,3,4], then you can do this operation on the last element, and the
        array will be [1,2,3,2].  If the element is odd, multiply it by 2.  For
        example, if the array is [1,2,3,4], then you can do this operation on
        the first element, and the array will be [2,2,3,4].

    The deviation of the array is the maximum difference between any two
    elements in the array.

    Return the minimum deviation the array can have after performing some
    number of operations.

    ==================================================
    FUNCTION: int minimumDeviation(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: 1
    Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2],
                 then the deviation will be 3 - 2 = 1.


    --- Example 2 ---
    Input: nums = [4,1,5,20,3]
    Output: 3
    Explanation: You can transform the array after two operations to
                 [4,2,5,5,3], then the deviation will be 5 - 2 = 3.


    --- Example 3 ---
    Input: nums = [2,10,8]
    Output: 3


    *** Constraints ***
    n == nums.length
    2 <= n <= 5 * 10^4
    1 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 25.55% */
/* Space Beats: 20.80% */

/* Time  Complexity: O(N + log(M) * log(N)) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minimumDeviation(std::vector<int> nums)
    {
        std::priority_queue<int, std::vector<int>> max_heap;
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] & 1)
            {
                max_heap.push(nums[i] * 2);
                min_heap.push(nums[i] * 2);
            }
            else
            {
                max_heap.push(nums[i]);
                min_heap.push(nums[i]);
            }
        }

        int max_val = max_heap.top();
        max_heap.pop();

        int min_val = min_heap.top(); // We DON't pop it

        int min_deviation = max_val - min_val;

        while (max_val % 2 == 0) // While max_val is Even
        {
            max_val /= 2;

            max_heap.push(max_val);
            min_heap.push(max_val);

            max_val = max_heap.top();
            max_heap.pop();

            min_val = min_heap.top(); // We DON't pop it

            min_deviation = std::min(min_deviation, max_val - min_val);
        }

        return min_deviation;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.90% */
/* Space Beats: 84.17% */

/* Time  Complexity: O(N * logN + logM * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minimumDeviation(vector<int>& nums)
    {
        std::priority_queue<int> max_heap;
        int min_val = INT_MAX;

        for (int num : nums)
        {
            if (num & 1)
                num *= 2;

            max_heap.push(num);
            min_val = std::min(min_val, num);
        }

        int min_deviation = INT_MAX;
        while (true)
        {
            int max_val = max_heap.top();
            max_heap.pop();

            min_deviation = std::min(min_deviation, max_val - min_val);

            /*
                The reason we need to break out of the loop when the maximum
                value is odd is that we have already transformed all odd
                numbers in the input array to even numbers by multiplying them
                by 2. Therefore, if the maximum value in the priority queue is
                odd, it must have been obtained by performing the "multiply by
                2" operation on some even number. We cannot undo this operation
                by performing the "divide by 2" operation, so we cannot reduce
                the maximum value any further.
            */
            if (max_val & 1)
                break;

            max_val /= 2;

            min_val = std::min(min_val, max_val);
            max_heap.push(max_val);
        }

        return min_deviation;
    }
};
