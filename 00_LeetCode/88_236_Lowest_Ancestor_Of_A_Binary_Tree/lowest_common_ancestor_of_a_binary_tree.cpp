#include <iostream>
#include <stack>

/*
	==============
	=== MEDIUM ===
	==============

	============================================
	236) Lowest Common Ancestor of a Binary Tree
	============================================

	============
	Description:
	============

	Given a binary tree, find the lowest common ancestor (LCA) of two given
	nodes in the tree.

	According to the *definition of LCA on Wikipedia:*"The lowest common
	ancestor is defined between two nodes 'p' and 'q' as the lowest node in 'T'
	that has both 'p' and 'q' as descendants(where we allow a node to be a
	descendant of itself)

	=====
	Node: *We allow a node to be a descendant of itself*
	=====

	===================================================================================
	FUNCTION: TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
	===================================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4], p = 5, q = 1
	Output: 3

	--- Example 2 ---
	Input:  root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4], p = 5, q = 4
	Output: 5

	--- Example 3 ---
	Input:  root = [1, 2], p = 1, q = 2
	Output: 1

	*** Constraints ***
	The number of nodes in the tree is in the range [2, 10^5]
	-10^9 <= Node.val <= 10^9
	All Node.val are unique.
	p != q
	p and q will exist in thre tree

*/



// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
	------------
	--- IDEA ---
	------------

	Since we're told that both 'p' and 'q' exist in the Tree, we do an inorder
	search where we push nodes as we go down, until we find our 'p' or 'q'.
	Also, if we end up going down the wrong path, at the end we pop that node
	since it does not represent the path to our 'p' or 'q'.

	We push p's path in stack_p, and q's path in stack_q.

	Note: We do not push the nodes themselves, only their parent nodes.
	      If it happens that either 'p' or 'q' is the root, that means that
		  stack_p in case of p == root, or stack_q in case of q == root, will
		  be empty. As we've said - We don't keep the nodes themselves in the
		  stack.

	After that we're in a situation similar to LeetCode Problem:
		160: Intersection of two Linked Lists

	In that problem, first we count the number of nodes in each of them and
	then we cut-off the difference, meaning we cut-off the difference of:
		longer - shorter
	from a longer one.

	Now both are of the same length and then just go one by one and find where
	they intersect.

	However, this is not it. But it's very similar. It would actually be the
	exact same if we weren't told this:
		*We allow a node to be a descendant of itself*

	Consider 2nd Example:
             3
      5              1
   6     2        0     8
       7   4

	Input:  root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4], p = 5, q = 4
	Output: 5

	Since 'p' = 5, stack_p will be [3]
	Since 'q' = 4, stack_q will be [3, 5, 2]

	If we were just to "cut-off the difference" we would return 3 as LSA, which
	is not true.

	So how should go resolve this?
	It's actually very simple.

	As you're trying to "pop" TreeNodes, one by one, before you pop you should
	check if:
		(if stack_p is longer than stack_q)
			if (stack_p.top == q)

		(or if stack_q is longer than stack_p)
			if (stack_q.top == p)

	That way we covered that case as well and the problem is resolved.
*/


class Solution {
private:
	int inorder_search(TreeNode* root, TreeNode* x, std::stack<TreeNode*>& stack_x)
	{
	    if (root == nullptr)
	        return 0;
	    else if (root == x)
	        return 1;
	    else
	        stack_x.push(root);

	    if (inorder_search(root->left, x, stack_x))
	        return 1;

	    if (inorder_search(root->right, x, stack_x))
	        return 1;

	    stack_x.pop();
	    return 0;
	}

public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
	    std::stack<TreeNode*> stack_p;
	    std::stack<TreeNode*> stack_q;

	    inorder_search(root, p, stack_p);
	    inorder_search(root, q, stack_q);

	    while (stack_p.size() > stack_q.size())
	    {
	        if (stack_p.top() == q)
	            return q;
	        else
	            stack_p.pop();
	    }

	    while (stack_q.size() > stack_p.size())
	    {
	        if (stack_q.top() == p)
	            return p;
	        else
	            stack_q.pop();
	    }

	    while (!stack_p.empty() && !stack_q.empty())
	    {
	        if (stack_p.top() != stack_q.top())
	        {
	            stack_p.pop();
	            stack_q.pop();
	        }
	        else
	            return stack_p.top();
	    }

	    return nullptr;
	}
};


int
tree_height(TreeNode* root)
{
    if (root == NULL)
        return 0;
    else
	{
		// Compute the height of each subtree
        int left_height  = tree_height(root->left);
        int right_height = tree_height(root->right);

		// Use the larger one
        if (left_height > right_height)
            return (left_height + 1);
        else
            return (right_height + 1);
    }
}


void
print_current_level(TreeNode* root, int level)
{
    if (root == nullptr)
	{
        std::cout << "null ";
        return;
	}
    if (level == 1)
        std::cout << root->val << " ";
    else if (level > 1)
	{
        print_current_level(root->left,  level - 1);
        print_current_level(root->right, level - 1);
    }
}


void
print_levelorder(TreeNode* root)
{
    int h = tree_height(root);

    for (int i = 1; i <= h; i++)
        print_current_level(root, i);
}


int
main()
{
	Solution sol;

	/* Example 1 */
	// TreeNode three(3);
	// TreeNode five(5);
	// TreeNode one(1);
	// TreeNode six(6);
	// TreeNode two(2);
	// TreeNode zero(0);
	// TreeNode eight(8);
	// TreeNode seven(7);
	// TreeNode four(4);

	// three.left  = &five;
	// three.right = &one;
	// five.left   = &six;
	// five.right  = &two;
	// one.left    = &zero;
	// one.right   = &eight;
	// two.left    = &seven;
	// two.right   = &four;

	// TreeNode* root = &three;
	// TreeNode* p    = &five;
	// TreeNode* q    = &one;



	/* Example 2 */
	TreeNode three(3);
	TreeNode five(5);
	TreeNode one(1);
	TreeNode six(6);
	TreeNode two(2);
	TreeNode zero(0);
	TreeNode eight(8);
	TreeNode seven(7);
	TreeNode four(4);

	three.left  = &five;
	three.right = &one;
	five.left   = &six;
	five.right  = &two;
	one.left    = &zero;
	one.right   = &eight;
	two.left    = &seven;
	two.right   = &four;

	TreeNode* root = &three;
	TreeNode* p    = &five;
	TreeNode* q    = &four;



	/* Example 3 */
	// TreeNode one(1);
	// TreeNode two(2);

	// one.left = &two;

	// TreeNode* root = &one;
	// TreeNode* p    = &one;
	// TreeNode* q    = &two;




	std::cout << "\n\t===============================================";
	std::cout << "\n\t=== LOWEST COMMON ANCESTOR OF A BINARY TREE ===";
	std::cout << "\n\t===============================================\n\n";

	/* Write Input */
	std::cout << "\n\tTree: ";
	print_levelorder(root);
	std::cout << "\n";
	std::cout << "\tp: " << p->val << "\n";
	std::cout << "\tq: " << q->val << "\n";

	/* Solution */
	TreeNode* ancestor = sol.lowestCommonAncestor(root, p, q);

	/* Write Output */
	std::cout << "\n\tLCA is: " << ancestor->val << "\n\n";


	return 0;
}
