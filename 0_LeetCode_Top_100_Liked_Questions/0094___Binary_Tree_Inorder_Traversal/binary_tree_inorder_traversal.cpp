#include <iostream>
#include <vector>
#include <stack>

/*
    ============
    === EASY ===
    ============

    =================================
    94) Binary Tree Inorder Traversal
    =================================

    ============
    Description:
    ============

    Given the "root" of a binary tree, return the inorder traversal of its
    nodes' values.

    =======================================================
    FUNCTION: vector<int> inorderTraversal(TreeNode* root);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [1, null, 2, 3]
    Output: [1, 3, 2]

    --- Example 2 ---
    Input:  root = []
    Output: []

    --- Example 3 ---
    Input:  root = [1]
    Output: [1]

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 100]
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

/* Time  Beats:   100% */
/* Space Beats: 98.93% */

/*
    Time  Complexity: O(n)

    Each node is visited only once.
*/
/*
    Space Complexity: O(n)

    Recursive calls of "inorder" function create a call stack which requires
    O(n) space in the worst case.

    Also, using the vector "vec" requires O(n) space.

    So O(n) + O(n) => O(n + n) => O(2 * n) => O(n)
*/
class Solution_Recursive {
public:
    std::vector<int> inorderTraversal(TreeNode* root)
    {
        std::vector<int> result;
        inorder(root, result);

        return result;
    }

private:
   void inorder(TreeNode* root, std::vector<int>& result)
    {
        if (!root)
            return;

        inorder(root->left, result);
        result.push_back(root->val);
        inorder(root->right, result);
    }
};




/* Time  Beats:   100% */
/* Space Beats: 73.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Iterative {
public:
    std::vector<int> inorderTraversal(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        std::stack<TreeNode*> stack;

        while (true)
        {
            if (root)
            {
                stack.push(root);
                root = root->left;
            }
            else
            {
                if (stack.empty())
                    break;

                root = stack.top();
                stack.pop();

                result.push_back(root->val);

                root = root->right;
            }
        }

        return result;
    }
};

int
main()
{
    Solution_Recursive sol_rec;
    Solution_Iterative sol_iter;

    /* Example 1 */
    TreeNode three(3);
    TreeNode two(2, &three, nullptr);
    TreeNode* one = new TreeNode(1, nullptr, &two);

    /* Example 2 */
    // Root is nullptr
    // TreeNode* one = nullptr;

    /* Example 3 */
    // TreeNode* one = new TreeNode(1);

    std::cout << "\n\t=====================================";
    std::cout << "\n\t=== BINARY TREE INORDER TRAVERSAL ===";
    std::cout << "\n\t=====================================\n";


    /* Write Input */
    std::cout << "\n\tTODO: Visual print of a binary Tree\n";


    /* Solution */
    // std::vector<int> result = sol_rec.inorderTraversal(one);
    std::vector<int> result = sol_iter.inorderTraversal(one);


    /* Write Output */
    bool first = true;
    std::cout << "\n\tInorder: [";
    for (auto x: result)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
