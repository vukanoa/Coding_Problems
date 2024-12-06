#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    2554) Maximum Number of Integers to Choose From a Range
    =======================================================

    ============
    Description:
    ============

    You are given an integer array banned and two integers n and maxSum. You
    are choosing some number of integers following the below rules:

        + The chosen integers have to be in the range [1, n].

        + Each integer can be chosen at most once.

        + The chosen integers should not be in the array banned.

        + The sum of the chosen integers should not exceed maxSum.

    Return the maximum number of integers you can choose following the
    mentioned rules.

    ===============================================================
    FUNCTION: int maxCount(vector<int>& banned, int n, int maxSum);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: banned = [1,6,5], n = 5, maxSum = 6
    Output: 2
    Explanation: You can choose the integers 2 and 4. 2 and 4 are from the
                 range [1, 5], both did not appear in banned, and their sum is
                 6, which did not exceed maxSum.

    --- Example 2 ---
    Input: banned = [1,2,3,4,5,6,7], n = 8, maxSum = 1
    Output: 0
    Explanation: You cannot choose any integer while following the mentioned
                 conditions.

    --- Example 3 ---
    Input: banned = [11], n = 7, maxSum = 50 Output: 7 Explanation: You can
    choose the integers 1, 2, 3, 4, 5, 6, and 7. They are from the range [1,
    7], all did not appear in banned, and their sum is 28, which did not exceed
    maxSum.

    *** Constraints ***
    1 <= banned.length <= 10^4
    1 <= banned[i], n <= 10^4
    1 <= maxSum <= 10^9

*/

using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Since we are only allowed to choose from [1..n], we only need to be careful
    about not choosing a "banned" integers.

    Therefore, the easiest way to check if some integers is banned is by using
    a HashSet. To build one, we need O(n) time, but after that every check is
    O(1).

    Also, it is very important for us to start checking from the lower integers
    because we have an upper bound "maxSum".

    For example:
        banned = [1,6],   n = 5,    maxSum = 9

        If we started from the back(i.e. n) we would've taken: 5 and 4

        However, that is not the maximum number of integers we can choose from
        this range given this MaxSum. Instead, we could choose: (2, 3, 4)

        Therefore, it is crucial to start from lower integers.


    To construct HashSet from "banned" vector, it takes us O(M) time.
    To go through all N elements it takes us O(N) time.

    Overall Time  Complexity is: O(M + N)
    Overall Space Complexity is: O(M) since we've used a HashSet of M size.

*/

/* Time  Beats: 68.32% */
/* Space Beats: 67.05% */

/* Time  Complexity: O(M + N) */  // M <==> banned.size(), N <==> n
/* Space Complexity: O(M)     */
class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum)
    {
        unordered_set<int> uset_banned(banned.begin(), banned.end()); // O(n)

        int result = 0;
        int curr_sum = 0;
        for (int i = 1; i <= n; i++)
        {
            if (uset_banned.find(i) != uset_banned.end()) // If it DOES exist in "banned" vector
                continue;

            if (curr_sum + i > maxSum)
            {
                return result;
            }
            else
            {
                curr_sum += i;
                result++; // Increment number of chosen integers
            }
        }

        return result;
    }
};
