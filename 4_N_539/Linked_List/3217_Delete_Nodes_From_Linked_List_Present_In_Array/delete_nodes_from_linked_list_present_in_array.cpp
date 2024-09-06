#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3217) Delete Nodes From Linked List Present In Array
    ====================================================

    ============
    Description:
    ============

    You are given an array of integers nums and the head of a linked list.
    Return the head of the modified linked list after removing all nodes from
    the linked list that have a value that exists in nums.

    ====================================================================
    FUNCTION: ListNode* modifiedList(vector<int>& nums, ListNode* head);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3], head = [1,2,3,4,5]
    Output: [4,5]
    Explanation: Remove the nodes with values 1, 2, and 3.

    --- Example 2 ---
    Input: nums = [1], head = [1,2,1,2,1,2]
    Output: [2,2,2]
    Explanation: Remove the nodes with value 1.

    --- Example 3 ---
    Input: nums = [5], head = [1,2,3,4]
    Output: [1,2,3,4]
    Explanation: No node has value 5.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    All elements in nums are unique.
    The number of nodes in the given list is in the range [1, 10^5].
    1 <= Node.val <= 10^5
    The input is generated such that there is at least one node in the linked list that has a value not present in nums.

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute force Solution would be to do this "while loop" for every element in
    the "nums" array.

    Once you come up with that Solution, ask yourself - Do I have some repeated
    work here? Can I optimize or remove "for loop" or "while loop"?

    You'll quickly realize that you cannot remove the "while loop". Then, ask
    yourself - Can I somehow remove the "for loop"?

    What is the purpose of that "for loop"?
    The purpose is to see, at each node in the the Linkd List, if that's the
    next node, i.e. the node to remove.

    Can we at any point(meaning any node) know if the next node is the one we
    have to remove, in O(1)?

    Well, currently we cannot since we have an array, but if we had a Hash Set,
    then we absolutely could.

    And voila - Construct the Hash Set from the input array "nums" and at each
    point(each node) in the "while loop" check if the next node is in the Hash
    Set.

    If it is - Skip it.
    If it is NOT - move the pointer "curr" to the right by one.

    That's it.

*/

/* Time  Beats: 90.81% */
/* Space Beats: 94.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head)
    {
        ListNode dummy(0);
        dummy.next = head;

        unordered_set<int> uset(nums.begin(), nums.end());

        ListNode* curr = &dummy;

        while (curr->next)
        {
            if (uset.find(curr->next->val) != uset.end())
                curr->next = curr->next->next;
            else
                curr = curr->next;
        }

        return dummy.next;
    }
};
