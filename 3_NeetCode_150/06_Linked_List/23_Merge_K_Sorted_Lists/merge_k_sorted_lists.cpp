/*
    ============
    === HARD ===
    ============

    ===========================
    23) Merge k Sorted Lists
    ===========================

    ============
    Description:
    ============

    You are given an array of k linked-lists "lists", each linked-list is
    sorted in ascending order.

    Merge all the linked-lists into one sorted linked-list and return it.

    =============================================================================
    FUNCTION: struct ListNode* mergeKLists(std::vector<struct ListNode*>& lists);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  lists = [[1, 4, 5], [1, 3, 4], [2, 6]]
    Output: [1, 1, 2, 3, 4, 4, 5, 6]
    Explanation: The linked-lists are:
    [
        1 -> 4 -> 5,
        1 -> 3 -> 4,
        2 -> 6
    ]
    merging them into one sorted list:
    1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

    --- Example 2 ---
    Input:  lists = []
    Output: []


    --- Example 3 ---
    Input:  lists = [[]]
    Output: []

    *** Constraints ***
    k == lists.length
    0 <= k <= lists[i].length <= 500
    - 10^4 <= lists[i][j] <= 10^4
    lists[i] is sorted in ascending order
    The sum of lists[i].length will not exceed 10^4

*/

#include <vector>
using namespace std;

// Definition for singly-linked list.
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

    Basic Brute-Force Solution. If you've solve "21 Merge Sorted Lists", then
    this Brute-Force Solution is trivial.

*/

/* Time  Beats: 10.07% */
/* Space Beats: 39.36% */

/* Time  Complexity: O(N * k) */
/* Space Complexity: O(1)     */
class Solution_Brute_Force {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        if (lists.empty())
            return nullptr;
            
        const int k = lists.size();

        ListNode* list1 = lists[0];
        // O(N * k) (entire block)
        for (int i = 1; i < k; i++) // O(k)
            list1 = merge_two_sorted_linked_lists(list1, lists[i]); // O(N)

        return list1;
    }

private:
    // O(list1_size + list2_size) --> O(N), i.e. "total number of nodes"
    ListNode* merge_two_sorted_linked_lists(ListNode* list1, ListNode* list2)
    {
        ListNode dummy(-1);
        ListNode* tail = &dummy;

        while (list1 && list2)
        {
            if (list1->val <= list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }

            tail = tail->next;
        }

        if ( ! list1)
            tail->next = list2;
        else
            tail->next = list1;

        return dummy.next;
    }
};
