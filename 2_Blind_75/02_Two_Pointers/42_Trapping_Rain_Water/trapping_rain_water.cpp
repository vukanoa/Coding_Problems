/*
    ============
    === HARD ===
    ============

    ===========================
    42) Trapping Rain Water
    ===========================

    ============
    Description:
    ============

    Given "n" non-negative integers representing an elevation map where the
    width of each bar is 1, compute how much water it can trap after raining.

    =============================================
    FUNCTION: int trap(std::vector<int>& height);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        ^
        |
        |
        |
        |
        |               |
        |       |```````| |```|
        |   |```| |   | | | | | |
        ---------------------------------
          0 1 0 2 1 0 1 3 2 1 2 1

                      0  1  2  3  4  5  6  7  8  9 10 11
    Input:  height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
    Output: 6




    --- Example 2 ---
        ^
        |
        |
        |           |
        | |`````````|
        | |     |   |
        | | |   | | |
        | | |   | | |
        ---------------------------------
          4 2 0 3 2 5

    Input:  height = [4, 2, 0, 3, 2, 5]
    Output: 9

    *** Constraints ***
    n == height.length
    1 <= n <= 2 * 10^4
    0 <= height[i] <= 10^5

*/

#include <vector>
#include <stack>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Forget how to program for a second. What does it mean to "Trap The Rain
    Water" between the bars in 2D?

    Look at an arbitrary range in the vector of bars.

        ^
        |
        |
        |
        |
        |               |
        |       |```````| |```|
        |   |```| |   | | | | | |
        ---------------------------------
          0 1 0 2 1 0 1 3 2 1 2 1
Indices: [0 1 2 3 4 5 6 7 8 9 A B]
A = 10
B = 11

    If we want to find out that there are 4 "blocks" of water between bars of
    height:
        2 and 3, respectively

    How are we going to do that? How can we know that there are two bars with
    height of 1 "inside" the range, between bars 2 and 3?

    Well, we can't. We can't calculate it like that if you think about it. It's
    impossible to know what sort of and how many bars of lower heights, than
    the range we're calculating, there are.

    So, then... How do we do it?

    We can only calculate how many "blocks" of water can be ABOVE current bar.

    It means that at each bar I have to know maximum height of the bar to the
    left until THIS bar(including this one) and maximum height of the bar to
    the right, from the back of the array "height", until THIS bar.

        ^
        |
        |
        |
        |
        |               |
        |       |```````| |```|
        |   |```| |   | | | | | |
        ---------------------------------
          0 1 0 2 1 0 1 3 2 1 2 1
Indices: [0 1 2 3 4 5 6 7 8 9 A B]
A = 10
B = 11

    Look at index 4(bar with height of 1)

    How many "blocks" of water can be above it?
    Well, let's ask our 1st question:
        1) What is the maximum height of the bar to the left until THIS bar?
           (Including this bar)

           It's bar of height 2 (At position 3)

    Then let's ask our 2nd question:
        2) What is the maximum height of the bar to the right, from the back of
           the array "height", until THIS bar?
           (Including this bar, as well)

           It's bar of height 3 (At position 7)

    Then let's ask our 3rd question:
        3) What is the current height at position 4?

           It's 1

    Then let's ask our 4th and final question:
        4) How do we calculate how many blocks of water can be above current
           bar?

           It's MINIMUM of "maximum height to the left" and "maximum height to
           the right" minus height of the bar at current position.

           min(left_max[i], right_max[i]) - height[i];

    Now we should do that for every single bar in our array "height".
    Since we need to find left_max & right_max for each height[i], we can do
    that in two separate for loops.
    But we're not going to do that in O(n^2) for each vector, i.e. left_max and
    right_max.

    We won't be calculating max bar to the left in a way that we go through the
    whole array for each index. That would be O(n^2).

    We can do that by always comparing and storing the taller bar of the two.
    So for left_max[i] we compare:
        max(left_max[i - 1], height[i]);
    and store it in left_max[i];

    Final part:
    We go through an entire array "height" and calculate how many water blocks
    can be ABOVE each bar.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  28.62% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int trap(vector<int>& height)
    {
        const int N = height.size();
        int result = 0;

        vector<int> left_max (N, 0);
        vector<int> right_max(N, 0);

        for (int i = 1; i < N; i++)
            left_max[i] = max(height[i-1], left_max[i-1]);

        for (int i = N-2; i >= 0; i--)
            right_max[i] = max(height[i+1], right_max[i+1]);

        for (int i = 1; i < N-1; i++)
        {
            int shorter_boundary = min(left_max[i], right_max[i]);
            int water_blocks     = shorter_boundary - height[i];

            result += max(0, water_blocks);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of storing the largest bar up to an index, we can use stack to keep
    track of the bars that are bounded by longer bars and hence may store
    water.

    We keep a stack and iterate over the array.

    We add the index of the bar to the stack if bar is smaller than or equal to
    the bar at the top of the stack, which means that the current bar is
    bounded by the previous bar in the stack.

    If we found a bar longer than that at the top, we are sure that the bar at
    the top of the stack is bounded by the current bar and a previous bar in
    the stack, hence, we can pop and add resulting trapped water to "total".

*/

/* Time  Beats: 78.91% */
/* Space Beats: 38.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Stack {
public:
    int trap(vector<int>& height)
    {
        const int N = height.size();
        int result = 0;

        stack<int> stack;

        int i = 0;
        while (i < N)
        {
            while ( ! stack.empty() && height[stack.top()] < height[i])
            {
                int prev_top = stack.top();
                stack.pop();

                if (stack.empty())
                    break;

                int distance         = i - stack.top() - 1;
                int shorter_boundary = min(height[i], height[stack.top()]) - height[prev_top];

                result += distance * shorter_boundary;
            }

            stack.push(i);

            // Increment
            i++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/


/* Time  Beats: 46.73% */
/* Space Beats: 97.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Two_Pointers {
public:
    int trap(vector<int>& height)
    {
        const int N = height.size();
        int result = 0;

        int L  = 0;
        int R = N - 1;

        int left_max  = 0;
        int right_max = 0;

        while (L < R)
        {
            if (height[L] < height[R])
            {
                L++;

                left_max = max(left_max, height[L]);
                result += left_max + height[L];
            }
            else
            {
                R--;
                right_max = max(right_max, height[R]);
                result += right_max - height[R];
            }
        }

        return result;
    }
};
