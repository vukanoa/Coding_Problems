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

class Solution{
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
	Solution sol;

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

	std::cout << "\n\tList1:";
	print_list(list1);

	std::cout << "\n\tList2:";
	print_list(list2);

	// Solution
	ListNode* head = sol.mergeTwoLists(list1, list2);

	std::cout << "\n\tMerged Lists: List1 & List2:";
	print_list(head);

	return 0;
}
