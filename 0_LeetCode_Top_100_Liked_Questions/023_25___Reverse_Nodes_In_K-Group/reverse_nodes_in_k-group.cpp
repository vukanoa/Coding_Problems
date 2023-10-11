#include <iostream>


/*
    ============
    === HARD ===
    ============

    ============================
    25) Reverse Nodes in k-Group
    ============================

    ============
    Description:
    ============

    Given the "head" of a linked list, reverse the nodes of the list "k" at a
    time, and return the modified list.

    "k" is a positive integer and is less than or equal to the length of the
    linked list. If the number of nodes is not a multiple of "k" then left-out
    nodes, in the end, should remain as it is.

    You may not alter the values in the list's nodes, only nodes themselves
    may be changed.

    =========================================================
    FUNCTION: ListNode* reverseKGroup(ListNode* head, int k);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  head = [1, 2, 3, 4, 5], k = 2
    Output: [2, 1, 4, 3, 5]

    --- Example 2 ---
    Input:  head = [1, 2, 3, 4, 5], k = 3
    Output: [3, 2, 1, 4, 5]

    *** Constraints ***
    The number of nodes in the list is "n".
    1 <= k <= n <= 5000
    0 <= Node.val <= 1000

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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
        head = head->next;
    }

    std::cout << "]\n\n";
}


/*
    ------------
    --- IDEA ---
    ------------

    We have two functions:
        1. reverseKgroup
        2. reverse_list

    I) reverseKGroup
        If k is equal to 1 or if head is nullptr, just return the head of the
        original list.

        First we count the number of nodes in the list and assign that number
        to variable "remaining_nodes".

        We have two pointers:
            1. local_head
                which points to the first node in the sublist we're trying
                to reverse. There is a drawn comment down there.
            2. ultimate head
                which points to the head of the entirely k-reversed list.

        There are "remaining_nodes" in the list at the beginning and after
        each k-reverse, we subtract 'k' from "remaining_nodes".
        While loop loops until remaining nodes is greater than or equal to k.

        Example:
        If there are 5 nodes and k = 2, then we can reverse:
            first with second
            third with fourth
            fifth remains as it is

        At the last "iteration", remaining nodes is going to be 1 and k = 2,
        thus we end the while loop and return the ultimate_head.

        At the beginning of the while loop, initialize:
            1. "tail" to point to "local_head" which is going to become the end
            of the sublist we're k-reversing afer the call of function
            "reverse_list".

            2. "rem" to nullptr, which represents the rest of the list that has
            yet to be k-reversed after the call of function "reverse_list".

        We're calling the function:
            reverse_list(local_head, rem, k)

        1. "local_head" is the head of the sublist we're reversing.

        2. "rem" should point to the first node of the rest of the list that
        has to been k-reversed. "rem" stands for Remainder(of the list).

        3. 'k' is the length of the sublist we're reversing.


        It's important to note what exactly this "reverse_list function" does.

        k = 3
                      tail ---
ultimate_head ---            |
         _______|      -------
        |              |
        v              v
        3 -> 2 -> 1 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> nullptr
                       ^
                       |
        local_head -----



        After the call of this function, we have this:

ultimate_head ---
         _______|
        |
        v
        3 -> 2 -> 1
                  |
                  v
        6 -> 5 -> 4 -> nullptr
        ^         ^
        |___      |
            |     |
local_head --     |
                  |
        tail-------


       7 -> 8 -> 9 -> 10 -> nullptr
       ^
       |
 rem ---

        That's it. That's how the list looks like AFTER the call of
        reverse_list function.


        Now we have to ask if this was a first reverse of k-nodes. If it is
        then make "ultimate_head" point to "local_head" and set "first" to
        false.

        Link current tail(in the first reversing), to the rest of the list.

        If it was:
                1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> nullptr

        Now it's:
                3 -> 2 -> 1 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> nullptr
                ^         ^    ^
                |         |    |
        local_head        |    |
                          |    |
                  tail ---     |
                               |
                       rem ----

        We have linked tail's next to the rest of the list denotes with pointer
        "rem".

        However, if it wasn't the first k-reverse then "first" is false and
        thus we have to relink the previous part of the list with the newly
        k-reversed sublist and we also have to relink the end of this newly
        k-reversed sublist with the rest of the list denoted with a pointer
        "rem".

        So, since the additional thing we have to do here is to relink the
        previous part of the list with this newly k-reversed sublist, that
        means we have to keep a pointer to the end of the list that is before
        the head of the sublist we're k-reversing. That is right before
        the "local_head" BEFORE the call of function "reverse_list".

        That pointer is going to be denoted with "tail_of_list_before_sublist".

        After we're finished, subtract 'k' from "remaining_nodes" and check
        the while loop condition and potentially loop again.

*/



/* Time  Beats: 54.58% */
/* Space Beats: 77.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
    void reverse_list(struct ListNode** head, struct ListNode** rem, int k)
    {
        struct ListNode* prev = nullptr;
        struct ListNode* curr = (*head);
        struct ListNode* next = (*head);

        // Rest of the list yet to be k-reversed
        (*rem) = nullptr;

        while (curr && k--)
        {
            if (k == 0)
                (*rem) = next->next;

            next = next->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        (*head) = prev;
    }


    struct ListNode* reverseKGroup(struct ListNode* head, int k)
    {
        if (k == 1 || head == nullptr)
            return head; // Return Original List

        int n = 0;
        struct ListNode* local_head = head;
        struct ListNode* ultimate_head = head;

        // Count the number of nodes in the list
        while (local_head)
        {
            n++;
            local_head = local_head->next;
        }
        local_head = head; // Make local_head point to head again

        int remaining_nodes = n;
        bool first = true;
        struct ListNode* tail_of_list_before_sublist;

                /*
                    ultimate_head ---
                                    |
                    -----------------
                    |
                    v
                    3 -> 2 -> 1 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9
                                   ^
                                   |
                       -------------
                       |
                    local_head

                    It's the head of a sublist that we're trying to reverse.
                    Sublist:
                        4 -> 5 -> 6
                    in this case (k = 3)
                */

        while (remaining_nodes >= k)
        {
            struct ListNode* tail = local_head;
            struct ListNode* rem = nullptr; // Remainder, rest of the list
            reverse_list(&local_head, &rem, k);

            if (first)
            {
                ultimate_head = local_head;
                first = false;
            }
            else if (k < n)
                tail_of_list_before_sublist->next = local_head;

            tail->next = rem;
            tail_of_list_before_sublist = tail;
            local_head = rem;

            remaining_nodes = remaining_nodes - k;

            // print_list(ultimate_head);
        }

        return ultimate_head;
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    This is a much more concise and robust Solution. Go through a few examples
    while looking at this code and you'll get a feel for how this works.

    It's much easier than me explaining it here.

*/

/* Time  Beats: 99.74% */
/* Space Beats: 15.91% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Neat {
public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        ListNode* dummy = new ListNode(0, head);
        ListNode* group_prev = dummy;

        for(;;)
        {
            ListNode* kth = get_kth(group_prev, k);

            if (!kth)
                break;
            ListNode* group_next = kth->next;

            /*** Reverse Linked List ***/
            ListNode* prev = kth->next;
            ListNode* curr = group_prev->next;

            while (curr != group_next)
            {
                ListNode* next = curr->next;

                curr->next = prev;
                prev = curr;
                curr = next;
            }

            /* Crucial part */
            ListNode* tmp = group_prev->next;
            group_prev->next = kth;
            group_prev = tmp;

        }

        return dummy->next;
    }

private:
    ListNode* get_kth(ListNode* group_prev, int k)
    {
        ListNode* tmp = group_prev;
        while (tmp && k > 0)
        {
            tmp = tmp->next;
            k--;
        }

        return tmp;
    }
};


int
main()
{
    Solution      sol;
    Solution_Neat sol_neat;

    /* Example 1 */
    // struct ListNode five (5);
    // struct ListNode four (4, &five);
    // struct ListNode three(3, &four);
    // struct ListNode two  (2, &three);
    // struct ListNode one  (1, &two);

    // struct ListNode* head = &one;
    // int k = 2;


    /* Example 2 */
    // struct ListNode five (5);
    // struct ListNode four (4, &five);
    // struct ListNode three(3, &four);
    // struct ListNode two  (2, &three);
    // struct ListNode one  (1, &two);

    // struct ListNode* head = &one;
    // int k = 3;


    /* Example 3 */
    // struct ListNode nine (9);
    // struct ListNode eight(8, &nine);
    // struct ListNode seven(7, &eight);
    // struct ListNode six  (6, &seven);
    // struct ListNode five (5, &six);
    // struct ListNode four (4, &five);
    // struct ListNode three(3, &four);
    // struct ListNode two  (2, &three);
    // struct ListNode one  (1, &two);

    // struct ListNode* head = &one;
    // int k = 3;


    /* Example 4 */
    struct ListNode eleven(11);
    struct ListNode ten   (10, &eleven);
    struct ListNode nine  (9,  &ten);
    struct ListNode eight (8,  &nine);
    struct ListNode seven (7,  &eight);
    struct ListNode six   (6,  &seven);
    struct ListNode five  (5,  &six);
    struct ListNode four  (4,  &five);
    struct ListNode three (3,  &four);
    struct ListNode two   (2,  &three);
    struct ListNode one   (1,  &two);

    struct ListNode* head = &one;
    int k = 3;


    /* Example 5 */
    // struct ListNode eleven(11);
    // struct ListNode ten   (10, &eleven);
    // struct ListNode nine  (9,  &ten);
    // struct ListNode eight (8,  &nine);
    // struct ListNode seven (7,  &eight);
    // struct ListNode six   (6,  &seven);
    // struct ListNode five  (5,  &six);
    // struct ListNode four  (4,  &five);
    // struct ListNode three (3,  &four);
    // struct ListNode two   (2,  &three);
    // struct ListNode one   (1,  &two);

    // struct ListNode* head = &one;
    // int k = 2;


    /* Example 6 */
    // struct ListNode eleven(11);
    // struct ListNode ten   (10, &eleven);
    // struct ListNode nine  (9,  &ten);
    // struct ListNode eight (8,  &nine);
    // struct ListNode seven (7,  &eight);
    // struct ListNode six   (6,  &seven);
    // struct ListNode five  (5,  &six);
    // struct ListNode four  (4,  &five);
    // struct ListNode three (3,  &four);
    // struct ListNode two   (2,  &three);
    // struct ListNode one   (1,  &two);

    // struct ListNode* head = &one;
    // int k = 1;


    /* Example 7 */
    // struct ListNode* head = nullptr;
    // int k = 3;



    std::cout << "\n\t================================";
    std::cout << "\n\t=== REVERSE NODES IN K-GROUP ===";
    std::cout << "\n\t================================\n\n";


    /* Write Input */
    std::cout << "\n\tOriginal List:";
    print_list(head);


    /* Solution */
    std::cout << "\n\t\t*** Reversing Nodes in K-Group (k = " << k << ") ***\n\n";
    // head = sol.reverseKGroup(head, k);
    head = sol_neat.reverseKGroup(head, k);


    /* Write Output */
    std::cout << "\n\tModified List:";
    print_list(head);

    return 0;
}
