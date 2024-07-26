#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================================
    1334) Find the City With the Smallest Number of Neighbors at a Threshold Distance
    =================================================================================

    ============
    Description:
    ============

    here are n cities numbered from 0 to n-1. Given the array edges where
    edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted
    edge between cities fromi and toi, and given the integer distanceThreshold.

    Return the city with the smallest number of cities that are reachable
    through some path and whose distance is at most distanceThreshold, If there
    are multiple such cities, return the city with the greatest number.

    Notice that the distance of a path connecting cities i and j is equal to
    the sum of the edges' weights along that path.

    ====================================================================================
    FUNCTION: int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold); 
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
    Output: 3
    Explanation: The figure above describes the graph. 
    The neighboring cities at a distanceThreshold = 4 for each city are:
    City 0 -> [City 1, City 2] 
    City 1 -> [City 0, City 2, City 3] 
    City 2 -> [City 0, City 1, City 3] 
    City 3 -> [City 1, City 2] 
    Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we
    have to return city 3 since it has the greatest number.


    --- Example 2 ---
    Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
    Output: 0
    Explanation: The figure above describes the graph. 
    The neighboring cities at a distanceThreshold = 2 for each city are:
    City 0 -> [City 1] 
    City 1 -> [City 0, City 4] 
    City 2 -> [City 3, City 4] 
    City 3 -> [City 2, City 4]
    City 4 -> [City 1, City 2, City 3] 
    The city 0 has 1 neighboring city at a distanceThreshold = 2.



    *** Constraints ***
    2 <= n <= 100
    1 <= edges.length <= n * (n - 1) / 2
    edges[i].length == 3
    0 <= fromi < toi < n
    1 <= weighti, distanceThreshold <= 10^4
    All pairs (fromi, toi) are distinct.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.94% */
/* Space Beats: 14.65% */

/* Time  Complexity: O(n^3 * logn) */
/* Space Complexity: O(n^2)        */
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        vector<vector<pair<int, int>>> adj_list(n);

        for (auto& edge : edges)
        {
            int v1       = edge[0];
            int v2       = edge[1];
            int distance = edge[2];

            adj_list[v1].push_back({v2, distance});
            adj_list[v2].push_back({v1, distance});
        }

        int result = -1;
        int min_count = INT_MAX;

        for (int src = 0; src < n; src++)
        {
            int count = dijkstra(adj_list, src, distanceThreshold);

            if (count <= min_count)
            {
                result = src;
                min_count = count;
            }
        }

        return result;
    }

private:
    int dijkstra(vector<vector<pair<int, int>>>& adj_list, int& src, int& distanceThreshold)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
        vector<int> distances(adj_list.size(), INT_MAX);

        min_heap.push({0, src});
        distances[src] = 0;

        while (!min_heap.empty())
        {
            int distance = min_heap.top().first;
            int node     = min_heap.top().second;
            min_heap.pop();

            if (distance > distances[node])
                continue;

            for (auto& entry : adj_list[node])
            {
                int neighbor = entry.first;
                int weight   = entry.second;

                int new_distance = distance + weight;

                if (new_distance <= distanceThreshold && new_distance < distances[neighbor])
                {
                    distances[neighbor] = new_distance;
                    min_heap.push({new_distance, neighbor});
                }
            }
        }

        int count = 0;
        for (int d : distances)
        {
            if (d <= distanceThreshold)
                count++;
        }

        return count - 1;
    }
};
