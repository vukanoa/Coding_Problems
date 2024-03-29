#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    148) Sort List
    ===========================

    ============
    Description:
    ============

    Given the "head" of a linked list, return the list after sorting it in
    ascending order.

    =====
    Node: Can you sort the linked list in O(n logn) time and O(1) memory?
    =====

    =============================================
    FUNCTION: ListNode* sortList(ListNode* head);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  head = [4, 2, 1, 3]
    Output: [1, 2, 3, 4]

    --- Example 2 ---
    Input:  head =[-1, 5, 3, 4, 0]
    Output: [-1, 0, 3, 4, 5]

    --- Example 3 ---
    Input:  head = []
    Output: []

    *** Constraints ***
    The number of nodes in the list is in the range [0, 5 * 10^4]
    -10^5 <= Node.val <= 10^5

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};




/* Quick Sort */
/* This Solution Gives TLE(Time Limit Exceeded)*/

/*
    Time  Complexity: O(n^2)
    The average Time Complexity is O(n * logn), however the absolute worst Time
    Complexity is O(n^2) and that happens when the chosen pivot in each
    partitioning step is either the smallest or the lagest element in the
    subarray, which causes the partition function to split the array into two
    subarrays of size 1 and n-1. This leads to n recursive calls, each with a
    subarray of size n-1, resulting in a worst-case Time Complexity of O(n^2).

    The worst case scenario for Quick Sort:
    [50000, 49999, 49998, 49997, ..., 3, 2, 1]

*/
/* Space Complexity: O(n) */
class Solution_Quick_Sort {
public:
    ListNode* sortList(ListNode* head)
    {
        if (head == nullptr)
            return nullptr;

        ListNode *tmp = head;
        while (tmp->next)
            tmp = tmp->next;

        ListNode *tail = tmp;

        return quick_sort(head, tail);
    }

private:
    ListNode* partition(ListNode* left, ListNode* right)
    {
        ListNode* front = NULL;
        ListNode* first_node = left;

        while(left != right)
        {
            if (left->val < right->val)
            {
                front = front ? front->next : first_node;

                if (front != left)
                    std::swap(front->val, left->val);
            }
            left = left->next;
        }
        std::swap(front ? front->next->val : first_node->val, right->val);

        return front ? front : first_node;
    }

    ListNode* quick_sort(ListNode* head, ListNode* tail)
    {
        if (head == NULL || tail == NULL || head == tail)
            return head;

        ListNode* pivot = partition(head, tail);

        quick_sort(head, pivot);
        quick_sort(pivot->next, tail);

        return head;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Top-Down Approach:
        Time:  O(n * logn)
        Space: O(logn)

    Classic Merge Sort on Linked List. (There is a better Solution down)


                                          ^
        10 -> 1 -> 60 -> 30 -> 5          |
            /        \                    |
    10 -> 1          60 -> 30 -> 5        |  log n
    /      \             /    \           |
  10       1           60      30 -> 5    |
  |        |           |       /      \   |
  |        |           |      30       5  v
--\--------/-----------|------\--------/-----------
   v      v            v       v      v
  1  ->  10           60      5   ->  30
  |                   \       /
  |                    v     v
   \                  5  ->  30  -> 60
    \                      /
     v                    v
   1  ->  5  -> 10  -> 30  -> 60



*/

/* Time  Beats: 81.24% */
/* Space Beats: 81.64% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(logn) */
class Solution_Merge_Sort_Classic{
public:
    ListNode* sortList(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        ListNode* mid   = middle(head);
        ListNode* left  = sortList(head);
        ListNode* right = sortList(mid);

        return merge(left, right);
    }

    ListNode* merge(ListNode* list1, ListNode* list2)
    {
        struct ListNode dummy_head(0);
        ListNode* ptr = &dummy_head;

        while (list1 && list2)
        {
            if (list1->val < list2->val)
            {
                ptr->next = list1;
                list1 = list1->next;
            }
            else
            {
                ptr->next = list2;
                list2 = list2->next;
            }

            ptr = ptr->next;
        }

        if (list1)
            ptr->next = list1;
        else
            ptr->next = list2;

        return dummy_head.next;
    }

    ListNode* middle(ListNode* head)
    {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* mid = slow->next;
        slow->next = nullptr;

        return mid;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but written in a different way. I believe this one is easier
    to read and grasp.

*/

/* Time  Beats: 99.10% */
/* Space Beats: 90.73% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(logn) */
class Solution_Efficient_Merge {
public:
    ListNode* sortList(ListNode* head)
    {
        if (!head || !head->next)
            return head;
        
        ListNode* mid = middle(head);

        ListNode* a = head;
        ListNode* b = mid->next;

        mid->next = nullptr;

        a = sortList(a);
        b = sortList(b);

        return merge_two_sorted_lists(a, b);
    }

private:
    ListNode* middle(ListNode* head)
    {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* merge_two_sorted_lists(ListNode* l1, ListNode* l2)
    {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 && l2)
        {
            if (l1->val <= l2->val)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }

            tail = tail->next;
        }

        if (!l1)
            tail->next = l2;
        else
            tail->next = l1;
        
        return dummy.next;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Bottom-Up Approach:
        Time:  O(n * logn)
        Space: O(1)

    The idea is simple.
    Go through the list and merge sorted lists.

    How do you do that if you have an unsorted list?
    Well in any list, a single element is always sorted - one element in the
    list, array or any other data structure, is considered sorted.

    So what we're doing here is:
        Merge Two Sorted Lists:
            1. 1st List is a single element
            2. 2nd List is a single element

    Consider this example:

    15 -> 7 -> 32 -> 1 -> 10 -> 11 -> 3 -> 4 -> 12 -> 8

    Now sort every two elements:

    Size = 2
    7 -> 15 -> 1 -> 32 -> 10 -> 11 -> 3 -> 4 -> 8 -> 12
    ~~~~~~~    ~~~~~~~    ~~~~~~~~    ~~~~~~~   ~~~~~~~~

    Now when we have sublists of 2 elements sorted, now we do the same, but
    for 4 elements. (Always the power of 2).

    Now we have:

    Size = 4
    1 -> 7 -> 15 -> 32 -> 3 -> 4 -> 10 -> 11 -> 8 -> 12
    ~~~~~~~~~~~~~~~~~~    ~~~~~~~~~~~~~~~~~~

    The rest is left untouched sinced we know that part is sorted.

    Now size is not 4, but 8.

    Size = 8
    1 -> 3 -> 4 -> 7 -> 10 -> 11 -> 15 -> 32 -> 8 -> 12
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    And finally, do it for 16.

    Size = 16
    1 -> 3 -> 4 -> 7 -> 8 -> 10 -> 11 -> 12 -> 15 -> 32
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    So we're passing the list logn times. For sizes: 2, 4, 8 and 16(in this ex)
    But each time we're doing "Merge Two Sorted Lists" which is O(n).

    Thus the overall Time Complexity is O(n * logn);
    But the Space Complexity is O(1) since we do not need the Stack for
    recursion since we are doing it iteratively.
*/

/* Time  Beats: 84.50% */
/* Space Beats: 97.86% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution_Merge_Sort_Improved{
public:
    ListNode* tail = new ListNode();
    ListNode* next_sublist = new ListNode();

    ListNode* sortList(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        int n = count_nodes(head);

        ListNode* start = head;
        ListNode dummy_head(0);

        for (int size = 1; size < n; size = size * 2)
        {
            tail = &dummy_head;

            while (start)
            {
                if (start->next == nullptr)
                {
                    tail->next = start;
                    break;
                }

                ListNode* mid = split(start, size);
                merge(start, mid);

                start = next_sublist;
            }
            start = dummy_head.next;
        }

        return dummy_head.next;
    }

    ListNode* split(ListNode* start, int size)
    {
        ListNode* mid_prev = start;
        ListNode* end = start->next;

        // Use "Fast and Slow" approach to find middle and end of second linked list
        for (int index = 1; index < size && (mid_prev->next || end->next); index++)
        {
            if (end->next)
            {
                if (end->next->next)
                    end = end->next->next;
                else
                    end = end->next;
            }

            if (mid_prev->next)
                mid_prev = mid_prev->next;
        }

        ListNode* mid = mid_prev->next;
        next_sublist = end->next;
        mid_prev->next = nullptr;
        end->next = nullptr;

        // Return the start of second linked list
        return mid;
    }

    void merge(ListNode* list1, ListNode* list2)
    {
        ListNode dummy_head(0);
        ListNode* new_tail = &dummy_head;

        while (list1 && list2)
        {
            if (list1->val < list2->val)
            {
                new_tail->next = list1;
                list1 = list1->next;
                new_tail = new_tail->next;
            }
            else
            {
                new_tail->next = list2;
                list2 = list2->next;
                new_tail = new_tail->next;
            }
        }

        new_tail->next = (list1) ? list1 : list2;

        // Traverse till the end of merged list to get the new_tail
        while (new_tail->next)
            new_tail = new_tail->next;

        // Link the old tail with the head of merged list
        tail->next = dummy_head.next;

        // Update the old tail with the new tail of merged list
        tail = new_tail;
    }

    int count_nodes(ListNode* head)
    {
        int cnt = 0;

        ListNode* ptr = head;
        while (ptr)
        {
            ptr = ptr->next;
            cnt++;
        }

        return cnt;
    }
};




void
print_list(struct ListNode* head)
{
    std::cout << "\n\t\t[";

    bool first = true;
    while (head)
    {
        if (!first)
            std::cout << " -> ";
        else
            first = false;

        std::cout << head->val;
        head = head->next;
    }

    std::cout << "]\n\n";
}


int
main()
{
    Solution_Quick_Sort          sol_quick;
    Solution_Merge_Sort_Classic  sol_merge_classic;
    Solution_Efficient_Merge     sol_efficient_merge;
    Solution_Merge_Sort_Improved sol_merge_improved;


    /* Example 1 */
    /*
        4 -> 2 -> 3 -> 1
    */
    struct ListNode one(1);
    struct ListNode three(3);
    struct ListNode two(2);
    struct ListNode four(4);
    three.next     = &one;
    two.next       = &three;
    four.next      = &two;
    struct ListNode* head = &four;


    /* Example 2 */
    /*
        -1 -> 5 -> 3 -> 4 -> 0
    */
    // struct ListNode minus_one(-1);
    // struct ListNode five(5);
    // struct ListNode three(3);
    // struct ListNode four(4);
    // struct ListNode zero(0);
    // minus_one.next = &five;
    // five.next = &three;
    // three.next = &four;
    // four.next = &zero;
    // struct ListNode* head = &minus_one;


    /* Example 3 */
    // struct ListNode* head = nullptr;


    std::cout << "\n\t=================";
    std::cout << "\n\t=== SORT LIST ===";
    std::cout << "\n\t=================\n\n";


    /* Before */
    std::cout << "\n\tBefore:";
    print_list(head);


    /* Solution */
    // head = sol_quick.sortList(head);
    // head = sol_merge_classic.sortList(head);
    head = sol_efficient_merge.sortList(head);
    // head = sol_merge_improved.sortList(head);


    /* After */
    std::cout << "\n\tAfter:";
    print_list(head);


    return 0;
}
