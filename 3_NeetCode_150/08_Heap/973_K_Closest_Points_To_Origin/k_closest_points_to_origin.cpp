/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    973) K Closest Points to Origin
    ===============================

    ============
    Description:
    ============

    Given an array of points where points[i] = [xi, yi] represents a point on
    the X-Y plane and an integer k, return the k closest points to the origin
    (0, 0).

    The distance between two points on the X-Y plane is the Euclidean distance
    (i.e., √(x1 - x2)^2 + (y1 - y2)^2).

    You may return the answer in any order. The answer is guaranteed to be
    unique (except for the order that it is in).

    ===========================================================================
    FUNCTION: vector<vector<int>> kClosest(vector<vector<int>>& points, int k);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[1,3],[-2,2]], k = 1
    Output: [[-2,2]]
    Explanation:
    The distance between (1, 3) and the origin is sqrt(10).
    The distance between (-2, 2) and the origin is sqrt(8).
    Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
    We only want the closest k = 1 points from the origin, so the answer is
    just [[-2,2]].


    --- Example 2 ---
    Input: points = [[3,3],[5,-1],[-2,4]], k = 2
    Output: [[3,3],[-2,4]]
    Explanation: The answer [[-2,4],[3,3]] would also be accepted.


    *** Constraints ***
    1 <= k <= points.length <= 10^4
    -10^4 <= xi, yi <= 104

*/

#include <cmath>
#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We can notice 2 things:
        1. We don't need to calculate the SQRT. The "higher" values are going
           to be "higher" anyway. So don't need to compute that. We can just do
           this: x1*x1 + y1*y1

        2. Since we don't need all N points, we don't have to sort all the
           computed distances. Imagine if we had a million of points and also
           imagine that k = 3.

           Why would we had to sort the entire array of million elements if we
           only need top 3?

           To get top 3, we need to use a Max Heap.
           Each time we calculate the distance between point Pi and Origin(0,0)
           we can push the pair of {distance, Point Pi} and if the number of
           distances(i.e. pairs) is greater than k, since we are inserting in a
           Max Heap, the biggest distance, i.e. the Point Pi that is farthest
           from the Origin(0, 0) can be evicted from our Max Heap, thus leaving
           us with exactly K closest points to Origin.
*/

/* Time  Beats: 35.28% */
/* Space Beats: 37.94% */

/* Time  Complexity: O(N * logK + K * logK) */
/* Space Complexity: O(N)                   */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        const int N = points.size();
        vector<vector<int>> result;

        priority_queue<pair<int, int>> max_heap;

        // O(N * logK) (entire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            int x = points[i][0];
            int y = points[i][1];

            max_heap.push( {x*x + y*y, i} ); // O(logK)

            if (max_heap.size() > k)
                max_heap.pop(); // O(logK)
        }

        // O(K * logK) (entire block)
        while ( ! max_heap.empty()) // O(k)
        {
            auto [distance, idx] = max_heap.top(); // O(1)
            max_heap.pop(); // O(logK)

            result.push_back(points[idx]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Quick-Select.

*/

/* Time  Beats:  6.92% */
/* Space Beats: 90.96% */

/* Time  Complexity: O(N^2), but O(N) AVERAGE time */
/* Space Complexity: O(1)                          */ // Result doesn't count
class Solution_2 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        int N = points.size();

        int left  = 0;
        int right = N-1;

        int pivot_idx = N; // Out-of-Bounds initially
        while (pivot_idx != k)
        {
            pivot_idx = quick_select(points, left, right);

            if (pivot_idx < k)
                left  = pivot_idx + 1;
            else
                right = pivot_idx - 1;
        }

        return vector<vector<int>>(points.begin(), points.begin() + k);
    }

private:
    int quick_select(vector<vector<int>>& points, int left, int right)
    {
        int pivot_idx = right;
        int pivot_distance = euclid_distance(points[pivot_idx]);

        int i = left - 1;
        int j = left;
        while (j < right)
        {
            int curr_distance = euclid_distance(points[j]);

            if (curr_distance <= pivot_distance)
                swap(points[++i], points[j]);

            // Increment
            j++;
        }
        swap(points[++i], points[pivot_idx]);

        return i;
    }

    /* Euclid Distance from ORIGIN */
    int euclid_distance(vector<int>& point)
    {
        return point[0] * point[0] +
               point[1] * point[1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.65% */
/* Space Beats: 61.46% */

/* Time  Complexity: O(N * logK + K * logK) --> O((N + K) * logK)*/
/* Space Complexity: O(K)                                        */
class Solution_3 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        const int N = points.size();
        vector<vector<int>> result;

        priority_queue<pair<double,int>> max_heap;

        // O(N * logK) (entire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            double distance = 1.0 * sqrt(1.0 * points[i][0] * points[i][0] + points[i][1] * points[i][1]);

            max_heap.push( {distance, i} ); // O(logk)

            if (max_heap.size() > k)
                max_heap.pop(); // O(logK)
        }

        // O(K * logK) (entire block)
        while ( ! max_heap.empty()) // O(K)
        {
            auto [distance, idx] = max_heap.top();
            max_heap.pop(); // O(logK)

            result.push_back(points[idx]);
        }

        return result;
    }
};
