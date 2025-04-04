/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    1123) Lowest Common Ancestor of Deepest Leaves
    ==============================================

    ============
    Description:
    ============


    Given the root of a binary tree, return the lowest common ancestor of its
    deepest leaves.

    Recall that:

        + The node of a binary tree is a leaf if and only if it has no children

        + The depth of the root of the tree is 0. if the depth of a node is d,
          the depth of each of its children is d + 1.

        + The lowest common ancestor of a set S of nodes, is the node A with
          the largest depth such that every node in S is in the subtree with
          root A.

    =====================================================
    FUNCTION: TreeNode* lcaDeepestLeaves(TreeNode* root);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,5,1,6,2,0,8,null,null,7,4]
    Output: [2,7,4]
    Explanation: We return the node with value 2, colored in yellow in the
                 diagram. The nodes coloured in blue are the deepest leaf-nodes
                 of the tree. Note that nodes 6, 0, and 8 are also leaf nodes,
                 but the depth of them is 2, but the depth of nodes 7 and 4 is
                 3.


    --- Example 2 ---
    Input: root = [1]
    Output: [1]
    Explanation: The root is the deepest node in the tree, and it's the lca of
                 itself.

    --- Example 3 ---
    Input: root = [0,1,3,null,2]
    Output: [2]
    Explanation: The deepest leaf node in the tree is 2, the lca of one node is
                 itself.


    *** Constraints ***
    The number of nodes in the tree will be in the range [1, 1000].
    0 <= Node.val <= 1000
    The values of the nodes in the tree are unique.

*/

#include <queue>
#include <unordered_map>
#include <unordered_set>
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

    This one is a very unnecessarily complex Solution, but it's good to be able
    to understand and see Solutions like this.

    It utilizes: DFS, BFS, HashMaps, HashSet and Queue.

    First, we do a DFS while trying to retrieve what is the deepest level in
    our BinaryTree.

    While're doing it, we're creating a "umap_node_to_parent" where each node
    is mapped to its parent. (You'll see what this is handy)

    Then we start from the root node and we're performing a BFS using Queue
    data structure.

    However we do NOT stop once queue.empty(), but once level == deepest_level,
    because we want to have all the nodes at the deepest level in our Queue.

    Then we push those leaf nodes at the deepest level to a HashSet.
    Then we go through our Hashset and for each node in the HashSet we get its
    parent node.

    We're going to propagate up to a single node. That can be a root node
    itself, or it can be some LCA somewhere within the Tree.

    Either way, we're going to end up with only a single node in our HashSet.

    Once that happens--We've found our LCA node and we return it.

*/

/* Time  Beats:  8.22% */
/* Space Beats: 12.58% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root)
    {
        if (!root->left && !root->right)
            return root;

        int deepest_level = 0;
        unordered_map<TreeNode*, TreeNode*> umap_node_to_parent;
        umap_node_to_parent[root] = nullptr;


        dfs(root, 0, deepest_level, umap_node_to_parent);

        queue<TreeNode*> queue;
        queue.push(root);
        int level = 0;

        /* BFS */
        while ( ! queue.empty() && level < deepest_level)
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                TreeNode* node = queue.front();
                queue.pop();

                if (node->left)
                    queue.push(node->left);

                if (node->right)
                    queue.push(node->right);
            }

            level++;
        }

        unordered_set<TreeNode*> uset;
        while ( ! queue.empty())
        {
            uset.insert(queue.front());
            queue.pop();
        }

        while (uset.size() > 1)
        {
            unordered_set<TreeNode*> tmp = {};

            for (const auto& node : uset)
                tmp.insert(umap_node_to_parent[node]);

            uset.clear();
            uset = tmp;
        }

        TreeNode* lca = *uset.begin();

        return lca;
    }

private:
    void dfs(TreeNode* root, int level, int& deepest_level, unordered_map<TreeNode*, TreeNode*>& umap_node_to_parent)
    {
        if ( ! root)
            return;

        deepest_level = max(deepest_level, level);

        if (root->left)
            umap_node_to_parent[root->left] = root;

        if (root->right)
            umap_node_to_parent[root->right] = root;

        dfs(root->left,  level+1, deepest_level, umap_node_to_parent);
        dfs(root->right, level+1, deepest_level, umap_node_to_parent);
    }
};
