#include <iostream>
#include <queue>

/*
    ============
    === EASY ===
    ============

    ============================
    543) Diameter of Binary Tree
    ============================

    ============
    Description:
    ============

    Given the "root" of a binary tree, return the length of the diameter of the
    tree.

    The diameter of a binary tree is the length of the longest path between any
    two nodes in a tree. This path may or may not pass through the "root".

    The length of a path between two nodes is represented by the number of
    edges between them.

    ===================================================
    FUNCTION: int diameterOfBinaryTree(TreeNode* root);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [1, 2, 3, 4, 5]
    Output: 3
    Explanation: 3 is the length of the path [4, 2, 1, 3] or [5, 2, 1, 3]

    --- Example 2 ---
    Input:  root = [1, 2]
    Output: 1

    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4]
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

    First, you MUST solve LeetCode 104. "Maximum Depth of a Binary Tree".

    After that, it's trivial.

*/

/* Time  Beats: 38.62% */
/* Space Beats:  7.01% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root)
    {
        int result = 0;
        depth(root, result);

        return result;
    }

private:
    int depth(TreeNode* root, int& result)
    {
        if (!root)
            return 0;

        int left  = depth(root->left, result);
        int right = depth(root->right, result);

        result = std::max(result, left + right);

        return 1 + std::max(left, right);
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
    std::cout << "\n\t\t\t(TODO: Implement a Visual representation of a Binary Tree)\n\n";
    std::cout << "\n\t*** Level Order ***";
    std::cout << "\n\tTree: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";
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
    Solution     sol;


    /* Example 1 */
    /*
        ___________
        _____1_____
        __2_____3__
        4___5______
    */
    // TreeNode one(1);
    // TreeNode two(2);
    // TreeNode three(3);
    // TreeNode four(4);
    // TreeNode five(5);

    // one.left   = &two;
    // one.right  = &three;
    // two.left   = &four;
    // two.right  = &five;

    // TreeNode* root = &one;




    /* Example 2 */
    /*
        _____
        __1__
        2____
    */
    // TreeNode one(1);
    // TreeNode two(2);

    // one.left = &two;

    // TreeNode* root = &one;




    /* Example 3 */
    /* 1 */
    // TreeNode one(1);

    // TreeNode* root = &one;



    /* Example 3 */
    /*
        _______________________
        ___________5___________
        _____4___________8_____
        __11__________13____4__
        7____2____________5____
    */
    // TreeNode five(5);
    // TreeNode four(4);
    // TreeNode eight(8);
    // TreeNode eleven(11);
    // TreeNode thirteen(13);
    // TreeNode four_2(4);
    // TreeNode seven(7);
    // TreeNode two(2);
    // TreeNode five_2(5);

    // five.left    = &four;
    // five.right   = &eight;
    // four.left    = &eleven;
    // eight.left   = &thirteen;
    // eight.right  = &four_2;
    // eleven.left  = &seven;
    // eleven.right = &two;
    // four_2.left  = &five_2;

    // TreeNode* root = &five;




    /* Example 4 */
    /*
        _______________________
        ___________10__________
        _____5__________-3_____
        __3_____2__________11__
        3__-2_____1____________
    */
    TreeNode ten(10);
    TreeNode five(5);
    TreeNode three(3);
    TreeNode two(2);
    TreeNode three_2(3);
    TreeNode minus_two(-2);
    TreeNode one(1);

    ten.left          = &five;
    five.left         = &three;
    five.right        = &two;
    three.left        = &three_2;
    three.right       = &minus_two;
    two.right         = &one;

    TreeNode* root = &ten;




    std::cout << "\n\t===============================";
    std::cout << "\n\t=== DIAMETER OF BINARY TREE ===";
    std::cout << "\n\t===============================\n";


    /* Write Input */
    print_levelorder(root);


    /* Solution */
    int diameter = sol.diameterOfBinaryTree(root);


    /* Write Output */
    std::cout << "\n\tDiameter: " << diameter << "\n\n";


    return 0;
}
