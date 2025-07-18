/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    858) Mirror Reflection
    ===========================

    ============
    Description:
    ============

    There is a special square room with mirrors on each of the four walls.
    Except for the southwest corner, there are receptors on each of the
    remaining corners, numbered 0, 1, and 2.

    The square room has walls of length p and a laser ray from the southwest
    corner first meets the east wall at a distance q from the 0th receptor.

    Given the two integers p and q, return the number of the receptor that the
    ray meets first.

    The test cases are guaranteed so that the ray will meet a receptor
    eventually.

    =============================================
    FUNCTION: int mirrorReflection(int p, int q);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: p = 2, q = 1
    Output: 2
    Explanation: The ray meets receptor 2 the first time it gets reflected
                 back to the left wall.

    --- Example 2 ---
    Input: p = 3, q = 1
    Output: 1


    *** Constraints ***
    1 <= q <= p <= 1000

*/

#include <algorithm>

/*
    ------------
    --- IDEA ---
    ------------

    Tedious, you should skip this one for sure!

*/

/* Time  Beats: 100.00% */
/* Space Beats: 40.57% */

/* Time  Complexity: O(p) */
/* Space Complexity: O(1) */
class Solution {
private:
    double EPSILON = 1e-6;

public:
    int mirrorReflection(int p, int q)
    {
        double curr_x = 0;
        double curr_y = 0;

        double ray_x = p; // room_length
        double ray_y = q; // laser_height

        // While it hasn't reached a receptor,...
        while ( ! ( is_close(curr_x, p) && (is_close(curr_y, 0) || is_close(curr_y, p)) || is_close(curr_x, 0) && is_close (curr_y, p) ))
        {
            double min_time_to_wall = 1e9;

            if ((   -curr_x / ray_x) > EPSILON) min_time_to_wall = std::min(min_time_to_wall,   -curr_x  / ray_x);
            if ((   -curr_y / ray_y) > EPSILON) min_time_to_wall = std::min(min_time_to_wall,   -curr_y  / ray_y);
            if (((p-curr_x) / ray_x) > EPSILON) min_time_to_wall = std::min(min_time_to_wall, (p-curr_x) / ray_x);
            if (((p-curr_y) / ray_y) > EPSILON) min_time_to_wall = std::min(min_time_to_wall, (p-curr_y) / ray_y);

            curr_x += ray_x * min_time_to_wall;
            curr_y += ray_y * min_time_to_wall;

            if (is_close(curr_x, p) || is_close(curr_x, 0)) ray_x *= -1;
            if (is_close(curr_y, p) || is_close(curr_y, 0)) ray_y *= -1;
        }

        if (is_close(curr_x, p) && is_close(curr_y, p))
            return 1;

        return is_close(curr_x, p) ? 0 : 2;
    }

private:
    bool is_close(double x, double y)
    {
        return std::abs(x - y) < EPSILON;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Even if this is a tedious problem, there is a smart Math Solution to this
    that is worth exploring and looking at.


    Instead of modelling the ray as a bouncing line, model it as a straight
    line through reflections of the room.

    For example, if p = 2, q = 1, then we can reflect the room horizontally,
    and draw a straight line from (0, 0) to (4, 2). The ray meets the receptor
    2, which was reflected from (0, 2) to (4, 2).

    In general, the ray goes to the first integer point (kp, kq) where k is an
    integer, and kp and kq are multiples of p. Thus, the goal is just to find
    the smallest k for which kq is a multiple of p.

    The mathematical answer is k = p / gcd(p, q).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  40.57% */

/* Time  Complexity: O(logP) */
/* Space Complexity: O(1)    */
class Solution_Math {
public:
    int mirrorReflection(int p, int q)
    {
        int gcd_value = gcd(p, q);

        p /= gcd_value;
        p %= 2;

        q /= gcd_value;
        q %= 2;

        if (p == 1 && q == 1)
            return 1;

        return p == 1 ? 0 : 2;
    }

private:
    int gcd(int a, int b)
    {
        if (a == 0)
            return b;

        return gcd(b % a, a);
    }
};
