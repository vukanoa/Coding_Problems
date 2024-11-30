#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === HARD ===
    ============

    =================================
    2097) Valid Arrangements of Pairs
    =================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti,
    endi]. An arrangement of pairs is valid if for every index i where 1 <= i <
    pairs.length, we have endi-1 == starti.

    Return any valid arrangement of pairs.

    =====
    Note: The inputs will be generated such that there exists a valid
          arrangement of pairs.
    =====

    ===========================================================================
    FUNCTION: vector<vector<int>> validArrangement(vector<vector<int>>& pairs);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
    Output: [[11,9],[9,4],[4,5],[5,1]]
    Explanation:
    This is a valid arrangement since endi-1 always equals starti.
    end0 = 9 == 9 = start1
    end1 = 4 == 4 = start2
    end2 = 5 == 5 = start3

    --- Example 2 ---
    Input: pairs = [[1,3],[3,2],[2,1]]
    Output: [[1,3],[3,2],[2,1]]
    Explanation:
    This is a valid arrangement since endi-1 always equals starti.
    end0 = 3 == 3 = start1
    end1 = 2 == 2 = start2
    The arrangements [[2,1],[1,3],[3,2]] and [[3,2],[2,1],[1,3]] are also valid

    --- Example 3 ---
    Input: pairs = [[1,2],[1,3],[2,1]]
    Output: [[1,2],[2,1],[1,3]]
    Explanation:
    This is a valid arrangement since endi-1 always equals starti.
    end0 = 2 == 2 = start1
    end1 = 1 == 1 = start2


    *** Constraints ***
    1 <= pairs.length <= 10^5
    pairs[i].length == 2
    0 <= starti, endi <= 10^9
    starti != endi
    No two pairs are exactly the same.
    There exists a valid arrangement of pairs.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Hierholzer_Algorithm {
public:
    unordered_map<int, vector<int>> adj_list;
    unordered_map<int, int> net_outdegree; // net outnet_outdegree
    vector<int> reverse_euler_path;

    vector<vector<int>> validArrangement(vector<vector<int>>& pairs)
    {
        const int N = pairs.size();
        adj_list.reserve(N);
        net_outdegree.reserve(N);

        /* Builds an Adjacency_List, i.e. Graph */
        for (auto& edge: pairs)
        {
            int start = edge[0];
            int end   = edge[1];

            adj_list[start].push_back(end);
            net_outdegree[start]++;
            net_outdegree[end]--;
        }

        int i0 = net_outdegree.begin()->first;

        // Find start vertex for Euler path
        for (auto& [node, outdegree]: net_outdegree)
        {
            if (outdegree == 1)
            {
                i0 = node;
                break;
            }
        }

        euler(i0);

        vector<vector<int>> result;
        result.reserve(N);

        for (int i = reverse_euler_path.size()-2; i >= 0; i--)
            result.push_back({reverse_euler_path[i+1], reverse_euler_path[i]});

        return result;
    }

private:
    void euler(int curr_node)
    {
        vector<int> stack = {curr_node};

        while ( ! stack.empty())
        {
            curr_node = stack.back();

            if (adj_list[curr_node].empty())
            {
                reverse_euler_path.push_back(curr_node);
                stack.pop_back();
            }
            else
            {
                int next_node = adj_list[curr_node].back(); // Neighbor node
                adj_list[curr_node].pop_back();
                stack.push_back(next_node);
            }
        }
    }
};
