#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    102) Binary Tree Level Order Traversal
    ======================================

    ============
    Description:
    ============

    Given the "root" of a binary tree, return the level ordder traversal of its
    nodes' values. (i.e., from left to right, level by level).

    =========================================================
    FUNCTION: vector<vector<int>> levelOrder(TreeNode* root);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [3, 9, 20, null, null, 15, 7]
    Output: [[3], [9, 20], [15, 7]]

    --- Example 2 ---
    Input:  root = [1]
    Output: [[1]]

    --- Example 3 ---
    Input:  root = []
    Output: []

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 2000]
    -1000 <= Node.val <= 1000

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

    It's just BFS. The only "tricky" part is to know when the current level
    ends and the next one begins.

    We do that but calculating the number of nodes in the queue before we enter
    the "for" loop.

    We don't push null nodes in the queue.

    Also, we don't push empty vector "level" into the "results" vector.
    That happens only in the last level.

    ___________
    _____1_____
    __2_____3__
    4___5_6___7

*/

/*
    ------------
    --- IDEA ---
    ------------

    Basic BFS Implementation.

    It's like a "multiplication table", you have to commit it to memory.
    It's a fundamental technique for Graphs(and Trees, but Trees are Graphs).

*/

/* Time  Beats: 88.21% */
/* Space Beats: 26.52% */

/*
    Time  Complexity: O(n)
*/
/*
    Space Complexity: O(n)

    The biggest level of the tree could be n/2, that's how Trees work. At least
    Binary Trees.
*/
class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<std::vector<int>> results;
        std::queue<TreeNode*> queue;
        queue.push(root);

        /* BFS */
        while (!queue.empty())
        {
            std::vector<int> curr_level;

            int size = queue.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode* node = queue.front();
                queue.pop();

                if (node->left)
                    queue.push(node->left);

                if (node->right)
                    queue.push(node->right);

                curr_level.push_back(node->val);
            }

            results.push_back(curr_level);
        }

        return results;
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

            if (!node)
            {
                vector_print.push_back("null");
                continue;
            }
            else
                vector_print.push_back(std::to_string(node->val));

            if (node->left)
                queue.push(node->left);
            else
                queue.push(nullptr);

            if (node->right)
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
    Solution sol;

    /* Example 1 */
    TreeNode fifteen(15);
    TreeNode seven(7);
    TreeNode twenty(20, &fifteen, &seven);
    TreeNode nine(9);
    TreeNode three(3, &nine, &twenty);

    TreeNode* root = &three;


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


    std::cout << "\n\t=========================================";
    std::cout << "\n\t=== BINARY TREE LEVEL ORDER TRAVERSAL ===";
    std::cout << "\n\t=========================================\n";


    /* Write Input */
    print_levelorder(root);


    /* Solution */
    std::vector<std::vector<int>> results = sol.levelOrder(root);


    /* Write Output */
    bool first = true;
    std::cout << "\n\tResults: [";
    for (auto x: results)
    {
        if (!first)
            std::cout << ", ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            std::cout << xx;
            first_first = false;
        }
        std::cout << "]";

        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
