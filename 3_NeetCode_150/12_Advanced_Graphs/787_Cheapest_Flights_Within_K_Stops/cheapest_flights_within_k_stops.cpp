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

#include <climits>
#include <queue>
#include <vector>
using namespace std;

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
class Solution_Bellman_Ford_Algorithm {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        vector<int> cost(n, INT_MAX);
        cost[src] = 0;

        for (int i = 0; i < k+1; i++)
        {
            vector<int> tmp_prices = cost;

            for (auto& entry : flights)
            {
                int from  = entry[0];
                int to    = entry[1];
                int price = entry[2];

                if (cost[from] == INT_MAX)
                    continue;

                if (cost[from] + price < tmp_prices[to])
                    tmp_prices[to] = cost[from] + price;
            }

            cost = tmp_prices;
        }

        return cost[dst] == INT_MAX ? -1 : cost[dst];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Classic BFS.

*/

/* Time  Beats: 69.94% */
/* Space Beats: 16.85% */

/* Time  Complexity: O(E * K)     */
/* Space Complexity: O(E + V * K) */
class Solution_BFS {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        const int V = n;
        const int E = flights.size();

        vector<vector<vector<int>>> adj_list(V);

        /* Create an Adjacency List */
        for (const auto& flight : flights)
        {
            const int& from  = flight[0];
            const int& to    = flight[1];
            const int& price = flight[2];

            adj_list[from].push_back( {to, price} );
        }

        queue<vector<int>> queue;
        queue.push( {0, 0, src} ); // {cost, stops, node}

        vector<int> cost(V, INT_MAX);
        cost[src] = 0;

        /* BFS */
        while ( ! queue.empty())
        {
            vector<int> front = queue.front();
            queue.pop();

            int curr_cost  = front[0];
            int curr_stops = front[1];
            int curr_node  = front[2];

            if (curr_stops > k)
                continue;

            for (const auto& neighbor : adj_list[curr_node])
            {
                int neighbor_node  = neighbor[0];
                int neighbor_price = neighbor[1];

                int new_cost = curr_cost + neighbor_price;

                if (new_cost < cost[neighbor_node])
                {
                    queue.push( {new_cost, curr_stops+1, neighbor_node} );
                    cost[neighbor_node] = new_cost;
                }
            }
        }

        return cost[dst] == INT_MAX ? -1 : cost[dst];
    }
};
