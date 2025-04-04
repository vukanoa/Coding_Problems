/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3147) Taking Maximum Energy From the Mystic Dungeon
    ===================================================

    ============
    Description:
    ============

    In a mystic dungeon, n magicians are standing in a line. Each magician has
    an attribute that gives you energy. Some magicians can give you negative
    energy, which means taking energy from you.

    You have been cursed in such a way that after absorbing energy from
    magician i, you will be instantly transported to magician (i + k). This
    process will be repeated until you reach the magician where (i + k) does
    not exist.

    In other words, you will choose a starting point and then teleport with k
    jumps until you reach the end of the magicians' sequence, absorbing all the
    energy during the journey.

    You are given an array energy and an integer k. Return the maximum possible
    energy you can gain.

    =====
    Note: that when you are reach a magician, you must take energy from them,
          whether it is negative or positive energy.
    =====

    ========================================================
    FUNCTION: int maximumEnergy(vector<int>& energy, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: energy = [5,2,-10,-5,1], k = 3
    Output: 3
    Explanation: We can gain a total energy of 3 by starting from magician 1 absorbing 2 + 1 = 3.

    --- Example 2 ---
    Input: energy = [-2,-3,-1], k = 2
    Output: -1
    Explanation: We can gain a total energy of -1 by starting from magician 2.


    *** Constraints ***
    1 <= energy.length <= 10^5
    -1000 <= energy[i] <= 1000
    1 <= k <= energy.length - 1

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 89.74% */
/* Space Beats: 27.78% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k)
    {
        const int N = energy.size();
        int result = 0;

        vector<int> gains(N, 0);
        for (int i = N-1; i >= N-k; i--)
            gains[i] = energy[i];

        for (int i = N-k-1; i >= 0; i--)
            gains[i] = energy[i] + gains[i + k];

        return *max_element(gains.begin(), gains.end());
    }
};
