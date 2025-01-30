/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3259) Maximum Energy Boost From Two Drinks
    ==========================================

    ============
    Description:
    ============

    You are given two integer arrays energyDrinkA and energyDrinkB of the same
    length n by a futuristic sports scientist. These arrays represent the
    energy boosts per hour provided by two different energy drinks, A and B,
    respectively.

    You want to maximize your total energy boost by drinking one energy drink
    per hour. However, if you want to switch from consuming one energy drink to
    the other, you need to wait for one hour to cleanse your system (meaning
    you won't get any energy boost in that hour).

    Return the maximum total energy boost you can gain in the next n hours.

    =====
    Note: that you can start consuming either of the two energy drinks.
    =====

    ===============================
    FUNCTION: long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: energyDrinkA = [1,3,1], energyDrinkB = [3,1,1]
    Output: 5
    Explanation:
    To gain an energy boost of 5, drink only the energy drink A (or only B).

    --- Example 2 ---
    Input: energyDrinkA = [4,1,1], energyDrinkB = [1,1,3]
    Output: 7
    Explanation:
    To gain an energy boost of 7:
        Drink the energy drink A for the first hour.
        Switch to the energy drink B and we lose the energy boost of the second hour.
        Gain the energy boost of the drink B in the third hour.


    *** Constraints ***
    n == energyDrinkA.length == energyDrinkB.length
    3 <= n <= 10^5
    1 <= energyDrinkA[i], energyDrinkB[i] <= 10^5

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This one is similar to two LeetCode problem:

        + 740 Delete and Earn
        + 198 House Robber

    However, instead of only one array, this one has two. Instead of:

        + skipping the current one and and taking the further one in the same
          array

        you can:

        + skip the current one and take the further one from the other
          energyDrink array.

    Make sure you know how to do these two problems before you try this one.

*/

/* Time  Beats: 75.14% */
/* Space Beats: 70.34% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB)
    {
        const int N = energyDrinkA.size();
        long long result = 0;

        vector<long long> dpA(N, 0);
        vector<long long> dpB(N, 0);

        dpA[N-1] = energyDrinkA[N-1];
        dpB[N-1] = energyDrinkB[N-1];

        for (int i = N-2; i >= 0; i--)
        {
            dpA[i] = max(energyDrinkA[i] + dpA[i+1], dpB[i+1]);
            dpB[i] = max(energyDrinkB[i] + dpB[i+1], dpA[i+1]);
        }

        return max(dpA[0], dpB[0]);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    As in two mentioned problems above, we can optimize Space Efficiency here
    as well, in the exact same way - by using only two additional variables.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.48% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB)
    {
        const int N = energyDrinkA.size();
        long long result = 0;

        long long dpA = energyDrinkA[N-1];
        long long dpB = energyDrinkB[N-1];

        for (int i = N-2; i >= 0; i--)
        {
            long long curr_A = max(energyDrinkA[i] + dpA, dpB);
            long long curr_B = max(energyDrinkB[i] + dpB, dpA);

            dpA = curr_A;
            dpB = curr_B;
        }

        return max(dpA, dpB);
    }
};
