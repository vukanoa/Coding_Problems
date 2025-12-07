/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    623) Add One Row to Tree
    ===========================

    ============
    Description:
    ============


    Given the root of a binary tree and two integers val and depth, add a row
    of nodes with value val at the given depth depth.

    Note that the root node is at depth 1.

    The adding rule is:

        + Given the integer depth, for each not null tree node cur at the depth
          depth - 1, create two tree nodes with value val as cur's left subtree
          root and right subtree root.

        + cur's original left subtree should be the left subtree of the new
          left subtree root.

        + cur's original right subtree should be the right subtree of the new
          right subtree root.

        + If depth == 1 that means there is no depth depth - 1 at all, then
          create a tree node with value val as the new root of the whole
          original tree, and the original tree is the new root's left subtree.

    ==================================================================
    FUNCTION: TreeNode* addOneRow(TreeNode* root, int val, int depth);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [4,2,6,3,1,5], val = 1, depth = 2
    Output: [4,1,1,2,null,null,6,3,1,5]

    --- Example 2 ---
    Input: root = [4,2,null,3,1], val = 1, depth = 3
    Output: [4,2,null,1,1,3,null,null,1]


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    The depth of the tree is in the range [1, 10^4].
    -100 <= Node.val <= 100
    -10^5 <= val <= 10^5
    1 <= depth <= the depth of tree + 1

*/

#include <queue>
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

    Classic BFS, nothing special about it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.89% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth)
    {
        if (depth == 1)
            return new TreeNode(val, root, nullptr);

        queue<TreeNode*> queue;
        queue.push(root);

        int curr_level = 1;
        /* BFS */
        while ( ! queue.empty())
        {
            int size = queue.size();

            while (size > 0)
            {
                TreeNode* curr_node = queue.front();
                queue.pop();

                if (curr_level == depth - 1)
                {
                    TreeNode* new_left_node  = new TreeNode(val);
                    TreeNode* new_right_node = new TreeNode(val);

                    TreeNode* orig_left_node  = curr_node->left;  // Can be NLL
                    TreeNode* orig_right_node = curr_node->right; // can be NLL

                    curr_node->left     = new_left_node;
                    new_left_node->left = orig_left_node;

                    curr_node->right      = new_right_node;
                    new_right_node->right = orig_right_node;
                }
                else
                {
                    if (curr_node->left)  queue.push(curr_node->left);
                    if (curr_node->right) queue.push(curr_node->right);
                }

                // Decrement
                size--;
            }

            curr_level++;
            if (curr_level == depth)
                break;
        }

        return root;
    }
};
