/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    478) Generate Random Point in a Circle
    ======================================

    ============
    Description:
    ============

    Given the radius and the position of the center of a circle, implement the
    function randPoint which generates a uniform random point inside the
    circle.

    Implement the Solution class:

        + Solution(double radius, double x_center, double y_center) initializes
          the object with the radius of the circle radius and the position of
          the center (x_center, y_center).

        + randPoint() returns a random point inside the circle. A point on the
          circumference of the circle is considered to be in the circle. The
          answer is returned as an array [x, y].

    ===============================
    CLASS:
    class Solution {
    public:
        Solution(double radius, double x_center, double y_center) {

        }

        vector<double> randPoint() {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["Solution", "randPoint", "randPoint", "randPoint"]
    [[1.0, 0.0, 0.0], [], [], []]
    Output
    [null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]

    Explanation
    Solution solution = new Solution(1.0, 0.0, 0.0);
    solution.randPoint(); // return [-0.02493, -0.38077]
    solution.randPoint(); // return [0.82314, 0.38945]
    solution.randPoint(); // return [0.36572, 0.17248]


    *** Constraints ***
    0 < radius <= 10^8
    -10^7 <= x_center, y_center <= 10^7
    At most 3 * 10^4 calls will be made to randPoint.

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 97.76% */
/* Space Beats: 56.21% */

/* Time  Complexity: O(1) */ // Due to "random sampling"
/* Space Complexity: O(1) */
class Solution {
public:
    double radius;
    double center_x;
    double center_y;

    Solution(double circle_radius, double x_center, double y_center)
    {
        radius   = circle_radius;
        center_x = x_center;
        center_y = y_center;
    }

    vector<double> randPoint()
    {
        double random_x = (1.0 * rand() / RAND_MAX * (2 * radius)) + (center_x - radius);
        double random_y = (1.0 * rand() / RAND_MAX * (2 * radius)) + (center_y - radius);

        while (squaredDistance(random_x, random_y, center_x, center_y) >= radius * radius)
        {
            random_x = (1.0 * rand() / RAND_MAX * (2 * radius)) + (center_x - radius);
            random_y = (1.0 * rand() / RAND_MAX * (2 * radius)) + (center_y - radius);
        }

        return {random_x, random_y};
    }

private:
    double squaredDistance(double x1, double y1, double x2, double y2)
    {
        return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    }
};
