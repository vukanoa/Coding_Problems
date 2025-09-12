/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2611) Mice and Cheese
    ===========================

    ============
    Description:
    ============

    There are two mice and n different types of cheese, each type of cheese
    should be eaten by exactly one mouse.

    A point of the cheese with index i (0-indexed) is:

        + reward1[i] if the first mouse eats it.
        + reward2[i] if the second mouse eats it.

    You are given a positive integer array reward1, a positive integer array
    reward2, and a non-negative integer k.

    Return the maximum points the mice can achieve if the first mouse eats
    exactly k types of cheese.

    ===============================================================================
    FUNCTION: int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: reward1 = [1,1,3,4], reward2 = [4,4,1,1], k = 2
    Output: 15
    Explanation: In this example, the first mouse eats the 2nd (0-indexed) and
    the 3rd types of cheese, and the second mouse eats the 0th and the 1st
    types of cheese.
    The total points are 4 + 4 + 3 + 4 = 15.
    It can be proven that 15 is the maximum total points that the mice can
    achieve.

    --- Example 2 ---
    Input: reward1 = [1,1], reward2 = [1,1], k = 2
    Output: 2
    Explanation: In this example, the first mouse eats the 0th (0-indexed) and
    1st types of cheese, and the second mouse does not eat any cheese.
    The total points are 1 + 1 = 2.
    It can be proven that 2 is the maximum total points that the mice can
    achieve.


    *** Constraints ***
    1 <= n == reward1.length == reward2.length <= 10^5
    1 <= reward1[i], reward2[i] <= 1000
    0 <= k <= n

*/

#include <numeric>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Essentially, for the mouse number 1, let him take the first 'k' rewards
    that have the highest DIFFERENCE between rewards.

    Why?

    Because we'll take EVERY TYPE of reward anyway, so let's minimize the loss.
    That's the entire "trick" here.

*/

/* Time  Beats: 5.13% */
/* Space Beats: 5.13% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k)
    {
        const int N = reward1.size();
        int result = 0;

        if (k == 0)
            return accumulate(reward2.begin(), reward2.end(), 0);

        priority_queue<vector<int>> max_heap;
        for (int i = 0; i < N; i++)
            max_heap.push( {reward1[i] - reward2[i], reward1[i], reward2[i]} );

        while ( ! max_heap.empty())
        {
            auto top = max_heap.top();
            max_heap.pop();

            if (k > 0)
            {
                result += top[1]; // reward1
                k--;
            }
            else
            {
                result += top[2]; // reward2
            }
        }

        return result;
    }
};
