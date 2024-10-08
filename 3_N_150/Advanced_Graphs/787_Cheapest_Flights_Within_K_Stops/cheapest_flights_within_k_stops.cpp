#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    787) Cheapest Flights Within K Stops
    ====================================

    ============
    Description:
    ============

    There are n cities connected by some number of flights. You are given an
    array flights where flights[i] = [fromi, toi, pricei] indicates that there
    is a flight from city fromi to city toi with cost pricei.

    You are also given three integers src, dst, and k, return the cheapest
    price from src to dst with at most k stops. If there is no such route,
    return -1.

    ==============================================================================================
    FUNCTION: int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k);
    ==============================================================================================

    ,==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
    Output: 700
    Explanation:
    The graph is shown above.
    The optimal path with at most 1 stop from city 0 to 3 is marked in red and
    has cost 100 + 600 = 700.  Note that the path through cities [0,1,2,3] is
    cheaper but is invalid because it uses 2 stops.


    --- Example 2 ---
    Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
    Output: 200
    Explanation:
    The graph is shown above.
    The optimal path with at most 1 stop from city 0 to 2 is marked in red and
    has cost 100 + 100 = 200.


    --- Example 3 ---
    Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
    Output: 500
    Explanation:
    The graph is shown above.
    The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.


    *** Constraints ***
    1 <= n <= 100
    0 <= flights.length <= (n * (n - 1) / 2)
    flights[i].length == 3
    0 <= fromi, toi < n
    fromi != toi
    1 <= pricei <= 104
    There will not be any multiple flights between two cities.
    0 <= src, dst, k < n
    src != dst

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Bellman-Ford Algorithm)

*/

/* Time  Beats: 52.88% */
/* Space Beats: 91.64% */

/* Time  Complexity: O(E * K) */
/* Space Complexity: O(n)     */
class Solution_Bellman-Ford Algorithm {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        vector<int> prices(n, INT_MAX);
        prices[src] = 0;

        for (int i = 0; i < k+1; i++)
        {
            vector<int> tmp_prices = prices;

            for (auto& entry : flights)
            {
                int source      = entry[0];
                int destination = entry[1];
                int price       = entry[2];

                if (prices[source] == INT_MAX)
                    continue;

                if (prices[source] + price < tmp_prices[destination])
                    tmp_prices[destination] = prices[source] + price;
            }

            prices = tmp_prices;
        }

        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Classic BFS.

*/

/* Time  Beats: 69.98% */
/* Space Beats: 80.43% */

/* Time  Complexity: O(E * K) */
/* Space Complexity: O(n + E) */
class Solution_BFS {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        vector<pair<int,int>> adj_list[n];

        for (const auto& entry : flights)
            adj_list[entry[0]].push_back({entry[1], entry[2]});

        queue<pair<int, pair<int,int>>> queue; // {stops, {node, distance}}

        queue.push({0, {src,0}});

        vector<int> distances(n, INT_MAX);
        distances[src] = 0;

        while ( ! queue.empty())
        {
            pair<int, pair<int, int>> one_flight = queue.front();
            queue.pop();

            int stops  = one_flight.first;
            int node   = one_flight.second.first;
            int weight = one_flight.second.second;

            if (stops > K)
                continue;

            for (auto i : adj_list[node])
            {
                int neighbor_node  = i.first;
                int neighbor_price = i.second;

                if (weight + neighbor_price < distances[neighbor_node])
                {
                    queue.push({stops+1, {neighbor_node, weight + neighbor_price}});
                    distances[neighbor_node] = weight + neighbor_price;
                }
            }
        }

        // destination do not reached under k stops
        if (distances[dst] == INT_MAX)
            return -1;

        return distances[dst];
    }
};
