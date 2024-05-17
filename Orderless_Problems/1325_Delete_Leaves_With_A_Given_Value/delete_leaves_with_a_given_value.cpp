#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1325) Delete Leaves With a Given Value
    ======================================

    ============
    Description:
    ============

    Given a binary tree root and an integer target, delete all the leaf nodes
    with value target.

    =====
    Note: that once you delete a leaf node with value target, if its parent
          node becomes a leaf node and has the value target, it should also be
          deleted (you need to continue doing that until you cannot).
    =====

    ================================================================
    FUNCTION: TreeNode* removeLeafNodes(TreeNode* root, int target);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

               1                            1                  1
             /   \                        /   \                  \
            /     \                      /     \                  \
           /       \        ===>        /       \     ===>         \
          /         \                  /         \                  \
         /           \                /           \                  \
        2             3              2             3                  3
       /             / \                            \                  \
      /             /   \                            \                  \
     /             /     \                            \                  \
    2             2       4                            4                  4

    Input: root = [1,2,3,2,null,2,4], target = 2
    Output: [1,null,3,null,4]
    Explanation: Leaf nodes in green with value (target = 2) are removed
                 (Picture in left).  After removing, new nodes become leaf
                 nodes with value (target = 2) (Picture in center).


    --- Example 2 ---
               1                              1
             /   \                          /
            /     \                        /
           /       \        ===>          /
          /         \                    /
         /           \                  /
        3             3                3
       / \                              \
      /   \                              \
     /     \                              \
    3       2                              2
    Input: root = [1,3,3,3,2], target = 3
    Output: [1,3,null,null,2]


    --- Example 3 ---
                 1                     1               1              1
                /                     /               /
               /                     /               /
              /        ==>          /      ==>      /      ==>
             /                     /               /
            /                     /               /
           2                     2               2
          /                     /
         /                     /
        /                     /
       2                     2
      /
     /
    2
    Input: root = [1,2,null,2,null,2], target = 2
    Output: [1]
    Explanation: Leaf nodes in green with value (target = 2) are removed at
                 each step.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 3000].
    1 <= Node.val, target <= 1000

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/*
    ------------
    --- IDEA ---
    ------------

    A standard DFS traversal on a Binary Tree. If you find this difficult, make
    sure to solve EASY Binary Tree Problems from Blind_75. After that, this
    becomes a breeze.

*/

/* Time  Beats: 92.90% */
/* Space Beats: 47.43% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target)
    {
        if (!root)
            return nullptr;

        if (!root->left && !root->right)
            return root->val == target ? nullptr : root;

        root->left  = removeLeafNodes(root->left,  target);
        root->right = removeLeafNodes(root->right, target);

        if (!root->left && !root->right)
            return root->val == target ? nullptr : root;

        return root;
    }
};
