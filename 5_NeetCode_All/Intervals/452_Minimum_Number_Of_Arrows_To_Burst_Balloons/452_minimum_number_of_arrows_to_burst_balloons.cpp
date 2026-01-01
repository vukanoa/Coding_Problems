#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    452) Minimum Number of Arrows to Burst Balloons
    ===============================================

    ============
    Description:
    ============

    There are some spherical balloons taped onto a flat wall that represents
    the XY-plane. The balloons are represented as a 2D integer array points
    where points[i] = [xstart, xend] denotes a balloon whose horizontal
    diameter stretches between xstart and xend. You do not know the exact
    y-coordinates of the balloons.

    Arrows can be shot up directly vertically (in the positive y-direction)
    from different points along the x-axis. A balloon with xstart and xend is
    burst by an arrow shot at x if xstart <= x <= xend. There is no limit to
    the number of arrows that can be shot. A shot arrow keeps traveling up
    infinitely, bursting any balloons in its path.

    Given the array points, return the minimum number of arrows that must be
    shot to burst all balloons.

    =============================================================
    FUNCTION: int findMinArrowShots(vector<vector<int>>& points);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[10,16],[2,8],[1,6],[7,12]]
    Output: 2
    Explanation: The balloons can be burst by 2 arrows:
    - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
    - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

    --- Example 2 ---
    Input: points = [[1,2],[3,4],[5,6],[7,8]]
    Output: 4
    Explanation: One arrow needs to be shot for each balloon for a total of 4
                 arrows.

    --- Example 3 ---
    Input: points = [[1,2],[2,3],[3,4],[4,5]]
    Output: 2
    Explanation: The balloons can be burst by 2 arrows:
    - Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
    - Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].


    *** Constraints ***
    1 <= points.length <= 10^5
    points[i].length == 2
    -2^31 <= xstart < xend <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    It doesn't require a genius to realize why the Output is 2 here:

        Input: points = [[10,16],[2,8],[1,6],[7,12]]
        Output: 2

    If we've sorted the Input:
        points = [[1,6],[2,8],[7,12],[10,16]]

    It easy to see that we need one arrow for the first two balloons and one
    for the other two.

    Had we draw them, it would like like this:

        1    6  8  12  16
        |----|
         |-----|
              |----|
                 |-----|

    Now it's super obvious to see that we can burst the first two balloons with
    one arrow and then the remaining two with the other.

    First two balloons could be burst at positions: 2, 3, 4, 5 and 6.
    While remaining two ballons could be burst at: 10, 11 and 12.

    It doesn't really matter at which points we've burst them, it only matters
    WHETHER we can bust them together or not.


    However, this could lead to a wrong Solution. Consider this example:

        Input: points = [[9,12],[1,10],[4,11],[8,12],[3,9],[6,9],[6,7]]

    If we sort it:
        points = [[1,10],[3,9],[4,11],[6,7],[6,9],[8,12],[9,12]]

    Using previous logic you'd think that we only have to check whether the
    current one, let's calls it points[R], whether points[R]'s start is LESS
    THAN OR EQUALS to the points[L](which is fixed)'s end.

    However, that would be wrong.

    Each time we findout that points[R]'s start is LESS THAN OR EQUALS to
    points[L]'s end, we MUST(!!!) take the MAXIMUM of:

        points[L]'s start and points[R]'s start

    Also, we MUST(!!!) take the MINIMUM of:

        points[L]'s end and points[R]'s end

    Otherwise, without doing that, we'd end up with a result of 1. Which is NOT
    true.

    Therefore, we ALWAYS have to keep SHRINKING the range we're currently
    deadling with, until we find out that the current points' start is STRICTLY
    GREATER than the range we're dealing with.

    Let's look an even more obvious example:
    Here's how it would work with the given example:
        points = [[1,10],[3,6],[7,8],[9,12],[11,12]]

        Fix pointer L at 0th point: [1, 10]
        Put pointer R at 1st point: [3, 6]

        Is points[R]'s start LESS THAN OR EQUALS to points[L]'s start?
        Yes.

        That means they OVERLAP. However, had we NOT taken the MAX of their
        starts and MIN of their ends, we would've continue dealing with a range
        [1, 10], which could be a mistake.

        It could be a mistake because maybe the next point is [7, 9].

        Is 7 LESS THAN OR EQUAL to 10?
        Yes!

        And the DO OVERLAP INDEED, however there is a BIG problem.

        Now we would say that a single arrow can burst all 3 of these points:
            [1,10], [3,6], [7,9]

        which is NOT(!!) true. Let me draw it:

            1        10
            |--------|
              3  6
              |--|
                  7 9
                  |-|

        You can clearly see that we CANNOT burst all of them using a single
        arrow. That is precisely why we MUST if the points[R]'s start is LESS
        THAN OR EQUAL to the current range's end we MUST take the minimum of
        points[R]'s end and current range's end.

        Had we done that here, it would look like this:

            [1, 10] and [3, 6] OVERLAP, therefore current range's end is the
            minimum between 10 and 6, which is 6.

            And we take the maximum between their "start" positions(which we'll
            quickly realize we don't even need).

            Now our current range is [3, 6].

        Let's introduce the next point: [7, 9]

            Do [3,6] and [7,9] OVERLAP?
            No!

            We need to use 2 arrows to burst these first 3 balloons.


        That's why we need to keep shrinking the range as long as the next
        point's start position is LESS THAN OR EQUAL to the "end" of current
        range.

        Also, notice that we do absolutely NOTHING by taking the MAXIMUM of the
        "start" positions since we've sorted the Input at the beginning.

        That's the entire Solution.

*/

/* Time  Beats: 72.38% */
/* Space Beats: 38.48% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the Sorting Algorithm
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points)
    {
        // Sort in O(n * logn)
        sort(points.begin(), points.end());

        int L = 0;
        int R = 1;

        int result = 0;
        vector<int> curr_range = points[L];

        while (R < points.size())
        {
            if (curr_range[1] < points[R][0])
            {
                result++;
                curr_range = points[R];
                L = R;
            }
            else // Potentially shorten the range inwards
            {
                curr_range[0] = max(curr_range[0], points[R][0]); // Max
                curr_range[1] = min(curr_range[1], points[R][1]); // Min // Unnecessary
            }

            R++;
        }
        result++;

        return result;
    }
};
