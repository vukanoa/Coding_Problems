/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    701) Insert Into A Binary Search Tree
    =====================================

    ============
    Description:
    ============

    You are given the root node of a binary search tree (BST) and a value to
    insert into the tree. Return the root node of the BST after the insertion.
    It is guaranteed that the new value does not exist in the original BST.

    Notice that there may exist multiple valid ways for the insertion, as long
    as the tree remains a BST after insertion. You can return any of them.

    ===========================================================
    FUNCTION: TreeNode* insertIntoBST(TreeNode* root, int val);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [4,2,7,1,3], val = 5
    Output: [4,2,7,1,3,5]

    --- Example 2 ---
    Input: root = [40,20,60,10,30,50,70], val = 25
    Output: [40,20,60,10,30,50,70,null,null,25]

    --- Example 3 ---
    Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
    Output: [4,2,7,1,3,5]


    *** Constraints ***
    The number of nodes in the tree will be in the range [0, 10^4].
    -10^8 <= Node.val <= 10^8
    All the values Node.val are unique.
    -10^8 <= val <= 10^8
    It's guaranteed that val does not exist in the original BST.

*/

#include <bits/stdc++.h>
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

    Basic Iterative implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  57.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Iterative {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val)
    {
        if ( ! root)
            return new TreeNode(val);

        TreeNode* curr = root;
        while (true)
        {
            if (val < curr->val)
            {
                if (curr->left == nullptr)
                {
                    curr->left = new TreeNode(val);
                    break;
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {
                if (curr->right == nullptr)
                {
                    curr->right = new TreeNode(val);
                    break;
                }
                else
                {
                    curr = curr->right;
                }
            }
        }

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Basic Recursive_Implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  22.89% */

class Solution_Recursive {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val)
    {
        if ( ! root)
            return new TreeNode(val);

        if (val < root->val)
            root->left  = insertIntoBST(root->left, val);
        else
            root->right = insertIntoBST(root->right, val);

        return root;
    }
};
