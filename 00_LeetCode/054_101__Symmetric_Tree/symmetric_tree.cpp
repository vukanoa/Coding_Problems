#include <iostream>
#include <vector>
#include <stack>
#include <queue>


/*
	============
	=== EASY ===
	============

	===========================
	101) Symmetric Tree
	===========================

	============
	Description:
	============

	Given the "root" of a binary tree, check whether it is a mirror of itself
	(i.e. symmetric around its center).

	===========================================
	FUNCTION: bool isSymmetric(TreeNode* root);
	===========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [1, 2, 2, 3, 4, 4, 3]
	Output: true

	--- Example 2 ---
	Input:  root = [1, 2, 2, null, 3, null, 3]
	Output: false

	*** Constraints ***
	The number of nodes in the tree is in the range [1, 1000]
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

	Idea is the same for both Recursive and Iterative Approach.

	Postorder is a mirror order of Preorder and vice versa.

	We push preorder values in vector "left" along with null-nodes which are
	of value -101.
	(It is said in the Description of a problem that a constraint
	is: -100 <= Node.val <= 100, so '-101' is out of bounds, meaning we can
	treat it as a "nullptr")

	We push preorder of left subtree in vector "left" and we push postorder
	of right subtree in vector "right".

	After that all we do is check:
		if (left[i] == right[right.size() - 1 - i])

	Meaning if the 0th element of the "left" vector equals to the last element
	of the "right" vector, and if 1st element of the "left" vector equals to
	the 1st element before the last element of the vector "right" and so on.

	If we find a single element that doesn't match - Tree is NOT Symmetric.
	Return false.

	If every single element matches - Tree is INDEED Symmetric.
	Return true.

*/


/* Time  Beats: 67.15% */
/* Space Beats:  5.18% */

/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(h)
	Where 'h' is the height of tree
*/
class Solution{
	void preorder(TreeNode* root, std::vector<int>& left)
	{
		if (root == nullptr)
		{
			left.push_back(-101); // Push null-nodes as -101
			return;
		}

		left.push_back(root->val);
		preorder(root->left, left);
		preorder(root->right, left);
	}

	void postorder(TreeNode* root, std::vector<int>& right)
	{
		if (root == nullptr)
		{
			right.push_back(-101); // Push null-nodes as -101
			return;
		}

		postorder(root->left, right);
		postorder(root->right, right);
		right.push_back(root->val);
	}

public:
	bool isSymmetric(TreeNode* root)
	{
		if (root == nullptr)
			return true;

		std::vector<int> left;
		std::vector<int> right;

		preorder (root->left,  left);
		postorder(root->right, right);

		if (left.size() != right.size())
			return false;

		for (int i = 0; i < left.size(); i++)
		{
			if (left[i] != right[left.size() - 1 - i])
				return false;
		}

		return true;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Same idea, implemented Iteratively.
	
*/


/* Time  Beats: 67.15% */
/* Space Beats:  5.18% */

/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(h)
	Where 'h' is the height of tree
*/
class Solution_Iter{
	void preorder_iter(TreeNode* root, std::vector<int>& left)
	{
		std::stack<TreeNode*> stack;

		while (root != nullptr || !stack.empty())
		{
			if (root == nullptr)
			{
				left.push_back(-101); // Left null

				root = stack.top();
				stack.pop();
			}
			else
			{
				left.push_back(root->val);

				if (root->val != -101)
				{

					if (root->right != nullptr)
						stack.push(root->right);
					else
					{
						TreeNode* null_node = new TreeNode(-101);
						stack.push(null_node);
					}

					root = root->left;
				}
				else
				{
					delete root;
					if (!stack.empty())
					{
						root = stack.top();
						stack.pop();
					}
					else
						root = nullptr;
				}
			}
		}
	}

	void postorder_iter(TreeNode* root, std::vector<int>& right)
	{
		if (root == nullptr)
			return;

		std::stack<TreeNode*> stack_1;
		std::stack<TreeNode*> stack_2;

		stack_1.push(root);

		while (!stack_1.empty())
		{
			root = stack_1.top();
			stack_1.pop();

			stack_2.push(root);

			if (root->val == -101)
			{
				if (!stack_1.empty())
				{
					TreeNode* null_node = new TreeNode(-101);
					stack_1.push(null_node);

					root = stack_1.top();
					stack_1.pop();

					delete root; // For preventing Memory Leak
					continue;
				}
				else
				{
					TreeNode* null_node = new TreeNode(-101);
					stack_1.push(null_node);
					break;
				}
			}

			if (root->left != nullptr)
				stack_1.push(root->left);
			else
			{
				TreeNode* null_node = new TreeNode(-101);
				stack_1.push(null_node);
			}

			if (root->right != nullptr)
				stack_1.push(root->right);
			else
			{
				TreeNode* null_node = new TreeNode(-101);
				stack_1.push(null_node);
			}
		}

		// For preventing Memory Leak
		while (!stack_1.empty())
		{
			TreeNode* node = stack_1.top();
			stack_1.pop();
			if (node->val == -101)
				delete node;
		}

		while (!stack_2.empty())
		{
			root = stack_2.top();
			stack_2.pop();

			right.push_back(root->val);

			// For preventing Memory Leak
			if (root->val == -101)
				delete root;
		}
	}

public:
	bool isSymmetric(TreeNode* root)
	{
		if (root == nullptr)
			return true;

		std::vector<int> left;
		std::vector<int> right;

		preorder_iter (root->left, left);
		postorder_iter(root->right, right);

		if (left.size() != right.size())
			return false;

		for (int i = 0; i < left.size(); i++)
		{
			if (left[i] != right[left.size() - 1 - i])
				return false;
		}

		return true;
	}
};




/*
	------------
	--- IDEA ---
	------------

	It's a similar problem to LeetCode: 100_Same_Tree with one difference.
	Instead of checking:
		p->left  subtree with q->left  subtree
			and
		p->right subtree with q->right subtree
	
	We check the exact opposite. We check:
		p->left  subtree with q->right subtree
			and
		p->right subtree with q->left  subtree
	
	Because that's how you properly check if two trees are mirrors.

	Look at a Visual representation of a Tree and go through the code and it'll
	be super obvious and easy to understand.
	
*/


/* Time  Beats: 88.40% */
/* Space Beats: 58.50% */

/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(h)
	Where 'h' is the height of tree
*/
class Solution_Neat{
private:
	bool dfs(TreeNode* p, TreeNode* q)
	{
		if (!p && !q)
			return true;

		if (!p || !q) // Only one is null
			return false;

		if (p->val != q->val)
			return false;

		return (dfs(p->left, q->right) && dfs(p->right, q->left));
	}

public:
	bool isSymmetric(TreeNode* root)
	{
		return dfs(root->left, root->right);
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
	Solution_Iter sol_iter;
	Solution_Neat sol_neat;

	/* Example 1 */
	TreeNode three1(3);
	TreeNode three2(3);
	TreeNode four1(4);
	TreeNode four2(4);
	TreeNode two1(2, &three1, &four1);
	TreeNode two2(2, &four2, &three2);
	TreeNode one(1, &two1, &two2);

	TreeNode* root = &one;


	/* Example 2 */
	// TreeNode three1(3);
	// TreeNode three2(3);
	// TreeNode two1(2, nullptr, &three1);
	// TreeNode two2(2, nullptr, &three2);
	// TreeNode one(1, &two1, &two2);

	// TreeNode* root = &one;


	/* Example 3 */
	// TreeNode* root = nullptr;

	/* Example 4 */
	// TreeNode two1(2);
	// TreeNode two2(2);
	// TreeNode one(1, &two1, &two2);

	// TreeNode* root = &one;


	/* Example 5 */
	// TreeNode five1(5);
	// TreeNode two1(2, &five1, nullptr);
	// TreeNode two2(2);
	// TreeNode one(1, &two1, &two2);

	// TreeNode* root = &one;


	std::cout << "\n\t======================";
	std::cout << "\n\t=== SYMMETRIC TREE ===";
	std::cout << "\n\t======================\n";


	/* Write Input */
	std::cout << "\n\t\t\t~~~ TODO: Write a visual print of BST ~~~\n";
	print_levelorder(root);


	/* Solution */
	// bool symmetric = sol.isSymmetric(root);
	// bool symmetric = sol_iter.isSymmetric(root);
	bool symmetric = sol_neat.isSymmetric(root);


	/* Write Output */
	if (symmetric)
		std::cout << "\n\tTree is INDEED Symmetric!\n\n";
	else
		std::cout << "\n\tTree is NOT Symmetric!\n\n";


	return 0;
}
