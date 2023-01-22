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


/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(logn) */
class Solution{
public:
	struct ListNode* sortList(struct ListNode* head)
	{
		if (!head || !head->next)
			return head;

		struct ListNode* mid   = mid_node(head);
		struct ListNode* left  = sortList(head);
		struct ListNode* right = sortList(mid);

		return merge(left, right);
	}

	struct ListNode* merge(struct ListNode* list1, struct ListNode* list2)
	{
		struct ListNode dummy_head(0);
		struct ListNode* ptr = &dummy_head;

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

	struct ListNode* mid_node(struct ListNode* head)
	{
		struct ListNode* slow = head;
        struct ListNode* fast = head->next;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        struct ListNode* mid = slow->next;
        slow->next = nullptr;

        return mid;
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
	Solution sol;

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
	head = sol.sortList(head);

	/* After */
	std::cout << "\n\tAfter:";
	print_list(head);

	return 0;
}
