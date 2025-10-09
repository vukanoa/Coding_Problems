/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    3494) Find Minimum Amount of Time to Brew Potions
    =================================================

    ============
    Description:
    ============

    You are given two integer arrays, skill and mana, of length n and m,
    respectively.

    In a laboratory, n wizards must brew m potions in order. Each potion has a
    mana capacity mana[j] and must pass through all the wizards sequentially to
    be brewed properly. The time taken by the ith wizard on the jth potion is
    timeij = skill[i] * mana[j].

    Since the brewing process is delicate, a potion must be passed to the next
    wizard immediately after the current wizard completes their work. This
    means the timing must be synchronized so that each wizard begins working on
    a potion exactly when it arrives.

    Return the minimum amount of time required for the potions to be brewed
    properly.

    ===================================================================
    FUNCTION: long long minTime(vector<int>& skill, vector<int>& mana);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: skill = [1,5,2,4], mana = [5,1,4,2]
    Output: 110

    --- Example 2 ---
    Input: skill = [1,1,1], mana = [1,1,1]
    Output: 5

    --- Example 3 ---
    Input: skill = [1,2,3,4], mana = [1,2]
    Output: 21


    *** Constraints ***
    n == skill.length
    m == mana.length
    1 <= n, m <= 5000
    1 <= mana[i], skill[i] <= 5000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 49.23% */
/* Space Beats: 88.72% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N)     */
class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana)
    {
        const int N = skill.size();
        const int M = mana.size();

        vector<long long> times(N, 0);

        for (int j = 0; j < M; j++)
        {
            long long curr_time = 0;

            for (int i = 0; i < N; i++)
            {
                curr_time = max(curr_time, times[i]) + skill[i] * mana[j];
            }

            times[N - 1] = curr_time;
            for (int i = N - 2; i >= 0; i--)
            {
                times[i] = times[i + 1] - skill[i + 1] * mana[j];
            }
        }

        return times[N - 1];
    }
};
