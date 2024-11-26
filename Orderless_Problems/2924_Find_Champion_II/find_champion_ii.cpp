#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2924) Find Champion II
    ===========================

    ============
    Description:
    ============


    There are n teams numbered from 0 to n - 1 in a tournament; each team is
    also a node in a DAG.

    You are given the integer n and a 0-indexed 2D integer array edges of
    length m representing the DAG, where edges[i] = [ui, vi] indicates that
    there is a directed edge from team ui to team vi in the graph.

    A directed edge from a to b in the graph means that team a is stronger than
    team b and team b is weaker than team a.

    Team a will be the champion of the tournament if there is no team b that is
    stronger than team a.

    Return the team that will be the champion of the tournament if there is a
    unique champion, otherwise, return -1.

    =====
    Note: + A cycle is a series of nodes a1, a2, ..., an, an+1 such that node a1 is
          the same node as node an+1, the nodes a1, a2, ..., an are distinct, and
          there is a directed edge from the node ai to node ai+1 for every i in the
          range [1, n].

          + A DAG is a directed graph that does not have any cycle.
    =====

    ==============================================================
    FUNCTION: int findChampion(int n, vector<vector<int>>& edges);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1],[1,2]]
    Output: 0
    Explanation: Team 1 is weaker than team 0. Team 2 is weaker than team 1. So
                 the champion is team 0.


    --- Example 2 ---
    Input: n = 4, edges = [[0,2],[1,3],[1,2]]
    Output: -1
    Explanation: Team 2 is weaker than team 0 and team 1. Team 3 is weaker than
                 team 1. But team 1 and team 0 are not weaker than any other
                 teams. So the answer is -1.


    *** Constraints ***
    1 <= n <= 100
    m == edges.length
    0 <= m <= n * (n - 1) / 2
    edges[i].length == 2
    0 <= edge[i][j] <= n - 1
    edges[i][0] != edges[i][1]
    The input is generated such that if team a is stronger than team b, team b is not stronger than team a.
    The input is generated such that if team a is stronger than team b and team b is stronger than team c, then team a is stronger than team c.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    1. Intuition

        This one is pretty damn simple if you can resist the overwhelming
        amount of description. If you don't get scared, it's shockingly easy.

        Since STRONG node is one(edge[0]) that POINTS to the other
        one(edge[1]), then all we need to know is - Which node does NOT appear
        as the weak node anywhere in the list of edges.

        In other, more technical words, we need to count how many nodes have an
        INDEGREE of 0.

        To be able to return that node, there MUST be ONLY ONE such node. If
        there is more than 1, we return -1(to indicate that there is no ONE
        Champion).


    2. Implementation:

        We'll create a vector called "indegree" of size n+1, with 0s as default
        values.

        num_of_strong_nodes is initialized with n(You'll see the point of it).

        We'll go through the edges and we'll increment the frequency of a node
        that is WEAKER in the current edge, i.e. indegree[edge[1]]++. That way
        we're "marking" the weaker node as certainly NOT the Champion, in each
        iteration.

        BEFORE doing that, if indegree of current edge[1] is 0(indegree of the
        WEAKER node is 0), then we want to DECREMENT num_of_strong_nodes by 1,
        indicating that there is one less element that is suitable to be the
        absolute winner, i.e. the Champion.

        Once we're finished, we can immediately check if there is EXACTLY 1
        element in num_of_strong_nodes.
        If there is NOT EXACTLY 1, we return -1 because there are either 0
        winners(which is impossible) or more than one winner, which is
        prohibited.

        However, if there is indeed EXACTLY one winner, then we return that
        specific node.

        Note that, since we have a vector "indegree" of size n:

            Example:
                n = 4
                indegree = [0, 0, 0, 0]
                            0  1  2  3

                If, at the end, there happens to be EXACTLY ONE winner, then
                the node that is the winner is equivalent to the INDEX in
                "indegree" vector that has the value of 0.

                (Read this again, it sounds complicated, but it's not that deep
                 You'll understand it if you read it one more time)

                That's why we're returning the INDEX of the element, from
                vector "indegree", that appeared the LEAST amount of times(i.e.
                0 times).

                INDEX of the element, from vector "indegree", is EQUIVALENT to
                the NODE from the graph. There are n nodes, from [0, n-1].

                It is GUARANTEED, that if there is EXACTLY ONE winner, the
                amount of times it appeared, as a WEAKER node in the edge, is
                CERTAINLY 0.

                Otherwise we would've already return -1, because
                num_of_strong_nodes would NOT be equal to EXACTLY one.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  66.24% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V)     */
class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges)
    {
        if (n == 1) // The Solution works for the Edge case as well, but w/e
            return 0;

        vector<int> indegree(n+1, 0);
        int num_of_strong_nodes = n; // Every node is considered "weak" at the beginning

        for (const vector<int>& edge : edges)
        {
            if (indegree[edge[1]] == 0)
                num_of_strong_nodes--;

            indegree[edge[1]]++;
        }

        if (num_of_strong_nodes != 1)
            return -1;

        int no_indegree_node_idx = min_element(indegree.begin(), indegree.end()) - indegree.begin();
        return no_indegree_node_idx; // It's "idx" from indegree vec, but it's actually just a node with that number
    }
};
