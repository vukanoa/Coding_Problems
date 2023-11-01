#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    735) Asteroid Collision
    ===========================

    ============
    Description:
    ============

    We are given an array asteroids of integers representing asteroids in a
    row.

    For each asteroid, the absolute value represents its size, and the sign
    represents its direction (positive meaning right, negative meaning left).
    Each asteroid moves at the same speed.

    Find out the state of the asteroids after all collisions. If two asteroids
    meet, the smaller one will explode. If both are the same size, both will
    explode. Two asteroids moving in the same direction will never meet.

    ================================================================
    FUNCTION: vector<int> asteroidCollision(vector<int>& asteroids);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: asteroids = [5,10,-5]
    Output: [5,10]
    Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never
                 collide.


    --- Example 2 ---
    Input: asteroids = [8,-8]
    Output: []
    Explanation: The 8 and -8 collide exploding each other.


    --- Example 3 ---
    Input: asteroids = [10,2,-5]
    Output: [10]
    Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide
                 resulting in 10.


    *** Constraints ***
    2 <= asteroids.length <= 10^4
    -1000 <= asteroids[i] <= 1000
    asteroids[i] != 0

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.20% */
/* Space Beats: 84.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // We don't count return vector as additional
class Solution {
public:
    std::vector<int> asteroidCollision(std::vector<int>& asteroids)
    {
        std::vector<int> stack;

        for (int i = 0; i < asteroids.size(); i++)
        {
            while (!stack.empty() && stack.back() > 0 && asteroids[i] < 0)
            {
                int diff = stack.back() + asteroids[i];

                if (diff < 0)
                    stack.pop_back();
                else if (diff > 0)
                    asteroids[i] = 0;
                else
                {
                    asteroids[i] = 0;
                    stack.pop_back();
                }
            }

            if (asteroids[i] != 0)
                stack.push_back(asteroids[i]);
        }

        return stack;
    }
};
