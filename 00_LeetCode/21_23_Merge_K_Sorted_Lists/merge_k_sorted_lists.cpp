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


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


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

			tail->next = lists[index];
			tail = tail->next;

			lists[index] = lists[index]->next;

			if (lists[index] == nullptr)
				null_cnt++;
		}

		return head->next;
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

	std::cout << "\n\tOriginal Lists:";
	for (const auto& x : lists)
		print_list(x);

	struct ListNode* head = sol.mergeKLists(lists);

	std::cout << "\n\n\n\tMerged k Sorted Lists:";
	print_list(head);
	std::cout << "\n\n";

	return 0;
}
