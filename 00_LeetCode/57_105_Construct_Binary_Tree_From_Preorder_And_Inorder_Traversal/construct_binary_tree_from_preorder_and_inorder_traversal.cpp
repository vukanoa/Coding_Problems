#include <iostream>
#include <vector>
#include <unordered_map>


/*
	==============
	=== MEDIUM ===
	==============

	==============================================================
	105) Construct Binary Tree from Preorder and Inorder Traversal
	==============================================================

	============
	Description:
	============

	Given two integer arrays "preorder" and "inorder" where "preorder" is the
	preorder traversal of a binary tree and "inorder" is the inorder traversal
	of the same tree, construct and return the binary tree.

	===========================================================================
	FUNCTION: TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);
	===========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  preorder = [3, 9, 20, 15, 7], inorder = [9, 3, 15, 20, 7]
	Output: [3, 9, 20, null, null, 15, 7]

	--- Example 2 ---
	Input:  preorder = [-1], inorder = [-1]
	Output: [-1]

	*** Constraints ***
	1 <= preorder.length <= 3000
	inorder.length == preorder.length
	-3000 <= preorder[i], inorder[i] <= 3000
	"preorder" and "inorder" consist of unique values
	Each value of "inorder" also appears in "preorder"
	"preorder" is guaranteed to be the preorder traversal of the tree.
	"inorder" is guaranteed to be the inorder traversal of the tree.

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

	Two key observations are:
		1. Preorder traversal follows:
			Root -> Left -> Right
		   therefore given the preorder array "preorder", we have an easy
		   access to the root which is preorder[0].

		2. Inorder traversal follows:
			Left -> Root -> Right
		   therefore if we know the position of "Root", we can recursively
		   split the entire array into two subtrees.

	Now the idea should be clear enough. We will design a recursion functions:
	it will set the first element of "preorder" as the root, and then construct
	the entire tree. To find the left and right subtrees, it will look for the
	root in "inorder", so that everything on the left should be the left
	subtree. Both subtrees can be constructed by making another recursion call.

	It is worth noting that, while we recursively construct the subtrees, we
	should choose the next element in "preorder" to initialize as the new
	roots. This is because the current one has already been initialized to a
	parent node for the subtrees.

	___________
	_____3_____
	__9_____20_
	1___2_15__7

	preorder: [3, 9, 1, 2, 20, 15, 7]
	           ^
	           |
	  root -------------
	                   |
	                   v
	inorder: [1, 9, 2, 3, 15, 20, 7]
	          ~~~~~~~     #########
	              ^           ^
	              |           |
	left_subtree --           |
	                          |
	right_subtree -------------


	                  |
	                  |
	                  |
	                  V
	          construct left subtree

	_____
	__9__
	1___2

	preorder: [3, 9, 1, 2, 20, 15, 7]
	              ^
	              |
	  root --------

	inorder: [1, 9, 2]
	          ~     #
	          ^     ^
	          |     |
	left_subtree    |
	                |
	right_subtree ---

	...
	...
	etc.
	...


	Algorithm:
		- Build a hashmap to record the relation of "values -> index" for
		  "inorder", so that we can find the position of root in constant time.

		- Initialize an integer variable "preorder_index" to keep track of the
		  element that will be used to construct the root.

		- Implement the recursion function "array_to_tree" which takes a range
		  of "inorder" and returns the constructed binary tree:
			- if the range is empty, return nullptr;
			- initialize the root with "preorder[preorder_index]" and then
			  increment "preorder_index";
			- recursively use the left and right portions of "inorder" to
			  construct the left and right subtrees.
		- Simply call the recursion function with the entire range of
		  "inorder".

	// Since I didn't implement a visual representation of BST, print the
	// preorder of the just contructed BST.
*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
private:
	int preorder_index;
	std::unordered_map<int, int> inorder_index_hashmap;
public:
	TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
	{
		preorder_index = 0;

		// Build a hashmap to store {value, its index}
		for (int i = 0; i < inorder.size(); i++)
			inorder_index_hashmap.insert({inorder[i], i});

		return array_to_tree(preorder, 0, preorder.size() - 1);
	}

	TreeNode* array_to_tree(std::vector<int>& preorder, int left, int right)
	{
		// If there are no elements to construct the tree
		if (left > right)
			return nullptr;

		// Select the preorder_index element as the root and increment it
		int root_value = preorder[preorder_index++];
		TreeNode* root = new TreeNode(root_value);


		/* Build left and right subtree */
		// Excluding inorder_index_hashmap[root_value] element because it's the root
		root->left  = array_to_tree(preorder, left, inorder_index_hashmap.at(root_value) - 1);
		root->right = array_to_tree(preorder, inorder_index_hashmap.at(root_value) + 1, right);

		return root;
	}
};


void
print_preorder(TreeNode* root)
{
	if (root == nullptr)
		return;

	std::cout << root->val << " ";
	print_preorder(root->left);
	print_preorder(root->right);
}


void
fill_preorder(TreeNode* root, std::vector<int>& preorder)
{
	if (root == nullptr)
		return;

	preorder.push_back(root->val);
	fill_preorder(root->left, preorder);
	fill_preorder(root->right, preorder);
}


void
fill_inorder(TreeNode* root, std::vector<int>& inorder)
{
	if (root == nullptr)
		return;

	fill_inorder(root->left, inorder);
	inorder.push_back(root->val);
	fill_inorder(root->right, inorder);
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
	/*
		___________
		_____3_____
		__9_____20_
		1___2_15__7
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
	// TreeNode seven(7);
	// TreeNode five(5, &seven, nullptr);
	// TreeNode four(4);
	// TreeNode two(2, &four, &five);
	// TreeNode six(6);
	// TreeNode three(3, nullptr, &six);
	// TreeNode one(1, &two, &three);
	// TreeNode* root = &one;
	/*
		_______________________
		___________1___________
		_____2___________3_____
		__4_____5___________6__
		______7________________
	*/


	/* This is the same for every Example (do not comment this)*/
	std::vector<int> preorder;
	std::vector<int> inorder;
	fill_preorder(root, preorder);
	fill_inorder(root, inorder);


	std::cout << "\n\t=================================================================";
	std::cout << "\n\t=== CONSTRUCT BINARY TREE FROM PREORDER AND INORDER TRAVERSAL ===";
	std::cout << "\n\t=================================================================\n";

	std::cout << "\n\tPreorder of the Constructed Binary Tree:\n\t";

	/* Solution */
	print_preorder(sol.buildTree(preorder, inorder));

	std::cout << "\n\n";

	return 0;
}
