/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    2467) Most Profitable Path in a Tree
    ====================================

    ============
    Description:
    ============

    There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at
    node 0. You are given a 2D integer array edges of length n - 1 where
    edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi
    in the tree.

    At every node i, there is a gate. You are also given an array of even
    integers amount, where amount[i] represents:

        + the price needed to open the gate at node i, if amount[i] is
          negative, or,

        + the cash reward obtained on opening the gate at node i, otherwise.

    The game goes on as follows:

        + Initially, Alice is at node 0 and Bob is at node bob.

        + At every second, Alice and Bob each move to an adjacent node. Alice
          moves towards some leaf node, while Bob moves towards node 0.

        + For every node along their path, Alice and Bob either spend money to
          open the gate at that node, or accept the reward. Note that:

            + If the gate is already open, no price will be required, nor will
              there be any cash reward.

            + If Alice and Bob reach the node simultaneously, they share the
              price/reward for opening the gate there. In other words, if the
              price to open the gate is c, then both Alice and Bob pay c / 2
              each. Similarly, if the reward at the gate is c, both of them
              receive c / 2 each.

        + If Alice reaches a leaf node, she stops moving. Similarly, if Bob
          reaches node 0, he stops moving. Note that these events are
          independent of each other.

    Return the maximum net income Alice can have if she travels towards the
    optimal leaf node.

    ===========================================================================================
    FUNCTION: int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
    Output: 6
    Explanation:
    The above diagram represents the given tree. The game goes as follows:
    - Alice is initially on node 0, Bob on node 3. They open the gates of their respective nodes.
      Alice's net income is now -2.
    - Both Alice and Bob move to node 1.
      Since they reach here simultaneously, they open the gate together and share the reward.
      Alice's net income becomes -2 + (4 / 2) = 0.
    - Alice moves on to node 3. Since Bob already opened its gate, Alice's income remains unchanged.
      Bob moves on to node 0, and stops moving.
    - Alice moves on to node 4 and opens the gate there. Her net income becomes 0 + 6 = 6.
    Now, neither Alice nor Bob can make any further moves, and the game ends.
    It is not possible for Alice to get a higher net income.

    --- Example 2 ---
    Input: edges = [[0,1]], bob = 1, amount = [-7280,2350]
    Output: -7280
    Explanation:
    Alice follows the path 0->1 whereas Bob follows the path 1->0.
    Thus, Alice opens the gate at node 0 only. Hence, her net income is -7280.


    *** Constraints ***
    2 <= n <= 10^5
    edges.length == n - 1
    edges[i].length == 2
    0 <= ai, bi < n
    ai != bi
    edges represents a valid tree.
    1 <= bob < n
    amount.length == n
    amount[i] is an even integer in the range [-10^4, 10^4].

*/

#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.38% */
/* Space Beats: 73.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_DFS_twice {
private:
    unordered_map<int, int> bob_path_time;
    vector<bool> opened;
    vector<vector<int>> adj_list;
    int max_income = INT_MIN;

public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount)
    {
        const int N = amount.size();

        adj_list.resize(N);
        for (const auto& edge : edges)
        {
            adj_list[edge[0]].push_back(edge[1]);
            adj_list[edge[1]].push_back(edge[0]);
        }

        opened.assign(N, false);
        find_bob_path(bob, 0);

        opened.assign(N, false);
        find_alice_path(0, 0, 0, amount);

        return max_income;
    }

private:
    bool find_bob_path(int curr_node, int time)
    {
        bob_path_time[curr_node] = time;
        opened[curr_node]  = true;

        if (curr_node == 0) // Bob reached its destination
            return true;

        for (const int& neighbor : adj_list[curr_node])
        {
            if ( ! opened[neighbor] && find_bob_path(neighbor, time + 1))
                return true;
        }

        // If node 0 isn't reached, remove current node from path
        bob_path_time.erase(curr_node);

        return false;
    }

    void find_alice_path(int curr_node, int time, int income, vector<int>& amount)
    {
        opened[curr_node] = true;

        // Alice reaches the node first
        if (bob_path_time.find(curr_node) == bob_path_time.end() || time < bob_path_time[curr_node])
            income += amount[curr_node];
        else if (time == bob_path_time[curr_node]) // Alice and Bob reach the node at the same time
            income += (amount[curr_node] / 2);

        // Update max value if current node is a new leaf
        if (adj_list[curr_node].size() == 1 && curr_node != 0)
            max_income = max(max_income, income);

        // Traverse through unvisited nodes
        for (const int& neighbor : adj_list[curr_node])
        {
            if ( ! opened[neighbor])
                find_alice_path(neighbor, time + 1, income, amount);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 70.88% */
/* Space Beats: 55.68% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_DFS_once {
private:
    vector<vector<int>> adj_list;
    vector<int> distanceFromBob;
    int n;

public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount)
    {
        n = amount.size();
        adj_list.resize(n, vector<int>());

        for (vector<int> edge : edges)
        {
            adj_list[edge[0]].push_back(edge[1]);
            adj_list[edge[1]].push_back(edge[0]);
        }
        distanceFromBob.resize(n);

        return find_paths(0, 0, 0, bob, amount);
    }

private:
    int find_paths(int curr_node, int prev_node, int time, int bob, vector<int>& amount)
    {
        int max_income = 0;
        int max_child = INT_MIN;

        // Find the node distances from Bob
        if (curr_node == bob)
            distanceFromBob[curr_node] = 0;
        else
            distanceFromBob[curr_node] = n;

        for (int adjacentNode : adj_list[curr_node])
        {
            if (adjacentNode != prev_node)
            {
                max_child = max(max_child, find_paths(adjacentNode, curr_node, time + 1, bob, amount));

                distanceFromBob[curr_node] = min(distanceFromBob[curr_node], distanceFromBob[adjacentNode] + 1);
            }
        }

        // Alice reaches the node first
        if (distanceFromBob[curr_node] > time)
        {
            max_income += amount[curr_node];
        }
        else if (distanceFromBob[curr_node] == time) // Alice and Bob reach the node at the same time
        {
            max_income += amount[curr_node] / 2;
        }

        // Return max income of Leaf-node
        if (max_child == INT_MIN)
            return max_income;

        return max_income + max_child;
    }
};
