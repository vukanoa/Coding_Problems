#include <iostream>
#include <vector>
#include <climits>

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


/*
    ------------
    --- IDEA ---
    ------------

    Make a dummy node and set both head and tail to point to it.
    Set "null_cnt" to 0. "null_cnt" will count how many of the lists are now
    pointing to nullptr. We have to use each and every one of nodes in each and
    every one of lists, so until that happens(until null_cnt is less than n),
    do the while loop.

    In the while loop immediately set local variable "min" to INT_MAX and index
    to -1.

    Now iterate through ALL the first nodes in each list and save the lowest
    value in variable "min" and save the index od the list with a lowest
    first node in a variable "index".

    Make tail's next point to that node with the current lowest of all the
    first nodes in lists and make tail point now point to that node.

    And make sure a list that contained that lowest first value now points to
    its next node:
            lists[index] = lists[index]->next;

    If that "next node" is nullptr then null_cnt++.

    Repeat this until every node in every list is processed, that is every
    list points to nullptr.

    Since our head points to dummy node, return head->next. We don't care about
    our dummy node.
*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* Much more Space  efficient than the, divide and conquer, solution below */

/* Time  Beats:  5.40% */
/* Space Beats: 96.36% */

/* Time  Complexity: O(totalNumberOfNodes * k) */
/* Space Complexity: O(1) */
class Solution_Brute {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        int n = lists.size();

        ListNode* dummy_node = new ListNode();
        ListNode* tail = dummy_node;

        std::vector<ListNode*> null_vec(n, nullptr);
        int idx = -1;

        while (lists != null_vec)
        {
            int min = INT_MAX;

            for (int i = 0; i < n; i++)
            {
                if (lists[i] != nullptr && lists[i]->val < min)
                {
                    idx = i;
                    min = lists[i]->val;
                }
            }

            tail->next = lists[idx];
            lists[idx] = lists[idx]->next;

            tail = tail->next;
            tail->next = nullptr;
        }

        return dummy_node->next;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's a kind of Merge Sort Solution.

*/

/* Time  Beats: 31.16% */
/* Space Beats:  8.90% */

/*
    Time  Complexity: O(n * logk)

    Divide and Conquer is used to iterate on the O(n * k) approach of merging
    one by one. For each step, 'n' nodes(all of them) are compared during the
    marge process - O(n).

    At the end of each step, the number of lists that need to be merged has
    been halfed, therefore the number of iterations needed is the number of
    times you can half 'k' until you get to 1, that is "logk"(base 2), so each
    step will be done "logk" times - O(logk)

    Thus the time Complexity is O(n * logk)
*/
/* Space Complexity: O(n) */
class Solution_Divide_And_Conquer {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        // Base cases
        if (lists.empty())
            return nullptr;
        else if (lists.size() == 1)
            return lists[0];

        // Divide and Conquer
        int mid = lists.size() / 2;
        std::vector<ListNode*> left(lists.begin(), lists.begin() + mid);
        std::vector<ListNode*> right(lists.begin() + mid, lists.end());

        ListNode* list1 = mergeKLists(left);
        ListNode* list2 = mergeKLists(right);

        return mergeTwoLists(list1, list2);
    }

private:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        ListNode  dummy(0);
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




/*
    ------------
    --- IDEA ---
    ------------

    This is a much easier to grasp "Divide & Conquer" Implementation.

*/

/* Time  Beats: 91.60% */
/* Space Beats: 38.05% */

/* Time  Complexity: O(n * logk) */
/* Space Complexity: O(n) */
class Solution_Divide_And_Conquer_Neat {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        if (lists.empty())
            return nullptr;

        while (lists.size() > 1)
        {
            std::vector<ListNode*> tmp_merged_lists;

            for (int i = 0; i < lists.size(); i+=2)
            {
                ListNode* list1 = lists[i];
                ListNode* list2 = i+1 < lists.size() ? lists[i+1] : nullptr;

                tmp_merged_lists.push_back(mergeTwoLists(list1, list2));
            }

            lists.clear();
            lists = tmp_merged_lists;
        }

        return lists[0];
    }

private:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        ListNode  dummy(0);
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




/*
    ------------
    --- IDEA ---
    ------------

    My own way, very similar to the one above. Wanted to have both of them here
    since some may find one easier to read.

*/

/* Time  Beats: 77.07% */
/* Space Beats: 51.62% */

/* Time  Complexity: O(n * logk) */
/* Space Complexity: O(n) */
class Solution_My_Way {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        if (lists.empty())
            return nullptr;
        
        while (lists.size() != 1)
        {
            std::vector<ListNode*> tmp;

            while (!lists.empty())
            {
                ListNode* list1 = lists.back();
                lists.pop_back();

                ListNode* list2;
                if (!lists.empty())
                {
                    list2 = lists.back();
                    lists.pop_back();
                }
                else
                    list2 = nullptr;
                
                ListNode* merged = mergeTwoLists(list1, list2);
                tmp.push_back(merged);
            }

            lists = tmp;
        }

        return lists.back();
    }

private:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        ListNode  dummy(0);
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
print_list(ListNode* head)
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

    std::cout << "]";
}


int
main()
{
    Solution_Brute                    sol_brute;
    Solution_Divide_And_Conquer       sol_divide_and_conquer;
    Solution_Divide_And_Conquer_Neat  sol_divide_and_conquer_neat;
    Solution_My_Way                   sol_my_way;

    /* Example 1 */
    ListNode five1(5);
    ListNode four1(4, &five1);
    ListNode one1 (1, &four1);

    ListNode four2 (4);
    ListNode three2(3, &four2);
    ListNode one2  (1, &three2);

    ListNode two3(2);
    ListNode six3(1, &two3);

    std::vector<struct ListNode*> lists;
    lists.push_back(&one1);
    lists.push_back(&one2);
    lists.push_back(&six3);


    /* Example 2 */
    // std::vector<struct ListNode*> lists;

    std::cout << "\n\t============================";
    std::cout << "\n\t=== MERGE K SORTED LISTS ===";
    std::cout << "\n\t============================\n\n";

    /* Write Input */
    std::cout << "\n\tOriginal Lists:";
    for (const auto& x : lists)
        print_list(x);

    /* Solution */
    // struct ListNode* head = sol_brute.mergeKLists(lists);
    // struct ListNode* head = sol_divide_and_conquer.mergeKLists(lists);
    // struct ListNode* head = sol_divide_and_conquer_neat.mergeKLists(lists);
    ListNode* head = sol_my_way.mergeKLists(lists);

    /* Write Output */
    std::cout << "\n\n\n\tMerged k Sorted Lists:";
    print_list(head);
    std::cout << "\n\n";

    return 0;
}
