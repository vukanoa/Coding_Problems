#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2300) Successful Pairs of Spells and Potions
    ============================================

    ============
    Description:
    ============

    You are given two positive integer arrays spells and potions, of length n
    and m respectively, where spells[i] represents the strength of the ith
    spell and potions[j] represents the strength of the jth potion.

    You are also given an integer success. A spell and potion pair is
    considered successful if the product of their strengths is at least
    success.

    Return an integer array pairs of length n where pairs[i] is the number of
    potions that will form a successful pair with the ith spell.

    ===================================================================================================
    FUNCTION: vector<int> successfulPairs(vector<int>& spells, vector<int>& points, long long success);
    ===================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
    Output: [4,0,3]
    Explanation:
    - 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
    - 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
    - 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
    Thus, [4,0,3] is returned.


    --- Example 2 ---
    Input: spells = [3,1,2], potions = [8,5,8], success = 16
    Output: [2,0,2]
    Explanation:
    - 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
    - 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful.
    - 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful.
    Thus, [2,0,2] is returned.



    *** Constraints ***
    n == spells.length
    m == potions.length
    1 <= n, m <= 10^5
    1 <= spells[i], potions[i] <= 10^5
    1 <= success <= 10^10

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 81.66% */
/* Space Beats: 25.73% */

/* Time  Complexity: O(N * logM + M * logM) */
/* Space Complexity: O(max(N, M)) */
class Solution_1 {
public:
    std::vector<int> successfulPairs(std::vector<int>& spells, std::vector<int>& potions, long long success)
    {
        const int N = spells.size();
        const int M = potions.size();
        std::vector<int> pairs;

        std::sort(potions.begin(), potions.end());

        for (int i = 0; i < N; i++)
        {
            int left  = 0;
            int right = M-1;

            while (left < right)
            {
                unsigned long long mid = left + (right - left) / 2;

                if (static_cast<unsigned long long>(spells[i]) * static_cast<unsigned long long>(potions[mid]) >= success)
                    right = mid  - 1;
                else
                    left  = mid + 1;
            }

            if (static_cast<unsigned long long>(spells[i]) * static_cast<unsigned long long>(potions[left]) >= success)
                pairs.push_back(M - left);
            else
                pairs.push_back(M - (left + 1));
        }

        return pairs;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a more clean way of implementing the same IDEA.

*/

/* Time  Beats: 83.34% */
/* Space Beats: 58.94% */

/* Time  Complexity: O(N * logM + M * logM) */
/* Space Complexity: O(max(N, M)) */
class Solution_2 {
public:
    std::vector<int> successfulPairs(std::vector<int>& spells, std::vector<int>& potions, long long success)
    {
        const int N = spells.size();
        const int M = potions.size();
        std::vector<int> pairs;

        std::sort(potions.begin(), potions.end());

        for (int& spell : spells)
        {
            int left  = 0;
            int right = M - 1;

            while (left <= right)
            {
                int mid = left + (right - left) / 2;

                if (static_cast<unsigned long long>(spell) * static_cast<unsigned long long>(potions[mid]) >= success)
                    right = mid - 1;
                else
                    left  = mid + 1;
            }

            pairs.push_back(M - left);
        }

        return pairs;
    }
};
