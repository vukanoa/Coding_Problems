/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    2104) Sum of Subarray Ranges
    ============================

    ============
    Description:
    ============

    You are given an integer array nums. The range of a subarray of nums is the
    difference between the largest and smallest element in the subarray.

    Return the sum of all subarray ranges of nums.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ---------------
    -- Follow Up --
    ---------------

    Could you find a solution with O(n) time complexity?


    ======================================================
    FUNCTION: long long subArrayRanges(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 4
    Explanation: The 6 subarrays of nums are the following:
    [1], range = largest - smallest = 1 - 1 = 0 
    [2], range = 2 - 2 = 0
    [3], range = 3 - 3 = 0
    [1,2], range = 2 - 1 = 1
    [2,3], range = 3 - 2 = 1
    [1,2,3], range = 3 - 1 = 2
    So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.

    --- Example 2 ---
    Input: nums = [1,3,3]
    Output: 4
    Explanation: The 6 subarrays of nums are the following:
    [1], range = largest - smallest = 1 - 1 = 0
    [3], range = 3 - 3 = 0
    [3], range = 3 - 3 = 0
    [1,3], range = 3 - 1 = 2
    [3,3], range = 3 - 3 = 0
    [1,3,3], range = 3 - 1 = 2
    So the sum of all ranges is 0 + 0 + 0 + 2 + 0 + 2 = 4.

    --- Example 3 ---
    Input: nums = [4,-2,-3,4,1]
    Output: 59
    Explanation: The sum of all subarray ranges of nums is 59.


    *** Constraints ***
    1 <= nums.length <= 1000
    -10^9 <= nums[i] <= 10^9

*/

#include <stack>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute Force.

*/

/* Time  Beats: 27.50% */
/* Space Beats: 97.43% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution_Brute_Force {
public:
    long long subArrayRanges(vector<int>& nums)
    {
        const int N = nums.size();

        long long result = 0;
        for (int i = 0; i < N-1; i++)
        {
            int largest = nums[i];
            int smallest= nums[i];

            for (int j = i+1; j < N; j++)
            {
                if (nums[j] > largest)
                    largest  = nums[j];

                if (nums[j] < smallest)
                    smallest = nums[j];

                result += largest - smallest;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  64.58% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Monotonicly_Increasing_Stack {
public:
    
    long long subArrayRanges(vector<int>& nums)
    {
        const int N = nums.size();
        long long sum = 0;

        stack<int> mono_incr_stack;
        vector<int> prev_min(N,-1);
        vector<int> prev_max(N,-1);
        vector<int> next_min(N, N);
        vector<int> next_max(N,N);
        
        for (int i = 0; i < N; i++)
        {
            while ( ! mono_incr_stack.empty() && nums[mono_incr_stack.top()] >= nums[i])
                mono_incr_stack.pop();

            if ( ! mono_incr_stack.empty())
                prev_min[i] = mono_incr_stack.top();

            mono_incr_stack.push(i);
        }

        while ( ! mono_incr_stack.empty())
            mono_incr_stack.pop();

        for (int i = N-1; i>= 0; i--)
        {
            while ( ! mono_incr_stack.empty() && nums[mono_incr_stack.top()] > nums[i])
                mono_incr_stack.pop();

            if ( ! mono_incr_stack.empty())
                next_min[i] = mono_incr_stack.top();

            mono_incr_stack.push(i);
        }
        
         for (int i = 0; i < N; i++)
         {
            while ( ! mono_incr_stack.empty() && nums[mono_incr_stack.top()] <= nums[i])
                mono_incr_stack.pop();

            if ( ! mono_incr_stack.empty())
                prev_max[i] = mono_incr_stack.top();

            mono_incr_stack.push(i);
         }

         while ( ! mono_incr_stack.empty())
             mono_incr_stack.pop();

         for (int i = N-1; i >= 0; i--)
         {
            while ( ! mono_incr_stack.empty() && nums[mono_incr_stack.top()] < nums[i])
                mono_incr_stack.pop();

            if ( ! mono_incr_stack.empty())
                next_max[i] = mono_incr_stack.top();

            mono_incr_stack.push(i);
         }
        
        for (int i = 0; i < N; i++)
        {
            long long left_min = i - prev_min[i];
            long long rightMin = next_min[i] - i;

            long long left_max  = i - prev_max[i];
            long long right_max = next_max[i] - i;

            sum += (left_max * right_max - left_min * rightMin) * nums[i];
        }

        return sum;
    }
};
