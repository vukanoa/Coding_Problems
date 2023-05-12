#include <iostream>
#include <vector>

// For printing
#include <queue>

/*
	==============
	=== MEDIUM ===
	==============

	================================
	199) Binary Tree Right Side View
	================================

	============
	Description:
	============

	Give the "root" of a binary tree, imagine yourself standing on the right
	side of it, return the values of the nodes you can see ordered from top
	to bottom.

	====================================================
	FUNCTION: vector<int> rightSideView(TreeNode* root);
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	     1
	  2     3
	    5    4

	Input:  root = [1, 2, 3, null, 5, null, 4]
	Output: [1, 3, 4]


	--- Example 2 ---
	  1
	     3

	Input:  root = [1, null, 3]
	Output: [1, 3]

	--- Example 3 ---


	Input:  root = []
	Output: []

	*** Constraints ***
	The number of nodes in thre tree is in the range [0, 100].
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

	Basic DFS.

	The only important thing here is that we must do right subtree, i.e. right
	elements, first and that we have to keep track of max_depth.

	Because once we put certain node's value in side view, i.e. "results"
	vector, then only the subtree that is one level deeper than the current
	max_depth can be seen.

	That's why we have to keep track of "level" at each node locally and keep
	track of "max_depth" globally.

	Now the Solution is self-explanatory.
	
*/

/* Time  Beats:   100% */
/* Space Beats: 88.57% */

/*
	Time  Complexity: O(n)
*/
/*
	Space Complexity: O(n)
	Because of the call Stack.
*/
class Solution{
public:
	std::vector<int> rightSideView(TreeNode* root)
	{
		std::vector<int> results;
		int level = 0;
		int max_depth = -1;

		dfs(root, results, level, max_depth);

		return results;
	}

private:
	void
	dfs(TreeNode* root, std::vector<int>& results, int level, int& max_depth)
	{
		if (root == nullptr)
			return;
		
		if (level > max_depth)
		{
			results.push_back(root->val);
			max_depth = level;
		}

		dfs(root->right, results, level+1, max_depth); // Right elements first
		dfs(root->left,  results, level+1, max_depth);
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
			 1
		  2     3
			5    4
	*/
	// TreeNode one(1);
	// TreeNode two(2);
	// TreeNode three(3);
	// TreeNode five(5);
	// TreeNode four(4);

	// one.left = &two;
	// one.right = &three;
	// two.right = &five;
	// three.right = &four;

	// TreeNode* root = &one;



	/* Example 2 */
	/*
		  1
			 3
	*/
	// TreeNode one(1);
	// TreeNode three(3);

	// one.right = &three;

	// TreeNode* root = &one;



	/* Example 3 */
	// TreeNode* root = nullptr;


	/* Example 4 */
	/*
	                   1
	           2            3
	       5       6           7
	    9       8
	     10

	*/
	TreeNode one(1);
	TreeNode two(2);
	TreeNode three(3);
	TreeNode four(4);
	TreeNode five(5);
	TreeNode six(6);
	TreeNode seven(7);
	TreeNode eight(8);
	TreeNode nine(9);
	TreeNode ten(10);

	one.left  = &two;
	one.right = &three;
	three.right = &seven;
	two.left = &five;
	two.right = &six;
	five.left = &nine;
	six.left = &eight;
	nine.right = &ten;

	TreeNode* root = &one;


	std::cout << "\n\t===================================";
	std::cout << "\n\t=== BINARY TREE RIGHT SIDE VIEW ===";
	std::cout << "\n\t===================================\n";


	/* Write Input */
	print_levelorder(root);


	/* Solution */
	std::vector<int> side_view = sol.rightSideView(root);

	/* Write Output */
	bool first = true;
	std::cout << "\n\tSide View: [";
	for (auto x: side_view)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
