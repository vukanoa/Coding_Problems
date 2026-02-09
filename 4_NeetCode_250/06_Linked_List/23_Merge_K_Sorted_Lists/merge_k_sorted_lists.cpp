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




/*
    ------------
    --- IDEA ---
    ------------

    Instead of iterating through each list and merging it with all the previous
    nodes, we can do a "Divide and Conquer" technique where we're merging N
    nodes exactly logk times.

    Where logk is the "heigh of the tree", meaning it's the total number of
    times we can divide 'k' lists before we hit 1.

    That's the definition of "logarithm".

*/

/* Time  Beats: 66.43% */
/* Space Beats:  24.61% */

/* Time  Complexity: O(N * logK) */
/* Space Complexity: O(logK)     */ // Because of the Call-Stack from Recursion
class Solution_Divide_and_Conquer {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        const int N = lists.size();

        // O(N * logk) (entire function)
        return divide_and_conquer(0, N-1, lists);
    }

private:
    // O(N * logk) (entire function)
    ListNode* divide_and_conquer(int low, int high, vector<ListNode*>& lists)
    {
        if (low > high)
            return nullptr;

        if (low == high)
            return lists[low]; // Or "lists[high]" it does NOT matter

        int mid = low + (high - low) / 2;

        // Divide
        ListNode* left  = divide_and_conquer(low  ,  mid, lists); // O(logk)
        ListNode* right = divide_and_conquer(mid+1, high, lists); // O(logk)

        // Conquer
        return merge_two_sorted_linked_lists(left, right); // O(N)
    }

    // O(list1_size + list2_size) --> O(N), i.e. "total number of nodes"
    ListNode* merge_two_sorted_linked_lists(ListNode* list1, ListNode* list2)
    {
        ListNode dummy(-1);
        ListNode* tail = &dummy;

        // O(list1_size + list2_size) (entire block)
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
