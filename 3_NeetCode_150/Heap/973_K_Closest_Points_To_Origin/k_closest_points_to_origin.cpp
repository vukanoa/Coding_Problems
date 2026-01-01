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
#include <algorithm>
#include <queue>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Since we're looking for the distance between point P and Origin(0, 0), we
    don't really have to use this formula: √(x1 - x2)^2 + (y1 - y2)^2).

    Actually we do, but we don't need to pass x2 and y2 since they are always
    going to be 0.

    So when we're calculating the distance between point P and Origin(0, 0), we
    can do it like this: √x1^2 + y1^2).

    We calculate the distance for each point and store it in a vector of pairs
    named "distances":
    distances = ( {<distance>, [xi, yi]}, {<distance>, [xi, yi]}, ...)

    After we're doing processing each point, we sort it by the first value,
    i.e. "distance".

    Then just iterate from 0 to k and push Points to vector "results".

*/

/* Time  Beats: 56.04% */
/* Space Beats: 24.83% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        vector<pair<double, vector<int>>> distances;

        for (auto& point : points)
            distances.push_back({euclidean_distance(point[0], point[1]), point});

        sort(distances.begin(), distances.end());

        vector<vector<int>> results;
        int i = 0;
        while (i < k)
            results.push_back(distances[i++].second);

        return results;
    }

private:
    double euclidean_distance(int& x1, int& y1)
    {
        return sqrt(x1*x1 + y1*y1);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can notice 2 things:
        1. We don't need to calculate the SQRT. The "higher" values are going
           to be "higher" anyway. So don't need to compute that. We can just do
           this: x1*x1 + y1*y1

        2. Since we don't need all n points, we don't have to sort all the
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

/*
    Time  Complexity: O(n * logk)
    k is less than or equal to n. Usually it's less than n, which makes this
    Solution faster than O(n * logn)

    This one in theory is faster, however on LeetCode, this Solution has a
    worse Time Complexity than the one above.
*/
/*
    Space Complexity: O(n)
*/
class Solution_2 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        priority_queue<pair<int, vector<int>>> max_heap;

        for (auto& point : points)
        {
            int x = point[0];
            int y = point[1];

            // Here instead of (x*x + y*y) we could've had this:
            // euclidean_distance(point[0], point[1])
            // However, it's unnecessary computation, hence (x*x + y*y)
            max_heap.push({x*x + y*y, point});

            // O(log k)
            if (max_heap.size() > k)
                max_heap.pop();
        }

        vector<vector<int>> result;
        for (int i = 0; i < k; i++)
        {
            result.push_back(max_heap.top().second);
            max_heap.pop();
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however we are explicitly using "min_heap", instead of a
    "max_heap", that's why there is this giant initialization of
    "priority_queue".

    The entire Solution is written in a slightly different way than above,
    however the IDEA is absolutely equivalent.

    We, again, do not have to calculate the entire Euclidean distance, we can
    just use (x*x + y*y) as the integer that represents the distance. It's
    completely the same whether we actually calculate the distance or we leave
    it like this.

    Therefore, why would we do some unnecessary computation every single time?

*/

/* Time  Beats: 63.64% */
/* Space Beats: 21.87% */

/* Time  Complexity: O(n * logk) */
/* Space Complexity: O(n) */
class Solution_3 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        priority_queue<pair<int, vector<int>>,
                            vector<pair<int, vector<int>>>,
                            greater<pair<int, vector<int>>>> min_heap;

        for (auto& point : points)
        {
            int distance = point[0]*point[0] + point[1]*point[1];
            min_heap.push({distance, point});
        }

        vector<vector<int>> result;
        while (k--)
        {
            auto top = min_heap.top();
            min_heap.pop();

            result.push_back(top.second);
        }

        return result;
    }
};




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
