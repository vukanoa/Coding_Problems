#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================================
    1509) Minimum Difference Between Largest and Smallest Value in Three Moves
    ==========================================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    In one move, you can choose one element of nums and change it to any value.

    Return the minimum difference between the largest and smallest value of
    nums after performing at most three moves.

    ===============================================
    FUNCTION: int minDifference(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,3,2,4]
    Output: 0
    Explanation: We can make at most 3 moves.
    In the first move, change 2 to 3. nums becomes [5,3,3,4].
    In the second move, change 4 to 3. nums becomes [5,3,3,3].
    In the third move, change 5 to 3. nums becomes [3,3,3,3].
    After performing 3 moves, the difference between the minimum and maximum is
    3 - 3 = 0.


    --- Example 2 ---
    Input: nums = [1,5,0,10,14]
    Output: 1
    Explanation: We can make at most 3 moves.
    In the first move, change 5 to 0. nums becomes [1,0,0,10,14].
    In the second move, change 10 to 0. nums becomes [1,0,0,0,14].
    In the third move, change 14 to 1. nums becomes [1,0,0,0,1].
    After performing 3 moves, the difference between the minimum and maximum is
    1 - 0 = 1.
    It can be shown that there is no way to make the difference 0 in 3 moves.


    --- Example 3 ---
    Input: nums = [3,100,20]
    Output: 0
    Explanation: We can make at most 3 moves.
    In the first move, change 100 to 7. nums becomes [3,7,20].
    In the second move, change 20 to 7. nums becomes [3,7,7].
    In the third move, change 3 to 7. nums becomes [7,7,7].
    After performing 3 moves, the difference between the minimum and maximum is
    7 - 7 = 0.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    There are only 4 possible scenarios that can happen once we know what is:
        1. Smallest value
        2. Second smallest value
        3. Second largest value
        4. Largest value

    And to know these 4 things in O(1), we can sort.

    (Although, we can, indeed, just traverse it multiple times, since that'd
    still be constant since we won't traverse is more than 3*4 times. That
    Solution is down below).

*/

/* Time  Beats: 91.16% */
/* Space Beats: 97.48% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depends on the sort
class Solution {
public:
    int minDifference(std::vector<int>& nums)
    {
        if(nums.size() <= 4)
            return 0;

        std::sort(nums.begin(), nums.end());

        const int n = nums.size();
        int res1 = std::abs(nums[0] - nums[n-4]);
        int res2 = std::abs(nums[3] - nums[n-1]);
        int res3 = std::abs(nums[1] - nums[n-3]);
        int res4 = std::abs(nums[2] - nums[n-2]);

        return std::min(std::min(res1, res2), std::min(res3, res4));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The same as above, however, implemented using a for loop, instead of
    writing all 4 cases explicitly.

*/

/* Time  Beats: 80.50% */
/* Space Beats: 97.48% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_For_Loop {
public:
    int minDifference(std::vector<int>& nums)
    {
        if(nums.size() <= 4)
            return 0;

        std::sort(nums.begin(), nums.end());
        int min = INT_MAX;

        int n = nums.size();
        for(int i = 0; i < 4; i++)
        {
            // We need to test 4 cases.
            int diff = nums[n - 4 + i] - nums[i];

            min = std::min(min, diff);
        }

        return min;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one runs in O(n) time since log4 is a Constant, therefore:
        O(n * log4) becomes just O(n).

    We could've also iterate each of the three times to find all 4 values.
    That would also be O(n), however, using Heap is a bit more efficient.
    Not much, though.

*/

/* Time  Beats: 99.30% */
/* Space Beats: 63.96% */

/* Time  Complexity: O(n)    */ // O(n * log4) -> O(n)
/* Space Complexity: O(n) */
class Solution_O_of_N {
public:
    int minDifference(std::vector<int>& nums)
    {
        if(nums.size() <= 4)
            return 0;

        // Top 4 smallest elements -> max_heap
        // Top 4 biggest  elements -> min_heap

        std::priority_queue<int, std::vector<int>> max_heap;
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

        for(int i = 0; i < 4; i++)
        {
            max_heap.push(nums[i]);
            min_heap.push(nums[i]);
        }

        for(int i = 4; i < nums.size(); i++)
        {
            if(max_heap.top() > nums[i])
            {
               max_heap.pop();
               max_heap.push(nums[i]);
            }

            if(min_heap.top() < nums[i])
            {
               min_heap.pop();
               min_heap.push(nums[i]);
            }
        }

        // Get small_4 and large_4
        std::vector<int> small_4(4);
        std::vector<int> large_4(4);

        for(int i = 0; i < 4; i++)
        {
            small_4[i] = max_heap.top();
            large_4[i] = min_heap.top();

            max_heap.pop();
            min_heap.pop();
        }

        int min = INT_MAX;

        for(int i = 0; i < 4; i++)
        {
            int small_value = small_4[3-i];
            int large_value = large_4[i];

            int diff = large_value - small_value;

            min = std::min(min, diff);
        }

        return min;
    }
};
