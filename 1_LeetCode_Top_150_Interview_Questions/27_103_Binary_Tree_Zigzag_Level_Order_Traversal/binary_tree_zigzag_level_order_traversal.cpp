#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    103) Binary Tree Zigzag Level Order Traversal
    =============================================

    ============
    Description:
    ============

    Given the root of a binary tree, return the zigzag level order traversal of
    its nodes' values. (i.e., from left to right, then right to left for the
    next level and alternate between).

    ===============================================================
    FUNCTION: vector<vector<int>> zigzagLevelOrder(TreeNode* root);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        ___________
        _____3_____
        __9____20__
        _____15___7

    Input: root = [3,9,20,null,null,15,7]
    Output: [[3],[20,9],[15,7]]




    --- Example 2 ---

        -----
        __1__

    Input: root = [1]
    Output: [[1]]




    --- Example 3 ---


    Input: root = []
    Output: []




    *** Constraints ***
    The number of nodes in the tree is in the range [0, 2000].
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

    _______________________
    ___________1___________
    _____2___________3_____
    __4_____5_____6_____7__
    8___9_10_11_12_13_14_15

    There's this IDEA out there that this problem should be done using only
    one deque in which you push an entire level and you reverse it at every
    odd level. However, that's unnecessary.

    The Time Complexity is still O(n), but you have more operations. The wall
    time clock is longer.

    Instead, we can use two vectors.
    In one we're pushing only when we are at the odd level and in the other we
    only push when we are at the even level.

    We always take the elements from the back of the vector.

    When we're at the ODD  level, we first push Left  child and then the Right.
    When we're at the EVEN level, we first push Right child and then the Left.

    That's it. This is faster.

*/

/* Time  Beats:  100% */
/* Space Beats: 27.23% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(max nodes at a single level) */
class Solution{
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        if (root == nullptr)
            return {};

        std::vector<std::vector<int>> results;
        results.push_back({root->val});

        std::vector<TreeNode*> left_to_right;
        std::vector<TreeNode*> right_to_left;

        bool zag = true;

        // Left
        if (root->left != nullptr)
            right_to_left.push_back(root->left);

        // Right
        if (root->right != nullptr)
            right_to_left.push_back(root->right);

        while (!left_to_right.empty() || !right_to_left.empty())
        {
            if (zag)
            {
                std::vector<int> level;

                while (!right_to_left.empty())
                {
                    TreeNode* tmp = right_to_left.back();
                    right_to_left.pop_back();

                    level.push_back(tmp->val);

                    // Right
                    if (tmp->right != nullptr)
                        left_to_right.push_back(tmp->right);

                    // Left
                    if (tmp->left != nullptr)
                        left_to_right.push_back(tmp->left);
                }

                results.push_back(level);
                zag = false;
            }
            else // left_to_right
            {
                std::vector<int> level;

                while (!left_to_right.empty())
                {
                    TreeNode* tmp = left_to_right.back();
                    left_to_right.pop_back();

                    level.push_back(tmp->val);

                    // Left
                    if (tmp->left != nullptr)
                        right_to_left.push_back(tmp->left);

                    // Right
                    if (tmp->right != nullptr)
                        right_to_left.push_back(tmp->right);
                }

                results.push_back(level);
                zag = true;
            }
        }

        return results;
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    Similar IDEA, this one uses deque and, therefore, is cleaner.

*/

/* Time  Beats: 100% */
/* Space Beats: 54.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(max nodes at a single level) */
class Solution_Deque{
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        if (!root)
            return {};

        std::deque<TreeNode*> deque;
        deque.push_back(root);

        std::vector<std::vector<int>> results;

        bool from_left_to_right = true;

        while (!deque.empty())
        {
            int size = deque.size();
            std::vector<int> tmp;

            for (int i = 0; i < size; i++)
            {
                if (from_left_to_right)
                {
                    TreeNode* node = deque.front();
                    deque.pop_front();


                    tmp.push_back(node->val);

                    if (node->left)
                        deque.push_back(node->left);

                    if (node->right)
                        deque.push_back(node->right);
                }
                else
                {
                    TreeNode* node = deque.back();
                    deque.pop_back();

                    tmp.push_back(node->val);

                    if (node->right)
                        deque.push_front(node->right);

                    if (node->left)
                        deque.push_front(node->left);
                }
            }

            results.push_back(tmp);

            // Change from Zig to Zag and vice versa
            from_left_to_right = !from_left_to_right;
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
    if (root == nullptr)
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
    Solution       sol;
    Solution_Deque sol_deque;


    /* Example 1 */
    /*
        ___________
        _____3_____
        __9____20__
        _____15___7
    */
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
    /*
        _______________________
        ___________1___________
        _____2___________3_____
        __4_____5_____6_____7__
        8___9_10_11_12_13_14_15
    */
    TreeNode fifteen (15);
    TreeNode fourteen(14);
    TreeNode thirteen(13);
    TreeNode twelve  (12);
    TreeNode eleven  (11);
    TreeNode ten     (10);
    TreeNode nine    (9);
    TreeNode eight   (8);

    TreeNode seven(7, &fourteen, &fifteen);
    TreeNode six  (6, &twelve,   &thirteen);
    TreeNode five (5, &ten,      &eleven);
    TreeNode four (4, &eight,    &nine);

    TreeNode three(3, &six,  &seven);
    TreeNode two  (2, &four, &five);
    TreeNode one  (1, &two,  &three);

    TreeNode* root = &one;



    std::cout << "\n\t================================================";
    std::cout << "\n\t=== BINARY TREE ZIGZAG LEVEL ORDER TRAVERSAL ===";
    std::cout << "\n\t================================================\n";


    /* Write Input */
    print_levelorder(root);


    /* Solution */
    // std::vector<std::vector<int>> results = sol.zigzagLevelOrder(root);
    std::vector<std::vector<int>> results = sol_deque.zigzagLevelOrder(root);


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

