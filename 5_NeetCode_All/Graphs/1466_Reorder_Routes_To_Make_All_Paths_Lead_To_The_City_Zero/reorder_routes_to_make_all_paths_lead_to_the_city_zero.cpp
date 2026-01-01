#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================================
    1466) Reorder Routes to Make All Paths Lead to the City Zero
    ============================================================

    ============
    Description:
    ============

    There are n cities numbered from 0 to n - 1 and n - 1 roads such that there
    is only one way to travel between two different cities (this network form a
    tree). Last year, The ministry of transport decided to orient the roads in
    one direction because they are too narrow.

    Roads are represented by connections where connections[i] = [ai, bi]
    represents a road from city ai to city bi.

    This year, there will be a big event in the capital (city 0), and many
    people want to travel to this city.

    Your task consists of reorienting some roads such that each city can visit
    the city 0. Return the minimum number of edges changed.

    It's guaranteed that each city can reach city 0 after reorder.

    ==================================================================
    FUNCTION: int minReorder(int n, vector<vector<int>>& connections);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
    Output: 3
    Explanation: Change the direction of edges show in red such that each node
    can reach the node 0 (capital).


    --- Example 2 ---
    Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
    Output: 2
    Explanation: Change the direction of edges show in red such that each node
    can reach the node 0 (capital).


    --- Example 3 ---
    Input: n = 3, connections = [[1,0],[2,0]]
    Output: 0

    *** Constraints ***
    2 <= n <= 5 * 10^4
    connections.length == n - 1
    connections[i].length == 2
    0 <= ai, bi <= n - 1
    ai != bi

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO (This one is very very unintuitive, please check the 2nd one below)

*/

/* Time  Beats: 34.40% */
/* Space Beats: 18.97% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_UNINTUITIVE {
public:

    int minReorder(int n, std::vector<std::vector<int>>& connections)
    {
        int s = connections.size();
        std::unordered_map<int, std::vector<int>> adj;
        std::unordered_set<int> visited;

        for(int i = 0; i < s; i++)
        {
            adj[connections[i][1]].push_back(+connections[i][0]);
            adj[connections[i][0]].push_back(-connections[i][1]);
        }

        int changes = 0;
        dfs(adj, visited, changes, 0);

        return changes;
    }

private:
    void dfs(std::unordered_map<int, std::vector<int>>& adj,
             std::unordered_set<int>& visited,
             int& changes,
             int curr_city)
    {
        visited.insert(curr_city);

        for(int& neighbor_city : adj[curr_city])
        {
            if(neighbor_city >= 0)
            {
                if(visited.find(neighbor_city) == visited.end()) // Not visited
                    dfs(adj, visited, changes, neighbor_city);
            }
            else
            {
                neighbor_city = std::abs(neighbor_city);

                if(visited.find(neighbor_city) == visited.end()) // Not visited
                {
                    changes++;
                    dfs(adj, visited, changes, neighbor_city);
                }
            }
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    BFS.

*/

/* Time  Beats: 44.16% */
/* Space Beats: 38.45% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_BFS {
public:
    int minReorder(int n, std::vector<std::vector<int>>& connections)
    {
        std::vector<std::vector<int>> road(n);
        std::vector<std::vector<int>> graph(n);

        for(auto conn : connections)
        {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);

            road[conn[0]].push_back(conn[1]);
        }

        std::queue<int> queue;
        queue.push(0);

        int changes = 0;
        std::vector<bool> visited(n, 0);

        while(!queue.empty())
        {
            int city = queue.front();
            queue.pop();

            visited[city] = true;

            for(auto neighbor : graph[city])
            {
                if(!visited[neighbor])
                {
                    queue.push(neighbor);
                    for(auto j : road[neighbor])
                    {
                        if(j == city)
                            changes--;
                    }

                    changes++;
                }
            }
        }

        return changes;
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  5.35% */
/* Space Beats: 16.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS {
public:
    int minReorder(int n, std::vector<std::vector<int>>& connections)
    {
        int result = 0;

        std::unordered_map<int, std::vector<int>> umap;
        std::unordered_map<int, bool> visited;

        for(auto conn : connections)
        {
            umap[conn[1]].push_back(+conn[0]);
            umap[conn[0]].push_back(-conn[1]);
        }

        dfs(umap, visited, result, 0);

        return result;
    }

private:
    void dfs(std::unordered_map<int, std::vector<int>>& umap,
             std::unordered_map<int, bool>& visited,
             int& result,
             int city)
    {
        visited[city] = true;

        for(auto neighbor : umap[city])
        {
            if (!visited[std::abs(neighbor)])
            {
                if (neighbor < 0)
                {
                    result++;
                    dfs(umap, visited, result, std::abs(neighbor));
                }
                else
                    dfs(umap, visited, result, neighbor);
            }
        }
    }
};


int
main()
{
    Solution_UNINTUITIVE sol_unintuitive;
    Solution_BFS         sol_bfs;
    Solution_DFS         sol_dfs;

    /* Example 1 */
    // std::vector<std::vector<int>> connections = {{1,0}, {1,2}, {3,2}, {3,4}};
    // int n = 5;

    /* Example 2 */
    // std::vector<std::vector<int>> connections = {{0,1}, {1,3}, {2,3}, {4,0}, {4,5}};
    // int n = 6;

    /* Example 3 */
    // std::vector<std::vector<int>> connections = {{1,0}, {2,0}};
    // int n = 5;

    /* Example 4 */
    std::vector<std::vector<int>> connections = {{0,3},{3,2},{3,4},{3,5},{6,4},{6,1},{7,0}};
    int n = 8;

    /* Example 4 */
    // std::vector<std::vector<int>> connections = {{4,3},{2,3},{1,2},{1,0}};
    // int n = 5;


    std::cout << "\n\t==============================================================";
    std::cout << "\n\t=== REORDER ROUTES TO MAKE ALL PATHS LEAD TO THE CITY ZERO ===";
    std::cout << "\n\t==============================================================\n";


    /* Write Input */
    std::cout << "\n\tn: " << n;

    bool first = true;
    std::cout << "\n\tConnections: [";
    for (auto x: connections)
    {
        if (!first)
            std::cout << ", ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            std::cout << xx;
            first_first = false;
        }
        std::cout << "]";

        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // int  result = sol_unintuitive.minReorder(n, connections);
    // int  result = sol_bfs.minReorder(n, connections);
    int  result = sol_dfs.minReorder(n, connections);


    /* Write Output */
    std::cout << "\n\tResult: " << result;

    std::cout << "\n\n";
    return 0;
}
