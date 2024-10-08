#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    1361) Validate Binary Tree Nodes
    ================================

    ============
    Description:
    ============

    You have n binary tree nodes numbered from 0 to n - 1 where node i has two
    children leftChild[i] and rightChild[i], return true if and only if all the
    given nodes form exactly one valid binary tree.

    If node i has no left child then leftChild[i] will equal -1, similarly for
    the right child.

    =====
    Note: Note that the nodes have no values and that we only use the node
          numbers in this problem.
    =====

    ===============================================================================================
    FUNCTION: bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild);
    ===============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
    Output: true

    --- Example 2 ---
    Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
    Output: false

    --- Example 3 ---
    Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
    Output: false


    *** Constraints ***
    n == leftChild.length == rightChild.length
    1 <= n <= 10^4
    -1 <= leftChild[i], rightChild[i] <= n - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.56% */
/* Space Beats:  5.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild)
    {
        unordered_set<int> uset;
        for (int i = 0; i < n; i++)
        {
            uset.insert(leftChild[i]);
            uset.insert(rightChild[i]);
        }

        uset.erase(-1); // Because it denotes a null node

        if (uset.size() == n) // Everyone has a parent --> Cycle detected
            return false;

        int root = -1;
        for (int i = 0; i < n; i++)
        {
            if (uset.find(i) == uset.end())
            {
                root = i;
                break;
            }
        }

        unordered_set<int> visited;

        return dfs(leftChild, rightChild, root, visited) && visited.size() == n;
    }

private:
    bool dfs(vector<int>& leftChild, vector<int>& rightChild, int node, unordered_set<int>& visited)
    {
        if (node == -1)
            return true;

        if (visited.find(node) != visited.end()) // Already visited
            return false;

        visited.insert(node);

        return dfs(leftChild, rightChild, leftChild[node],  visited) &&
               dfs(leftChild, rightChild, rightChild[node], visited);
    }
};
