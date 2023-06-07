#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

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

	I don't know why but this IDEA is more readable to me. Though it is a lot
	less efficient than the Solution_efficient, so it's important to
	understand both.

	IDEAs are almost equivalent, but the first one "shows you how it's done",
	since it uses both vector and recursion, while the Solution_efficient
	uses only recursion and is more compact.
	
*/


/* Time  Beats:  7.42% */
/* Space Beats: 10.22% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_readable{
private:
	int i = 0;

public:
	TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
	{
		if (inorder.empty())
			return nullptr;

		TreeNode *root = new TreeNode(preorder[i++]);
		int tmp = root->val;

		/* inorder for the left subtree */
		int x = 0;
		std::vector<int> left_inorder;
		while(inorder[x] != tmp)
		{
			left_inorder.push_back(inorder[x]);
			x++;
		}

		x++; // Skip the root; So it points at first node of the right subtree

		/* inorder for the right subtree */
		std::vector<int> right_inorder;
		while (x < inorder.size())
		{
			right_inorder.push_back(inorder[x]);
			x++;
		}

		root->left  = buildTree(preorder,  left_inorder);
		root->right = buildTree(preorder, right_inorder);

		return root;
	}
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

	Now the idea should be clear enough. We will design a recursive function:
	It will set the first element of "preorder" as the root, and then construct
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
	             |
	             v
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
	// preorder of the just constructed BST.
*/

/* Time  Beats: 98.46% */
/* Space Beats: 33.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_efficient {
private:
	int preorder_index;
	std::unordered_map<int, int> inorder_value_index_hashmap;
public:
	TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
	{
		preorder_index = 0;

		// Build a hashmap to store {value, its index}
		for (int i = 0; i < inorder.size(); i++)
			inorder_value_index_hashmap.insert({inorder[i], i});

		return array_to_tree(preorder, 0, preorder.size() - 1);
	}

	TreeNode* array_to_tree(std::vector<int>& preorder, int first_index, int last_index)
	{
		// If there are no elements to construct the tree
		if (first_index > last_index)
			return nullptr;

		// Select the preorder_index element as the root and increment it
		int root_value = preorder[preorder_index++];
		TreeNode* root = new TreeNode(root_value);

		/* Build left and right subtree */
		// Excluding inorder_value_index_hashmap[root_value] element because that's the root
		root->left  = array_to_tree(preorder,               first_index                     , inorder_value_index_hashmap.at(root_value) - 1);
		root->right = array_to_tree(preorder, inorder_value_index_hashmap.at(root_value) + 1,              last_index                       );

		return root;
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
	std::cout << "\n\t(TODO: Implement a Visual representation of a Binary Tree)";
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


void
print_preorder(std::vector<int>& preorder)
{
	bool first = true;
	std::cout << "\n\tPreorder: [";
	for (auto x: preorder)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";
}


void
print_inorder(std::vector<int>& inorder)
{
	bool first = true;
	std::cout << "\n\tInorder:  [";
	for (auto x: inorder)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";
}


int
main()
{
	Solution_readable sol_read;
	Solution_efficient sol_eff;

	/* Example 1 */
	/*
		___________
		_____3_____
		__9_____20_
		1___2_15__7
	*/
	std::vector<int> preorder = {3, 9, 1, 2, 20, 15, 7};
	std::vector<int> inorder  = {1, 9, 2, 3, 15, 20, 7};


	/* Example 2 */
	/*
		___-1___
	*/
	// std::vector<int> preorder = {-1};
	// std::vector<int> inorder  = {-1};


	/* Example 3 */
	/*
		___1___
	*/
	// std::vector<int> preorder = {1};
	// std::vector<int> inorder  = {1};


	/* Example 4 */
	/*
		Empty
	*/
	// std::vector<int> preorder;
	// std::vector<int> inorder;


	/* Example 5 */
	/*
		_____
		__1__
		2____
	*/
	// std::vector<int> preorder = {1, 2};
	// std::vector<int> inorder  = {2, 1};


	/* Example 6 */
	/*
		_______________________1_______________________
		___________2___________________________________
		_____3_________________________________________
		__4____________________________________________
		5______________________________________________
	*/
	// std::vector<int> preorder = {1, 2, 3, 4, 5};
	// std::vector<int> inorder  = {5, 4, 3, 2, 1};


	/* Example 7 */
	/*
		_______________________
		___________1___________
		_____2___________3_____
		__4_____5___________6__
		______7________________
	*/
	// std::vector<int> preorder = {1, 2, 4, 5, 7, 3, 6};
	// std::vector<int> inorder  = {4, 2, 7, 5, 1, 3, 6};


	std::cout << "\n\t=================================================================";
	std::cout << "\n\t=== CONSTRUCT BINARY TREE FROM PREORDER AND INORDER TRAVERSAL ===";
	std::cout << "\n\t=================================================================\n";


	/* Write Input */
	print_preorder(preorder);
	print_inorder(inorder);


	/* Solution */
	// TreeNode* root = sol_read.buildTree(preorder, inorder);
	TreeNode* root = sol_eff.buildTree(preorder, inorder);


	/* Write Output */
	std::cout << "\n\t\t=== Constructed Binary Tree ===\n\n";
	print_levelorder(root);


	return 0;
}
