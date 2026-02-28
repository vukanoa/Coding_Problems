/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1325) Delete Leaves With a Given Value
    ======================================

    ============
    Description:
    ============

    Given a binary tree root and an integer target, delete all the leaf nodes
    with value target.

    =====
    Note: that once you delete a leaf node with value target, if its parent
          node becomes a leaf node and has the value target, it should also be
          deleted (you need to continue doing that until you cannot).
    =====

    ================================================================
    FUNCTION: TreeNode* removeLeafNodes(TreeNode* root, int target);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

               1                            1                  1
             /   \                        /   \                  \
            /     \                      /     \                  \
           /       \        ===>        /       \     ===>         \
          /         \                  /         \                  \
         /           \                /           \                  \
        2             3              2             3                  3
       /             / \                            \                  \
      /             /   \                            \                  \
     /             /     \                            \                  \
    2             2       4                            4                  4

    Input: root = [1,2,3,2,null,2,4], target = 2
    Output: [1,null,3,null,4]
    Explanation: Leaf nodes in green with value (target = 2) are removed
                 (Picture in left).  After removing, new nodes become leaf
                 nodes with value (target = 2) (Picture in center).


    --- Example 2 ---
               1                              1
             /   \                          /
            /     \                        /
           /       \        ===>          /
          /         \                    /
         /           \                  /
        3             3                3
       / \                              \
      /   \                              \
     /     \                              \
    3       2                              2
    Input: root = [1,3,3,3,2], target = 3
    Output: [1,3,null,null,2]


    --- Example 3 ---
                 1                     1               1              1
                /                     /               /
               /                     /               /
              /        ==>          /      ==>      /      ==>
             /                     /               /
            /                     /               /
           2                     2               2
          /                     /
         /                     /
        /                     /
       2                     2
      /
     /
    2
    Input: root = [1,2,null,2,null,2], target = 2
    Output: [1]
    Explanation: Leaf nodes in green with value (target = 2) are removed at
                 each step.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 3000].
    1 <= Node.val, target <= 1000

*/

#include <stack>
#include <unordered_map>
#include <unordered_set>
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

    A standard DFS traversal on a Binary Tree. If you find this difficult, make
    sure to solve EASY Binary Tree Problems from Blind_75.

    After that, this becomes a breeze.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.09% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target)
    {
        if ( ! root)
            return nullptr;

        root->left  = removeLeafNodes(root->left,  target);
        root->right = removeLeafNodes(root->right, target);

        // I can't prevent Memory Leak because of LeetCode's Memory management
        if (root->val == target && ! root->left && ! root->right)
            return nullptr;

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however this Implementation prevents Memory Leak.

    The root of the tree (the original input) is owned by LeetCode, so you must
    never delete it -- otherwise, the framework will try to free it afterward
    and crash. 

    Nodes are freed(delete) anyway by the LeetCode, so we can't do it manually.
    Hwever, if for some reason you want to do it manually, then you can simply
    free all of the nodes EXCEPT for the original root that is the Input of the
    entire Tree.

*/

// LeetCode times are weird sometimes.
/* Time  Beats: 76.17% */
/* Space Beats:  9.62% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Without_Memory_Leak {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target)
    {
        return dfs(root, target, nullptr);
    }

private:
    TreeNode* dfs(TreeNode* root, int target, TreeNode* parent)
    {
        if ( ! root)
            return nullptr;

        root->left  = dfs(root->left,  target, root);
        root->right = dfs(root->right, target, root);

        if (root->val == target && ! root->left && ! root->right)
        {
            if (parent)
                delete root;

            return nullptr;
        }

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   4.78% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Iterative_Postorder {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target)
    {
        unordered_set<TreeNode*> visited;

        unordered_map<TreeNode*, TreeNode*> parent;
        parent[root] = nullptr;

        stack<TreeNode*> stack;
        stack.push(root);

        while ( ! stack.empty())
        {
            TreeNode* curr = stack.top();
            stack.pop();

            if (curr->val == target && curr->left == curr->right) // Leaf
            {
                TreeNode* curr_parent = parent[curr];

                if (curr_parent == nullptr) // Global Root needs to be removed
                    return nullptr;

                if (curr_parent->left == curr)
                    curr_parent->left = nullptr;

                if (curr_parent->right == curr)
                    curr_parent->right = nullptr;

            }
            else if (visited.find(curr) == visited.end()) // curr NOT visited
            {
                visited.insert(curr);
                stack.push(curr);

                if (curr->left)
                {
                    stack.push(curr->left);
                    parent[curr->left] = curr;
                }

                if (curr->right)
                {
                    stack.push(curr->right);
                    parent[curr->right] = curr;
                }
            }
        }

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea as above, however we do NOT need to use a HashMap to remember the
    parent of the current node. Instead, we know that the top of the stack is
    always the parent of the current node.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  13.57% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Optimal_Iterative_Postorder {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target)
    {
        stack<TreeNode*> stack;
        TreeNode* curr = root;
        TreeNode* last_right_node = nullptr;

        while (curr || ! stack.empty())
        {
            // Find the leftmost node
            while (curr)
            {
                stack.push(curr);
                curr = curr->left;
            }

            curr = stack.top();

            // Find the rightmost node that wasn't processed yet
            if (curr->right && curr->right != last_right_node)
            {
                curr = curr->right;
                continue;
            }

            stack.pop();

            // If it's a LEAF
            if (curr->val == target && curr->right == curr->left)
            {
                if (stack.empty()) // Global Root needs to be removed
                    return nullptr;

                TreeNode* curr_parent = stack.top();

                // Unlink the current node from its parent
                if (curr_parent->left == curr)
                    curr_parent->left = nullptr;
                else
                    curr_parent->right = nullptr;
            }

            last_right_node = curr;
            curr = nullptr;
        }

        return root;
    }
};
