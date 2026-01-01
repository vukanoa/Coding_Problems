#include <iostream>
#include <unordered_map>
#include <vector>

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

/*
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
*/




/*
    ------------
    --- IDEA ---
    ------------

    It's very similar to "Clone Singly Linked List with Random Pointers".

    However, Graph is, obviously, a different Data Structure, so the code
    differs as well.

    1. Do a DFS on a give Graph
    2. While performing a DFS, make a copy of the current node and push current
       original node, as a key in the Hash Map and copied node as a value.
    3. When ou finish, you must link copied nodes.
    4. Iterate through entires in the Hash Map and do this:
           Node* original  = entry.first;
           Node* copy_node = entry.second;

           // This is the CRUX
           for (int i = 0; i < original->neighbors.size(); i++)
               copy_node->neighbors.push_back(umap[original->neighbors[i]]);

*/

/* Time  Beats: 100% */
/* Space Beats: 67.55% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    Node* cloneGraph(Node* node)
    {
        if (node == nullptr)
            return nullptr;

        std::unordered_map<Node*, Node*> umap;

        // Create Clones
        clone_graph(umap, node);

        // Link all Clones
        for (auto& entry : umap)
        {
            Node* original  = entry.first;
            Node* copy_node = entry.second;

            for (int i = 0; i < original->neighbors.size(); i++)
                copy_node->neighbors.push_back(umap[original->neighbors[i]]);
        }

        return umap[node];
    }

    void clone_graph(std::unordered_map<Node*, Node*>& umap, Node* curr_node)
    {
        // If it was already processed
        if (umap.find(curr_node) != umap.end())
            return;

        Node* copy_node = new Node(curr_node->val); // Make a Copy Node
        umap.insert({curr_node, copy_node});        // Insert in Hash Map

        for (int i = 0; i < curr_node->neighbors.size(); i++)
            clone_graph(umap, curr_node->neighbors[i]);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, implemented differently. This one is a bit easier to read,
    maybe.

*/

/* Time  Beats: 75.96% */
/* Space Beats: 79.71% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    Node* cloneGraph(Node* node)
    {
        if (!node)
            return nullptr;

        std::unordered_map<Node*, Node*> umap;

        // Create Clones
        clone_graph(node, nullptr, umap);

        // Link all Clones
        for (auto& entry : umap)
        {
            for (Node*& nei : entry.first->neighbors)
                entry.second->neighbors.push_back(umap[nei]);
        }

        return umap[node];
    }

private:
    void clone_graph(Node* node, Node* prev, std::unordered_map<Node*, Node*>& umap)
    {
        if (umap.find(node) == umap.end())
        {
            Node* copy = new Node(node->val);
            umap.insert({node, copy});
        }

        for (Node*& nei : node->neighbors)
        {
            if (nei == prev || umap.count(nei))
                continue;

            clone_graph(nei, node, umap);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is a bit different than the two above. We are pushing nodes as
    we're visited them.

    Take one example and go through the code and it'll be clear. Especially if
    you get the idea behind the above two Solutions.

*/

/* Time  Beats: 75.96% */
/* Space Beats: 21.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_3 {
public:
    Node* cloneGraph(Node* node)
    {
        if (!node)
            return nullptr;

        std::unordered_map<Node*, Node*> old_to_new;

        return dfs(node, old_to_new);
    }

private:
    Node* dfs(Node* node, std::unordered_map<Node*, Node*>& old_to_new)
    {
        if (old_to_new.count(node)) // If "node" exists in the HashMap
            return old_to_new[node];

        Node* copy_node = new Node(node->val);
        old_to_new.insert({node, copy_node});

        for (Node*& nei : node->neighbors)
            copy_node->neighbors.push_back(dfs(nei, old_to_new));

        return copy_node;
    }
};
