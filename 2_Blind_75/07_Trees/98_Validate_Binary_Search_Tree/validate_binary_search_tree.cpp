/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    98) Validate Binary Search Tree
    ===============================

    ============
    Description:
    ============

    Given the "root" of a binary tree, determine if it is a valid binary search
    tree(BST)

    A valid BST is defined as follows:
        - The left subtree of a node containts only nodes with keys less than
          the node's key.

        - The right subtree of a node contains only nodes with keys greater
          than the node's key.

        - Both the left and right subtrees must also be binary search trees.

    ==========================================
    FUNCTION: bool isValidBST(TreeNode* root);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [2, 1, 3]
    Output: true

    --- Example 2 ---
    Input:  root = [5, 1, 4, null, null, 3, 6]

    *** Constraints ***
    - The number of nodes in the tree is in the range [1, 10^4]
    - -2^31 <= Nodel.val <= 2^31 - 1

*/

#include <climits>
#include <queue>
#include <tuple>
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

    It's obvious that if you go to the right subtree that all the elements must
    be greater than the root node. However, it's NOT so obvious to notice
    almost the same thing - The LOWEST value that is allowed to appear in the
    RIGHT subtree is bounded by the root node's value.


    For example:
                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____9__
                        ______2___4_X__________
                                    ^
                                    |
                                  this value MUST BE GREATER than 5, since it
                                  it belongs in a RIGHT SUBTREE of node 5.

    It must be greater than 5 because otherwise it would NOT be a BST anymore.

    So whenever we are going to the right subtree of current's root node, we
    must say that the current node is the LEFT_BOUND or LOWER_BOUND.

    Similarly, whenever we are going to the left subtree of current's root node
    we must say that the current node is the RIGHT_BOUND or UPPER_BOUND.
                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____9__
                        ______2___X_6__________
                                  ^
                                  |
                         This value must be LOWER than 5 since it belongs to
                         the LEFT subtree of 5.

                         However, it also must be GREATER than 3 since it
                         belongs to the RIGHT subtree of 3.

    However, we can't pass simple values since maybe there is no constraint
    for either lower or upper bound and we don't want to erroneously check
    when we don't have to since it could lead to an incorrect result.

    Therefore, instead of passing a value as an lower_bound or upper_bound, we
    are going to pass a pointer to an entire node that represents the bound.

    In that case, if there is NO lower_bound or upper bound, we won't be
    checking if the rule is infringed and will just continue as normal.

    Here is an example where we don't have a limit for how low values can be.
    I.e. there is no LOWER_BOUND, it's nullptr.

                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____9__
                        X_____2___4_6__________
                        ^
                        |
                This value does NOT have a lower_bound.

    You are, hopefully, noticing a pattern.

    If we go to the right subtree, lower_bound becomes the current root.
    However, upper_bound is INHERITED. Meaning, if it's nullptr, there is no
    upper_bound.

    If we go to the left  subtree, upper_bound becomes the current root.
    However, lower_bound is INHERITED. Meaning, if it's nullptr, there is no
    lower_bound.


    In the 2nd Example in this IDEA, we had this Tree.

                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____9__
                        ______2___X_6__________

    Once we are at node 3 and we want to go to its right subtree, then the
    lower_bound becomes 3 itself, however upper_bound is INHERITED.

    What does that mean?

    It means that if there is any upper_bound so far, it will persist.


    Let's see an example where upper_bound is INHERITED, but it's a nullptr.

                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____X__
                        ______2___4_6__________

    Once we are at node 8 and we go to the right, again we'll say that our
    lower_bound is equal to 8, however the upper_bound is inherited.

    Since at this point, upper_bound is nullptr, we will use that. That means
    that in the right subtree of root 8, there are no limits in how big values
    can be found in nodes to the right.

    However, as we've already concluded the left bound is value 8 itself.

*/

/* Time  Beats: 95.81% */
/* Space Beats: 83.78% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isValidBST(TreeNode* root)
    {
        return dfs(root, nullptr, nullptr);
    }

private:
    bool dfs(TreeNode* root, TreeNode* lower_bound, TreeNode* upper_bound)
    {
        if ( ! root)
            return true;

        if (lower_bound && lower_bound->val >= root->val)
            return false;

        if (upper_bound && upper_bound->val <= root->val)
            return false;

        return dfs(root->left,  lower_bound,   root     ) &&
               dfs(root->right,    root    , upper_bound);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    However, for this specific problems and these specific Constraints, we can
    indeed use just numbers.

    I could've used "long" instead of "long long", but whenever I use "long"
    (because I wish the type to be 64bit), "long" is not consistent.

    "long"      is AT LEAST 32 bits, and on Windows it tends to be 32bit.
    "long long" is AT LEAST 64 bits, and it's 64bits on ALL architectures.

    That's why I always prefer to use "long long" instead of "long".

    TL;DR using "long" when I ALWAYS want 64 bits is NOT portable.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.03% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Using_Numbers {
public:
    bool isValidBST(TreeNode* root)
    {
        return dfs(root, LLONG_MIN, LLONG_MAX);
    }

private:
    bool dfs(TreeNode* root, long long lower_bound, long long upper_bound)
    {
        if ( ! root)
            return true;

        if ( ! (lower_bound < root->val && root->val < upper_bound))
            return false;

        return dfs(root->left,   lower_bound,    root->val ) &&
               dfs(root->right,   root->val ,   upper_bound);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Just a BFS implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.16% */
class Solution_BFS_Using_Numbers {
public:
    bool isValidBST(TreeNode* root)
    {
        queue<tuple<TreeNode*, long long, long long>> queue;
        queue.push( {root, LLONG_MIN, LLONG_MAX} );

        /* BFS */
        while ( ! queue.empty())
        {
            int size = queue.size();

            while (size > 0)
            {
                auto [root, lower_bound, upper_bound] = queue.front();
                queue.pop();

                if ( ! (lower_bound < root->val && root->val < upper_bound))
                    return false;

                if (root->left)
                    queue.push( {root->left, lower_bound, root->val} );

                if (root->right)
                    queue.push( {root->right, root->val, upper_bound} );


                // Decrement
                size--;
            }
        }

        return true;
    }
};
