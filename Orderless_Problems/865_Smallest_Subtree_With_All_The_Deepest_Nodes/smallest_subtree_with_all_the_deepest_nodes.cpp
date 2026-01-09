/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    865) Subtree With All the Deepest Nodes
    =======================================

    ============
    Description:
    ============

    Given the root of a binary tree, the depth of each node is the shortest
    distance to the root.

    Return the smallest subtree such that it contains all the deepest nodes in
    the original tree.

    A node is called the deepest if it has the largest depth possible among any
    node in the entire tree.

    The subtree of a node is a tree consisting of that node, plus the set of
    all descendants of that node.

    ==========================================================
    FUNCTION: TreeNode* subtreeWithAllDeepest(TreeNode* root);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,5,1,6,2,0,8,null,null,7,4]
    Output: [2,7,4]
    Explanation: We return the node with value 2, colored in yellow in the
                 diagram. The nodes coloured in blue are the deepest nodes of
                 the tree. Notice that nodes 5, 3 and 2 contain the deepest
                 nodes in the tree but node 2 is the smallest subtree among
                 them, so we return it.

    --- Example 2 ---
    Input: root = [1]
    Output: [1]
    Explanation: The root is the deepest node in the tree.

    --- Example 3 ---
    Input: root = [0,1,3,null,2]
    Output: [2]
    Explanation: The deepest node in the tree is 2, the valid subtrees are the
                 subtrees of nodes 2, 1 and 0 but the subtree of node 2 is the
                 smallest.


    *** Constraints ***
    The number of nodes in the tree will be in the range [1, 500].
    0 <= Node.val <= 500
    The values of the nodes in the tree are unique.

*/

#include <queue>
#include <unordered_map>
#include <utility>
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

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.28% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root)
    {
        return dfs(root).first;
    }

private:
    pair<TreeNode*, int> dfs(TreeNode* root)
    {
        if ( ! root)
            return {nullptr, 0}; // {left_subtree_root, left_subtree_depth}

        auto left  = dfs(root->left);
        auto right = dfs(root->right);

        if (left.second > right.second)
            return {left.first, left.second + 1};

        if (left.second < right.second)
            return {right.first, right.second + 1};

        return {root, left.second + 1};
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   7.32% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Depth_plus_LCA {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root)
    {
        unordered_map<TreeNode*, int> depth;
        depth.clear();
        depth[nullptr] = -1;

        dfs(root, nullptr, depth);

        int max_depth = -1;
        for (const auto& entry : depth)
            max_depth = max(max_depth, entry.second);

        return solve(root, depth, max_depth);
    }

private:
    void dfs(TreeNode* node, TreeNode* parent, unordered_map<TreeNode*, int>& depth)
    {
        if (node == nullptr)
            return;

        depth[node] = depth[parent] + 1;

        dfs(node->left, node, depth);
        dfs(node->right, node, depth);
    }

    TreeNode* solve(TreeNode* node, unordered_map<TreeNode*, int>& depth, int& max_depth)
    {
        if (node == nullptr || depth[node] == max_depth)
            return node;

        TreeNode* left  = solve(node->left, depth, max_depth);
        TreeNode* right = solve(node->right, depth, max_depth);

        if (left && right)
            return node;

        return left ? left : right;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The idea is pretty simple. First, we perform a BFS to find the leftmost and
    rightmost nodes on the DEEPEST level.

    For example:

                                    3 
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
                       5                         1
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                6             2           0             8
                             / \
                            /   \
                           /     \
                          7       4                          
                          ^       ^
                          |       |
                          |       |
                      leftmost   rightmost


    (Or if it's easier to look at this):

        _______________________
        ___________3___________
        _____5___________1_____
        __6_____2_____0_____8__
        ______7___4____________
              ^   ^
              |   |
            __|   |__
            |        |
         leftmost   rightmost


    Then, we simply try to find the LCA(i.e. Lowest Common Ancestor) of those
    two nodes.

    In this example, it is trivial, but imagine if we had this:

                                    3 
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
                       5                         1
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                6             2           0             8
                             / \                      /
                            /   \                    /
                           /     \                  /
                          7       4                9         
                          ^                        ^
                          |                        |
                          |                        |
                      leftmost                    rightmost


    (Or if it's easier to look at this):

        _______________________
        ___________3___________
        _____5___________1_____
        __6_____2_____0_____8__
        ______7___4________9___
              ^            ^
              |            |
            __|            |__
            |                 |
         leftmost            rightmost


    Now it's much more clear. The LCA of node_7 and node_9 is the root node 3.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  27.77% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_LCA {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode* leftmost  = nullptr;
        TreeNode* rightmost = nullptr;

        queue<TreeNode*> queue;
        queue.push(root);

        /* BFS */
        while ( ! queue.empty())
        {
            int level_size = queue.size();
            leftmost = queue.front();

            for (int i = 0; i < level_size; ++i)
            {
                TreeNode* curr = queue.front();
                queue.pop();

                rightmost = curr;

                if (curr->left)
                    queue.push(curr->left);

                if (curr->right)
                    queue.push(curr->right);
            }
        }

        /*
           "leftmost" and "rightmost" are the leftmost and rightmost nodes of
           the DEEPEST level in the entire tree. That's why this works!
        */
        return lca(root, leftmost, rightmost); // Lowest Common Ancestor
    }

private:
    TreeNode* lca(TreeNode* node, TreeNode* p, TreeNode* q)
    {
        if (node == nullptr || node == p || node == q)
            return node;

        TreeNode* left  = lca(node->left, p, q);
        TreeNode* right = lca(node->right, p, q);

        if (left && right)
            return node;

        return left ? left : right;
    }
};
