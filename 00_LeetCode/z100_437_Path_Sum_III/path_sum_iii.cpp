#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	437) Path Sum III
	===========================

	============
	Description:
	============

	Given the "root" of a binary tree and an integer "targetSum", return the
	number of paths where the sum of the values along the path equals
	"targetSum".

	The path does not need to start or end at the root or a leaf, but it must
	go downwards (i.3., traveling only from parent nodes to child nodes).

	=====================================================
	FUNCTION: int pathSum(TreeNode* root, int targetSum);
	=====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [10, 5, -3, 3, 2, null, 11, 3, -2, null, 1],
	        targetSum = 8
	Output: 3

	--- Example 2 ---
	Input:  root = [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1],
	        targetSum = 22
	Output: 3

	*** Constraints ***
	The number of nodes in the tree is in the range [0, 1000].
	-10^9 <= Node.val <= 10^9
	-1000 <= targetSum <= 1000

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

	The idea is very simple. It's a kind of Brute Force DFS solution.

	In function "pathSum" we have:
		return DFS(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);

	Let's go one by one:
	1) DFS(root, targetSum)
	2) pathSum(root->left, targetSum)
	3) pathSum(root->right, targetSum)

	1st one means do a DFS including current node.

	In the first example we have:
	_______________________
	___________10__________
	_____5__________-3_____
	__3_____2__________11__
	3__-2_____1____________

	It means that we will consider both path but INCLUDING this current node,
	10 in this case.

	2nd one means - Do a same problem starting with a current's left node as
	root node.

	3rd one means - Do a same problem starting with a current's right node as
	root node.



	Inside DFS, we have:
        return (node->val == sum ? 1 : 0) + DFS(node->left, sum - node->val) + DFS(node->right, sum - node->val);

	Again, let's unpack:
		a) (node->val == sum ? 1 : 0)
		b) DFS(node->left, sum - node->val)
		c) DFS(node->right, sum - node->val)

	"a)" means if the current node->val is equal to the sum we're searching for
	(this sum can be the absolute sum or the subSum since we always subtract
	current node->val from sum(or subSum) when going left or right).
	If it it then include 1 in equation we're returning.

	"b)" means do a DFS starting with the current's node left as root, but
	include this current one so, the second argument is now:
		sum - node->val

	"c" same as "b)" but current's node right as root.

*/



/*
	Worst Time  Complexity: O(n^2)
	Best  Time  Complexity: O(n * logn) // Balanced Tree
*/
/*
	Space Complexity: O(n)
	due to recursion
*/
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum)
    {
        if (root == nullptr)
            return 0;

        return DFS(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
    }

    int DFS(TreeNode* node, long long int sum)
    {
        if (node == nullptr)
            return 0;

        return (node->val == sum ? 1 : 0) + DFS(node->left, sum - node->val) + DFS(node->right, sum - node->val);
    }
};



/* Print nodes at a current level */
void printCurrentLevel(TreeNode* root, int level)
{
    if (root == NULL)
	{
        std::cout << "null ";
        return;
	}
    if (level == 1)
        std::cout << root->val << " ";
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(TreeNode* node)
{
    if (node == NULL)
        return 0;
    else {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight) {
            return (lheight + 1);
        }
        else {
            return (rheight + 1);
        }
    }
}

/* Function to print level
order traversal a tree*/
void printLevelOrder(TreeNode* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}

int
main()
{
	Solution sol;

	/* Example 1 */
	/*
		_______________________
		___________10__________
		_____5__________-3_____
		__3_____2__________11__
		3__-2_____1____________
	*/
	// TreeNode ten(10);
	// TreeNode five(5);
	// TreeNode minus_three(-3);
	// TreeNode three(3);
	// TreeNode two(2);
	// TreeNode eleven(11);
	// TreeNode three_2(3);
	// TreeNode minus_two(-2);
	// TreeNode one(1);

	// ten.left          = &five;
	// ten.right         = &minus_three;
	// five.left         = &three;
	// five.right        = &two;
	// minus_three.right = &eleven;
	// three.left        = &three_2;
	// three.right       = &minus_two;
	// two.right         = &one;

	// TreeNode* root = &ten;
	// int targetSum = 8;


	/* Example 2 */
	/*
		_______________________
		___________5___________
		_____4___________8_____
		__11__________13____4__
		7____2____________5___1
	*/
	TreeNode five(5);
	TreeNode four(4);
	TreeNode eight(8);
	TreeNode eleven(11);
	TreeNode thirteen(13);
	TreeNode four_2(4);
	TreeNode seven(7);
	TreeNode two(2);
	TreeNode five_2(5);
	TreeNode one(1);

	five.left    = &four;
	five.right   = &eight;
	four.left    = &eleven;
	eight.left   = &thirteen;
	eight.right  = &four_2;
	eleven.left  = &seven;
	eleven.right = &two;
	four_2.left  = &five_2;
	four_2.right = &one;

	TreeNode* root = &five;
	int targetSum = 22;

	/* Example 3 */

	std::cout << "\n\t====================";
	std::cout << "\n\t=== PATH SUM III ===";
	std::cout << "\n\t====================\n\n";

	/* Write Input */
	std::cout << "\n\tTree:\n\t\t";
	printLevelOrder(root);
	std::cout << "\n";

	/* Solution */
	int count = sol.pathSum(root, targetSum);

	/* Write Output */
	std::cout << "\n\tOutput: " << count << "\n\n";

	return 0;
}
