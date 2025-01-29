/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    3331) Find Subtree Sizes After Changes
    ======================================

    ============
    Description:
    ============

    You are given a tree rooted at node 0 that consists of n nodes numbered
    from 0 to n - 1. The tree is represented by an array parent of size n,
    where parent[i] is the parent of node i. Since node 0 is the root,
    parent[0] == -1.

    You are also given a string s of length n, where s[i] is the character
    assigned to node i.

    We make the following changes on the tree one time simultaneously for all
    nodes x from 1 to n - 1:

    Find the closest node y to node x such that y is an ancestor of x, and
    s[x] == s[y]. If node y does not exist, do nothing. Otherwise, remove the
    edge between x and its current parent and make node y the new parent of x
    by adding an edge between them.

    Return an array answer of size n where answer[i] is the size of the subtree
    rooted at node i in the final tree.

    ======================================================================
    FUNCTION: vector<int> findSubtreeSizes(vector<int>& parent, string s);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: parent = [-1,0,0,1,1,1], s = "abaabc"
    Output: [6,3,1,1,1,1]

    --- Example 2 ---
    Input: parent = [-1,0,4,0,1], s = "abbba"
    Output: [5,2,1,1,1]
    The parent of node 4 will change from node 1 to node 0.
    The parent of node 2 will change from node 4 to node 1.


    *** Constraints ***
    n == parent.length == s.length
    1 <= n <= 10^5
    0 <= parent[i] <= n - 1 for all i >= 1.
    parent[0] == -1
    parent represents a valid tree.
    s consists only of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N + H) */ // Where 'H' is the Height of the Tree
/* Space Complexity: O(N^2)   */

/* Time  Beats: 86.81% */
/* Space Beats: 86.90% */
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s)
    {
        vector<vector<int>> adj_list(s.length());
        vector<int> answer(s.length(), 0);
        
        for (int i = 1; i < parent.size(); i++)
            adj_list[parent[i]].push_back(i);
        
        unordered_map<char, vector<int>> state;
        calculate_subtree_sizes(0, adj_list, s, state, answer);
        
        return answer;
    }

private:
    void calculate_subtree_sizes(int curr_node, vector<vector<int>>& adj_list, string& s, unordered_map<char, vector<int>>& state, vector<int> &answer)
    {
        answer[curr_node] = 1;
        state[s[curr_node]].push_back(curr_node);
        
        for (int child_node : adj_list[curr_node])
        {
            calculate_subtree_sizes(child_node, adj_list, s, state, answer);
            
            if(!state[s[child_node]].empty())
            {
                int ancestorNode = state[s[child_node]].back();
                answer[ancestorNode] += answer[child_node];
            }
            else
            {
                answer[curr_node] += answer[child_node];
            }
        }
        
        state[s[curr_node]].pop_back();
    }
};
