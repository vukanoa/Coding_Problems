#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    2359) Find Closest Node To Given Two Nodes
    ==========================================

    ============
    Description:
    ============

    You are given a directed graph of n nodes numbered from 0 to n - 1, where
    each node has at most one outgoing edge.

    The graph is represented with a given 0-indexed array edges of size n,
    indicating that there is a directed edge from node i to node edges[i]. If
    there is no outgoing edge from i, then edges[i] == -1.

    You are also given two integers node1 and node2.

    Return the index of the node that can be reached from both node1 and node2,
    such that the maximum between the distance from node1 to that node, and
    from node2 to that node is minimized. If there are multiple answers, return
    the node with the smallest index, and if no possible answer exists, return
    -1.

    Note that edges may contain cycles.

    ===========================================================================
    FUNCTION: int closestMeetingNode(vector<int>& edges, int node1, int node2);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        1 ----> 2 <---- 0
                |
                |
                v
                3

    Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
    Output: 2
    Explanation: The distance from node 0 to node 2 is 1, and the distance from
                 node 1 to node 2 is 1.  The maximum of those two distances is
                 1. It can be proven that we cannot get a node with a smaller
                 maximum distance than 1, so we return node 2.



    --- Example 2 ---

        1 <---- 0
        |
        |
        v
        2
    Input: edges = [1,2,-1], node1 = 0, node2 = 2
    Output: 2
    Explanation: The distance from node 0 to node 2 is 2, and the distance from
                 node 2 to itself is 0.  The maximum of those two distances is
                 2. It can be proven that we cannot get a node with a smaller
                 maximum distance than 2, so we return node 2.


    *** Constraints ***
    n == edges.length
    2 <= n <= 10^5
    -1 <= edges[i] < n
    edges[i] != i
    0 <= node1, node2 < n

*/

/*
    ------------
    --- IDEA ---
    ------------

    The hardest part abou this problem is to understand what they are asking us
    to do.

    Specifically, this part of the Description:

        "Return the index of the node that can be reached from both node1 and
        node2, such that the maximum between the distance from node1 to that
        node, and from node2 to that node is minimized. If there are multiple
        answers, return the node with the smallest index, and if no possible
        answer exists, return -1."

    What they are trying to say is that, from node1 you can reach multiple
    nodes.

    In this example:
            edges = [2, 2, 3, 4, 2]
                     0  1  2  3  4

            node1 = 0
            node2 = 3

                                  0
                                  |
                                  v
                         1 -----> 2 <----|
                            ______|      |
                            |            |
                            v            |
                            3 ----> 4 ----


    From node1, you can reach: 0(self), 2, 3, 4

    From node2, you can reach: 3(self), 4, 2

    So, what they are trying to say is: All the nodes which you can reach from
    both node1 and node2, take the greater distance(maximum) and out of all
    those nodes which you've taken the maximum distance, take the minimum.

    Let me simplify it even more:

    From node1:
        can reach : distance
               0  :   0
               2  :   1
               3  :   2
               4  :   3


    From node2:
        can reach : distance
               3  :   0
               4  :   1
               2  :   2

    Now, let's say, for example, that we are checking if node 4 is reachable
    from both node1 and node2.

    Since we can find it present in both maps, we can conclude that it is. Now
    take the greater distance of the two.

    Distance of the node 4 from node1(0) is 3.

    On the other hand, the distance of node 4 from node2(3) is 1.

    So, which distance is greater? 3 or 1?
    It's 3.

    So currently, the minimum distance of all the max distances of the nodes
    we can both reach from node1 and node2 is 3.

    However, let's check other nodes that are reachable from both node1 and
    node2.

    Node 3's distance from node1(0) is 2, and from node2(3) is 0.

    Greater distance is 2.

    Is this "Greater distance" of value 2 LESS than the current MINIMUM(which
    at this point is 3)?
    It is, okay, then update.

    There is one more node that is reachable from both sources and that is node
    2.

    Node 2's distance from node1(0) is 1 and from node2(3) is 2.
    Greater distance is 2.

    However this time we don't have to update since "Greater distance" is not
    LESS than the current MINIMUM(which is 2).

    At the end, we just return MINIMUM(2 in this case).

*/

/* Time  Beats: 96.40% */
/* Space Beats: 78.78% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2)
    {
        std::vector<int> node1_dist = BFS(node1, edges);
        std::vector<int> node2_dist = BFS(node2, edges);

        int result_node = -1;
        int min_dist = INT_MAX;

        for (int i = 0; i < edges.size(); i++)
        {
            int curr_max_dist = std::max(node1_dist[i], node2_dist[i]);

            if (curr_max_dist < min_dist)
            {
                min_dist = curr_max_dist;
                result_node = i;
            }
        }

        return result_node;
    }

private:
    std::vector<int> BFS(int src, std::vector<int>& edges)
    {
        std::vector<int> distance(edges.size(), INT_MAX);
        std::queue<int> queue;
        queue.push(src);
        distance[src] = 0;

        while (!queue.empty())
        {
            int node = queue.front();
            queue.pop();

            if (edges[node] != -1 && distance[edges[node]] == INT_MAX)
            {
                queue.push(edges[node]);
                distance[edges[node]] = distance[node] + 1;
            }
        }

        return distance;
    }
};
