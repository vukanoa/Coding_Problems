/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1124) Longest Well-Performing Interval
    ======================================

    ============
    Description:
    ============

    We are given hours, a list of the number of hours worked per day for a
    given employee.

    A day is considered to be a tiring day if and only if the number of hours
    worked is (strictly) greater than 8.

    A well-performing interval is an interval of days for which the number of
    tiring days is strictly larger than the number of non-tiring days.

    Return the length of the longest well-performing interval.

    =============================================
    FUNCTION: int longestWPI(vector<int>& hours);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: hours = [9,9,6,0,6,6,9]
    Output: 3
    Explanation: The longest well-performing interval is [9,9,6].

    --- Example 2 ---
    Input: hours = [6,6,6]
    Output: 0


    *** Constraints ***
    1 <= hours.length <= 10^4
    0 <= hours[i] <= 16

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

/* Time  Beats: 100.00% */
/* Space Beats:  77.42% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int longestWPI(vector<int>& hours)
    {
        int N = hours.size();
        int result = 0;

        vector<int> prefix_sum(N + 1);
        prefix_sum[0] = 0;

        for (int i = 0; i < N; i++)
            prefix_sum[i + 1] = prefix_sum[i] + (hours[i] > 8 ? 1 : -1);

        stack<int> mono_decr_stack;

        for (int i = 0; i <= N; i++)
        {
            if (mono_decr_stack.empty() || prefix_sum[mono_decr_stack.top()] > prefix_sum[i])
                mono_decr_stack.push(i);
        }

        for (int j = N; j >= 0; j--)
        {
            while ( ! mono_decr_stack.empty() && prefix_sum[mono_decr_stack.top()] < prefix_sum[j])
            {
                result = max(result, j - mono_decr_stack.top());
                mono_decr_stack.pop();
            }
        }

        return result;
    }
};
