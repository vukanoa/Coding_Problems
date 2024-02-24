#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    21) Merge Two Sorted Lists
    ===========================

    ============
    Description:
    ============

    You are given the heads of two sorted linked lists list1 and list2.

    Merge the two lists in a one sorted list. The list should be made by
    splicing together the nodes of the first two lists.

    Return the head o fhte merged linked list.

    ====================================================================
    FUNCTION: ListNode* mergeTwoLists(ListNode* list1, ListNode* list2);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  list1 = [1, 2, 4], list2 = [1, 3, 4]
    Output: [1, 1, 2, 3, 4, 4]

    --- Example 2 ---
    Input:  list1 = [], list2 = []
    Output: []

    --- Example 3 ---
    Input:  list1 = [], list2 = [0]
    Output: [0]

    *** Constraints ***
    The number of nodes in both lists is in the range [0, 50]
    -100 <= Node.val <= 100
    Both list1 and list2 are sorted in non-decreasing order.

*/

// Definition for singly-linked list.
typedef struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
}ListNode;

/*
    ------------
    --- IDEA ---
    ------------

    Check if either of lists(list1 or list2) is nullptr, if it is, then return
    the other. Even if the other is a nullputr as well, we would essentially
    just return a nullptr which is a corect answer in a case where both lists
    are indeed nullptr's.

    Since it is noted that the lists are SORTED, our finally merged list have
    to begin with a smaller head of list1 & list2.

    So if list1->val is smaller than list2->val then our global head of the new
    merged list which we will return as a result, named "head", have to point
    to this node.

    And make list1 point to its next node in the list.

    If it was the opposite, then make "head" point to list2 and make list2
    point to its next node in the list.

    Let tail point to "head" before we begin "weaving" these two lists.

    Now enter the while loop which iterates while BOTH list1 and list2 point to
    atleast one node. Meaning neither is nullptr.

    If either or both are nullptr, break the while loop.

    Inside of the while loop, always check which one points to a lower value.
    If list1->val is smaller than list2->val then let tail's next point to this
    (smaller node of the list1 or list2, list1 in this case) node and update
    tail to now point to that node.

    If list2->val is smaller or equal to list1 then do the same as above, just
    but with list2.

    After breaking the while loop check if list1 is empty, meaning that list1
    is pointing to nullptr, if that is indeed the case, then make sure that
    tail->next points to the other, potentially non-empty, list, list2 in this
    case.

    If it was the opposite, then do the same as above, but swap the place of
    words "list1" and "list2".

    However, if both were pointing to nullptr then we would've entered the
    first if statement and that would just make tail's next point to a nullptr
    which basically does nothing.

    And at the very end, just return the "head".

*/

/* Time  Beats: 68.57% */
/* Space Beats: 86.90% */

/*
    Time  Complexity: O(m + n)

    Where m is the length of list1
    and n is the length of list2
*/
/*
    Space Complexity: O(1)
*/
class Solution_Naive {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        if (list1 == nullptr)
            return list2;
        else if (list2 == nullptr)
            return list1;

        ListNode* head;
        if (list1->val < list2->val)
        {
            head = list1;
            list1 = list1->next;
        }
        else
        {
            head = list2;
            list2 = list2->next;
        }

        ListNode* tail = head;

        while (list1 && list2)
        {
            if (list1->val < list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
                tail = tail->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
                tail = tail->next;
            }
        }

        if (list1 == nullptr)
            tail->next = list2;
        else
            tail->next = list1;

        return head;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Using Dummy node to avoid the initial if-else.
    It's a beat more neatly written.

*/

/* Time  Beats: 100% */
/* Space Beats: 11.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        // On the Stack
        ListNode dummy(0); // It's faster than ListNode *dummy = new ListNode()
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

        if (!list1)
            tail->next = list2;
        else
            tail->next = list1;

        return dummy.next;
    }
};


void
print_list(struct ListNode* head)
{
    std::cout << "\n\t[";

    bool first = true;
    while (head)
    {
        if (!first)
            std::cout << " -> ";
        else
            first = false;

        std::cout << head->val;
        head = head->next; }

    std::cout << "]\n\n";
}


int
main()
{
    Solution_Naive     sol_naive;
    Solution_Efficient sol_efficient;

    /* Example 1 */
    ListNode four1(4);
    ListNode two1 (2, &four1);
    ListNode one1 (1, &two1);

    ListNode four2 (4);
    ListNode three2(3, &four2);
    ListNode one2  (1, &three2);

    ListNode* list1 = &one1;
    ListNode* list2 = &one2;



    /* Example 2 */
    // ListNode* list1 = nullptr;
    // ListNode* list2 = nullptr;



    /* Example 3 */
    // ListNode zero2(0);

    // ListNode* list1 = nullptr;
    // ListNode* list2 = &zero2;


    std::cout << "\n\t==============================";
    std::cout << "\n\t=== MERGE TWO SORTED LISTS ===";
    std::cout << "\n\t==============================\n";


    /* Write Input */
    std::cout << "\n\tList1:";
    print_list(list1);

    std::cout << "\n\tList2:";
    print_list(list2);


    // Solution
    // ListNode* head = sol_naive.mergeTwoLists(list1, list2);
    ListNode* head = sol_efficient.mergeTwoLists(list1, list2);


    /* Write Input */
    std::cout << "\n\tMerged Lists: List1 & List2:";
    print_list(head);

    return 0;
}
