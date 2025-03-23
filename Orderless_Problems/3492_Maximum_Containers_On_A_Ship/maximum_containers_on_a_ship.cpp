/*
    ============
    === EASY ===
    ============

    ==================================
    3492) Maximum Containers on a Ship
    ==================================

    ============
    Description:
    ============

    You are given a positive integer n representing an n x n cargo deck on a
    ship. Each cell on the deck can hold one container with a weight of exactly
    w.

    However, the total weight of all containers, if loaded onto the deck, must
    not exceed the ship's maximum weight capacity, maxWeight.

    Return the maximum number of containers that can be loaded onto the ship.

    =========================================================
    FUNCTION: int maxContainers(int n, int w, int maxWeight);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, w = 3, maxWeight = 15
    Output: 4
    Explanation: The deck has 4 cells, and each container weighs 3. The total
                 weight of loading all containers is 12, which does not exceed
                 maxWeight.


    --- Example 2 ---
    Input: n = 3, w = 5, maxWeight = 20
    Output: 4
    Explanation: The deck has 9 cells, and each container weighs 5. The maximum
                 number of containers that can be loaded without exceeding
                 maxWeight is 4.


    *** Constraints ***
    1 <= n <= 1000
    1 <= w <= 1000
    1 <= maxWeight <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 13.16% */
/* Space Beats: 97.80% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int maxContainers(int n, int w, int maxWeight)
    {
        int result = 0;
        for (int i = 0; i < n * n; i++)
        {
            result += w;

            if (result == maxWeight)
                break;
            else if (result > maxWeight)
            {
                result -= w;
                break;
            }
        }

        return result / w;
    }
};
