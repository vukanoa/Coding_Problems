/*
    ============
    === HARD ===
    ============

    =================================
    124) Binary Tree Maximum Path Sum
    =================================

    ============
    Description:
    ============

    A path in a binary tree is a sequence of nodes where each pair of adjacent
    nodes in the sequence has an edge connecting them. A node can only appear
    in the sequence at most once. Note that the path does not need to pass
    through the root.

    The path sum of a path is the sum of the node's values in the path.

    Given the root of a binary tree, return the maximum path sum of any
    non-empty path.

    =========================================
    FUNCTION: int maxPathSum(TreeNode* root);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        _____
        __1__
        2___3

    Input:  root = [1, 2, 3]
    Output: 6



    --- Example 2 ---
        ___________
        ____-10____
        __9_____20_
        ______15__7

    Input:  root = [-10, 9, 20, null, null, 15, 7]
    Output: 42

    *** Constraints ***
    The number of nodes in the tree is in the range [1, 3 * 10^4]
    -1000 <= Node.val <= 1000

*/

#include <algorithm>
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

    I tried to think of base cases and expanded the logic.

    I went through it this way:
        If you have a single node, what is the maximum path?
            The node itself.

        If you have a small tree of root and both root's left node and root's
        right node, what is the max?

            _____X_____
            __X_____X__

            It's either:
                1. Sum of all three, or
                2. Sum of root and left, or
                3. Sum of root and right, or
                4. A single node, out of those three, with the highest value

        What if we add another level to the previous example. What if we had
        something like this? (As in Example 2)

            ___________
            ____-10____
            __9_____20_
            ______15__7

        Every time we're returning from a subtree in "dfs" function, we should
        return the PATH with max value considering that the current node will
        not be the absolute root of the tree/subtree with a maximum path.

        It's a bit confusing if you just read it like this.

        Look at node 20. Once it processes both left and right subtrees, we can
        see that the max path in the entire tree is 42(15 + 20 + 7), however
        if there were a greater path, we cannot return 42 once we're on
        root=20 because that's not possible to be the path that we can
        concatenate further. (Since we have already split once)

        If we've used both the left and the right subtree, that's it. We cannot
        concatenate on top of that.

        However if we want to use the current root as the node of a larger
        tree/subtree, then in that case we have to pick either:
            1. current node's left subtree PATH or
            2. right subtree PATH
        since that is a Path and we CAN concatenate to it.
        (also we do that only if either left or right are greater than 0,
        otherwise just return root->val, or right->val + 0 to be exact)

        Consider another Example:

            _______________________
            ___________5___________
            _____4___________8_____
            __11_________13_____4__
            7___2_________________1

        Look at node 8.
        13 + 8 + 5 = 21

        However, if we want to use 8 as a single node in a larger tree, then
        we have to pick either 13 or 5.

        We pick 13.

        And at the end, maximum path is 48. How?

        7 + 11 + 4 + 5 + 8 + 13

        Notice how we excluded right subtree of node 11, and right subtree of
        node 8, since we have to form a LINEAR PATH. We can't "fork" while
        traversing.

*/

/* Time  Beats: 97.22% */
/* Space Beats: 71.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Elegant {
public:
    int maxPathSum(TreeNode* root)
    {
        const int NODE_MIN_VAL = -1000;
        int result = NODE_MIN_VAL - 1;

        dfs(root, result);

        return result;
    }

private:
    int dfs(TreeNode* root, int& result)
    {
        if ( ! root)
            return 0;

        int left_path_max  = max(0, dfs(root->left, result));
        int right_path_max = max(0, dfs(root->right, result));

        // This is WITH Split
        result = max(result, left_path_max + root->val + right_path_max);

        // Return PATH(ie. without Split)
        return root->val + max(left_path_max, right_path_max);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is the equivalent, but messier implementation. I've included both so
    that you can compare where the optimization, or elegance, lays.

*/

/* Time  Beats: 14.62% */
/* Space Beats: 12.13% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Messier {
public:
    int maxPathSum(TreeNode* root)
    {
        const int NODE_MIN_VAL = -1000;
        int result = NODE_MIN_VAL - 1;

        dfs(root, result);

        return result;
    }

private:
    int dfs(TreeNode* root, int& result)
    {
        if ( ! root)
            return 0;

        int left_path_max  = dfs(root->left, result);
        int right_path_max = dfs(root->right, result);

        int curr_with_left  = left_path_max  + root->val;
        int curr_with_right = right_path_max + root->val;
        int curr_only       = root->val;
        int curr_path_sum   = left_path_max + right_path_max + root->val;

        result = max( {result, curr_with_left, curr_with_right, curr_only, curr_path_sum} );

        return max( {curr_with_left, curr_only, curr_with_right} );
    }
};
