#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	==================================
	230) Kth Smallest Element in a BST
	==================================

	============
	Description:
	============

	Given the "root" of a binary search tree, and an integer 'k', return the
	k-th smallest value (1-indexed) of all the values of the nodes in tree.

	Follow up: If the BST is modified often(i.e., we can do insert and delete
	operations) and you need to find the kth smallest frequently, how would you
	optimize?

	=================================================
	FUNCTION: int kthSmallest(TreeNode* root, int k);
	=================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [3, 1, , null, 2], k = 1
	Output: 1

	--- Example 2 ---
	Input:  root = [5, 3, 6, 2, 4, null, null, 1], k = 3
	Output: 3

	*** Constraints ***
	The number of nodes in the tree is 'n'.
	1 <= k <= n <= 10^4
	0 <= Nodelva. <= 10^4

*/


/*
	------------
	--- IDEA ---
	------------

	If it was the k-th Largest Element:
		count the left subtree
		count the right subtree

		if (right_subtree_num_nodes + 1 == k)
			return root->val; // That's what we're looking for
		else if (k <= right_subtree_num_nodes)
		{
			recursively do this in the right subtree.
		}
		else
		{
			k = right_subtree_num_nodes - 1
			recursively try to find in the left subtree with new k
		}

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

	The Approach is similar to how Quick-Select works. At least in some sense.
	In Quick-Select we had to use the "partition" function and at the end of it
	swap pivot with nums[i].

	However, since over here we have a BST, we don't have to do that.
	Anyway, the part that is shared between both algorithms is:
		if you k == num_of_element_left_of_pivot + 1
			then that means the pivot itself(or in this problem, the root
			itself) is the solution.

	Here we call function "count_nodes_of_subtree" to recursively count both
	the left and the right subtree. (We're counting the number of nodes in each
	subtree)

	Since it is said that this is 1-indexed, meaning that if k = 1, we need to
	return the smallest element.
	Or if k = 2 we need to return the 2nd smallest element in the tree.

	Thus, previoulsy stated, if number of nodes in the left subtree + 1 = k
	we've found it! Return the root and that's it.

	Else if k <= number of nodes in the left subtree
		That means out desired element is in the left subtree.
		Try to do this function recursively on root's left subtree.

	else
		It is certainly in the root's right subtree, but we cannot just
		recursively do the same on the root's right subtree because we need
		the SMALLEST and we've cut out the left subtree and the root itself,
		thus we HAVE to subtract num_of_nodes_in_root's_left_subtree - 1.
		-1 because we need to take root itself into account.

		Now just do recursively the same algorithm on root's right subtree, but
		with this new 'k' value.
*/



/* It's similar to Quick Select */

/*	Average Time  Complexity: O(n) */
/*
	Worst   Time  Complexity: O(n^2)
	if the tree is essentially a Linked List
*/
/*
	Space Complexity: O(h)
	where 'h' is the height of three. At worst 'h' <==> 'n', therefore O(n)
*/
class Solution{
private:
	void count_nodes_of_subtree(TreeNode* root, int& cnt)
	{
		if (root == nullptr)
			return;

		cnt++;
		count_nodes_of_subtree(root->left, cnt);
		count_nodes_of_subtree(root->right, cnt);
	}

public:
	int kthSmallest(TreeNode* root, int k)
	{
		int left  = 0;
		int right = 0;
		count_nodes_of_subtree(root->left, left);
		count_nodes_of_subtree(root->right, right);

		if (left + 1 == k)
			return root->val;
		else if (k <= left)
			return kthSmallest(root->left, k);
		else
		{
			k = k - left - 1; // -1 indicates the root itself
			return kthSmallest(root->right, k);
		}
	}
};


void
inorder(TreeNode* root)
{
	if (root == nullptr)
		return;

	inorder(root->left);
	std::cout << root->val << " ";
	inorder(root->right);
}


int
main()
{
	Solution sol;

	/* Example 1 */
	// TreeNode three(3);
	// TreeNode one(1);
	// TreeNode four(4);
	// TreeNode two(2);

	// three.left  = &one;
	// three.right = &four;
	// one.right = &two;

	// TreeNode* root = &three;
	// int k = 1;



	/* Example 2 */
	TreeNode five(5);
	TreeNode three(3);
	TreeNode six(6);
	TreeNode two(2);
	TreeNode four(4);
	TreeNode one(1);

	five.left   = &three;
	five.right  = &six;
	three.left  = &two;
	three.right = &four;
	two.left    = &one;

	TreeNode* root = &five;
	int k = 3;


	std::cout << "\n\t=====================================";
	std::cout << "\n\t=== KTH SMALLEST ELEMENT IN A BST ===";
	std::cout << "\n\t=====================================\n\n";

	/* Write Input */
	std::cout << "\n\tTree: ";
	inorder(root);
	std::cout << "\n";

	/* Solution */
	int kth = sol.kthSmallest(root, k);

	/* Write Output */
	if (k == 1)
		std::cout << "\n\t" << k << "st Smallest: " << kth << "\n\n";
	else if (k == 2)
		std::cout << "\n\t" << k << "nd Smallest: " << kth << "\n\n";
	else if (k == 3)
		std::cout << "\n\t" << k << "rd Smallest: " << kth << "\n\n";
	else
		std::cout << "\n\t" << k << "th Smallest: " << kth << "\n\n";

	return 0;
}
