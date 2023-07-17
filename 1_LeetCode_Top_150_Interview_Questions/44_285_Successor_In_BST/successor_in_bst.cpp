#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	285) Successor in BST
	===========================

	============
	Description:
	============

	Given the root of a binary search tree and a node p in it, return the
	in-order successor of that node in the BST. If the given node has no
	in-order successor in the tree, return null.

	The successor of a node p is the node with the smallest key greater than
	p.val.

	=================================================================
	FUNCTION: TreeNode* inorderSuccessor(TreeNode* root, TreeNode p);
	=================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [2, 1, 3], p = 1
	Output: 2

	*** Constraints ***
	Unknown

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

	Since we're given a BST, it means that the next node of given 'p' is always
	the leftmost node in the right subtree.
	
	The basecase is that the root node is the 'p' node, in that case if the
	right subtree exists, return the leftmost node of the right subtree.
	(that is what "successor" function does)

	So let's consider one Example:

	_______________________8_______________________
	___________4______________________15___________
	_____2___________7___________12________________
	________3_____6___________11____14_____________
	________________________10____13_______________

	There are basic Examples and Tricky Examples.

	Basic Example: p = 2
		In this case, we just have to find the 2 in a BST and then if the right
		subtree isn't null, return the leftmost node in the right subtree.

		Pretty much the same as in the base case.
	
	Tricky Example: p = 7
		If you tried the same approach on p = 7, you would returned nullptr,
		however that would not the true.

		7 doesn't have the right subtree, but it doesn't mean that it does not
		have a successor node.

		In this case, the successor is the root node.

		So how can we know that the 7 has a successor node if he doesn't have
		a right subtree?

		We will keep track of the path we've gone to in finding a node, 7 in
		this case. However, we have to notice that the Tricky Example always
		happens once we go to the right at last after which we're on the 'p'
		node.

		So in keeping the track of the path we've gone to find a 'p' node, we
		are going to push a pair of int:(right | left).

		"left" will be designated with a false boolean value, whereas "right"
		will be the opposite - true.

		Again, let's draw the same example for the ease of reading:

		_______________________8_______________________
		___________4______________________15___________
		_____2___________7___________12________________
		________3_____6___________11____14_____________
		________________________10____13_______________

		If 'p' is 7, then the Stack will look like this:

		First we're at the root 8, since that is not equal to 'p', we push the
		value of that node, but we have to see if we're going to push it with
		a false("left") or true("right") value.

		How are we going to determine that?
		Well, it's simply a traversing of a BST. Is 7 less than current node,
		if it is, then go left, but before going left, push the pair on the
		stack.

			The pair is: {15, false};

		So our Stack looks like this:

		|  8: false |
		+-----------+
		|   Stack   |
		+-----------+

		Now we're on the node 4. Is 4 a 'p' node(7)? Not it's not. Is 4 less
		than 7? No, then go right, but before going right push the pair on the
		stack:
			The pair is: {4, true}

		So our Stack looks like this:

		|  4: true  |
		+-----------+
		|  8: false |
		+-----------+
		|   Stack   |
		+-----------+

		Now we're on the node 7, which is the 'p' node. What do we do know?

		Well, first we have to see if the 'p' node has the right subtree. Since
		it does not, then we have to take the use of the Stack.

		So what are we going to do?
		We have to pop elements off of the Stack as long as the top element is
		not with the second value of "false", meaning that we turned left.

		Essentially we're trying to find the last occassion at which we have
		gone to the left. The node which from we've gone to the left is our
		solution, i.e. the successor of the 'p' node.

		After the popping, the Stack looks like this:

		|  8: false |
		+-----------+
		|   Stack   |
		+-----------+

		And we just return the top's element first value. If the Stack is empty
		return null, meaning there is no successor in the tree. (15 is an
		example of that).

*/

/* Time  Complexity: O(log n) */
/* Space Complexity: O(log n) */
class Solution{
public:
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p)
	{
		if (root == nullptr)
			return nullptr;

		if (root == p)
		{
			if (root->right == nullptr)
				return nullptr;

			// Successor of root
			return successor(root->right);
		}

		std::stack<std::pair<TreeNode*, bool>> stack;

		while (root != nullptr)
		{
			// Basic Example
			if (root->left == p)
			{
				if (root->left->right != nullptr)
					return successor(root->left->right);

				return root;
			}
			// Tricky Example
			else if (root->right == p)
			{
				if (root->right->right != nullptr)
					return successor(root->right->right);

				while (!stack.empty())
				{
					std::pair<TreeNode*, bool> pair = stack.top();

					if (pair.second == true) // Right
						stack.pop();
					else
						return pair.first;
				}
			}
			// Go either left or right:
			else
			{
				if (p->val < root->val)
				{
					stack.push({root, false}); // Left is false
					root = root->left;
				}
				else
				{
					stack.push({root, true});  // Right is true
					root = root->right;
				}
			}
		}

		return nullptr;
	}

private:
	TreeNode* successor(TreeNode* root)
	{
		while (root->left != nullptr)
			root = root->left;

		return root;
	}
};
