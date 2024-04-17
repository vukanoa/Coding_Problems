#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    99) Recover Binary Search Tree
    ==============================

    ============
    Description:
    ============

    You are given the root of a binary search tree (BST), where the values of
    exactly two nodes of the tree were swapped by mistake. Recover the tree
    without changing its structure.

    Follow up: A solution using O(n) space is pretty straight-forward. Could
               you devise a constant O(1) space solution?

    ===========================================
    FUNCTION: void recoverTree(TreeNode* root);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                                    1
                                  /
                                 /
                                /
                               /
                              /
                             3
                              \
                               \
                                \
                                 2

    Input: root = [1,3,null,null,2]
    Output: [3,1,null,null,2]
    Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3
                 makes the BST valid.


    --- Example 2 ---
                                    3
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             1             4
                                          /
                                         /
                                        /
                                       2

    Input: root = [3,1,4,null,null,2]
    Output: [2,1,4,null,null,3]
    Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping
                 2 and 3 makes the BST valid.



    *** Constraints ***
    The number of nodes in the tree is in the range [2, 1000].
    -2^31 <= Node.val <= 2^31 - 1

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

    Populate vector "nodes" with all the actual nodes by doing an INORDER
    traversal.

    Then:
        1) Find first value(going from the left to right) that is NOT in
           order(i.e. greater than the next)

        2) Find first value(from the back, i.e. going from the right to left)
           that is SMALLER than the value found under 1).

        3) Swap values found in 1) and 2).

*/

/* Time  Beats: 93.59% */
/* Space Beats: 11.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    void recoverTree(TreeNode* root)
    {
        std::vector<TreeNode*> nodes;
        inorder(root, nodes); // Populate nodes by doing an INORDER traversal

        TreeNode* first;
        TreeNode* second;

        /* Find first value that is NOT in order, i.e. greater than the next */
        for(int i = 0; i < nodes.size()-1; i++)
        {
            if(nodes[i]->val > nodes[i+1]->val)
            {
                first = nodes[i];
                break;
            }
        }

        /*
            Starting from the back, find value that is SMALLER than "first"
            value that is NOT in order.
        */
        for(int i = nodes.size()-1; i >= 0; i--)
        {
            if(nodes[i]->val < first->val)
            {
                second = nodes[i];
                break;
            }
        }

        std::swap(first->val, second->val);
    }

private:
    void inorder(TreeNode* root, std::vector<TreeNode*>& nodes)
    {
        if(!root)
            return;

        inorder(root->left, nodes);
        nodes.push_back(root);
        inorder(root->right, nodes);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is essentially a similar approach, however this one doesn't use any
    extra space. It doesn't even use a recursion. Instead, what it does is it
    implements a "Morris inorder traversal" after which it just swaps elements
    pointed to by "first" and "second".


    The intuition behind this code is to use a modified Morris traversal to
    find the two nodes in a BST that have been swapped. In a Morris traversal,
    we thread the right pointer of each node to its predecessor in the inorder
    traversal. This allows us to traverse the tree without using a stack.

    Initialize two pointers, prev and current, to null. While current is NOT
    null:

        If current->left is NOT null:
            Find the predecessor of current in the inorder traversal.

            If the predecessor is nullptr:
                current is the first node in the inorder traversal.
            else
                thread the predecessor's right pointer to current.

        Set current to current->left.

        Otherwise, if current->right is NOT nullptr and current->right is NOT
        the predecessor of current:

            Set current to current->right.

        Otherwise, if prev is NOT nullptr and prev->val > current->val:
            If first is nullptr, then prev is the first node in the inorder
            traversal.

        Set second  to current.
        Set prev    to current.
        Set current to current->right.


    If first and second are not null, then swap their values.

*/

/* Time  Beats: 56.11% */
/* Space Beats: 99.02% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Morris {
public:
    void recoverTree(TreeNode* root)
    {
        TreeNode* prev    = nullptr;
        TreeNode* current = root;
        TreeNode* first   = nullptr;
        TreeNode* second  = nullptr;

        while (current)
        {
            if (current->left)
            {
                TreeNode* tmp = current->left;

                while (tmp->right && tmp->right != current)
                    tmp = tmp->right;

                if (tmp->right == nullptr)
                {
                    tmp->right = current;
                    current = current->left;
                }
                else
                {
                    tmp->right = nullptr;
                    if (prev && prev->val > current->val)
                    {
                        if (first == nullptr)
                            first = prev;

                        second = current;
                    }

                    prev    = current;
                    current = current->right;
                }
            }
            else
            {
                if (prev && prev->val > current->val)
                {
                    if (first == nullptr)
                        first = prev;

                    second = current;
                }

                prev = current;
                current = current->right;
            }
        }

        std::swap(first->val, second->val);
    }
};
