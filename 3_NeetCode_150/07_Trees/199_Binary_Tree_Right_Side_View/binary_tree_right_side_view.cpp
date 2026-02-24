/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    199) Binary Tree Right Side View
    ================================

    ============
    Description:
    ============

    Give the "root" of a binary tree, imagine yourself standing on the right
    side of it, return the values of the nodes you can see ordered from top
    to bottom.

    ====================================================
    FUNCTION: vector<int> rightSideView(TreeNode* root);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
         1
      2     3
        5    4

    Input:  root = [1, 2, 3, null, 5, null, 4]
    Output: [1, 3, 4]


    --- Example 2 ---
      1
         3

    Input:  root = [1, null, 3]
    Output: [1, 3]

    --- Example 3 ---


    Input:  root = []
    Output: []

    *** Constraints ***
    The number of nodes in thre tree is in the range [0, 100].
    -100 <= Node.val <= 100

*/

#include <vector>
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

    Basic DFS.

    The only important thing here is to implement DFS going to the right first,
    since we are asked to return **Right Side View**.

    It's maybe not super-intuitive, but if the top level is "level 1", then we
    can use that to our advantage and each time we are at some level we shall
    ask if this level is greater than the size of "result".

    Why are we doing that?

    First of all, as I've said, we're always going to the right first!
    That will ensure that if there are multiple nodes in this level, only the
    rightmost node's value gets to be put in "result".

    However, if there is some deeper node somewhere in the tree that is NOT all
    the way to the right, such as this:

                 _______________________
    Level: 1     ___________1___________
    Level: 2     _____2___________3_____
    Level: 3     __4_____5_____6_____7__
    Level: 4     8_____9________________

    Here, as we can see, Level 4 nodes are not all the way to the right, thus
    the one we shall put in the "result" is the rightmost on that level, i.e.
    node "9".

    Since we'll always check the rightmost node of each level on the FIRST
    "entrance" to that level, then we only have to make sure that we put that
    one.

    In other words, if we have put [1, 3, 7] in our "result" so far and we
    enter "Level 4" for the very first time - We are GUARANTEED to "hit" the
    rightmost node in this "new level"(Deepest so far).

    Therefore we ask:

        If the current depth (4 in this case) is EQUAL to the amount of
        elements in "result"(i.e. result.size()), then that means we still
        haven't put a node from the current depth(level 4 in this case) in
        vector "result".

        Therefore, we put "4" in "result" and now we have: [1, 3, 7, 4].

    Once we "hit" node 8, that is also at Level 4, we will NOT insert it in our
    vector "result" since now Level 4 is NOT greater than result.size().

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root)
    {
        vector<int> result;

        right_dfs(root, 0, result);

        return result;
    }

private:
    void right_dfs(TreeNode* root, int curr_depth, vector<int>& result)
    {
        if ( ! root)
            return;

        if (curr_depth == result.size())
            result.push_back(root->val);

        right_dfs(root->right, curr_depth + 1, result);
        right_dfs(root->left,  curr_depth + 1, result);
    }
};
