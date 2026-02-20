/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    230) Kth Smallest Element in a BST
    ==================================

    ============
    Description:
    ============

    Given the "root" of a binary search tree, and an integer 'k', return the
    k-th smallest value (1-indexed) of all the values of the nodes in tree.

    Follow up: If the BST is modified often(i.e., we can do insert and delete
    operations) and you need to find the kth smallest frequently, how would you
    optimize?

    =================================================
    FUNCTION: int kthSmallest(TreeNode* root, int k);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [3, 1, 4, null, 2], k = 1
    Output: 1

    --- Example 2 ---
    Input:  root = [5, 3, 6, 2, 4, null, null, 1], k = 3
    Output: 3

    *** Constraints ***
    The number of nodes in the tree is 'n'.
    1 <= k <= n <= 10^4
    0 <= Nodelva. <= 10^4

*/

#include <vector>
#include <stack>
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

    The idea is to build an array as we traverse the BST in an inorder way.
    An inorder traversal is in and of itself a sorted traversal in a BST.

    Then just return (k - 1)th element from that array.

*/

/* Time  Beats: 90.30% */
/* Space Beats: 19.42% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_inorder {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        vector<int> vec;
        inorder(root, vec);

        return vec[k - 1];
    }

private:
    void inorder(TreeNode* root, std::vector<int>& vec)
    {
        if (!root)
            return;

        inorder(root->left,  vec);
        vec.push_back(root->val);
        inorder(root->right, vec);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterative Inorder Traversal

    The above recursion could be converted into iteration, with the help of
    stack. This way one could speed up the solution because there is no need
    to build the entire inroder traversal, and one could stop after the kth
    element.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  40.63% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Iterative {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        stack<TreeNode*> stack;

        while (true)
        {
            while (root != nullptr)
            {
                stack.push(root);
                root = root->left;
            }

            root = stack.top();
            stack.pop();

            if (--k == 0)
                return root->val;

            root = root->right;
        }

        return -1; // Unreachable
    }
};
