/*
    ============
    === EASY ===
    ============

    ================================
    1184) Distance Between Bus Stops
    ================================

    ============
    Description:
    ============

    A bus has n stops numbered from 0 to n - 1 that form a circle. We know the
    distance between all pairs of neighboring stops where distance[i] is the
    distance between the stops number i and (i + 1) % n.

    The bus goes along both directions i.e. clockwise and counterclockwise.

    Return the shortest distance between the given start and destination stops.

    =========================================================================================
    FUNCTION: int distanceBetweenBusStops(vector<int>& distance, int start, int destination);
    =========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: distance = [1,2,3,4], start = 0, destination = 1
    Output: 1
    Explanation: Distance between 0 and 1 is 1 or 9, minimum is 1.

    --- Example 2 ---
    Input: distance = [1,2,3,4], start = 0, destination = 2
    Output: 3
    Explanation: Distance between 0 and 2 is 3 or 7, minimum is 3.

    --- Example 3 ---
    Input: distance = [1,2,3,4], start = 0, destination = 3
    Output: 4
    Explanation: Distance between 0 and 3 is 6 or 4, minimum is 4.


    *** Constraints ***
    1 <= n <= 10^4
    distance.length == n
    0 <= start, destination < n
    0 <= distance[i] <= 10^4

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 16.59% */
/* Space Beats: 16.36% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination)
    {
        const int N = distance.size();

        if (start == destination)
            return 0; // We're already at our destination

        if (destination < start)
            swap(start, destination);


        partial_sum(distance.begin(), distance.end(), distance.begin());
        //          START_INPUT,      END_INPUT,      START_OUTPUT

        int one = distance[destination-1] - (start > 0 ? distance[start-1] : 0);
        int two = distance[N-1] - one;

        return min(one, two);
    }
};
