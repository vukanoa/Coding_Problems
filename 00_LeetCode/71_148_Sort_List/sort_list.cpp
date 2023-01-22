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
class Solution_worse{
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


/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution{
public:
	ListNode* tail = new ListNode();
	ListNode* next_sublist = new ListNode();

	ListNode* sortList(ListNode* head)
	{
		if (!head || !head->next)
			return head;

		int n = get_count(head);

		ListNode* start = head;
		ListNode dummy_head(0);

		for (int size = 1; size < n; size = size * 2)
		{
			tail = &dummy_head;

			while (start)
			{
				if (!start->next)
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

	int get_count(ListNode* head)
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
