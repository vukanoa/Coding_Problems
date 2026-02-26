/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    449) Serialize and Deserialize BST
    ==================================

    ============
    Description:
    ============

    Serialization is converting a data structure or object into a sequence of
    bits so that it can be stored in a file or memory buffer, or transmitted
    across a network connection link to be reconstructed later in the same or
    another computer environment.

    Design an algorithm to serialize and deserialize a binary search tree.
    There is no restriction on how your serialization/deserialization algorithm
    should work. You need to ensure that a binary search tree can be serialized
    to a string, and this string can be deserialized to the original tree
    structure.

    The encoded string should be as compact as possible.

    ===============================
    CLASS:
    class Codec {
    public:

        // Encodes a tree to a single string.
        string serialize(TreeNode* root) {
            
        }

        // Decodes your encoded data to tree.
        TreeNode* deserialize(string data) {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [2,1,3]
    Output: [2,1,3]

    --- Example 2 ---
    Input: root = []
    Output: []


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 10^4].
    0 <= Node.val <= 10^4
    The input tree is guaranteed to be a binary search tree.
*/

#include <string>
#include <sstream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* Time  Beats: 81.19% */
/* Space Beats: 71.17% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        ostringstream out;
        inorder_serialize(root, out);

        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        istringstream in(data);

        return inorder_deserialize(in);
    }

private:
    void inorder_serialize(TreeNode* root, ostringstream& out)
    {
        if ( ! root)
        {
            out << "# ";
        }
        else
        {
            out << root->val << " ";
            inorder_serialize(root->left,  out);
            inorder_serialize(root->right, out);
        }
    }

    TreeNode* inorder_deserialize(istringstream& in)
    {
        string value_str;

        in >> value_str;

        if (value_str == "#")
            return nullptr;

        TreeNode* root = new TreeNode(stoi(value_str));
        root->left  = inorder_deserialize(in);
        root->right = inorder_deserialize(in);

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
