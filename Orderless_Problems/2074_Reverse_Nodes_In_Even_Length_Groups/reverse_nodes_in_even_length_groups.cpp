/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    2074) Reverse Nodes in Even Length Groups
    =========================================

    ============
    Description:
    ============

    You are given the head of a linked list.

    The nodes in the linked list are sequentially assigned to non-empty groups
    whose lengths form the sequence of the natural numbers (1, 2, 3, 4, ...).
    The length of a group is the number of nodes assigned to it. In other words

        + The 1st node is assigned to the first group.

        + The 2nd and the 3rd nodes are assigned to the second group.

        + The 4th, 5th, and 6th nodes are assigned to the third group, and so
          on.

    Note that the length of the last group may be less than or equal to 1 + the
    length of the second to last group.

    Reverse the nodes in each group with an even length, and return the head of
    the modified linked list.

    ============================================================
    FUNCTION: ListNode* reverseEvenLengthGroups(ListNode* head);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [5,2,6,3,9,1,7,3,8,4]
    Output: [5,6,2,3,9,1,4,8,3,7]
    Explanation:
    - The length of the first group is 1, which is odd, hence no reversal occurs.
    - The length of the second group is 2, which is even, hence the nodes are reversed.
    - The length of the third group is 3, which is odd, hence no reversal occurs.
    - The length of the last group is 4, which is even, hence the nodes are reversed.

    --- Example 2 ---
    Input: head = [1,1,0,6]
    Output: [1,0,1,6]
    Explanation:
    - The length of the first group is 1. No reversal occurs.
    - The length of the second group is 2. The nodes are reversed.
    - The length of the last group is 1. No reversal occurs.

    --- Example 3 ---
    Input: head = [1,1,0,6,5]
    Output: [1,0,1,5,6]
    Explanation:
    - The length of the first group is 1. No reversal occurs.
    - The length of the second group is 2. The nodes are reversed.
    - The length of the last group is 2. The nodes are reversed.


    *** Constraints ***
    The number of nodes in the list is in the range [1, 10^5].
    0 <= Node.val <= 10^5

*/


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

    Self-explanatory. Fairly standard Linked-List problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* reverseEvenLengthGroups(ListNode* head)
    {
        // Creating a dummy node to avoid adding checks for the first node
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prev = dummy;

        // Loop to determine the lengths of groups
        for(int len = 1; head && len < 1e5; len++)
        {
            ListNode* tail = head;
            ListNode* next_head;

            // Determining the length of the current group
            // Its maximum length can be equal to len
            int j = 1;
            while (j < len && tail && tail->next)
            {
                tail = tail->next;
                j++;
            }

            // Head of the next group
            next_head = tail->next;

            if ((j % 2) == 0)
            {
                // If even sized group is found
                // Reversing the group and setting prev and head appropriately
                tail->next = nullptr;
                prev->next = reverse_list(head);

                prev = head;

                head->next = next_head;
                head = next_head;
            }
            else
            {
                // If group is odd sized, then simply going towards the next
                // group
                prev = tail;
                head = next_head;
            }
        }

        // Returning the head
        return dummy->next;
    }

private:
    // Function to reverse a linked list
    ListNode* reverse_list(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr)
        {
            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};
