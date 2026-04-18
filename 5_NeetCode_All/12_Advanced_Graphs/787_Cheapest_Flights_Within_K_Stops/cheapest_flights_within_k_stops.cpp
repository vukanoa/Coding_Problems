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

#include <algorithm>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Here we are NOT solving general "Shortest Path in a graph", instead we are
    solving "Shortest path with at most k stops". That's a crucial difference.

    This changes the Bellman-Ford variant.

    Classic Bellman-Ford does V-1 iterations because ANY shortest pat in a
    Graph without negative cycles as AT MOST V-1 edges.

    After "i" iterations, we are guaranteed correct shortest paths that use AT
    MOST "i" edges.


    Here, the Constraint is different: AT MOST k stops means at most k+1 edges.

    Therefore, we only care about paths with: 

        <= k+1 edges

    not ALL possible paths. That is why we run the "relaxation" loop exactly
    k+1 times.

    Key invariant here:

        After iteration "i", cost[x] stores the minimum cost to reach "x" using
        at most "i" edges.

        Because we copy into new_cost, each iteration only extends paths BY ONE
        edge.

            i = 0   ---> paths with    0   edges(i.e. just "src")
            i = 1   ---> paths with <= 1   edge
            ...
            i = k+1 ---> paths with <= k+1 edges

*/

/* Time  Beats: 52.88% */
/* Space Beats: 91.64% */

/* Time  Complexity: O(n + E * K) */
/* Space Complexity: O(n)         */
class Solution_Bellman_Ford_Algorithm {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        vector<int> cost(n, INT_MAX);
        cost[src] = 0;

        for (int i = 0; i < k+1; i++)
        {
            vector<int> new_cost = cost;

            for (auto& flights : flights)
            {
                int from  = flights[0];
                int to    = flights[1];
                int price = flights[2];

                if (cost[from] == INT_MAX)
                    continue;

                if (cost[from] + price < new_cost[to])
                    new_cost[to] = cost[from] + price;
            }

            cost = new_cost;
        }

        return cost[dst] == INT_MAX ? -1 : cost[dst];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 7.12% */
/* Space Beats: 5.12% */

/* Time  Complexity: O(E * k * log(V * k)) */
/* Space Complexity: O(V * k  +  E)        */
class Solution_Dijkstra_Like {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        vector<vector<vector<int>>> adj_list(n);

        /* Create an Adjacency List */
        for (const auto& flight : flights)
        {
            const int& from  = flight[0];
            const int& to    = flight[1];
            const int& price = flight[2];

            adj_list[from].push_back( {to, price} );
        }

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> queue;
        queue.push( {0, 0, src} ); // {cost, stops, node}

        vector<vector<int>> cost(n, vector<int>(k + 2, INT_MAX));
        cost[src][0] = 0;

        /* Dijkstra-like */
        while ( ! queue.empty())
        {
            vector<int> front = queue.top();
            queue.pop();

            int curr_cost  = front[0];
            int curr_stops = front[1];
            int curr_node  = front[2];

            if (curr_stops > k)
                continue;

            if (curr_cost > cost[curr_node][curr_stops])
                continue;

            for (const auto& neighbor : adj_list[curr_node])
            {
                int neighbor_node  = neighbor[0];
                int neighbor_price = neighbor[1];

                int new_cost  = curr_cost  + neighbor_price;
                int new_stops = curr_stops + 1;

                if (new_stops <= k + 1 && new_cost < cost[neighbor_node][new_stops])
                {
                    cost[neighbor_node][new_stops] = new_cost;
                    queue.push( {new_cost, new_stops, neighbor_node} );
                }
            }
        }

        int result = *min_element(cost[dst].begin(), cost[dst].end());

        return result == INT_MAX ? -1 : result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Shortest Path Faster Algorithm

*/

/* Time  Beats: 100.00% */
/* Space Beats:  19.12% */

/* Time  Complexity: O(E * K)     */
/* Space Complexity: O(E + V * K) */
class Solution_Shortest_Path_Faster_Algorithm {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        vector<int> cost(n, INT_MAX);
        cost[src] = 0;

        vector<vector<vector<int>>> adj_list(n);

        /* Create an Adjacency List */
        for (const auto& flight : flights)
        {
            const int& from  = flight[0];
            const int& to    = flight[1];
            const int& price = flight[2];

            adj_list[from].push_back( {to, price} );
        }

        queue<tuple<int, int, int>> queue;
        queue.push( {0, 0, src} );

        while ( ! queue.empty())
        {
            auto [curr_price, curr_stops, curr_node] = queue.front();
            queue.pop();

            if (curr_stops > k)
                continue;

            for (const auto& neighbor : adj_list[curr_node])
            {
                int neighbor_node  = neighbor[0];
                int neighbor_price = neighbor[1];

                int new_cost = curr_price + neighbor_price;

                if (new_cost < cost[neighbor_node])
                {
                    cost[neighbor_node] = new_cost;
                    queue.push( {new_cost, curr_stops+1, neighbor_node} );
                }
            }
        }

        return cost[dst] == INT_MAX ? -1 : cost[dst];
    }
};
