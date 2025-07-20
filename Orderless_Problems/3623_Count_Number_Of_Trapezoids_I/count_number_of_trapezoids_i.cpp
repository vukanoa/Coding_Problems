/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3623) Count Number of Trapezoids I
    ==================================

    ============
    Description:
    ============

    You are given a 2D integer array points, where points[i] = [xi, yi]
    represents the coordinates of the ith point on the Cartesian plane.

    A horizontal trapezoid is a convex quadrilateral with at least one pair of
    horizontal sides (i.e. parallel to the x-axis). Two lines are parallel if
    and only if they have the same slope.

    Return the number of unique horizontal trapezoids that can be formed by
    choosing any four distinct points from points.

    Since the answer may be very large, return it modulo 10^9 + 7.

    ===========================================================
    FUNCTION: int countTrapezoids(vector<vector<int>>& points); 
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]
    Output: 3
    Explanation:
    Using points [1,0], [2,0], [3,2], and [2,2].
    Using points [2,0], [3,0], [3,2], and [2,2].
    Using points [1,0], [3,0], [3,2], and [2,2].


    --- Example 2 ---
    Input: points = [[0,0],[1,0],[0,1],[2,1]]
    Output: 1
    Explanation: There is only one horizontal trapezoid that can be formed.


    *** Constraints ***
    4 <= points.length <= 10^5
    –10^8 <= xi, yi <= 10^8
    All points are pairwise distinct.

*/

#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    In order for a Trapezoid to be PARALLEL with x axis, its two horizontal
    sides MUST be parallel with the x axis and must not overlap.

    Now that we know this, we simply count the number of points at each y.

    Let's say we have something like this:

            [2, 4, 3, 5, 7, 2]
        y =  0  1  2  3  4  5

    First let's convert each set of points to how many different ways can we
    pick them.

    It would be this:

            [3, 4, 6, 5, 7, 2]
             |           |
             |           |
          C(3,2)  ... C(7,2)
             |           |
             |           |
             v           v
            3!           7!
          ------      --------------
      2! * (3 - 2)!    2! * (7 - 2)!
            |             |
            |             |
            |             |
            v             v
            3             21

          [3, 6, 15, 10, 21, 1]
           0  1   2   3   4  5

    Now all we have to do is for EACH y, multiply with other y's.


    But wouldn't that be... O(N^2)?
    Yes it would! Good catch!

    So... How do we overcome that?


    There is this mathematical trick you should know:
    The sum of our array:

          [3, 6, 15, 10, 21, 1]
           0  1   2   3   4  5

    is: 1 + 6 + 15 + 10 + 21 + 1 = 54

    If we subtract y=0 which is 3, then it's 51.


    Instead of doing this:

        3 * 6  + 3 * 15 + 3 * 10 + 3 * 21 + 3 * 1 = 153

    We can simply do:  3 * (6 + 15 + 10 + 21 + 1) = 153


    It's basic algebra, but sometimes we forget this in the heat of the moment
    in the Contest.

*/

/* Time  Beats: 89.34% */
/* Space Beats:     -% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    const int MOD = 1e9 + 7;

public:
    int countTrapezoids(vector<vector<int>>& points)
    {
        const int N = points.size();
        int result = 0;

        unordered_map<int, int> y_freq;

        for (const auto& p : points)
        {
            const int x = p[0];
            const int y = p[1];

            y_freq[y]++;
        }

        vector<long long> pair_counts_per_y;
        for (const auto& [_, freq] : y_freq)
        {
            long long bin = 1LL * freq * (freq - 1) / 2;

            pair_counts_per_y.push_back(bin);
        }

        if (pair_counts_per_y.empty())
            return 0;

        long long sum = accumulate(pair_counts_per_y.begin(), pair_counts_per_y.end(), 0LL);

        for (unsigned i = 0; i < pair_counts_per_y.size()-1; i++)
        {
            sum -= pair_counts_per_y[i];
            result = (result + ((pair_counts_per_y[i] * sum) % MOD)) % MOD;
        }

        return result;
    }
};
