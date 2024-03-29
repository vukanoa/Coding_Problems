#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    61) Rotate List
    ===========================

    ============
    Description:
    ============

    Given the head of a linked list, rotate the list to the right by k places.

    =======================================================
    FUNCTION: ListNode* rotateRight(ListNode* head, int k);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    1 --> 2 --> 3 --> 4 --> 5

    5 --> 1 --> 2 --> 3 --> 4 // Rotate 1

    4 --> 5 --> 1 --> 2 --> 3 // Rotate 2

    Input: head = [1,2,3,4,5], k = 2
    Output: [4,5,1,2,3]




    --- Example 2 ---
    0 --> 1 --> 2

    2 --> 0 --> 1 // Rotate 1

    1 --> 2 --> 0 // Rotate 2

    0 --> 1 --> 2 // Rotate 3

    2 --> 0 --> 1 // Rotate 4 (Same as Rotate 1)
    Input: head = [0,1,2], k = 4
    Output: [2,0,1]




    *** Constraints ***
    The number of nodes in the list is in the range [0, 500].
    -100 <= Node.val <= 100
    0 <= k <= 2 * 109

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

/* Time  Beats: 95.21% */
/* Space Beats: 25.37% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Elegant {
public:
    ListNode* rotateRight(ListNode* head, int k)
    {
        if (head == nullptr)
            return nullptr;

        int n = 1;
        ListNode* tail = head;
        while (tail->next)
        {
            tail = tail->next;
            n++;
        }

        tail->next = head;
        k = k % n;

        for (int i = 0; i < n - k; i++)
            tail = tail->next;

        head = tail->next;
        tail->next = nullptr;

        return head;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    I believe this one is easier to read and grasp than the above one.
    However, the above one is much more elegant!

*/

/* Time  Beats: 89.85% */
/* Space Beats: 21.70% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Verbose {
public:
    ListNode* rotateRight(ListNode* head, int k)
    {
        if (k == 0 || !head || !head->next)
            return head;

        int n = count_nodes(head);

        k = k % n;
        if (k == 0)
            return head;

        ListNode dummy(0);
        dummy.next = head;

        ListNode* right = head;
        for (int i = 0; i < k; i++)
            right = right->next;

        ListNode* left = &dummy;

        while (right)
        {
            left  = left->next;
            right = right->next;
        }

        ListNode* tail = left;
        for (int i = 0; i < k; i++)
            tail = tail->next;

        dummy.next = left->next;
        left->next = nullptr; // Unlink
        tail->next = head;

        return dummy.next;
    }

private:
    int count_nodes(ListNode* head)
    {
        int count = 0;
        while (head)
        {
            count++;
            head = head->next;
        }

        return count;
    }
};
