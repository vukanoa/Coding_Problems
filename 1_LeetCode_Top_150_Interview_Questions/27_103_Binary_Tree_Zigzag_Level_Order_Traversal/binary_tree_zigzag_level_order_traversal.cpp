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

    Very similar to classical "Level order" Traversal, however, we must use a
    deque instead of a queue, since we have to push elements in different order
    based on the level we're on.

    If the "results" vector's size is an EVEN number, we're going to do the
    same thing as we did in classical "Level order" Traversal.

    However, once the "results" vector's size is an ODD number, we're going to
    be popping elements form the back instead of front and we're going to be
    checking current node's right first and the current node's left.

    Also we won't push "left" and "right" nodes(if they exist) to the end of
    the "deque", instead we're going to be pushing it to the front.

    Summary:
        Once the results.size() is EVEN, we do the same as in "Level order":
            pop elements  from the front
            push elements to   the back  // Push "left" & "right" if they exist

        Once the results.size() is ODD,  we do the opposite:
            pop  elements from the back
            push elements to   the front // Push "left" & "right" if they exist

*/

/* Time  Beats: 100.00% */
/* Space Beats:   7.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(max nodes at a single level) */
class Solution {
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<std::vector<int>> results;

        std::deque<TreeNode*> deque;
        deque.push_back(root);

        while (!deque.empty())
        {
            std::vector<int> curr_level;

            int size = deque.size();
            for (int i = 0; i < size; i++)
            {
                if (results.size() % 2 == 0) // From left to right
                {
                    TreeNode* node = deque.front();
                    deque.pop_front();

                    /* Left First */
                    if (node->left)
                        deque.push_back(node->left);

                    /* Right Second*/
                    if (node->right)
                        deque.push_back(node->right);

                    curr_level.push_back(node->val);
                }
                else
                {
                    TreeNode* node = deque.back();
                    deque.pop_back();

                    /* Right First */
                    if (node->right)
                        deque.push_front(node->right);

                    /* Left Second */
                    if (node->left)
                        deque.push_front(node->left);

                    curr_level.push_back(node->val);
                }
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
    Solution sol;


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
    std::vector<std::vector<int>> results = sol.zigzagLevelOrder(root);


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
