#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    605) Can Place Flowers
    ===========================

    ============
    Description:
    ============

    You have a long flowerbed in which some of the plots are planted, and some
    are not. However, flowers cannot be planted in adjacent plots.

    Given an integer array flowerbed containing 0's and 1's, where 0 means
    empty and 1 means not empty, and an integer n, return true if n new flowers
    can be planted in the flowerbed without violating the no-adjacent-flowers
    rule and false otherwise.

    ==============================================================
    FUNCTION: bool canPlaceFlowers(vector<int>& flowerbed, int n);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: flowerbed = [1,0,0,0,1], n = 1
    Output: true


    --- Example 2 ---
    Input: flowerbed = [1,0,0,0,1], n = 2
    Output: false


    *** Constraints ***
    1 <= flowerbed.length <= 2 * 10^4
    flowerbed[i] is 0 or 1.
    There are no two adjacent flowers in flowerbed.
    0 <= n <= flowerbed.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.79% */
/* Space Beats: 12.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_1 {
public:
    bool canPlaceFlowers(std::vector<int>& flowerbed, int n)
    {
        if (n == 0)
            return true;

        for (int i = 0; i < flowerbed.size(); i++)
        {
            if (flowerbed[i] == 0 &&
               (i == 0 || flowerbed[i-1] == 0) &&
               (i == flowerbed.size()-1 || flowerbed[i+1] == 0))
            {
                flowerbed[i] = 1;
                n--;

                if (!n)
                    return true;
            }
        }

        return false;
    }
};




/* Time  Beats: 98.26% */
/* Space Beats: 25.15% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool canPlaceFlowers(std::vector<int>& flowerbed, int n)
    {
        if (n == 0)
            return true;

        int prev = 0; // So that we do not modify original "flowerbed".
        for (int i = 0; i < flowerbed.size(); i++)
        {
            if (flowerbed[i] == 0 &&
               (prev == 0) &&
               (i == flowerbed.size()-1 || flowerbed[i+1] == 0))
            {
                prev = 1;
                n--;

                if (n == 0)
                    return true;
            }
            else
                prev = flowerbed[i];
        }

        return false;
    }
};




/* Time  Beats: 95.94% */
/* Space Beats: 13.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_3 {
public:
    bool canPlaceFlowers(std::vector<int>& flowerbed, int n)
    {
        std::vector<int> extended_flowerbed;
        extended_flowerbed.push_back(0);
        extended_flowerbed.insert(extended_flowerbed.end(), flowerbed.begin(), flowerbed.end());
        extended_flowerbed.push_back(0);

        for (int i = 1; i < extended_flowerbed.size() - 1; i++)
        {
            if (extended_flowerbed[i - 1] == 0 &&
                extended_flowerbed[  i  ] == 0 &&
                extended_flowerbed[i + 1] == 0)
            {
                extended_flowerbed[i] = 1;
                n--;
            }
        }

        return n <= 0;
    }
};
