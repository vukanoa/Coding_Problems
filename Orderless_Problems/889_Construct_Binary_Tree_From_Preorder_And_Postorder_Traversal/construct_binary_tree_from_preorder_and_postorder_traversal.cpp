/*
    ==============
    === MEDIUM ===
    ==============

    ================================================================
    889) Construct Binary Tree from Preorder and Postorder Traversal
    ================================================================

    ============
    Description:
    ============

    Given two integer arrays, preorder and postorder where preorder is the
    preorder traversal of a binary tree of distinct values and postorder is the
    postorder traversal of the same tree, reconstruct and return the binary
    tree

    If there exist multiple answers, you can return any of them.

    ========================================================================================
    FUNCTION: TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder);
    ========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
    Output: [1,2,3,4,5,6,7]

    --- Example 2 ---
    Input: preorder = [1], postorder = [1]
    Output: [1]


    *** Constraints ***
    1 <= preorder.length <= 30
    1 <= preorder[i] <= preorder.length
    All the values of preorder are unique.
    postorder.length == preorder.length
    1 <= postorder[i] <= postorder.length
    All the values of postorder are unique.
    It is guaranteed that preorder and postorder are the preorder traversal and postorder traversal of the same binary tree.

*/

#include <vector>
using namespace std;


/**
 * Definition for a binary tree node.
*/
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

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder)
    {
        const int N = preorder.size();

        if (N == 1)
            return new TreeNode(preorder[0]);

        int L = 0;
        int R = N-1;

        TreeNode* root = new TreeNode(preorder[0]);
        int i = 1;

        return recursion(preorder, postorder, root, i, L, R, true);
    }

private:
    TreeNode* recursion(vector<int>& preorder, vector<int>& postorder, TreeNode* curr_node, int& i, int L, int R, bool to_left)
    {
        if (i == preorder.size() || L >= R)
            return nullptr;

        for (int x = L; x < R; x++)
        {
            if (preorder[i] == postorder[x])
            {
                if (to_left)
                {
                    curr_node->left = new TreeNode(preorder[i]);
                    i++;

                    recursion(preorder, postorder, curr_node->left, i, L, x, true);

                    L = x+1;
                    to_left = false;
                }
                else
                {
                    curr_node->right = new TreeNode(preorder[i]);
                    i++;

                    recursion(preorder, postorder, curr_node->right, i, L, x, true);

                    to_left = true;
                }
            }

            if (i == preorder.size())
                break;
        }

        return curr_node;
    }
};
