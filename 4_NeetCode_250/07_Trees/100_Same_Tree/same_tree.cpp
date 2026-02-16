/*
    ============
    === EASY ===
    ============

    ===========================
    100) Same Tree
    ===========================

    ============
    Description:
    ============

    Given the roots of two binary trees p and q, write a function to check if
    they are the same or not.

    Two binary trees are considered the same if they are structurally
    identical, and the nodes have the same value.

    ====================================================
    FUNCTION: bool isSameTree(TreeNode* p, TreeNode* q);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        _____    _____
        __1__    __1__
        2___3    2___3

    Input: p = [1,2,3], q = [1,2,3]
    Output: true



    --- Example 2 ---
        _____    _____
        __1__    __1__
        2____    ____2
    Input: p = [1,2], q = [1,null,2]
    Output: false



    --- Example 3 ---
        _____    _____
        __1__    __1__
        2___1    1___2

    Input: p = [1,2,1], q = [1,1,2]
    Output: false



    *** Constraints ***
    The number of nodes in both trees is in the range [0, 100].
    -10^4 <= Node.val <= 10^4

*/

#include <queue>
#include <utility>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
    ------------
    --- IDEA ---
    ------------

    Basic, self-explanatory, Binary Tree problem using DFS;

*/

/* Time  Beats:    100% */
/* Space Beats:  45.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS {
public:
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        if ( ! p && ! q) return true;
        if ( ! p || ! q) return false;

        if (p->val != q->val)
            return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Implmentation using BFS(i.e. "Level Order") approach.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  12.81% */
class Solution_BFS {
public:
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        queue<pair<TreeNode*, TreeNode*>> queue;
        queue.push( {p, q} );

        while ( ! queue.empty())
        {
            auto [node_p, node_q] = queue.front();
            queue.pop();

            if ( ! node_p && ! node_q) continue;
            if ( ! node_p || ! node_q) return false; // One is nullptr, other is NOT

            if (node_p->val != node_q->val)
                return false;

            queue.push( {node_p->left,  node_q->left}  );
            queue.push( {node_p->right, node_q->right} );
        }

        return true;
    }
};
