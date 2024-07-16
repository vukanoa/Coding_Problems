#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================================================
    2096) Step-By-Step Directions From a Binary Tree Node to Another
    ================================================================

    ============
    Description:
    ============

    You are given the root of a binary tree with n nodes. Each node is uniquely
    assigned a value from 1 to n. You are also given an integer startValue
    representing the value of the start node s, and a different integer
    destValue representing the value of the destination node t.

    Find the shortest path starting from node s and ending at node t. Generate
    step-by-step directions of such path as a string consisting of only the
    uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific
    direction:

        'L' means to go from a node to its left child node.
        'R' means to go from a node to its right child node.
        'U' means to go from a node to its parent node.

    Return the step-by-step directions of the shortest path from node s to node
    t.

    ==============================================================================
    FUNCTION: string getDirections(TreeNode* root, int startValue, int destValue);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
    Output: "UURL"
    Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.

    --- Example 2 ---
    Input: root = [2,1], startValue = 2, destValue = 1
    Output: "L"
    Explanation: The shortest path is: 2 → 1.


    *** Constraints ***
    The number of nodes in the tree is n.
    2 <= n <= 105
    1 <= Node.val <= n
    All the values in the tree are unique.
    1 <= startValue, destValue <= n
    startValue != destValue

*/


/*
    ------------
    --- IDEA ---
    ------------

    Intuition

    Use the DFS method solving 236. Lowest Common Ancestor of a Binary Tree.
    Approach

    Define the function TreeNode* LCA(TreeNode* root, int x, int y) which is a
    modification solving 236.

    Lowest Common Ancestor of a Binary Tree. Define bool dfs(TreeNode* root,
    int x, string& path, bool rev = 0) which has a parameter path
    (calling by reference) & a boolean parameter rev=0 in
    getDirections update root= LCA(root, startValue, destValue)

    Perform dfs(root, startValue, pathFrom, 1), dfs(root, destValue, pathTo)
    pathFrom + pathTo is the answer

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */

/* Time  Beats: 99.85% */
/* Space Beats: 69.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string getDirections(TreeNode* root, int startValue, int destValue)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        root = LCA(root, startValue, destValue);
        string path_from = "";
        string path_to   = "";

        dfs(root, startValue, path_from, 1);
        dfs(root, destValue,  path_to);

        return path_from + path_to;
    }


private:
    bool dfs(TreeNode* root, int x, string& path, bool rev = 0)
    {
        if (root == NULL)
            return 0;

        if (root->val == x)
            return 1;

        path += (rev ? 'U' : 'L');
        if (dfs(root->left, x, path, rev))
            return 1;
        path.pop_back();

        path += (rev ? 'U' : 'R');
        if (dfs(root->right, x, path, rev))
            return 1;
        path.pop_back();

        return 0;
    }

    TreeNode* LCA(TreeNode* root, int x, int y)
    {
        if (root == NULL || root->val == x || root->val == y)
            return root;

        TreeNode* left  = LCA(root->left,  x, y);
        TreeNode* right = LCA(root->right, x, y);

        if (left  == NULL)
            return right;

        if (right == NULL)
            return left;

        return root;
    }
};
