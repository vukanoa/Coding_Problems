/*
    ============
    === HARD ===
    ============

    ========================================
    1515) Best Position for a Service Centre
    ========================================

    ============
    Description:
    ============

    A delivery company wants to build a new service center in a new city. The
    company knows the positions of all the customers in this city on a 2D-Map
    and wants to build the new center in a position such that the sum of the
    euclidean distances to all customers is minimum.

    Given an array positions where positions[i] = [xi, yi] is the position of
    the ith customer on the map, return the minimum sum of the euclidean
    distances to all customers.

    In other words, you need to choose the position of the service center
    [xcentre, ycentre] such that the following formula is minimized:

    Answers within 10^(-5) of the actual value will be accepted.

    ===============================================================
    FUNCTION: double getMinDistSum(vector<vector<int>>& positions);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: positions = [[0,1],[1,0],[1,2],[2,1]]
    Output: 4.00000
    Explanation: As shown, you can see that choosing
                 [xcentre, ycentre] = [1, 1] will make the distance to each
                 customer = 1, the sum of all distances is 4 which is the
                 minimum possible we can achieve.

    --- Example 2 ---
    Input: positions = [[1,1],[3,3]]
    Output: 2.82843
    Explanation: The minimum possible sum of distances = sqrt(2) + sqrt(2) =
                 2.82843


    *** Constraints ***
    1 <= positions.length <= 50
    positions[i].length == 2
    0 <= xi, yi <= 100

*/

#include <cfloat>
#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.95% */
/* Space Beats: 12.09% */

/* Time  Complexity: O(N * log(R / eps)) */ // R --> Initial step range
/* Space Complexity: O(1)                */
class Solution {
private:
    /* Signing Cross */
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    double getMinDistSum(vector<vector<int>>& points)
    {
        double best = DBL_MAX;
        vector<double> center = {0.0, 0.0};

        double step = 100.0;
        const double eps = 1e-6;

        while (step > eps)
        {
            bool improved = false;

            for (const auto &dir : directions)
            {
                vector<double> next_center =
                {
                    center[0] + step * dir.first,
                    center[1] + step * dir.second
                };

                double curr = total_distance(points, next_center);

                if (curr < best)
                {
                    best = curr;
                    center = next_center;
                    improved = true;

                    break;
                }
            }

            if ( ! improved)
                step *= 0.5;
        }

        return best;
    }

private:
    double distance_from_point(const vector<int>& point, const vector<double>& center)
    {
        double dx = point[0] - center[0];
        double dy = point[1] - center[1];
        return sqrt(dx * dx + dy * dy);
    }

    double total_distance(const vector<vector<int>>& points, const vector<double>& center)
    {
        double sum = 0.0;
        for (const auto &point : points)
            sum += distance_from_point(point, center);

        return sum;
    }
};
