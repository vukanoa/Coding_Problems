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
class Solution{
public:
	struct ListNode* mergeKLists(std::vector<struct ListNode*>& lists)
	{
		struct ListNode dummy;

		struct ListNode* head = &dummy;
		struct ListNode* tail = &dummy;

		int n = lists.size();
		int null_cnt = 0;

		while (null_cnt < n)
		{
			int min = INT_MAX;
			int index = -1;
			for (int i = 0; i < n; i++)
			{
				if (lists[i] != nullptr && lists[i]->val < min)
				{
					min = lists[i]->val;
					index = i;
				}
			}

			if (index < 0)
				break;

			tail->next = lists[index];
			tail = tail->next;

			lists[index] = lists[index]->next;

			if (lists[index] == nullptr)
				null_cnt++;
		}

		return head->next;
	}
};



/* More Time efficient than the above solution */

/* Time  Beats: 31.16% */
/* Space Beats:  8.90% */
class Solution_Divide_And_Conquer{
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

        ListNode* l1 = mergeKLists(left);
        ListNode* l2 = mergeKLists(right);

        return mergeTwoLists(l1, l2);
    }

private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 && l2)
        {
            if (l1->val < l2->val)
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

        if (l1)
            tail->next = l1;

        if (l2)
            tail->next = l2;

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
		head = head->next;
	}

	std::cout << "]";
}



int
main()
{
	Solution sol;
	Solution_Divide_And_Conquer sol_divide_and_conquer;

	/* Example 1 */
	struct ListNode five1(5);
	struct ListNode four1(4, &five1);
	struct ListNode one1 (1, &four1);

	struct ListNode four2 (4);
	struct ListNode three2(3, &four2);
	struct ListNode one2  (1, &three2);

	struct ListNode two3(2);
	struct ListNode six3(1, &two3);

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
	// struct ListNode* head = sol.mergeKLists(lists);
	struct ListNode* head = sol_divide_and_conquer.mergeKLists(lists);

	/* Write Output */
	std::cout << "\n\n\n\tMerged k Sorted Lists:";
	print_list(head);
	std::cout << "\n\n";

	return 0;
}
