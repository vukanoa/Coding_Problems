/*

    The distance between 2 binary strings is the sum of their lengths after
    removing the common prefix. For example: the common prefix of 1011000 and
    1011110 is 1011 so the distance is len("000") + len("110") = 3 + 3 = 6.

    Given a list of binary strings, pick a pair that gives you maximum distance
    among all possible pair and return that distance.

*/

/*
My cpp solution with trie and level traversing.

    Build a tire tree.
    The node value is the max suffix length of each prefix.
    The left node means '0', and the right node means '1'.
    The isEnd means whether a node is the last char of the string.
    Traversing the tree and update the max distance.
    For each node, the max distance is the sum of two children.

    If there is only one child and the node is the end of one string, then the
    maxdistance is the value of the child.
*/

#include<iostream>
#include<vector>
#include<string>
#include<queue>

/*
    ------------
    --- IDEA ---
    ------------

    Trie + BFS.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
private:
    struct TreeNode{
        int val;
        bool is_end;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val) : val(val), is_end(false), left(nullptr), right(nullptr){}
    };

public:
    int maxDistance(std::vector<std::string>& bin_strings)
    {
        TreeNode* root = new TreeNode(0);
        buildTree(root, bin_strings);

        int max_distance = 0;

        std::queue<TreeNode*> queue;
        queue.push(root);

        while(!queue.empty())
        {
            TreeNode* cur = queue.front();
            queue.pop();

            if(cur->left || cur->right)
            {
                if(cur->left && cur->right)
                    max_distance = std::max(max_distance, cur->left->val + cur->right->val);
                else if(cur->is_end)
                    max_distance = std::max(max_distance, cur->left ? cur->left->val : cur->right->val);
            }

            if(cur->left)
                queue.push(cur->left);

            if(cur->right)
                queue.push(cur->right);
        }

        return max_distance;
    }

private:
    void buildTree(TreeNode* root, std::vector<std::string>& bin_strings)
    {
        for(int i = 0; i < bin_strings.size(); i++)
        {
            TreeNode* cur = root;

            int j = 0;
            int len = bin_strings[i].length();

            while(j < len)
            {
                if(bin_strings[i][j] == '0')
                {
                    if(cur->left == nullptr)
                        cur->left = new TreeNode(len - j);
                    else
                        cur->left->val = std::max(cur->left->val, len - j);

                    cur = cur->left;
                }
                else
                {
                    if(cur->right == nullptr)
                        cur->right = new TreeNode(len - j);
                    else
                        cur->right->val = std::max(cur->right->val, len - j);

                    cur = cur->right;
                }

                j++;
            }

            cur->is_end = true;
        }

        return;
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<std::string> bin_strings = {"1011000", "1011110", "1010000", "111000"};

    /* Example 2 */
    // std::vector<std::string> bin_strings = {"1011", "1001", "1000", "0000", "0001"};

    /* Example 3 */
    std::vector<std::string> bin_strings = {"1011000", "10101", "10000", "00", "11100000", "01000000000000000"};

    /* Example 4 */
    // std::vector<std::string> bin_strings = {"1011000", "10101", "1000", "0000", "0001"}; 


    std::cout << "\n\t====================";
    std::cout << "\n\t=== MAX DISTANCE ===";
    std::cout << "\n\t====================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tBinary Strings: [";
    for (auto x: bin_strings)
    {
        if (!first)
            std::cout << ", ";

        std::cout << "\"" << x << "\"";
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    int result = sol.maxDistance(bin_strings);


    /* Write Output */
    std::cout << "\n\tResult(Max Distance): " << result;

    std::cout << "\n\n";

    return 0;
}
