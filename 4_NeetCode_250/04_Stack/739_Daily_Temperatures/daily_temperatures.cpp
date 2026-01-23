/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    739) Daily Temperatures
    ===========================

    ============
    Description:
    ============

    Given an array of integers "temperatures" represents the daily
    temperatures, return an array "answer" such that answer[i] is the number of
    days you have to wait after the i-th day to get a warmer temperature. If
    there is no future day for which this is possible, keep answer[i] == 0
    instead.

    ===================================================================
    FUNCTION: vector<int> dailyTemperatures(vector<int>& temperatures);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
    Output: [1, 1, 4, 2, 1, 1, 0, 0]

    --- Example 2 ---
    Input:  temperatures = [30, 40, 50, 60],
    Output: [1, 1, 1, 0]

    --- Example 3 ---
    Input:  temperatures = [30, 60, 90]
    Output: [1, 1, 0]

    *** Constraints ***
    1 <= temperatures.length <= 10^5
    30 <= temperatures[i] <= 100

*/

#include <vector>
#include <stack>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The whole idea is - Monotonic Stack.
    Classic Monotonic Stack problem.

    Simulation of the Algorithm is self-explanatory

    Algorithm:
    Before start:

                   temp = [73, 74, 75, 71, 69, 72, 76, 73]
                 answer = [ 0,  0,  0,  0,  0,  0,  0,  0]
        mono_decr_stack = | Empty                        |

    1)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ------------- i
   |
   |                         0   1   2   3   4   5   6   7
   |    Before : answer  = [ 0,  0,  0,  0,  0,  0,  0,  0]
   |    After  : answer  = [ 0,  0,  0,  0,  0,  0,  0,  0]
   |
   |
   |    while( ! mono_decr_stack.empty() && temp[mono_decr_stack.top()] <= temp[i])
   |    {
   |        mono_decr_stack.pop();
   |    }
   |
   |    if ( ! mono_decr_stack.empty())
   |        answer[i] = mono_decr_stack.top() - i;
   |    // else
   |    //     answer[i] = 0;  // We don't need to do this because of the initialization of answer
   |
   |
   |    Before : mono_decr_stack = | Empty                        |
   |    After  : mono_decr_stack = | 0                            |
   |                                 ^
   |                                 |
   |_________________________________|



    2)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ----------------- i
   |
   |                         0   1   2   3   4   5   6   7
   |    Before : answer  = [ 0,  0,  0,  0,  0,  0,  0,  0]
   |    After  : answer  = [ 1,  0,  0,  0,  0,  0,  0,  0]
   |                      ^
   |
   |    while( ! mono_decr_stack.empty() && temp[mono_decr_stack.top()] <= temp[i])
   |    {
   |        mono_decr_stack.pop();
   |    }
   |
   |    if ( ! mono_decr_stack.empty())
   |        answer[i] = mono_decr_stack.top() - i;
   |    // else
   |    //     answer[i] = 0;  // We don't need to do this because of the initialization of answer
   |
   |
   |    Before : mono_decr_stack = | 0                            |
   |    After  : mono_decr_stack = | 1                            |
   |                                 ^
   |                                 |
   |_________________________________|




    3)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   --------------------- i
   |
   |                         0   1   2   3   4   5   6   7
   |    Before : answer  = [ 1,  0,  0,  0,  0,  0,  0,  0]
   |    After  : answer  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |                          ^
   |
   |    while( ! mono_decr_stack.empty() && temp[mono_decr_stack.top()] <= temp[i])
   |    {
   |        mono_decr_stack.pop();
   |    }
   |
   |    if ( ! mono_decr_stack.empty())
   |        answer[i] = mono_decr_stack.top() - i;
   |    // else
   |    //     answer[i] = 0;  // We don't need to do this because of the initialization of answer
   |
   |
   |    Before : mono_decr_stack = | 1                            |
   |    After  : mono_decr_stack = | 2                            |
   |                                 ^
   |                                 |
   |_________________________________|



    4)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ------------------------- i
   |
   |                         0   1   2   3   4   5   6   7
   |    Before : answer  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |    After  : answer  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |
   |
   |    while( ! mono_decr_stack.empty() && temp[mono_decr_stack.top()] <= temp[i])
   |    {
   |        mono_decr_stack.pop();
   |    }
   |
   |    if ( ! mono_decr_stack.empty())
   |        answer[i] = mono_decr_stack.top() - i;
   |    // else
   |    //     answer[i] = 0;  // We don't need to do this because of the initialization of answer
   |
   |
   |    Before : mono_decr_stack = | 2                            |
   |    After  : mono_decr_stack = | 2 | 3                        |
   |                                     ^
   |                                     |
   |_____________________________________|




    5)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ----------------------------- i
   |
   |                         0   1   2   3   4   5   6   7
   |    Before : answer  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |    After  : answer  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |
   |
   |    while( ! mono_decr_stack.empty() && temp[mono_decr_stack.top()] <= temp[i])
   |    {
   |        mono_decr_stack.pop();
   |    }
   |
   |    if ( ! mono_decr_stack.empty())
   |        answer[i] = mono_decr_stack.top() - i;
   |    // else
   |    //     answer[i] = 0;  // We don't need to do this because of the initialization of answer
   |
   |
   |    Before : mono_decr_stack = | 2 | 3                        |
   |    After  : mono_decr_stack = | 2 | 3 | 4                    |
   |                                         ^
   |                                         |
   |_________________________________________|



    6)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   --------------------------------- i
   |
   |                         0   1   2   3   4   5   6   7
   |    Before : answer  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |    After  : answer  = [ 1,  1,  0,  2,  1,  0,  0,  0]
   |                                  ^   ^
   |
   |    while( ! mono_decr_stack.empty() && temp[mono_decr_stack.top()] <= temp[i])
   |    {
   |        mono_decr_stack.pop();
   |    }
   |
   |    if ( ! mono_decr_stack.empty())
   |        answer[i] = mono_decr_stack.top() - i;
   |    // else
   |    //     answer[i] = 0;  // We don't need to do this because of the initialization of answer
   |
   |
   |    Before : mono_decr_stack = | 2 | 3 | 4                    |
   |    After  : mono_decr_stack = | 2 | 5                        |
   |                                     ^
   |                                     |
   |_____________________________________|




    7)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ------------------------------------- i
   |
   |                         0   1   2   3   4   5   6   7
   |    Before : answer  = [ 1,  1,  0,  2,  1,  0,  0,  0]
   |    After  : answer  = [ 1,  1,  4,  2,  1,  1,  0,  0]
   |                              ^           ^
   |
   |    while( ! mono_decr_stack.empty() && temp[mono_decr_stack.top()] <= temp[i])
   |    {
   |        mono_decr_stack.pop();
   |    }
   |
   |    if ( ! mono_decr_stack.empty())
   |        answer[i] = mono_decr_stack.top() - i;
   |    // else
   |    //     answer[i] = 0;  // We don't need to do this because of the initialization of answer
   |
   |
   |    Before : mono_decr_stack = | 2 | 5                        |
   |    After  : mono_decr_stack = | 6                            |
   |                                 ^
   |                                 |
   |_________________________________|



    8)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ----------------------------------------- i
   |
   |                         0   1   2   3   4   5   6   7
   |    After  : answer  = [ 1,  1,  4,  2,  1,  1,  0,  0]
   |    After  : answer  = [ 1,  1,  4,  2,  1,  1,  0,  0]
   |
   |
   |    while( ! mono_decr_stack.empty() && temp[mono_decr_stack.top()] <= temp[i])
   |    {
   |        mono_decr_stack.pop();
   |    }
   |
   |    if ( ! mono_decr_stack.empty())
   |        answer[i] = mono_decr_stack.top() - i;
   |    // else
   |    //     answer[i] = 0;  // We don't need to do this because of the initialization of answer
   |
   |
   |
   |    Before : mono_decr_stack = | 6                            |
   |    After  : mono_decr_stack = | 6 | 7                        |
   |                                     ^
   |                                     |
   |_____________________________________|

*/

/* Time  Beats: 61.21% */
/* Space Beats: 82.18% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures)
    {
        const int N = temperatures.size();
        vector<int> answer(N, 0);

        stack<int> mono_decr_stack; // Monotonically DECREASING Stack(of indices)
        mono_decr_stack.push(N-1);

        for (int i = N-2; i >= 0; i--)
        {
            while ( ! mono_decr_stack.empty() && temperatures[mono_decr_stack.top()] <= temperatures[i])
            {
                mono_decr_stack.pop();
            }

            if ( ! mono_decr_stack.empty())
                answer[i] = mono_decr_stack.top() - i;

            mono_decr_stack.push(i);
        }

        return answer;
    }
};
