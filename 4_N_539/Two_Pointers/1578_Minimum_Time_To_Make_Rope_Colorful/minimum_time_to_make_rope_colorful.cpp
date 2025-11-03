/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    1578) Minimum Time to Make Rope Colorful
    ========================================

    ============
    Description:
    ============

    Alice has n balloons arranged on a rope. You are given a 0-indexed string
    colors where colors[i] is the color of the ith balloon.

    Alice wants the rope to be colorful. She does not want two consecutive
    balloons to be of the same color, so she asks Bob for help. Bob can remove
    some balloons from the rope to make it colorful. You are given a 0-indexed
    integer array neededTime where neededTime[i] is the time (in seconds) that
    Bob needs to remove the ith balloon from the rope.

    Return the minimum time Bob needs to make the rope colorful.

    ==============================================================
    FUNCTION: int minCost(string colors, vector<int>& neededTime);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: colors = "abaac", neededTime = [1,2,3,4,5]
    Output: 3
    Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
                 Bob can remove the blue balloon at index 2. This takes 3
                 seconds.  There are no longer two consecutive balloons of the
                 same color. Total time = 3.


    --- Example 2 ---
    Input: colors = "abc", neededTime = [1,2,3]
    Output: 0
    Explanation: The rope is already colorful. Bob does not need to remove any
                 balloons from the rope.


    --- Example 3 ---
    Input: colors = "aabaa", neededTime = [1,2,3,4,1]
    Output: 2
    Explanation: Bob will remove the balloons at indices 0 and 4. Each balloons
                 takes 1 second to remove.  There are no longer two consecutive
                 balloons of the same color. Total time = 1 + 1 = 2.


    *** Constraints ***
    n == colors.length == neededTime.length
    1 <= n <= 10^5
    1 <= neededTime[i] <= 10^4
    colors contains only lowercase English letters.

*/

#include <numeric>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Iterate through the entire string, one-by-one with two pointers. Each time
    two colors(i.e. letters) are the same, we add lesser of two neededTimes to
    the result.

    The problem arises once the "right one" is the smaller because if we simply
    continue to compare the next two, the "left one" will point at the one we
    have just evicted.

    Example:

            8 2 1 4 5 8 9 2 6  // neededTime
            A A A B B C D B A  // colors
            L R


        Since balloons under L and R are of equal colors, we have to evict the
        one with lesser "neededTime". In this case it's the "right one".

        However, if we don't take into consideration that we've just evicted
        the "right one" and not the "left one", we'll end up in this situation:

            8 2 1 4 5 8 9 2 6  // neededTime
            A A A B B C D B A  // colors
              L R


        This would NOT be a right thing to do since now our "L" pointers points
        at the balloon we've previously evicted. Because of that, if we evict
        the "right one", we ONLY move the 'R' pointer, but we count how many
        "right ones" have we evicted CONSECUTIVELY(this is important!).

        So, we won't be in this faulty case, instead we will take 'R' from the
        initial state and move it to the right by one, and we will count that
        we've evicted one "right one" so far. We'll keep that in "move_left"
        variable.

        The next state, from the initial one, is this:

            8 2 1 4 5 8 9 2 6  // neededTime
            A A A B B C D B A  // colors
            L   R

            move_left = 1;


        Now we are checking ballons above 'L' and 'R" pointers. They are of
        same color. The "right one" needs less time, therefore we do the same
        thing - We move 'R' pointer by one to the right and we increment
        variable move_left.


            8 2 1 4 5 8 9 2 6  // neededTime
            A A A B B C D B A  // colors
            L     R

            move_left = 2;


        Now we see that balloons above 'L' and 'R' are NOT the same color, we
        move 'R' by one again(that's always the same), but we move the 'L' by
        one too this time. Additionally we also move the 'L' pointer by
        move_left positions to the right. AND WE RESET move_left to 0! (This is
        why the word "CONSECUTIVE" was important!)

            8 2 1 4 5 8 9 2 6  // neededTime
            A A A B B C D B A  // colors
                  L R

            move_left = 0;


        And we continue doing the same until our 'R' pointer is out of bounds.

    At the end we just return "result" variable which holds the correct result.

*/

/* Time  Beats: 99.52% */
/* Space Beats: 15.97% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minCost(string colors, vector<int>& neededTime)
    {
        const int N = colors.length();

        int L  = 0;
        int R = 1;

        int result = 0;

        int move_left = 0;
        while (R < N)
        {
            if (colors[L] == colors[R])
                result += min(neededTime[L], neededTime[R]);

            if (colors[L] == colors[R] && neededTime[L] > neededTime[R])
            {
                move_left++;
            }
            else
            {
                L++;
                L += move_left;

                move_left = 0; // Reset
            }

            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of moving "left" and counting, all we have to do is simply find
    out which out of the CONSECUTIVE balloons should remain on the rope.

    In other words -- if there are CONSECUTIVE balloons on the rope, we'll
    leave the one that has the highest neededTime.

    Why?
    Because we want MINIMUM time to remove redundant balloons, therefore leave
    those with HIGHEST neededTime to remove as they are.

    This way we'll calculate the total_sum of neededTime, and then we'll
    subtract the ones that we left on the rope.


    This way the approach is much more simple and straight forward.
    "In every CONSECUTIVE group of balloons of same color, add only the one
     with the HIGHEST neededTime".

    At the end we simply subtract those from total_sum.

*/

/* Time  Beats: 59.28% */
/* Space Beats: 65.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
    int minCost(string colors, vector<int>& neededTime)
    {
        const int N = colors.size();
        int total_sum = accumulate(neededTime.begin(), neededTime.end(), 0);

        int sum_of_remaining = 0;
        int max_time = neededTime[0];

        int L = 0;
        int R = 1;
        while (R < N)
        {
            if (colors[L] == colors[R])
            {
                max_time = max(max_time, neededTime[R]);
            }
            else
            {
                sum_of_remaining += max_time;
                L = R;
                max_time = neededTime[R];
            }

            // Increment
            R++;
        }
        sum_of_remaining += max_time;

        return total_sum - sum_of_remaining;
    }
};
