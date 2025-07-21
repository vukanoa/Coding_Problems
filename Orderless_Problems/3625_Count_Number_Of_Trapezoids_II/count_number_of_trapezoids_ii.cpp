/*
    ============
    === HARD ===
    ============

    ===================================
    3625) Count Number of Trapezoids II
    ===================================

    ============
    Description:
    ============

    You are given a 2D integer array points where points[i] = [xi, yi]
    represents the coordinates of the ith point on the Cartesian plane.

    Return the number of unique trapezoids that can be formed by choosing any
    four distinct points from points.

    A trapezoid is a convex quadrilateral with at least one pair of parallel
    sides. Two lines are parallel if and only if they have the same slope.

    ===========================================================
    FUNCTION: int countTrapezoids(vector<vector<int>>& points);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
    Output: 2
    Explanation: There are two distinct ways to pick four points that form a
                 trapezoid:
    + The points [-3,2], [2,3], [3,2], [2,-3] form one trapezoid.
    + The points [2,3], [3,2], [3,0], [2,-3] form another trapezoid.


    --- Example 2 ---
    Input: points = [[0,0],[1,0],[0,1],[2,1]]
    Output: 1
    Explanation: There is only one trapezoid which can be formed.


    *** Constraints ***
    4 <= points.length <= 500
    –1000 <= xi, yi <= 1000
    All points are pairwise distinct.

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First, Maximum number of points is 500 therefore there are at most:

        "N choose 2"
             |
             |
             v
         C(N, 2)    =   N * (N-1) / 2   = 124750

    Which is 124750 edges, therefore a solution checking all edges in linear
    time can be acceptable.


    Second, two edges are considered parallel if the angle of those edges with
    x-axis are the same.

        Note: Be careful with a parallelogram because we can count it twice!



    List out all possible edges then group them by its slope(i.e. angle).

    In each group, all edges are parallel or in a same line. To handle edges in
    a same line, we group edges by the its intersection with x-axis.

    If two edges intersect with the x-axis at a same point, they are in a same
    line. Then count all possible trapeziods by grouping two parallel edges.


    A parallelogram which has two pair of parallel sides will be appear in two
    angle groups. To detect a parallelogram, we group edge with a same angle
    by its length. If two edges have a same length and they are parallel, they
    form a parallelogram. To count the number of parallelogram, group edges by
    its lengths.

*/

/* Time  Beats: 88.89% */
/* Space Beats:  5.29% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
private:
    static const long long DEFAULT_SCALE = 1LL * 1e9;

public:
    int countTrapezoids(vector<vector<int>>& points)
    {
        const int N = points.size();

        // umap[angle][intersection][length] = count
        unordered_map<long long, unordered_map<long long, unordered_map<long long, long long>>> umap;

        for (int i1 = 0; i1 < N; i1++)
        {
            for (int i2 = i1+1; i2 < N; i2++)
            {
                long long x1 = points[i1][0];
                long long y1 = points[i1][1];

                long long x2 = points[i2][0];
                long long y2 = points[i2][1];

                long long angle = get_angle(x1, y1, x2, y2);
                long long encoded_x_axis_intersection = get_encoded_x_axis_intersection(x1, y1, x2, y2);
                long long len = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);

                umap[angle][encoded_x_axis_intersection][len]++;
            }
        }

        long long trapezoid_count = 0;
        long long parallelogram_count = 0;

        for (auto iter = umap.begin(); iter != umap.end(); iter++)
        {
            auto [trapezoid, parallelogram] = helper_count_trapezoids_and_parallelogram(iter->second);

            trapezoid_count     += trapezoid;
            parallelogram_count += parallelogram;
        }

        return trapezoid_count + parallelogram_count / 2;
    }

    pair<long long, long long> helper_count_trapezoids_and_parallelogram(unordered_map<long long, unordered_map<long long, long long>>& umap_grouped_by_intersection)
    {
        long long edge_count = 0;
        for (auto& [intersection, grouped_by_len] : umap_grouped_by_intersection)
        {
            for (auto& [len, freq] : grouped_by_len)
                edge_count += freq;
        }

        long long trapezoid_count = 0;
        for (auto& [intersection, grouped_by_len] : umap_grouped_by_intersection)
        {
            int count = 0;
            for (auto& [len, freq] : grouped_by_len)
                count += freq;

            trapezoid_count += count * (edge_count - count);
            edge_count -= count;
        }
        
        // ----------------------------
        // --- Handle parallelogram ---
        // ----------------------------

        // umap_grouped_by_len[length][intersection]
        unordered_map<long long, unordered_map<long long, long long>> umap_grouped_by_len_and_intersection;

        for (auto& [intersection, grouped_by_len] : umap_grouped_by_intersection)
        {
            for (auto& [len, freq] : grouped_by_len)
            {
                umap_grouped_by_len_and_intersection[len][intersection] += freq;
            }
        }

        long long parallelogram_count = 0;
        for (auto& [len, group_by_intersection] : umap_grouped_by_len_and_intersection)
        {
            int total = 0;

            for (auto& [intersection, freq] : group_by_intersection)
                total += freq;

            for (auto& [intersection, freq] : group_by_intersection)
            {
                parallelogram_count += freq * (total - freq);
                total -= freq;
            }
        }

        return {trapezoid_count - parallelogram_count, parallelogram_count};
    }

private:
    long long encode_fraction(long long x, long long y, long long bias = 2000, long long scale = DEFAULT_SCALE)
    {
        // std::gcd (C++17) is strict and may return 0 if x or y is 0
        // long long gcd = std::gcd(x, y); // does NOT work

        long long gcd = __gcd(x, y);       // WORKS
        x /= gcd;
        y /= gcd;

        return x + bias + (y + bias) * scale;
    }

    long long get_angle(double x1, double y1, double x2, double y2)
    {
        long long x = x2 - x1;
        long long y = y2 - y1;

        return encode_fraction(x, y);
    }

    long long get_encoded_x_axis_intersection(double x1, double y1, double x2, double y2)
    {
        if (y1 == y2)
            return encode_fraction(DEFAULT_SCALE / 10, y1);

        /*
            Find intersection with x axis:
            y - y1 = (y2 - y1) / (x2 - x1) * (x - x1)

            However, when y = 0

            x = x1 - y1 * (x2 - x1) / (y2 - y1)

            Make sure there are no error while dividing intergers
        */

        return encode_fraction(x1 * (y2 - y1) - y1 * (x2 - x1), y2 - y1, 0);
    }
};
