/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    133) Clone Graph
    ===========================

    ============
    Description:
    ============

    Given a reference of a node in a connected undirected graph.

    Return a deep copy (clone) of the graph.

    Each node in the graph contains a value (int) and a list (List[Node]) of
    its neighbors.

        class Node {
        public:
            int val;
            vector<Node*> neighbors;
        };


    Test case format:

    For simplicity, each node's value is the same as the node's index
    (1-indexed). For example, the first node with val == 1, the second node
    with val == 2, and so on. The graph is represented in the test case using
    an adjacency list.

    An adjacency list is a collection of unordered lists used to represent a
    finite graph. Each list describes the set of neighbors of a node in the
    graph.

    The given node will always be the first node with val = 1. You must return
    the copy of the given node as a reference to the cloned graph.

    =======================================
    FUNCTION: Node* cloneGraph(Node* node);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
    Output: [[2,4],[1,3],[2,4],[1,3]]
    Explanation: There are 4 nodes in the graph.
    1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
    2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
    3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
    4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).


    --- Example 2 ---
    Input: adjList = [[]]
    Output: [[]]
    Explanation: Note that the input contains one empty list. The graph
    consists of only one node with val = 1 and it does not have any neighbors.


    --- Example 3 ---
    Input: adjList = []
    Output: []
    Explanation: This an empty graph, it does not have any nodes.


    *** Constraints ***
    The number of nodes in the graph is in the range [0, 100].
    1 <= Node.val <= 100
    Node.val is unique for each node.
    There are no repeated edges and no self-loops in the graph.
    The Graph is connected and all nodes can be visited starting from the given
    node.

*/

#include <unordered_map>
#include <vector>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }
    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    It's very similar to "Clone Singly Linked List with Random Pointers".

    However, Graph is, obviously, a different Data Structure, so the code
    differs as well.

    1. Do a DFS on a given Graph and clone vertices, i.e. populate Hash Map.

    2. While performing a DFS, make a copy of the current node and push current
       original node as a key in the Hash Map and copied node as a value.

    3. Link new, cloned/copied, vertices.

    4. Return the clone of the Input "node".

*/

/* Time  Beats: 67.66% */
/* Space Beats: 45.26% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V)     */
class Solution {
public:
    Node* cloneGraph(Node* node)
    {
        unordered_map<Node*, Node*> umap;

        /* Clone vertices of Graph, i.e. Populate Hash Map */
        dfs(node, umap);

        /* Link all Clones(copied vertices) */
        for (auto& [orig, copy] : umap)
        {
            for (const auto& orig_nei : orig->neighbors)
                copy->neighbors.push_back(umap[orig_nei]);
        }

        return umap[node];
    }

private:
    // TC: O(V + E) --> O(V + E)
    // SC: O(V + V) --> O(V)      // Recursion of depth V + Hash Map of V size
    void dfs(Node* node, unordered_map<Node*, Node*>& umap)
    {
        if ( ! node)
            return;

        Node* copy = new Node(node->val);
        umap.insert( {node, copy} );

        for (const auto& nei : node->neighbors)
        {
            if (umap.count(nei))
                continue;

            dfs(nei, umap);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Single Pass implementation.

*/

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V)     */

/* Time  Beats: 34.07% */
/* Space Beats: 45.26% */
class Solution_Single_Pass {
public:
    Node* cloneGraph(Node* node)
    {
        unordered_map<Node*, Node*> orig_to_copy;
        orig_to_copy.insert( {nullptr, nullptr} );

        return dfs(node, orig_to_copy);
    }

private:
    Node* dfs(Node* node, unordered_map<Node*, Node*>& orig_to_copy)
    {
        if (orig_to_copy.count(node))
            return orig_to_copy[node];

        /* Create a Clone */
        Node* copy = new Node(node->val);
        orig_to_copy[node] = copy;

        /* Link Neighbors */
        for (Node* nei : node->neighbors)
            copy->neighbors.push_back(dfs(nei, orig_to_copy));

        return copy;
    }
};
