/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2866) Beautiful Towers II
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed array maxHeights of n integers.

    You are tasked with building n towers in the coordinate line. The ith tower
    is built at coordinate i and has a height of heights[i].

    A configuration of towers is beautiful if the following conditions hold:

        + 1 <= heights[i] <= maxHeights[i]
        + heights is a mountain array.

    Array heights is a mountain if there exists an index i such that:

        + For all 0 < j <= i, heights[j - 1] <= heights[j]
        + For all i <= k < n - 1, heights[k + 1] <= heights[k]

    Return the maximum possible sum of heights of a beautiful configuration of
    towers.

    =================================================================
    FUNCTION: long long maximumSumOfHeights(vector<int>& maxHeights);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: maxHeights = [5,3,4,1,1]
    Output: 13
    Explanation: One beautiful configuration with a maximum sum is heights =
                 [5,3,3,1,1]. This configuration is beautiful since:
    - 1 <= heights[i] <= maxHeights[i]  
    - heights is a mountain of peak i = 0.
    It can be shown that there exists no other beautiful configuration with a
    sum of heights greater than 13.

    --- Example 2 ---
    Input: maxHeights = [6,5,3,9,2,7]
    Output: 22
    Explanation: One beautiful configuration with a maximum sum is heights =
    [3,3,3,9,2,2]. This configuration is beautiful since:
    - 1 <= heights[i] <= maxHeights[i]
    - heights is a mountain of peak i = 3.
    It can be shown that there exists no other beautiful configuration with a
    sum of heights greater than 22.

    --- Example 3 ---
    Input: maxHeights = [3,2,5,5,2,3]
    Output: 18
    Explanation: One beautiful configuration with a maximum sum is heights =
    [2,2,5,5,2,2]. This configuration is beautiful since:
    - 1 <= heights[i] <= maxHeights[i]
    - heights is a mountain of peak i = 2. 
    Note that, for this configuration, i = 3 can also be considered a peak.
    It can be shown that there exists no other beautiful configuration with a
    sum of heights greater than 18.


    *** Constraints ***
    1 <= n == maxHeights.length <= 10^5
    1 <= maxHeights[i] <= 10^9

*/

#include <stack>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 35.78% */
/* Space Beats: 20.10% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long maximumSumOfHeights(vector<int>& maxHeights) 
    {
        const int N = maxHeights.size();

        //////////////////////////////////////////////////////
        /// Previous smaller element using Monotonic Stack ///
        //////////////////////////////////////////////////////
        stack<int>  mono_stack;          // Monotonically INCREASING Stack
        vector<int> prev_smaller(N, -1); // Stores indices of the closest smaller element to the left

        for (int i = 0; i < N; i++)
        {
            while ( ! mono_stack.empty() && maxHeights[mono_stack.top()] >= maxHeights[i])
                mono_stack.pop(); 
            
            if ( ! mono_stack.empty())
                prev_smaller[i] = mono_stack.top();

            mono_stack.push(i);
        }


        //////////////////////////////////////////////////
        /// Next smaller element using Monotonic Stack ///
        //////////////////////////////////////////////////
        mono_stack = stack<int>();       // Monotinicaly INCREASING stack
        vector<int> next_smaller(N, N);  // Stores indices of the closest smaller element to the right

        for (int i = N-1; i >= 0; i--)
        {
            while ( ! mono_stack.empty() && maxHeights[mono_stack.top()] >= maxHeights[i])
                mono_stack.pop();

            if ( ! mono_stack.empty())
                next_smaller[i] = mono_stack.top();

            mono_stack.push(i);
        }


        ////////////////
        /// Left Sum ///
        ////////////////
        vector<long long> prefix_sum(N, 0LL);
        prefix_sum[0] = maxHeights[0];
        for (int i = 1; i < N; i++)
        {
            int idx_of_prev_smaller = prev_smaller[i];
            int equal_count         = i - (idx_of_prev_smaller + 1) + 1; 

            // All elements, INCLUSIVELY, in [(prev_smaller_idx + 1) ... i] will be set to maxHeights[i]
            // And there are:
            //
            //     i - (idx_of_prev_smaller + 1) + 1
            //
            // of them. We'll call it "equal_count"
            
            prefix_sum[i] = 1LL * equal_count * maxHeights[i];
            
            if (idx_of_prev_smaller != -1)
                prefix_sum[i] += prefix_sum[idx_of_prev_smaller];
        }


        /////////////////
        /// Right Sum ///
        /////////////////
        vector<long long> suffix_sum(N, 0LL);
        suffix_sum[N-1] = maxHeights[N-1];

        for (int i = N-2; i >= 0; i--)
        {
            int idx_of_next_smaller = next_smaller[i];
            int equal_count         = (idx_of_next_smaller - 1) - i + 1;

            // All elements, INCLUSIVELY, in [i ... (next_smaller_idx - 1)] will be set to maxHeights[i]
            // And there are:
            //
            //    (idx_of_next_smaller - 1) - i + 1 
            //
            // of them. We'll call it "equal_count"
            
            suffix_sum[i] = 1LL * equal_count * maxHeights[i];
            
            if (idx_of_next_smaller != N)
                suffix_sum[i] += suffix_sum[idx_of_next_smaller]; 
        }


        //////////////////
        /// get Result ///
        //////////////////
        long long result = 0LL;
        for (int i = 0; i < N; i++)
        {
            long long total_sum = prefix_sum[i] + suffix_sum[i] - maxHeights[i];

            result = max(result, total_sum);
        }

        return result;
    }
};
