#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1552) Magnetic Force Between Two Balls
    ======================================

    ============
    Description:
    ============

    In the universe Earth C-137, Rick discovered a special form of magnetic
    force between two balls if they are put in his new invented basket. Rick
    has n empty baskets, the ith basket is at position[i], Morty has m balls
    and needs to distribute the balls into the baskets such that the minimum
    magnetic force between any two balls is maximum.

    Rick stated that magnetic force between two different balls at positions x
    and y is |x - y|.

    Given the integer array position and the integer m. Return the required
    force.

    ========================================================
    FUNCTION: int maxDistance(vector<int>& position, int m); 
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: position = [1,2,3,4,7], m = 3
    Output: 3
    Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the
    magnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is
    3. We cannot achieve a larger minimum magnetic force than 3.


    --- Example 2 ---
    Input: position = [5,4,3,2,1,1000000000], m = 2
    Output: 999999999
    Explanation: We can use baskets 1 and 1000000000.


    *** Constraints ***
    n == position.length
    2 <= n <= 10^5
    1 <= position[i] <= 10^9
    All integers in position are distinct.
    2 <= m <= position.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one is almost exactly the same as: 
    LeetCode 1482 Minimum Number Of Days To Make m Bouquets

*/

/* Time  Beats: 92.16% */
/* Space Beats: 36.17% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int maxDistance(vector<int>& position, int m)
    {
        /* Sort */
        std::sort(position.begin(), position.end());

        int left  = 1;
        int right = position.back() - position[0];

        int result = -1;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;

            int last_position = position[0];
            int balls = 1;

            for(int i = 1; i < position.size(); i++)
            {
                if(position[i] - last_position >= mid)
                {
                    last_position = position[i];
                    balls++;
                }
            }

            if(balls >= m)
            {
                result = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return result;
    }
};
