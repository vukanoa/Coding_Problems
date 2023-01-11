#include <iostream>
#include <stack>


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

	Base case:
	If root is nullptr just return immediately.

	Until you find a node with both "left" and "right" pointers pointing to
	nullptr and stack is Empty do:

	If root->right does exist, push it onto the stack.

	If root->left does exist, make root's right pointer point to this node and
	make root->left point to nullptr since that is a requirement from the
	Description problem.

	If root->left does NOT exist then make root's right point to the node that
	is on top of the stack and pop the stack.

	However if neither root->left exists nor does stack contain an element
	make root->right = nullptr, just in case, and break the while loop.

	At the end of the while loop always move root to root->right(next element).

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    void flatten(TreeNode* root)
    {
        if (root == nullptr)
            return;

        std::stack<TreeNode *> stack;

        while (1)
        {
            if (root->right != nullptr)
                stack.push(root->right);

            if (root->left != nullptr)
            {
                root->right = root->left;
                root->left = nullptr;
            }
            else if (!stack.empty())
            {
                TreeNode* node = stack.top();
                stack.pop();
                root->right = node;
            }
            else
            {
                root->right = nullptr;
                break;
            }

            root = root->right;
        }
    }
};


void
print_list(TreeNode *head)
{
    TreeNode* cur = head;
	printf("\n\t");

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


int
main()
{
	Solution sol;

	/* Example 1 */
	// TreeNode fifteen(15);
	// TreeNode seven(7);
	// TreeNode twenty(20, &fifteen, &seven);
	// TreeNode nine(9);
	// TreeNode three(3, &nine, &twenty);
	// TreeNode* root = &three;
	/*
		___________
		_____3_____
		__9_____20_
		______15__7
	*/


	/* Example 2 */
	// TreeNode one(-1);
	// TreeNode* root = &one;


	/* Example 3 */
	// TreeNode one(1);
	// TreeNode* root = &one;


	/* Example 4 */
	// TreeNode* root = nullptr;


	/* Example 5 */
	// TreeNode two(2);
	// TreeNode one(1, &two, nullptr);
	// TreeNode* root = &one;
	/*
		_____
		__1__
		2____
	*/


	/* Example 6 */
	// TreeNode five(5);
	// TreeNode four(4, &five, nullptr);
	// TreeNode three(3, &four, nullptr);
	// TreeNode two(2, &three, nullptr);
	// TreeNode one(1, &two, nullptr);
	// TreeNode* root = &one;
	/*
		_______________________1_______________________
		___________2___________________________________
		_____3_________________________________________
		__4____________________________________________
		5______________________________________________
	*/


	/* Example 7 */
	TreeNode seven(7);
	TreeNode five(5, &seven, nullptr);
	TreeNode four(4);
	TreeNode two(2, &four, &five);
	TreeNode six(6);
	TreeNode three(3, nullptr, &six);
	TreeNode one(1, &two, &three);
	TreeNode* root = &one;
	/*
		_______________________
		___________1___________
		_____2___________3_____
		__4_____5___________6__
		______7________________
	*/


	std::cout << "\n\t==========================================";
	std::cout << "\n\t=== FLATTEN BINARY TREE TO LINKED LIST ===";
	std::cout << "\n\t==========================================\n\n";

	std::cout << "\n\tFlattened Binary Tree to Linked List:\n";

	/* Solution */
	sol.flatten(root);
	print_list(root);

	return 0;
}
