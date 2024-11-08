#include <iostream>
#include <stack>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    114) Flatten Binary Tree to Linked List
    =======================================

    ============
    Description:
    ============

    Given the "root" of a binary tree, flatten the tree into a 'linked list':
        - The 'linked list' should use the same TreeNode class where the
          "right" child pointer points to the next node in the list and the
          "left" child pointer is always "null".

        - The 'linked list' should be in the same order as a pre-order
          traversal of the binary tree.

    =======================================
    FUNCTION: void flatten(TreeNode* root);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [1, 2, 5, 3, 4, null, 6]
    Output: [1, null, 2, null, 3, null, 4, null, 5, null, 6]

    --- Example 2 ---
    Input:  root = []
    Output: []

    --- Example 3 ---
    Input:  root = [0]
    Output: [0]

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

    It's very intuitive.
    Since we're required to make a Linked List in preorder, we'll do a DFS on
    the BST and while iterating through nodes, we'll push right subtrees on the
    stack.

    Since it is required to form a Linked list using only "right" pointers and
    since it is required to make "left" pointers point to nullptr at the end,
    we have to do a few things.

    Since we're doing a DFS, we'll always go to the left. However, since we
    also have to make every "left" pointer point to nullptr, we have to save
    left subtree in a temporary pointer called "left_subtree" which we will
    pass as the next node to process and assign it to root->right.
    We'll also say: root->left = nullptr.

    Though, we only have to save left subtree if it is not nullptr.

    Since we're doing DFS recursively, every time we enter the function, check
        if the root argument is nullptr then:
            pop from the stack(right subtree) and continue from there.

    There's only one edge case. If the root argument is nullptr and the stack
    is empty(That happens only once we try to process the left subtree of the
    very last node in the tree, which is the deepest, right most node).
    In that case immediately return nullptr.

*/

/* Time  Beats: 92.94% */
/* Space Beats: 20.96% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
private:
    std::stack<TreeNode*> stack;

    TreeNode* dfs(TreeNode* root)
    {
        if (root == nullptr)
        {
            if (stack.empty())
                return nullptr;

            root = stack.top();
            stack.pop();
        }

        if (root->right != nullptr)
            stack.push(root->right);

        TreeNode* left_subtree = nullptr;
        if (root->left != nullptr)
            left_subtree = root->left;

        root->left = nullptr;
        root->right = dfs(left_subtree);

        return root;
    }

public:
    void flatten(TreeNode* root)
    {
        root = dfs(root);
    }
};


void
print_list(TreeNode *head)
{
    TreeNode* cur = head;
    printf("\t\tList: ");

    if (head == nullptr)
        printf("Empty");

    while (cur)
    {
        if (cur->right == nullptr)
            printf("%d ", cur->val);
        else
            printf("%d -> ", cur->val);

        // It is said to link nodes with "right" pointers
        cur = cur->right;
    }
    printf("\n\n");
}




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
    std::cout << "\n\t\tTree: [";
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
        __9_____20_
        ______15__7
    */
    // TreeNode fifteen(15);
    // TreeNode seven(7);
    // TreeNode twenty(20, &fifteen, &seven);
    // TreeNode nine(9);
    // TreeNode three(3, &nine, &twenty);
    // TreeNode* root = &three;


    /* Example 2 */
    /*
        ___-1___
    */
    // TreeNode one(-1);
    // TreeNode* root = &one;


    /* Example 3 */
    /*
        ___1___
    */
    // TreeNode one(1);
    // TreeNode* root = &one;


    /* Example 4 */
    /*
        Empty
    */
    // TreeNode* root = nullptr;


    /* Example 5 */
    /*
        _____
        __1__
        2____
    */
    // TreeNode two(2);
    // TreeNode one(1, &two, nullptr);
    // TreeNode* root = &one;


    /* Example 6 */
    /*
        _______________________1_______________________
        ___________2___________________________________
        _____3_________________________________________
        __4____________________________________________
        5______________________________________________
    */
    // TreeNode five(5);
    // TreeNode four(4, &five, nullptr);
    // TreeNode three(3, &four, nullptr);
    // TreeNode two(2, &three, nullptr);
    // TreeNode one(1, &two, nullptr);
    // TreeNode* root = &one;


    /* Example 7 */
    /*
        _______________________
        ___________1___________
        _____2___________3_____
        __4_____5___________6__
        ______7________________
    */
    TreeNode seven(7);
    TreeNode five(5, &seven, nullptr);
    TreeNode four(4);
    TreeNode two(2, &four, &five);
    TreeNode six(6);
    TreeNode three(3, nullptr, &six);
    TreeNode one(1, &two, &three);
    TreeNode* root = &one;


    std::cout << "\n\t==========================================";
    std::cout << "\n\t=== FLATTEN BINARY TREE TO LINKED LIST ===";
    std::cout << "\n\t==========================================\n";


    /* Write Input */
    print_levelorder(root);


    /* Solution */
    sol.flatten(root);


    /* Write Output */
    std::cout << "\n\tFlattened Binary Tree to Linked List:\n";
    print_list(root);


    return 0;
}
