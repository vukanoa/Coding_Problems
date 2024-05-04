#include <iostream>
#include <sstream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    331) Verify Preorder Serialization of a Binary Tree
    ===================================================

    ============
    Description:
    ============

    One way to serialize a binary tree is to use preorder traversal. When we
    encounter a non-null node, we record the node's value. If it is a null
    node, we record using a sentinel value such as '#'.

                                    9
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             3             2
                            / \             \
                           /   \             \
                          /     \             \
                         4       1             6

    For example, the above binary tree can be serialized to the string
    "9,3,4,#,#,1,#,#,2,#,6,#,#", where '#' represents a null node.

    Given a string of comma-separated values preorder, return true if it is a
    correct preorder traversal serialization of a binary tree.

    It is guaranteed that each comma-separated value in the string must be
    either an integer or a character '#' representing null pointer.

    You may assume that the input format is always valid.

        For example, it could never contain two consecutive commas, such as
        "1,,3".

    Note: You are not allowed to reconstruct the tree.

    =====================================================
    FUNCTION: bool isValidSerialization(string preorder);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---


    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

/*
    ------------
    --- IDEA ---
    ------------

    We use stringstream to split the string by commas. We use nodes to count
    the nodes we are allowed to have next.  Every time we get a new node we
    decrease nodes, if we got below zero it's false.  If we get a non-null
    node, we can have after it two more nodes. At the end, we are supposed to
    end up with nodes == 0, otherwise the tree is not good.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.54% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isValidSerialization(string preorder)
    {
        std::istringstream ss(preorder);
        std::string curr_token;

        int nodes = 1;
        while (getline(ss, curr_token, ','))
        {
            nodes--;

            if (nodes < 0)
                return false;

            if (curr_token != "#")
                nodes += 2;
        }

        return nodes == 0;
    }
};
