/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    235) Lower Common Ancestor of BST
    =================================

    ============
    Description:
    ============

    Given a binary search tree (BST), find the lowest common ancestor (LCA)
    node of two given nodes in the BST.

    According to the definition of LCA on Wikipedia: “The lowest common
    ancestor is defined between two nodes p and q as the lowest node in T that
    has both p and q as descendants (where we allow a node to be a descendant
    of itself).”

    ===================================================================================
    FUNCTION: TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
    Output: 6
    Explanation: The LCA of nodes 2 and 8 is 6.


    --- Example 2 ---
    Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
    Output: 2
    Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a
                 descendant of itself according to the LCA definition.


    --- Example 3 ---
    Input: root = [2,1], p = 2, q = 1
    Output: 2


    *** Constraints ***
    The number of nodes in the tree is in the range [2, 105].
    -109 <= Node.val <= 109
    All Node.val are unique.
    p != q
    p and q will exist in the BST.

*/

#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
    ------------
    --- IDEA ---
    ------------

    Use the property of the BST(Binary Search Tree).

    If both p's and q's values are LESS than the value of the current node,
    then go to the left. We are 100% certain it's not in the right subtree
    because of the property of the BST itself.

    Conversely, if both p's and q's values are GREATER than the value of the
    current node, then go to the right. It's certainly not in the remaining
    part of the left subtree.

*/

/* Time  Beats: 94.59% */
/* Space Beats: 59.75% */

/* Time  Complexity: O(H) */ // Where 'H' is the Height of the Tree
/* Space Complexity: O(1) */
class Solution_Iterative {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        TreeNode* curr = root;

        while (curr)
        {
            /* Using the property of the BST */
            if (p->val < curr->val && q->val < curr->val)
            {
                curr = curr->left;
            }
            else if (p->val > curr->val && q->val > curr->val)
            {
                curr = curr->right;
            }
            else
            {
                return curr;
            }
        }

        return nullptr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We do the same thing as above, just in a recursive way.

*/

/* Time  Beats: 96.39% */
/* Space Beats: 72.79% */

/* Time  Complexity: O(H) */ // Where 'H' is the Height of the Tree
/* Space Complexity: O(H) */
class Solution_Recursive {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == p || root == q)
            return root;

        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);

        if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We, actually, do NOT need to use the BST property when it comes to values.

    This is an important approach to understand for finding a LCA if you
    haven't solved it this way.

    First, if the root itself is either p or q, we return immediately since
    we're told that the node CAN be a descendant of ITSELF.

    However, if that's NOT the case, then we try to find either of them(p or q)
    in the left subtree.

    If we ever hit either of the nodes(i.e. p or q), we return.
    Why?

    Consider this:

                               
                                    9             
                            6               13     
                        3       8       10      14  
                      1   5                       17


                                    9 
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       6                        13
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                3             8           10           14
               / \           /                           \
              /   \         /                             \
             /     \       /                               \
            1       5     7                                17


    Let's say:

        p = 1
        q = 6

    When we get to node 6(which equals to node q), we don't have to keep gong
    down, we can STOP here and only check the right subtree of 9.

    Why?

    We'll since we have entered this left subtree where we've found 6, that
    means the parent node is NEITHER p nor q.

    Therefore, since we've successfully found a q in the left subtree of 9, we
    do NOT have to keep searching below. Instead, we can only check 9's RIGHT
    subtree.

    If we do INDEED find p there, then we return 9(parent) as the LCA.
    If we do NOT    find p there, then we return 6         as the LCA.

    In the 2nd case we're allowed to return 6 immediately because we're told
    in the Constraints that both p and q CERTAINLY exist in the tree.

    So if we've found either of them at one point and the other is NOT in the
    right subtree of its parent, then it's CERTAINLY BELOW us.

    In that case 6 is guaranteed to be a LCA of p and q.

*/

/* Time  Complexity: O(H) */ // Where 'H' is the Height of the Tree
/* Space Complexity: O(H) */
class Solution_Straightforward {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if ( ! root)
            return nullptr;

        if (root == p || root == q)
            return root;

        TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right)
            return root;

        if (left)
            return left;

        if (right)
            return right;

        return nullptr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The is ABSOLUTELY equivalent to the above approach, it's just written in
    a more concise way.

    It's good to be aware of both implementations.

*/

/* Time  Beats: 79.08% */
/* Space Beats:  6.01% */

/* Time  Complexity: O(H) */ // Where 'H' is the Height of the Tree
/* Space Complexity: O(H) */
class Solution_Straightforward_Concise {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if ( ! root || root == p || root == q)
            return root;

        TreeNode* left  = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        return left && right ? root : (left ? left : right);
    }
};
