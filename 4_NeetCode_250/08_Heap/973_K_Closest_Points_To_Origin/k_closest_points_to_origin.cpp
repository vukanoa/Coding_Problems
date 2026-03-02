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

    TODO

*/

/* Quick select */
class Solution_Quick_Select {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        int N = points.size();

        int left  = 0;
        int right = N - 1;

        while (left <= right)
        {
            int mid = quick_select_algo(points, left, right);

            if (mid == k)
                break;

            if (mid < k)
                left  = mid + 1;
            else
                right = mid - 1;
        }

        return vector<vector<int>>(points.begin(), points.begin() + k);
    }

private:
    int quick_select_algo(vector<vector<int>>& points, int left, int right)
    {
        vector<int> pivot_point = points[left];

        while (left < right)
        {
            while (left < right && compare(points[right], pivot_point) >= 0)
                right--;

            points[left] = points[right];

            while (left < right && compare(points[left], pivot_point) <= 0)
                left++;

            points[right] = points[left];
        }

        points[left] = pivot_point;

        return left;
    }

    int compare(vector<int>& first, vector<int>& second)
    {
        return  first[0] *  first[0] +  first[1] *  first[1] -
               second[0] * second[0] - second[1] * second[1];
    }
};
