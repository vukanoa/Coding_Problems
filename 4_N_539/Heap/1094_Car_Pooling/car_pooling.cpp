#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1094) Car Pooling
    ===========================

    ============
    Description:
    ============

    There is a car with capacity empty seats. The vehicle only drives east
    (i.e., it cannot turn around and drive west).

    You are given the integer capacity and an array trips where trips[i] =
    [numPassengersi, fromi, toi] indicates that the ith trip has numPassengersi
    passengers and the locations to pick them up and drop them off are fromi
    and toi respectively. The locations are given as the number of kilometers
    due east from the car's initial location.

    Return true if it is possible to pick up and drop off all passengers for
    all the given trips, or false otherwise.

    ====================================================================
    FUNCTION: bool carPooling(vector<vector<int>>& trips, int capacity);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: trips = [[2,1,5],[3,3,7]], capacity = 4
    Output: false

    --- Example 2 ---
    Input: trips = [[2,1,5],[3,3,7]], capacity = 5
    Output: true


    *** Constraints ***
    1 <= trips.length <= 1000
    trips[i].length == 3
    1 <= numPassengersi <= 100
    0 <= fromi < toi <= 1000
    1 <= capacity <= 10^5

*/

/* Time  Beats: 99.48% */
/* Space Beats: 60.01% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity)
    {
        // O(n * logn)
        // Sort by index 1's value(second element out of 3) in ASCENDING order
        std::sort(trips.begin(), trips.end(), [](const std::vector<int>& a,
                                                 const std::vector<int>& b)
                                                {
                                                    return a[1] < b[1];
                                                });

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> min_heap;

        // O(n * logk)
        for (std::vector<int>& trip : trips)
        {
            int to_take_passengers = trip[0];
            int from = trip[1];
            int to = trip[2];

            /*
                min_heap.top().first <==> Earliest destination from some trip
                                          that already started(its passengers
                                          are currently in the car)
            */
            while (!min_heap.empty() && min_heap.top().first <= from)
            {
                int to_drop_passengers = min_heap.top().second;
                min_heap.pop(); // O(logk)

                capacity += to_drop_passengers;
            }

            if (capacity < to_take_passengers)
                return false;

            capacity -= to_take_passengers;
            min_heap.push( {to, to_take_passengers} ); // O(logk)
        }

        return true;
    }
};
