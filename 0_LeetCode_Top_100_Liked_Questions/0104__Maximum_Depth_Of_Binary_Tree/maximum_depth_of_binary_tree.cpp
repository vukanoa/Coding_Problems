#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === EASY ===
    ============

    =================================
    104) Maximum Depth of Binary Tree
    =================================

    ============
    Description:
    ============

    Given the "root" of a binary tree, return its maximum depth.

    A binary Tree's maximum depth is the nmber of nodes along the longest path
    from the root node down to the farthest leaf node.

    =======================================
    FUNCTION: int maxDepth(TreeNode* root);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [3, 9, 20, null, null, 15, 7]
    Output: 3

    --- Example 2 ---
    Input:  root = [1, null, 2]
    Output: 2

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 10^4]
    -100 <= Node.val <= 100

*/

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

    The base case - If we have a nullptr as an input, we should return 0.

    Let's assume that we know the max depth of the left subtree and the max
    depth od the right subtree. And currently we're at the parent node of those
    two subtrees.

    Ask yourself - How would you get the maximum depth of the entire tree
    including this current node?

    Simply take the deeper subtree of the two and add 1(the current node).


    Notice that if the Input was only a single node, our base case + recursion
    would do the trick.

    Both the left and the right subtrees' depth would be 0 and if we take the
    max out of those two subtrees and add 1(the current node) we'll get the
    maximum depth of this entire single-node Binary Tree.

    That's why we're able to perform this elegant recursion.

    We are doing an inorder DFS and we're doing what we described above.

*/

/* Time  Beats: 100% */
/* Space Beats: 34.31% */

/*    Time  Complexity: O(n) */
/*
    Space Complexity: O(h)
    Where 'h' is the height of the tree, for the recursive stack.
*/
class Solution{
public:
    int maxDepth(TreeNode* root)
    {
        if ( ! root)
            return 0;

        return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, implemented in a worse way. It's good to be able to see
    both ways because you get to appreciate the above implementation more.

*/

/* Time  Beats: 61.79% */
/* Space Beats: 98.60% */

/* Time  Complexity: O(n) */
/*
    Space Complexity: O(h)
    Where 'h' is the height of the tree, for the recursive stack.
*/
class Solution_2 {
public:
    int maxDepth(TreeNode* root)
    {
        return depth(root, 0);
    }

private:
    int depth(TreeNode* root, int level)
    {
        if ( ! root)
            return level;

        return std::max(depth(root->left, level+1), depth(root->right, level+1));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent idea to both above, but coded in an even worse way than
    Solution_2.

    Again, it's good to be able to see all the ways of implementing the same
    idea because that way you get to appreciate the very first Solution in this
    file.

*/

/* Time  Beats: 73.50% */
/* Space Beats: 19.35% */

/*    Time  Complexity: O(n) */
/*
    Space Complexity: O(h)
    Where 'h' is the height of the tree, for the recursive stack.
*/
class Solution_3 {
public:
    int maxDepth(TreeNode* root)
    {
        int max = 0;
        dfs(root, 0, max);

        return max;
    }

private:
    void dfs(TreeNode* root, int current, int& max)
    {
        if ( ! root)
            return;

        // If current is not nullptr, add it to the current path and check max
        max = std::max(max, current + 1);

        dfs(root->left , current + 1, max);
        dfs(root->right, current + 1, max);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, implemented in an Iterative order which is even worse than
    Solution 3.

    Again, once you see all Four Solutions, you get to appreciate the first one
    a lot more.

*/

/* Time  Beats: 67.09% */
/* Space Beats:  9.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Iterative_DFS_Preorder {
public:
    int maxDepth(TreeNode* root)
    {
        std::stack<std::pair<TreeNode*, int>> stack;

        stack.push({root, 1});
        int result = 0;

        while ( ! stack.empty())
        {
            std::pair<TreeNode*, int> entry = stack.top();
            stack.pop();

            TreeNode* node = entry.first;
            int depth = entry.second;

            if (node)
            {
                result = std::max(result, depth);

                // We are adding nullptr as well
                stack.push({node->left,  depth + 1});
                stack.push({node->right, depth + 1});
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Using BFS(i.e. Level-Order)

*/

/* Time  Beats: 88.24% */
/* Space Beats:  9.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_BFS {
public:
    int maxDepth(TreeNode* root)
    {
        if (root == nullptr)
            return 0;

        int level = 0;
        std::queue<TreeNode*> queue;

        // Emplace is a bit faster than "push" for custom Data Types
        queue.emplace(root);

        while ( ! queue.empty())
        {
            int nodes_at_this_level = queue.size();

            for (int i = 0; i < nodes_at_this_level; i++)
            {
                TreeNode* node = queue.front();
                queue.pop(); // Pop from the front because it's a queue

                if (node->left)
                    queue.emplace(node->left);

                if (node->right)
                    queue.emplace(node->right);
            }

            level++;
        }

        return level;
    }
};




/*
    =============================
    === This is just printing ===
    =============================
*/

void
print_array(std::vector<std::string>& nums)
{
    bool first = true;
    std::cout << "\n\t*** Level Order ***";
    std::cout << "\n\tTree: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";
}


void
print_levelorder(TreeNode* root)
{
    if (!root)
        return;

    std::queue<TreeNode*> queue;
    queue.push(root);

    std::vector<std::string> vector_print;

    while (!queue.empty())
    {
        int size = queue.size();

        for (int i = 0; i < size; i++)
        {
            TreeNode* node = queue.front();
            queue.pop();

            if (node == nullptr)
            {
                vector_print.push_back("null");
                continue;
            }
            else
                vector_print.push_back(std::to_string(node->val));

            if (node->left != nullptr)
                queue.push(node->left);
            else
                queue.push(nullptr);

            if (node->right != nullptr)
                queue.push(node->right);
            else
                queue.push(nullptr);
        }
    }

    int x = vector_print.size() - 1;
    while (vector_print[x] == "null")
    {
        vector_print.pop_back();
        x--;
    }

    print_array(vector_print);
}


int
main()
{
    Solution                        sol;
    Solution_2                      sol_2;
    Solution_3                      sol_3;
    Solution_Iterative_DFS_Preorder sol_iter;
    Solution_BFS                    sol_bfs;


    /* Example 1 */
    // TreeNode fifteen(15);
    // TreeNode seven(7);
    // TreeNode twenty(20, &fifteen, &seven);
    // TreeNode nine(9);
    // TreeNode three(3, &nine, &twenty);

    // TreeNode* root = &three;


    /* Example 2 */
    // TreeNode one(1);

    // TreeNode* root = &one;


    /* Example 3 */
    // TreeNode* root = nullptr;


    /* Example 4 */
    // TreeNode two(2);
    // TreeNode one(1, &two, nullptr);

    // TreeNode* root = &one;


    /* Example 5 */
    // TreeNode five(5);
    // TreeNode four(4, &five, nullptr);
    // TreeNode three(3, &four, nullptr);
    // TreeNode two(2, &three, nullptr);
    // TreeNode one(1, &two, nullptr);

    // TreeNode* root = &one;


    /* Example 6 */
    TreeNode seven(7);
    TreeNode five(5, &seven, nullptr);
    TreeNode four(4);
    TreeNode two(2, &four, &five);
    TreeNode six(6);
    TreeNode three(3, nullptr, &six);
    TreeNode one(1, &two, &three);

    TreeNode* root = &one;


    std::cout << "\n\t======================================";
    std::cout << "\n\t=== MAXIMUM DEPTH OF A BINARY TREE ===";
    std::cout << "\n\t======================================\n";


    /* Write Input */
    print_levelorder(root);


    /* Solution */
    int depth = sol.maxDepth(root);


    /* Write Output */
    std::cout << "\n\tMaximum Depth is: " << depth << "\n\n";


    return 0;
}
