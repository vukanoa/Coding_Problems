/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3217) Delete Nodes From Linked List Present in Array
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
    The input is generated such that there is at least one node in the linked
    list that has a value not present in nums.

*/

#include <unordered_set>
#include <vector>
using namespace std;

/**
 * Definition for singly-linked list.
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};




/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory. Read through the code and you'll understand it.

*/

/* Time  Beats: 79.58% */
/* Space Beats: 48.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head)
    {
        const int N = nums.size();

        unordered_set<int> uset(nums.begin(), nums.end());

        ListNode dummy(0);
        ListNode* curr = &dummy;

        while (head)
        {
            if ( ! uset.count(head->val))
            {
                curr->next = head;
                curr = curr->next;
            }

            head = head->next;
            curr->next = nullptr;
        }

        return dummy.next;
    }
};
