#include <iostream>
#include <sstream>
#include <string>

/*
	============
	=== HARD ===
	============

	==========================================
	297) Serialize and Deserialize Binary Tree
	==========================================

	============
	Description:
	============

	Serialization is the process of converting a data structure or object into
	a sequence of bits so that it can be stored in a file or memory buffer, or
	transmitted across a network connection link to be reconstructed later in
	the same or another computer environment.

	Design an algorithm to serialize and deserialize a binary tree. There is no
	restriction on how your serialization/deserialization algorithm should
	work. You just need to ensure that a binary tree can be serialized to a
	string and this string can be deserialized to the original tree structure.

	Clarification: The input/output format is the same as how LeetCode
	serializes a binary tree. You do not necessarily need to follow this
	format, so please be creative and come up with different approaches
	yourself.

	=====
	Link: (How LeetCode serializes a binary tree)
	https://support.leetcode.com/hc/en-us/articles/360011883654-What-does-1-null-2-3-mean-in-binary-tree-representation-
	=====

	===============================================================
	CLASS: 
	//
		* Definition for a binary tree node.
		* struct TreeNode {
		*     int val;
		*     TreeNode *left;
		*     TreeNode *right;
		*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		* };
	//
	class Codec {
	public:

		// Encodes a tree to a single string.
		string serialize(TreeNode* root) {
			
		}

		// Decodes your encoded data to tree.
		TreeNode* deserialize(string data) {
			
		}
	};

	// Your Codec object will be instantiated and called as such:
	// Codec ser, deser;
	// TreeNode* ans = deser.deserialize(ser.serialize(root));
	===============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	___________
	_____1_____
	__2_____3__
	______4___5

	Input: root = [1,2,3,null,null,4,5]
	Output: [1,2,3,null,null,4,5]



	--- Example 2 ---
	Input: root = []
	Output: []



	*** Constraints ***
	The number of nodes in the tree is in the range [0, 10^4].
	-1000 <= Node.val <= 1000

*/

/*
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/

/*
	------------
	--- IDEA ---
	------------

	It's pretty straightforward. It's just a basic recursion + manipulation of
	strings using istringstream and ostringstream.

	istringstream uses a <Space> character(i.e. ' ') as a delimiter by default.

	That's basically the entire Solution.

*/

/* Time  Beats: 99.48% */
/* Space Beats: 33.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Codec {
public:
	// O(n)
	string serialize(TreeNode* root)
	{
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	// O(n)
	TreeNode* deserialize(string data)
	{
		istringstream in(data);
		return deserialize(in);
	}


private:
	void serialize(TreeNode* root, std::ostringstream& out)
	{
		if (root)
		{
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else
		{
			out << "# ";
		}
	}

	TreeNode* deserialize(std::istringstream& in)
	{
		std::string val;
		in >> val;

		if (val == "#")
			return nullptr;

		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);

		return root;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
