/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    3275) K-th Nearest Obstacle Queries
    ===================================

    ============
    Description:
    ============

    There is an infinite 2D plane.

    You are given a positive integer k. You are also given a 2D array queries,
    which contains the following queries:

    queries[i] = [x, y]: Build an obstacle at coordinate (x, y) in the
    plane. It is guaranteed that there is no obstacle at this coordinate when
    this query is made.

    After each query, you need to find the distance of the kth nearest obstacle
    from the origin.

    Return an integer array results where results[i] denotes the kth nearest
    obstacle after query i, or results[i] == -1 if there are less than k
    obstacles.

    Note that initially there are no obstacles anywhere.

    The distance of an obstacle at coordinate (x, y) from the origin is given
    by |x| + |y|.

    ========================================================================
    FUNCTION: vector<int> resultsArray(vector<vector<int>>& queries, int k);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: queries = [[1,2],[3,4],[2,3],[-3,0]], k = 2
    Output: [-1,7,5,3]
    Explanation:
        Initially, there are 0 obstacles.
        After queries[0], there are less than 2 obstacles.
        After queries[1], there are obstacles at distances 3 and 7.
        After queries[2], there are obstacles at distances 3, 5, and 7.
        After queries[3], there are obstacles at distances 3, 3, 5, and 7.


    --- Example 2 ---
    Input: queries = [[5,5],[4,4],[3,3]], k = 1
    Output: [10,8,6]
    Explanation:
        After queries[0], there is an obstacle at distance 10.
        After queries[1], there are obstacles at distances 8 and 10.
        After queries[2], there are obstacles at distances 6, 8, and 10.



    *** Constraints ***
    1 <= queries.length <= 2 * 10^5
    All queries[i] are unique.
    -109 <= queries[i][0], queries[i][1] <= 10^9
    1 <= k <= 10^5

*/

#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic use of a Heap.

    If you've never done a problem similar to this, try this one from Blind_75:

        347) Top K Frequent Elements

    Since we need to take care only of k-th longest distance, then that means
    we only care about first k distances. Each time we push the new one, if
    the size is greater than k, we pop the biggest one and VOILA, we have a
    Heap of size k again, but this time the top is our desired k-th distance.

*/

/* Time  Beats: 89.59% */
/* Space Beats: 89.59% */

/* Time  Complexity: O(n * logk) */
/* Space Complexity: O(k)        */
class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k)
    {
        const int N = queries.size();
        vector<int> result(N);

        priority_queue<int> max_heap;
        for(int i = 0; i < N; i++)
        {
            max_heap.push(abs(queries[i][0]) + abs(queries[i][1]));

            if (max_heap.size() > k)
                max_heap.pop();

            result[i] = (max_heap.size() == k) ? max_heap.top() : -1;
        }

        return result;
    }
};
