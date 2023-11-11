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

/* Time  Beats: 19.13% */
/* Space Beats:  8.87% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity)
    {
        std::priority_queue<std::vector<int>,
                            std::vector<std::vector<int>>,
                            std::greater<std::vector<int>>> currently_driven;

        // O(n)
        std::vector<std::vector<int>> rearranged_trips;
        for (auto& trip : trips)
            rearranged_trips.push_back( {trip[1], trip[0], trip[2]} );


        // O(n)
        std::priority_queue<std::vector<int>,
                            std::vector<std::vector<int>>,
                            std::greater<std::vector<int>>> yet_to_be_driven(rearranged_trips.begin(),
                                                                             rearranged_trips.end());

        if (capacity < yet_to_be_driven.top()[1])
            return false;

        int from = yet_to_be_driven.top()[0];
        int num_passengers = yet_to_be_driven.top()[1];
        int to   = yet_to_be_driven.top()[2];
        yet_to_be_driven.pop();

        // In this order because we care the most about the "end location"
        currently_driven.push( {to, from, num_passengers} );

        int current_location = from;
        capacity -= num_passengers;

        // O(n * logn)
        while (!yet_to_be_driven.empty())
        {
            while (!currently_driven.empty())
            {
                std::vector<int> driven = currently_driven.top();

                if (current_location == driven[0]) // driven[2] == "end location", i.e. "to"
                {
                    capacity += driven[2];
                    currently_driven.pop();
                }
                else
                    break;
            }

            std::vector<int> not_driven = yet_to_be_driven.top();
            if (current_location == not_driven[0])
            {
                if (capacity < not_driven[1])
                    return false;

                int from = yet_to_be_driven.top()[0];
                int num_passengers = yet_to_be_driven.top()[1];
                int to   = yet_to_be_driven.top()[2];
                yet_to_be_driven.pop();

                capacity -= num_passengers;
                currently_driven.push( {to, from, num_passengers} );
            }

            if (currently_driven.empty() && yet_to_be_driven.empty())
                return true;
            else if (!currently_driven.empty() && !yet_to_be_driven.empty())
                current_location = std::min(currently_driven.top()[0], yet_to_be_driven.top()[0]);
            else if (!currently_driven.empty())
                current_location = currently_driven.top()[0];
            else
                current_location = yet_to_be_driven.top()[0];
        }

        return true;
    }
};
