/*
    ============
    === HARD ===
    ============

    ====================================
    2509) Cycle Length Queries in a Tree
    ====================================

    ============
    Description:
    ============

    You are given an integer n. There is a complete binary tree with 2n - 1
    nodes. The root of that tree is the node with the value 1, and every node
    with a value val in the range [1, 2n - 1 - 1] has two children where:

        + The left node has the value 2 * val, and
        + The right node has the value 2 * val + 1.

    You are also given a 2D integer array queries of length m, where queries[i]
    = [ai, bi]. For each query, solve the following problem:

        + Add an edge between the nodes with values ai and bi.
        + Find the length of the cycle in the graph.
        + Remove the added edge between nodes with values ai and bi.

    Note that:

        + A cycle is a path that starts and ends at the same node, and each
          edge in the path is visited only once.

        + The length of a cycle is the number of edges visited in the cycle.

        + There could be multiple edges between two nodes in the tree after
          adding the edge of the query.

    Return an array answer of length m where answer[i] is the answer to the ith
    query.

    ==============================================================================
    FUNCTION: vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, queries = [[5,3],[4,7],[2,3]]
    Output: [4,5,3]
    Explanation: The diagrams above show the tree of 23 - 1 nodes. Nodes colored in red describe the nodes in the cycle after adding the edge.
    - After adding the edge between nodes 3 and 5, the graph contains a cycle of nodes [5,2,1,3]. Thus answer to the first query is 4. We delete the added edge and process the next query.
    - After adding the edge between nodes 4 and 7, the graph contains a cycle of nodes [4,2,1,3,7]. Thus answer to the second query is 5. We delete the added edge and process the next query.
    - After adding the edge between nodes 2 and 3, the graph contains a cycle of nodes [2,1,3]. Thus answer to the third query is 3. We delete the added edge.

    --- Example 2 ---
    Input: n = 2, queries = [[1,2]]
    Output: [2]
    Explanation: The diagram above shows the tree of 22 - 1 nodes. Nodes colored in red describe the nodes in the cycle after adding the edge.
    - After adding the edge between nodes 1 and 2, the graph contains a cycle of nodes [2,1]. Thus answer for the first query is 2. We delete the added edge.


    *** Constraints ***
    2 <= n <= 30
    m == queries.length
    1 <= m <= 10^5
    queries[i].length == 2
    1 <= ai, bi <= 2n - 1
    ai != bi

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 68.98% */
/* Space Beats: 96.26% */

/* Time  Complexity: O(Q * logN) */
/* Space Complexity: O(Q)        */
class Solution {
public:
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries)
    {
        const int Q = queries.size();
        
        vector<int> answer;
        answer.reserve(Q); // To prevent repeated reallocations
        
        for (auto& query : queries)
        {
            int a = query[0];
            int b = query[1];

            int level_a = get_level((1 << (32 - __builtin_clz(a)))) - 1;
            int level_b = get_level((1 << (32 - __builtin_clz(b)))) - 1;

            if (level_a > level_b)
            {
                swap(level_a, level_b);
                swap(a, b);
            }

            int diff = level_b - level_a;
            while (diff > 0)
            {
                b /= 2;
                --diff;
            }
            
            int level_LCA = level_a;
            while (a != b)
            {
                --level_LCA;

                a /= 2;
                b /= 2;
            }

            answer.push_back(1 + (level_a - level_LCA) +
                                 (level_b - level_LCA));
        }

        return answer;
    }

private:
    // 0-based "indexing" of levels, i.e. root_node(i.e. 1) is at level 0.
    int get_level(int node)
    {
        int level = 0;
        
        while (node > 1)
        {
            node /= 2;
            ++level;
        }

        return level;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Written in a MUCH more simple way, although I still kind of prefer the
    above one.

*/

/* Time  Complexity: O(Q * logN) */
/* Space Complexity: O(Q)        */
class Solution_Elegant {
public:
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries)
    {
        const int Q = queries.size();
        vector<int> answer(Q, 0);

        for (int idx = 0; idx < Q; idx++)
        {
            int a = queries[idx][0];
            int b = queries[idx][1];

            int edges_between_a_and_b = 0;

            while (a != b)
            {
                if (a > b)
                    a /= 2;
                else
                    b /= 2;

                ++edges_between_a_and_b;
            }

            // +1 because of the direct edge we've just introduced with the
            // current query
            answer[idx] = edges_between_a_and_b + 1;
        }

        return answer;
    }
};
