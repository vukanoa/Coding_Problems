/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3447) Assign Elements to Groups with Constraints
    ================================================

    ============
    Description:
    ============

    You are given an integer array groups, where groups[i] represents the size
    of the ith group. You are also given an integer array elements.

    Your task is to assign one element to each group based on the following
    rules:

        + An element j can be assigned to a group i if groups[i] is divisible
          by elements[j].

        + If there are multiple elements that can be assigned, assign the
          element with the smallest index j.

        + If no element satisfies the condition for a group, assign -1 to that
          group.

    Return an integer array assigned, where assigned[i] is the index of the
    element chosen for group i, or -1 if no suitable element exists.

    =====
    Note: An element may be assigned to more than one group.
    =====

    =================================================================================
    FUNCTION: vector<int> assignElements(vector<int>& groups, vector<int>& elements);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: groups = [8,4,3,2,4], elements = [4,2]
    Output: [0,0,-1,1,0]
    Explanation:
        elements[0] = 4 is assigned to groups 0, 1, and 4.
        elements[1] = 2 is assigned to group 3.
        Group 2 cannot be assigned any element.


    --- Example 2 ---
    Input: groups = [2,3,5,7], elements = [5,3,3]
    Output: [-1,1,0,-1]
    Explanation:
        elements[1] = 3 is assigned to group 1.
        elements[0] = 5 is assigned to group 2.
        Groups 0 and 3 cannot be assigned any element.


    --- Example 3 ---
    Input: groups = [10,21,30,41], elements = [2,1]
    Output: [0,1,0,1]
    Explanation:
    elements[0] = 2 is assigned to the groups with even values, and
    elements[1] = 1 is assigned to the groups with odd values.


    *** Constraints ***
    1 <= groups.length <= 10^5
    1 <= elements.length <= 10^5
    1 <= groups[i] <= 10^5
    1 <= elements[i] <= 10^5

*/

#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.10% */
/* Space Beats: 63.16% */

/* Time  Complexity: O(N + M + M * sqrt(G)) */ // G <==> max value in groups
/* Space Complexity: O(N)                   */
class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements)
    {
        vector<int> result;

        unordered_map<int,int> elem_to_idx;
        for (int i = 0; i < elements.size(); i++)
        {
            if (elem_to_idx.count(elements[i]) == 0) // Doesn't exist
                elem_to_idx[elements[i]] = i;
        }

        for (int i = 0; i < groups.size(); i++)
            check(groups[i], elem_to_idx, result);

        return result;
    }

private:
    void check(int group, unordered_map<int,int>& elem_to_idx, vector<int>& result)
    {
        int idx = INT_MAX;

        for (int f = 1; f*f <= group; f++) // f <==> factor
        {
            if (group % f == 0 && elem_to_idx.count(f))
                idx = min(idx, elem_to_idx[f]);

            if (f != group/f && group % f == 0 && elem_to_idx.count(group/f))
                idx = min(idx, elem_to_idx[group/f]);
        }

        if (idx != INT_MAX)
            result.push_back(idx);
        else
            result.push_back(-1);
    }
};
