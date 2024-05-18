#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    979) Distribute Coins in Binary Tree
    ====================================

    ============
    Description:
    ============

    You are given the root of a binary tree with n nodes where each node in the
    tree has node.val coins. There are n coins in total throughout the whole
    tree.

    In one move, we may choose two adjacent nodes and move one coin from one
    node to another. A move may be from parent to child, or from child to
    parent.

    Return the minimum number of moves required to make every node have exactly
    one coin.

    ==============================================
    FUNCTION: int distributeCoins(TreeNode* root);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,0,0]
    Output: 2
    Explanation: From the root of the tree, we move one coin to its left child,
                 and one coin to its right child.


    --- Example 2 ---
    Input: root = [0,3,0]
    Output: 3
    Explanation: From the left child of the root, we move two coins to the root
                 [taking two moves]. Then, we move one coin from the root of
                 the tree to the right child.


    *** Constraints ***
    The number of nodes in the tree is n.
    1 <= n <= 100
    0 <= Node.val <= n
    The sum of all Node.val is n.

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

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  22.37% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int distributeCoins(TreeNode* root)
    {
        return dfs(root, nullptr);
    }

private:
    int dfs(TreeNode* root, TreeNode* parent) // Postorder DFS
    {
        if ( ! root)
            return 0;

        int moves = dfs(root->left, root) + dfs(root->right, root);
        int excess_coins = root->val - 1; // Give excess_coins to parent node

        if (parent)
            parent->val += excess_coins; // Now parent's coins

        moves += std::abs(excess_coins);

        return moves;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Why Post-Order Traversal

    Post-order traversal is a tree traversal method where you process the left
    subtree, then the right subtree, and finally the current node. This
    traversal is particularly useful for problems where decisions at a node
    depend on the results from its children. Here's why post-order traversal is
    suited for this problem:


    1. Dependency on Subtrees:

        + Each node's coin balance is dependent on its subtrees. To determine
          whether a node has excess or deficit coins, you need to know the coin
          balance of its left and right children first.

        + Post-order traversal ensures that by the time you process a node, you
          have already processed its children, and you know the coin balance
          for both subtrees.


    2. Aggregating Results

        + By processing the left and right subtrees first, you can aggregate
          the results (i.e., the excess or deficit coins) and determine the
          number of moves required to balance the subtrees before dealing with
          the current node.

        + This aggregation is crucial because the number of moves needed at a
          node includes not only the moves to balance itself but also the moves
          required to balance its subtrees.



    3. Simplifies Calculation

        + With post-order traversal, the calculation at each node becomes
          straightforward. You can simply take the excess coins from the left
          and right subtrees and adjust the current node's coin count
          accordingly.

        + This avoids the complexity of needing to backtrack or perform
          additional traversals, making the algorithm efficient.



    Understanding the Formula for Moves:

    The goal is to redistribute the coins such that every node has exactly one
    coin. Let's understand the excess coins at each node and how the moves are
    calculated.

    1. Excess Coins

        + For any given node, the excess coins can be calculated as:
              excess = total coins at node and its subtrees − 1

        + The -1 accounts for the fact that each node needs exactly one coin.



    2. Steps to Calculate Moves

        + Post-Order Traversal: Traverse the tree in a post-order manner. This
          ensures that we first process the left and right subtrees before the
          current node.

        + Calculate Excess Coins for Subtrees:
            + left_excess = postOrder(root->left): Calculate the excess coins
              in the left subtree.

            + right_excess = postOrder(root->right): Calculate the excess coins
              in the right subtree.



    3. Calculate Moves:

        + The number of moves required to balance the left and right subtrees
          is the sum of the absolute values of left_excess and right_excess:

              moves += ∣left_excess∣ + ∣right_excess∣


        + This is because the excess (or deficit) in each subtree needs to be
          moved to or from the current node to balance it.

        + The total excess coins at the current node after balancing its
          subtrees is:

              excess at node = root->val + left_excess + right_excess − 1.


    Example:

                        0
                      /   \
                     /     \
                    /       \
                   /         \
                  /           \
                 6             0
                /             / \
               /             /   \
              /             /     \
             0             0       0


    Knowing all of the above explanation, try to "simulate" on this example and
    you'll surely understand it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.89% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int distributeCoins(TreeNode* root)
    {
        int moves = 0;
        dfs(root, moves);

        return moves;
    }

private:
    int dfs(TreeNode* root, int& moves)
    {
        if ( ! root)
            return 0;

        int left_excess  = dfs(root->left,  moves);
        int right_excess = dfs(root->right, moves);

        moves += std::abs(left_excess) + std::abs(right_excess);

        return root->val + left_excess + right_excess - 1;
    }
};
