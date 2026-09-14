/*
    ============
    === EASY ===
    ============

    ========================================================================
    1379) Find a Corresponding Node of a Binary Tree in a Clone of That Tree
    ========================================================================

    ============
    Description:
    ============

    Given two binary trees original and cloned and given a reference to a node
    target in the original tree.

    The cloned tree is a copy of the original tree.

    Return a reference to the same node in the cloned tree.

    =====
    Note: that you are not allowed to change any of the two trees or the target
          node and the answer must be a reference to a node in the cloned tree. 
    =====


    ---------------
    -- Follow Up --
    ---------------

        Could you solve the problem if repeated values on the tree are allowed?


    ==========================================================================================
    FUNCTION: TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target);
    ==========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tree = [7,4,3,null,null,6,19], target = 3
    Output: 3
    Explanation: In all examples the original and cloned trees are shown. The
                 target node is a green node from the original tree. The answer
                 is the yellow node from the cloned tree.

    --- Example 2 ---
    Input: tree = [7], target =  7
    Output: 7

    --- Example 3 ---
    Input: tree = [8,null,6,null,5,null,4,null,3,null,2,null,1], target = 4
    Output: 4


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    The values of the nodes of the tree are unique.
    target node is a node from the original tree and is not null.

*/

#include <queue>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 18.17% */
/* Space Beats: 58.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_DFS {
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target)
    {
        if (original == nullptr)
            return nullptr;

        if (original == target)
            return cloned;

        TreeNode* left = getTargetCopy(original->left,  cloned->left,  target);

        if (left != nullptr)
            return left;

        TreeNode* right = getTargetCopy(original->right, cloned->right, target);

        return right;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.63% */
/* Space Beats:  5.19% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS {
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target)
    {
        if (original == nullptr)
            return nullptr;

        if (original == target)
            return cloned;


        queue<TreeNode*> orig_queue;
        queue<TreeNode*> clone_queue;

        orig_queue.push(original);
        clone_queue.push(cloned);

        while ( ! orig_queue.empty())
        {
            auto orig_node  = orig_queue.front();
            auto clone_node = clone_queue.front();

            orig_queue.pop();
            clone_queue.pop();

            if (orig_node == target)
                return clone_node;

            if (orig_node->left)
            {
                orig_queue.push(orig_node->left);
                clone_queue.push(clone_node->left);
            }

            if (orig_node->right)
            {
                orig_queue.push(orig_node->right);
                clone_queue.push(clone_node->right);
            }
        }

        return nullptr; // Unreachable code since "target" is ALWAYS present
    }
};
