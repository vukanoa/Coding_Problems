#include <iostream>
#include <vector>
#include <priority_queue>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    1642) Furthest Building You Can Reach
    =====================================

    ============
    Description:
    ============

    You are given an integer array heights representing the heights of
    buildings, some bricks, and some ladders.

    You start your journey from building 0 and move to the next building by
    possibly using bricks or ladders.

    While moving from building i to building i+1 (0-indexed),

        + If the current building's height is greater than or equal to the next
          building's height, you do not need a ladder or bricks.

        + If the current building's height is less than the next building's
          height, you can either use one ladder or (h[i+1] - h[i]) bricks.

    Return the furthest building index (0-indexed) you can reach if you use the
    given ladders and bricks optimally.

    ==============================================================================
    FUNCTION: int furthestBuilding(vector<int>& heights, int bricks, int ladders);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
    Output: 4
    Explanation: Starting at building 0, you can follow these steps:
    - Go to building 1 without using ladders nor bricks since 4 >= 2.
    - Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
    - Go to building 3 without using ladders nor bricks since 7 >= 6.
    - Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
    It is impossible to go beyond building 4 because you do not have any more bricks or ladders.


    --- Example 2 ---
    Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
    Output: 7


    --- Example 3 ---
    Input: heights = [14,3,19,3], bricks = 17, ladders = 0
    Output: 3


    *** Constraints ***
    1 <= heights.length <= 10^5
    1 <= heights[i] <= 10^6
    0 <= bricks <= 10^9
    0 <= ladders <= heights.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.27% */
/* Space Beats: 45.57% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders)
    {
        priority_queue<int> max_heap; // Using a max-heap to store the largest jumps
        int num_buildings = heights.size();
        int building_index;

        for (building_index = 0; building_index < num_buildings - 1; building_index++)
        {
            int height_difference = heights[building_index + 1] - heights[building_index];

            if (height_difference > 0)
            {
                if (bricks >= height_difference)
                {
                    bricks -= height_difference;
                    max_heap.push(height_difference);
                }
                else if (ladders > 0)
                {
                    if ( ! max_heap.empty() && max_heap.top() > height_difference)
                    {
                        int largest_jump = max_heap.top();
                        bricks += largest_jump - height_difference;
                        max_heap.pop();
                        max_heap.push(height_difference);
                    }

                    ladders--;
                }
                else
                    break;
            }
        }

        return building_index;
    }
};
