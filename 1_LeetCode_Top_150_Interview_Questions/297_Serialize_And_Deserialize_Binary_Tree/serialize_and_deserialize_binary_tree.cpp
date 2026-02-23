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

#include <sstream>
#include <string>
using namespace std;

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

    TODO

*/

/* Time  Beats: 5.07% */
/* Space Beats: 5.00% */

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
        int i = 0;
        return inorder_deserialize(data, i);
    }

private:
    void inorder_serialize(TreeNode* root, ostringstream& out)
    {
        if (root == nullptr)
        {
            out << "#_"; // '#' <==> nullptr
            return;
        }

        out << root->val << "_";
        inorder_serialize(root->left, out);
        inorder_serialize(root->right, out);
    }

    TreeNode* inorder_deserialize(string data, int& i)
    {
        if (i == data.size())
            return nullptr;

        string value_str;
        value_str.reserve(5); // Max length string is for "-1000", i.e. 5 chars

        /* Build current value */
        while (i < data.size() && data[i] != '_')
        {
            value_str += data[i];
            i++;
        }
        i++; // Skip over the '_'

        if (value_str == "#")
            return nullptr;

        TreeNode* node = new TreeNode(stoi(value_str));

        node->left  = inorder_deserialize(data, i);
        node->right = inorder_deserialize(data, i);

        return node;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Virtually same idea, however it's beneficial to be aware of this in C++
    because it makes the code much cleaner.

*/

/* Time  Beats: 80.25% */
/* Space Beats: 41.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Codec_Concise {
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
        if (root == nullptr)
        {
            out << "# "; // '#' <==> nullptr
            return;
        }

        out << root->val << " "; // Obligatory to use <Space> for this Solution
        inorder_serialize(root->left, out);
        inorder_serialize(root->right, out);
    }

    TreeNode* inorder_deserialize(istringstream& in)
    {
        string value_str;
        in >> value_str; // Reads until it hits a <Space> character

        if (value_str == "#")
            return nullptr;

        TreeNode* root = new TreeNode(stoi(value_str));

        root->left  = inorder_deserialize(in);
        root->right = inorder_deserialize(in);

        return root;
    }
};
