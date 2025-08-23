/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2731) Movements of Robots
    ===========================

    ============
    Description:
    ============

    Some robots are standing on an infinite number line with their initial
    coordinates given by a 0-indexed integer array nums and will start moving
    once given the command to move. The robots will move a unit distance each
    second.

    You are given a string s denoting the direction in which robots will move
    on command. 'L' means the robot will move towards the left side or negative
    side of the number line, whereas 'R' means the robot will move towards the
    right side or positive side of the number line.

    If two robots collide, they will start moving in opposite directions.

    Return the sum of distances between all the pairs of robots d seconds after
    the command. Since the sum can be very large, return it modulo 10^9 + 7.

    =====
    Note:
        + For two robots at the index i and j, pair (i,j) and pair (j,i) are
          considered the same pair.

        + When robots collide, they instantly change their directions without
          wasting any time.

        Collision happens when two robots share the same place in a moment.
            + For example, if a robot is positioned in 0 going to the right and
              another is positioned in 2 going to the left, the next second
              they'll be both in 1 and they will change direction and the next
              second the first one will be in 0, heading left, and another will
              be in 2, heading right.

            + For example, if a robot is positioned in 0 going to the right and
            another is positioned in 1 going to the left, the next second the
            first one will be in 0, heading left, and another will be in 1,
            heading right.

    =====

    ==============================================================
    FUNCTION: int sumDistance(vector<int>& nums, string s, int d);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-2,0,2], s = "RLL", d = 3
    Output: 8
    Explanation:
    After 1 second, the positions are [-1,-1,1]. Now, the robot at index 0 will move left, and the robot at index 1 will move right.
    After 2 seconds, the positions are [-2,0,0]. Now, the robot at index 1 will move left, and the robot at index 2 will move right.
    After 3 seconds, the positions are [-3,-1,1].
    The distance between the robot at index 0 and 1 is abs(-3 - (-1)) = 2.
    The distance between the robot at index 0 and 2 is abs(-3 - 1) = 4.
    The distance between the robot at index 1 and 2 is abs(-1 - 1) = 2.
    The sum of the pairs of all distances = 2 + 4 + 2 = 8.

    --- Example 2 ---
    Input: nums = [1,0], s = "RL", d = 2
    Output: 5
    Explanation:
    After 1 second, the positions are [2,-1].
    After 2 seconds, the positions are [3,-2].
    The distance between the two robots is abs(-2 - 3) = 5.


    *** Constraints ***
    2 <= nums.length <= 10^5
    -2 * 10^9 <= nums[i] <= 2 * 10^9
    0 <= d <= 10^9
    nums.length == s.length
    s consists of 'L' and 'R' only
    nums[i] will be unique.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a variation of a very famous problem:

        LeetCode 1503: Last Moment Before All Ants Fall Out of a Plank

    "There are some ants on a plank at some positions. They are moving right or
     left, and change directions when they bump into each other. When does the
     last ant fall off the plank?"


    At first glance it may seem difficult or even impossible to keep track of
    all collisions simulateously.

    But there is a very very important observation here -- When to ants bump
    into each other(or robots in this case) we can just act as if they are
    passing through each other, like ghosts.

    At the end we need to return the distance between EVERY TWO ants(robots),
    therefore we don't really care where did each original ant(robot) end up
    exactly.

    We ONLY care about relative positions of ants(robots) in total.

    Therefore, once two ants(robots) collide, we can treat them as if they are
    passing through each other like ghosts.

    That's why now we can just add or subtract the amount of seconds 'd' for
    each robot in "nums".

    Once that is done, it is useful to sort those ending positions and then we
    are going to grapple with "differences between each pair of robots".

    The difficulty in this last step lies in the Constraints of this problem:

        2 <= nums.length <= 10^5

    That means that in order to calculate the difference between each PAIR of
    robots, that would take us O(N^2) which unacceptable for these Constraints.



    This may not be intuitive at all, but this is the way these kinds of
    computations are done efficiently. If you're NOT familiar with them, here
    it is:

         We can compute this easily by first sorting the array, then
         multiplying the ending position times the index, minus the prefix sum.

    This gives us the distance between all pairs of robots without double
    counting.

    It sounds complicated, and it may be that way, but once you get famialiar
    with it, it's not too bad.

*/

/* Time  Beats: 87.82% */
/* Space Beats: 41.12% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    int MOD = 1e9 + 7;

public:
    int sumDistance(vector<int>& nums, string s, int d)
    {
        const int N = nums.size();
        long long result = 0;

        // We can treat them as passing through each other
        vector<long long> end_position_of_robot(nums.begin(), nums.end());

        // Move each robot to its end position
        for (int i = 0; i < N; i++)
        {
            if (s[i] == 'R')
                end_position_of_robot[i] += d;
            else
                end_position_of_robot[i] -= d;
        }

        /* Sort */
        sort(end_position_of_robot.begin(), end_position_of_robot.end());

        long long prefix = 0;
        for (long long i = 0; i < N; i++)
        {
            result += i * end_position_of_robot[i] - prefix;
            result %= MOD;

            prefix += end_position_of_robot[i];
        }

        return result;
    }
};
