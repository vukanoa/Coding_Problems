#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ==============================
    590) N-ary Postorder Traversal
    ==============================

    ============
    Description:
    ============

    Given the root of an n-ary tree, return the postorder traversal of its
    nodes' values.

    Nary-Tree input serialization is represented in their level order
    traversal. Each group of children is separated by the null value (See
    examples)


    ---------------
    -- Follow Up --
    ---------------

        Recursive solution is trivial, could you do it iteratively?


    ============================================
    FUNCTION: vector<int> postorder(Node* root);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,null,3,2,4,null,5,6]
    Output: [5,6,3,2,4,1]

    --- Example 2 ---
    Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
    Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 10^4].
    0 <= Node.val <= 104
    The height of the n-ary tree is less than or equal to 1000.

*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

/*
    ------------
    --- IDEA ---
    ------------

    A fundamental postorder tweaked for N-ary Trees. If you don't understand
    this, please return to the basic of Binary Tree traversals.

*/

/* Time  Beats: 51.70% */
/* Space Beats: 80.43% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<int> postorder(Node* root)
    {
        vector<int> result;

        dfs(root, result);

        return result;
    }

private:
    void dfs(Node* root, vector<int>& result)
    {
        if ( ! root)
            return;

        for (const auto node : root->children)
            dfs(node, result);

        result.push_back(root->val);
    }
};
