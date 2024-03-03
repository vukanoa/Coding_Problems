#include <iostream>
#include <vector>
#include <stack>

/*
    ============
    === HARD ===
    ============

    ==================================
    84) Largest Rectangle in Histogram
    ==================================

    ============
    Description:
    ============

    Given an array of integers "heights" representing the histogram's bar
    height where the width of each bar is 1, return the area of the largest
    rectangle in the histogram.

    =========================================================
    FUNCTION: int largestRectangleArea(vector<int>& heights);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  heights = [2, 1, 5, 6, 2, 3]
    Output: 10

    --- Example 2 ---
    Input:  heights = [2, 4]
    Output: 4

    *** Constraints ***
    1 <= heights.length <= 10^5
    0 <= heights[i] <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Brute force solution would be to find:
        1. first bar to the left  that is smaller than the current one, and
        2. first bar to the right that is also smaller than the current one,
    for each bar(each number in the array).

    Since that would take O(n^2) we have to optimize it somehow.

    We can use stack.
    So how can a stack help us optimize this solution?

    We have two vectors: "left" and "right". Those represent the left most bar
    (inclusive) up to which the current bar is the lowest.

    And the right most bar(inclusive) up to which the current bar is the
    lowest.

    Size of both left and right is the same as the size of the array - we will
    have the left and the right bound for each and every bar.

    After we have that it's easy to calculate max_area for each bar. After that
    all we have to do is just return the maximum value of all of those
    max_areas.

    But how does the stack help us?
    Consider this example:
        [2, 1, 5, 6, 2, 3]

    If the stack is empty, that means the left most bar that has to be included
    in calculating the max area of the current bar is the bar at index 0, that
    is why we say:
        left[i] = 0;

    and we push current index's in the stack.
    Why?

    If the stack isn't empty then while the stack is not empty and while
    the bar under the index at the top of the stack is greater than or equals
    to current bar's height, pop from the stack.

    After the while loop ended see if stack is empty, if it is then:
        left[i] = 0

    and if it is not then:
        left[i] = stack.top() + 1;

    Why stack.top() + 1?
    Because we have found the bar whose height is less than the height of the
    current one, thus we have to exclude that, so we add + 1 since stack.top()
    returns the index of the bar not the height of the bar.


    Let's go Iteration by iteration:
    === 1st Iteration ===

    left    = [-1, -1, -1, -1, -1, -1]
    heights = [ 2,  1,  5,  6,  2,  3]
                ^
    Stack
    ----------------
    |
    ----------------


    === 2nd Iteration ===

    left    = [ 0, -1, -1, -1, -1, -1]
    heights = [ 2,  1,  5,  6,  2,  3]
                    ^
    Stack
    ----------------
    | 0 |
    ----------------
    pop()
    push(1)


    === 3rd Iteration ===

    left    = [ 0,  0, -1, -1, -1, -1]
    heights = [ 2,  1,  5,  6,  2,  3]
                        ^
    Stack
    ----------------
    | 1 |
    ----------------
    push(2)


    === 4th Iteration ===

    left    = [ 0,  0,  2, -1, -1, -1]
    heights = [ 2,  1,  5,  6,  2,  3]
                            ^
    Stack
    ----------------
    | 1 | 2 |
    ----------------
    push(3)


    === 5th Iteration ===

    left    = [ 0,  0,  2,  3, -1, -1]
    heights = [ 2,  1,  5,  6,  2,  3]
                                ^
    Stack
    ----------------
    | 1 | 2 | 3 |
    ----------------
    pop
    pop
    push(4)


    === 6th Iteration ===

    left    = [ 0,  0,  2,  3,  2, -1]
    heights = [ 2,  1,  5,  6,  2,  3]
                                    ^
    Stack
    ----------------
    | 1 | 4 |
    ----------------
    push(5)


    After the for loop:

    left   =  [ 0,  0,  2,  3,  2,  5]
    heights = [ 2,  1,  5,  6,  2,  3]
                                       ^
    Stack
    ----------------
    | 1 | 4 | 5 |
    ----------------


    After this, we have to do a similar thing for "right" vector, therefore we
    first have to clear the stack.

    The rest of the algorithm was explained at the beginning of this
    explanation.

*/


/* Time  Beats: 66.90% */
/* Space Beats: 60.71% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights)
    {
        int n = heights.size();
        std::vector<int> left(n);
        std::vector<int> right(n);

        std::stack<int> stack;

        // Fill left
        for (int i = 0; i < n; i++)
        {
            if (stack.empty())
            {
                left[i] = 0;
                stack.push(i);
            }
            else
            {
                while (!stack.empty() && heights[stack.top()] >= heights[i])
                    stack.pop();

                left[i] = stack.empty() ? 0 : stack.top() + 1;
                stack.push(i);
            }
        }

        // Clear stack
        while (!stack.empty())
            stack.pop();

        // Fill right
        for (int i = n - 1; i >= 0; i--)
        {
            if (stack.empty())
            {
                right[i] = n - 1;
                stack.push(i);
            }
            else
            {
                while (!stack.empty() && heights[stack.top()] >= heights[i])
                    stack.pop();

                right[i] = stack.empty() ? n - 1 : stack.top() - 1;
                stack.push(i);
            }
        }

        int max_area = 0;
        for (int i = 0; i < n; i++)
        {
            int width = right[i] - left[i] + 1;
            max_area = std::max(max_area, heights[i] * width);
        }

        return max_area;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Let's see if we can notice some patterns. There are a few different
    situations.

    1)
        #
        # #
        2 1

        The first one is the bigger than the second one. We cannot extend the
        first one any farther. There is a little "hole" above the bar 1.
        So, the biggest rectangle we can get is just this bar 2 * width=1

        However, for the bar 1, we can extend it, but to the left.
        We cannot extend bar 2 to the right, but we can extend bar left,
        potentially, to the right. There's nothing coming to stop us just yet.

        Let's look at the opposite scenario.


    2)
          #
        # #
        1 2

        In this case we can keep extending bar 1 to the right, there's nothing
        stopping us.
        And for the bar 2, there is nothing coming to stop us just yet.


    3)
        # #
        # #
        2 2

        In this case, we can also keep extending it. There's no smaller
        rectangle stopping us to be extended farther to the right.


    This tells us that current heights are going to be increasing.
    If heights aren't in increasing order, they will be popped.

    Now let's look at the scenario where all the heights are indeed in
    increasing order.

    4)
             #
           # #
         # # #
       # # # #
       1 2 3 4

       1 can keep extending all the way to 4.
       2 can keep extending all the way to 4.
       3 can keep extending all the way to 4.
       4 can keep extending because there's nothing coming to stop us just yet.

       However, none of them can be extended to the left, because the height
       to the left is smaller, so they cannot be extended.

       But what would happen if we would introduce a smaller height after?

    5)
             #
           # # #
         # # # #
       # # # # #
       1 2 3 4 3
             ^
            pop


       That would mean that 4 cannot be extended any farther. So all we can do
       is say:"Okay, these are the boundaries of height 4, let's compute the
       area which is going to be 1 * 4 in this case", and then we have to
       remove this from being considered, so we pop it.

    6)
             #
           # #
         # # # #
       # # # # #
       1 2 3 4 2
           ^^^
           pop

       Similar thing would happen. We cannot extend the 4, however we cannot
       extend 3 either(we cannot extend it past bar 4), but we can extend
       previous bars, which are 2 and 1(from right to left, respectively).

    7)
             #
           # #
         # # #
       # # # # #
       1 2 3 4 1
         ^^^^^
          pop

       Let's look out last example to drive this point on.
       Neither 4, nor 3, nor 2 can be extended to the right past 4.
       Only bar 1(the left one) can be extended past 4 and potentially further.

       So first we compute the rectangle of width=1 and height 4 and remove it
       from consideration.

       Then we compute the rectangle of width=2 and height 3 and remove it from
       consideration.

       Lastly, we compute the rectangle of width=3 and heights 2 and remove it
       from consideration.

       In this case we had a 1 and we popped 3 elements from consideration.

       Notice how we're only popping the most recent elements. We're not
       popping an element that's in the middle. We're only popping them from
       the "top" to the "bottom".

       So that tells us that we should use a Stack for this problem.
       The Stack will contain the current heights that we're considering and
       will pop them from the top when we're no longer considering them.


    Now let's look at the Algorithm and let's do a Simulation:

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************


                                __________________
              6                 |     STACK      |
            5 #                 | index | height |
            # #                 |       |        |
            # #   3             |       |        |     Max Area: 0
        2   # # 2 #             |       |        |
        # 1 # # # #             |       |        |
        # # # # # #             |       |        |
        0 1 2 3 4 5             |       |        |

        I'm going to be maintaining what's the max_area so far.

-------------------------------------------------------------------------------

    1)
                                __________________
              6                 |     STACK      |
            5 #                 | index | height |
            # #             --> |   0   |   2    |
            # #   3             |       |        |     Max Area: 0
        2   # # 2 #             |       |        |
        # 1 # # # #             |       |        |
        # # # # # #             |       |        |
        0 1 2 3 4 5             |       |        |
        i

        Since there's nothing in the Stack, we can't pop anything, let's just
        add it.

-------------------------------------------------------------------------------

    2)
                                __________________
              6                 |     STACK      |
            5 #                 | index | height |
            # #             --> |   0   |   1    |
            # #   3             |       |        |     Max Area: 2
        2   # # 2 #             |       |        |
        # 1 # # # #             |       |        |
        # # # # # #             |       |        |
        0 1 2 3 4 5             |       |        |
          i

        Next we get to height=1 and since it is smaller than the top of the
        stack we're going to pop the top(2) from the stack, but before we pop
        it let's just see what's the max area that we could've gotten with this
        2 height.

        So, starting at index 0, and we've just reach the index 1 before which
        we have to stop since 2 > 1. So that's the range of the width:
        From 0 to 1 => Width is 1, Height is 2 => Area = 2
        So far, our Max Area is 2 now.

        And now we pop the 2 from the Stack and we push 1 to the Stack. But,
        what's the index of this new height=1 that we're trying to push?
        Well, we're currently on the index 1 so we could say that the index is
        indeed 1, but we're going to do it a little differently.

        If you look at this height=2 and height=1 you can see that we can
        extend this height=1 to back, all the way back.

        So instead of saying that the index of this height=1 starts at index 1,
        we're going to say that it starts at index 0, because we can extend it
        all the way back to the index 0(inclusive).

-------------------------------------------------------------------------------

    3)
                                __________________
              6                 |     STACK      |
            5 #                 | index | height |
            # #                 |   0   |   1    |
            # #   3         --> |   2   |   5    |     Max Area: 2
        2   # # 2 #             |       |        |
        # 1 # # # #             |       |        |
        # # # # # #             |       |        |
        0 1 2 3 4 5             |       |        |
            i

        It's the height=5, there's no restriction. The height=1 that is on the
        top of the Stack can be extended because 5 > 1, so just push height=5
        onto the Stack alongside his corresponding index=2.

-------------------------------------------------------------------------------

    4)
                                __________________
              6                 |     STACK      |
            5 #                 | index | height |
            # #                 |   0   |   1    |
            # #   3             |   2   |   5    |     Max Area: 2
        2   # # 2 #         --> |   3   |   6    |
        # 1 # # # #             |       |        |
        # # # # # #             |       |        |
        0 1 2 3 4 5             |       |        |
              i

        Same as in previous step. Height=6 is greater than the height that is
        on the top of the Stack, thus just push height=6 with its corresponding
        index=3.

        Heights are in increasing order so that means we don't have to pop
        anything. The 5 can be extended to the right, that's why we don't have
        to pop it.

-------------------------------------------------------------------------------

    5)
                                __________________
              6                 |     STACK      |
            5 #                 | index | height |
            # #                 |   0   |   1    |
            # #   3         --> |   2   |   2    |     Max Area: 6, then 10
        2   # # 2 #             |       |        |
        # 1 # # # #             |       |        |
        # # # # # #             |       |        |
        0 1 2 3 4 5             |       |        |
                i

        Here is where interesting things happen.
        Since the height=6 that is on the Top of the Stack can't go any
        farther, because we've reach the height=2, this height=6, which started
        at index 3, stopped at index 4, that means its width is only 1.

        We have to pop it now, but before we pop it, let's get the area that it
        could've made.

        Width=1 * Height=6 => Area = 6 --> Area > Max Area --> Max Area = Area
        And now we pop the height=6 from the Stack.

        Now the Top of our Stack is 5. But height=5 is also greater than the
        height=2 as well, that means this 5 can't be extended any farther than
        index 4.

        So before we pop it we have to compute the Area.

        We look at the starting index of this 5 which is index 2, and we
        stopped it at index 4, so that means its width is 2, and the height=5,
        so the Area is creates is 10.

        Thus, again, we update the Max Area:
            10 > Max Area => Max Area = 10

        And now we pop this height=5 from the Top of our Stack.

        Now we look at the new Top of our Stack. It's height=1.
            1 < height[i]

        So we don't have to pop this height=1 from the Stack, because it can
        continue to be extended through index=4 and potentially farther.

        Now we can finally push this height=2 on the Top of the Stack. But what
        will be the starting index of this height of 2?

        We could put index=4, but we can notice that we've just popped two
        elements: 6 and 5, respectively, so that means that this height=2 can
        be extended backwards up to the last popped index(which was index=2 of
        the bar height=5).

        So since our heights[i] can be extended backwards all the way back to
        the index=2(inclusive), that's the index we're going to put alongside
        height=2, on the Top of the Stack.

-------------------------------------------------------------------------------

    6)
                                __________________
              6                 |     STACK      |
            5 #                 | index | height |
            # #                 |   0   |   1    |
            # #   3             |   2   |   2    |     Max Area: 10
        2   # # 2 #         --> |   5   |   3    |
        # 1 # # # #             |       |        |
        # # # # # #             |       |        |
        0 1 2 3 4 5             |       |        |
                  i

        And lastly, we reach index=5 height=3.

        Height=3 is greater than the height=2 that is currently on the Top of
        the Stack, that means height=2 can be extended so there's no reason to
        pop anything.

        Since we don't have to pop anything, we just push height=3 with its
        corresponding index=5 on Top of the Stack.

-------------------------------------------------------------------------------

    7)
              __________________
              |     STACK      |
              | index | height |
              |   0   |   1    |
              |   2   |   2    |     Max Area: 10
          --> |   5   |   3    |
              |       |        |
              |       |        |
              |       |        |

        Now since we have 3 elements that we didn't end up popping from the
        Stack, what that tells us is that we're able to extend them all the way
        to the end of the Histogram, so we still need to compute the Areas we
        could've created from these heights.

        So let's iterate through them and figure that out.
        We're "iterating" from the Top of the Stack to the bottom, popping each
        time, so essentially we'll just work with what's on the Top of the
        Stack.

        Index=5 and Height=3 and it went all the way to the end of the
        Histogram.
        That means the width of it is just 1(index 5 is the very last index in
        the Histogram).

        So: Width=1 * Height=3 => Area = 3 // But it's not bigger than Max Area

        Now we pop that element from the Stack.

-------------------------------------------------------------------------------

    8)
              __________________
              |     STACK      |
              | index | height |
              |   0   |   1    |
          --> |   2   |   2    |     Max Area: 10
              |       |        |
              |       |        |
              |       |        |
              |       |        |

        Index=2 and Height=2 and it went all the way to the end of the
        Histogram.
        That means the width of it is:
            Index=5 - Index=2 + 1
        which is 4.

        So: Width=4 * Height=2 => Area = 8 // But it's not bigger than Max Area

        Now we pop that element from the Stack.

-------------------------------------------------------------------------------

    9)
              __________________
              |     STACK      |
              | index | height |
          --> |   0   |   1    |
              |       |        |     Max Area: 10
              |       |        |
              |       |        |
              |       |        |
              |       |        |

        Index=0 and Height=1 and it went all the way to the end of the
        Histogram.
        That means the width of it is:
            Index=5 - Index=0 + 1
        which is 6.

        So: Width=6 * Height=1 => Area = 6 // But it's not bigger than Max Area

        Now we pop that element from the Stack.

-------------------------------------------------------------------------------

    10)
              __________________
              |     STACK      |
              | index | height |
              |       |        |
              |       |        |     Max Area: 10
              |       |        |
              |       |        |
              |       |        |
              |       |        |

        Our Stack is Empty at the very end.

-------------------------------------------------------------------------------

*/

/* Time  Beats: 89.17% */
/* Space Beats: 63.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Neat {
public:
    int largestRectangleArea(std::vector<int>& heights)
    {
        int n = heights.size();

        int max_area = 0;
        std::stack<std::pair<int , int>> stack; // pair: (index, height)

        for (int i = 0; i < n; i++)
        {
            int start = i;

            while (!stack.empty() && stack.top().second > heights[i])
            {
                std::pair<int, int> top = stack.top();
                stack.pop();

                max_area = std::max(max_area, top.second * (i - top.first));
                start = top.first;
            }

            stack.push({start, heights[i]});
        }

        while (!stack.empty())
        {
            std::pair<int, int> top = stack.top();
            stack.pop();

            max_area = std::max(max_area, top.second * (n - top.first));
        }

        return max_area;
    }
};


int
main()
{
    Solution sol;
    Solution_Neat sol_neat;

    /* Example 1 */
    // std::vector<int> heights = {2, 1, 5, 6, 2, 3};

    /* Example 2 */
    // std::vector<int> heights = {2, 4};

    /* Example 3 */
    // std::vector<int> heights = {5, 2, 4, 7, 9, 3, 2, 6};

    /* Example 4 */
    // std::vector<int> heights = {5, 2, 8, 7, 9, 3, 2, 9};

    /* Example 5 */
    // std::vector<int> heights = {1, 1, 1, 1, 1, 1};

    /* Example 6 */
    // std::vector<int> heights = {1, 2, 9, 8, 1, 1};

    /* Example 7 */
    std::vector<int> heights = {3, 5, 5, 4, 0, 1, 7};

    std::cout << "\n\t======================================";
    std::cout << "\n\t=== LARGEST RECTANGLE IN HISTOGRAM ===";
    std::cout << "\n\t======================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tHeights: [";
    for (auto x: heights)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // int max_area = sol.largestRectangleArea(heights);
    int max_area = sol_neat.largestRectangleArea(heights);


    /* Write Output */
    std::cout << "\n\tMax Area: " << max_area << "\n\n";


    return 0;
}
