#include <iostream>
#include <queue>

/*
	============
	=== EASY ===
	============

	===========================
	234) Palindrome Linked List
	===========================

	============
	Description:
	============

	Given the "head" of a singly linked list, return "true" if it is a
	palindrome or "false" otherwise.

	Follow up: Could you do it in O(n) time and O(1) space?

	============================================
	FUNCTION: bool isPalindrome(ListNode* head);
	============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  head = [1, 2, 2, 1]
	Output: true

	--- Example 2 ---
	Input:  head = [1, 2]
	Output: false

	*** Constraints ***
	The number of node sin the list is in the range [1, 10^5]
	0 <= Node.val <= 9

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


/*
	Table of Contents:
	1. Solution                   [Time: O(n), Space: O(n)]
	2. Solution_Without_Modifying [Time: O(n), Space: O(n)]
	3. Solution_Recursive         [Time: O(n), Space: O(n)]
	4. Solution_Follow_Up         [Time: O(n), Space: O(1)]
	5. Solution_Follow_Up_2       [Time: O(n), Space: O(1)]
*/


/*
	------------
	--- IDEA ---
	------------

	Push elements in queue while reversing the linked list.

	Afterwards check if the queue from 0 to n-1 have the same values as
	the reversed linked list.

	===========================================================================
	Note: In the second part of this implementation, I could just iterate
	through the reverse linked list, however that would leave the Original
	Linked list transformed, which is not a good programming practice. Thus I'm
	going to write a Solution both with and without that part and compare their
	Time and Space Beats records.

	This one is leaving the Original list modified.
	===========================================================================

	(Or just push elements in vector without reversing the linked list and then
	check if the vector from n-1 to n have the same values as the original
	linked list)

*/

/* Time  Beats: 98.50% */
/* Space Beats: 70.5% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	bool isPalindrome(ListNode* head)
	{
		if (head->next == nullptr)
			return true;

		std::queue<int> queue;

		ListNode* prev = nullptr;
		ListNode* curr = head;
		ListNode* next = head;

		while (curr != nullptr)
		{
			queue.push(curr->val);
			next = curr->next;

			curr->next = prev;
			prev = curr;
			curr = next;
		}

		head = prev;

		while (head != nullptr)
		{
			if (head->val == queue.front())
			{
				queue.pop();
				head = head->next;
			}
			else
				return false;
		}

		return true;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Without the modification of the Original List, but virtually the same
	Solution as the one above.
	
*/

/* Time  Beats: 86.61% */
/* Space Beats: 65.51% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Without_Modifying {
public:
	bool isPalindrome(ListNode* head)
	{
		if (head->next == nullptr)
			return true;

		std::queue<int> queue;

		ListNode* prev = nullptr;
		ListNode* curr = head;
		ListNode* next = head;

		while (curr != nullptr)
		{
			queue.push(curr->val);
			next = curr->next;

			curr->next = prev;
			prev = curr;
			curr = next;
		}

		head = prev;

		prev = nullptr;
		curr = head;
		next = head;

		/*
			Check if the List is a palindrome while reversing the list in its
			Original state
		*/
		while (curr != nullptr)
		{
			if (curr->val == queue.front())
			{
				queue.pop();

				next = curr->next;

				curr->next = prev;
				prev = curr;
				curr = next;
			}
			else
				return false;
		}

		return true;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Much more inneficient than the previous, above, Solution.

	It's just a recursive approach.
	
*/

/* Time  Beats: 45.25% */
/* Space Beats: 37.73% */

/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(n)
	It's always O(n) because of the Stack Frame. It needs to get to n before
	it starts to pop.
*/
class Solution_Recursive{
private:
	ListNode* front_pointer;

	bool recursive_check(ListNode* current_node)
	{
		if (current_node != nullptr)
		{
			if (!recursive_check(current_node->next))
				return false;

			if (current_node->val != front_pointer->val)
				return false;

			front_pointer = front_pointer->next;
		}

		return true;
	}

public:
	bool isPalindrome(ListNode* head)
	{
		front_pointer = head;

		return recursive_check(head);
	}
};




/*
	------------
	--- IDEA ---
	------------

	Reverse Second Half In-place

	The ONLY way we can avoid using O(n) extra space is by modifying the input
	in-place.

	The strategy we can use is to reverse the second half of the Linked List
	in-place (modifying the Linked List structure), and then comparing it with
	the first half.
	Afterwards, we should re-reverse the second half and put the list back
	together. While you don't need to restore the list to pass the test cases,
	it is still good programming practice because the function could be a part
	of a bigger program that doesn't want the Linked List broken.

	Algorithm
	Steps are:
		1. Find the end of the first half (Two pointers technique)
		2. Reverse the second half
		3. Determine whether or not there is a palindrome
		4. Restore the list
		5. Return the result


	Note:
	This Approach doesn't use lambda function and uses a lot of functions
	generally, therefore it's slower than the 2nd implementation below.

*/

/* Time  Beats: 25.20% */
/* Space Beats: 57.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Follow_Up {
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

	ListNode* reverse_list(ListNode* head)
	{
		ListNode* prev = nullptr;
		ListNode* curr = head;
		ListNode* next = head;

		while (curr != nullptr)
		{
			next = curr->next;

			curr->next = prev;
			prev = curr;
			curr = next;
		}

		return prev;
	}

	bool check_palindrome(ListNode* first, ListNode* second)
	{
		while (second != nullptr)
		{
			if (first->val != second->val)
				return false;

			first  = first->next;
			second = second->next;
		}

		return true;
	}

public:
	bool isPalindrome(ListNode* head)
	{

		ListNode* first_list_tail  = middle(head);
		ListNode* second_list_head = first_list_tail->next;

		// Unlink from the 2nd Half
		first_list_tail->next = nullptr;

		// Reverse 2nd List
		second_list_head = reverse_list(second_list_head);

		// Check if it is a palindrome and store the result
		bool palindrome = check_palindrome(head, second_list_head);

		// Reverse 2nd List again
		second_list_head = reverse_list(second_list_head);

		// Reconstruct the list
		first_list_tail->next = second_list_head;

		return palindrome;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Absolutely equivalent Solution to the one above, but implemented using
	lambda function for reversing the list and no functions for other parts.

	That makes it faster.
	
*/

/* Time  Beats: 56.31% */
/* Space Beats: 67.90% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Follow_Up_2 {
public:
	bool isPalindrome(ListNode* head)
	{
		/* Empty List is considered a palindrome */
		if (head == nullptr)
			return true;

		/* Two Pointers Technique(Tortoise and Hare. Floyd's Algorithmm) */
		/* O(n) */
		ListNode* slow = head;
		ListNode* fast = head->next;

		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}

		ListNode* head_2 = slow->next;

		// Unlink from the 2nd Half
		slow->next = nullptr;


		/* O(n) */
		auto reverse = [&](){

			/* Reverse Linked List */
			ListNode* prev = nullptr;
			ListNode* curr = head_2;
			ListNode* next = head_2;

			while (curr)
			{
				next = curr->next;

				curr->next = prev;
				prev = curr;
				curr = next;
			}

			return prev;
		};

		/* O(n) */
		head_2 = reverse();

		/* Check if two Linked Lists are the same */
		/* O(n) */
		ListNode* tmp_1 = head;
		ListNode* tmp_2 = head_2;

		while (tmp_1 && tmp_2)
		{
			if (tmp_1->val != tmp_2->val)
				return false;

			tmp_1 = tmp_1->next;
			tmp_2 = tmp_2->next;
		}


		/* ========================================================= */
		/* === Return Linked List in its Original form and order === */
		/* ========================================================= */

		/* Find last in First List */
		tmp_1 = head;
		while (tmp_1->next != nullptr)
			tmp_1 = tmp_1->next;
		
		/* O(n) */
		head_2 = reverse();

		// Link with 2nd Half so it forms the Original list
		tmp_1->next = head_2;
		
		return true;
	}
};
	

void
print_list(struct ListNode* head)
{
	std::cout << "\n\t\t";

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

	std::cout << "\n\n";
}


int
main()
{
	Solution                   sol;
	Solution_Without_Modifying sol_wo_mod;
	Solution_Recursive         sol_rec;
	Solution_Follow_Up         sol_follow_up;
	Solution_Follow_Up_2       sol_follow_up_2;


	/* Example 1 */
	// ListNode one_1(1);
	// ListNode two_1(2);
	// ListNode two_2(2);
	// ListNode one_2(1);

	// one_1.next = &two_1;
	// two_1.next = &two_2;
	// two_2.next = &one_2;

	// ListNode* head = &one_1;




	/* Example 2 */
	// ListNode one(1);
	// ListNode two(2);

	// one.next = &two;

	// ListNode* head = &one;




	/* Example 3 */
	ListNode one_1(1);
	ListNode two_1(2);
	ListNode three(3);
	ListNode two_2(2);
	ListNode one_2(1);

	one_1.next = &two_1;
	two_1.next = &three;
	three.next = &two_2;
	two_2.next = &one_2;

	ListNode* head = &one_1;




	std::cout << "\n\t==============================";
	std::cout << "\n\t=== PALINDROME LINKED LIST ===";
	std::cout << "\n\t==============================\n\n";


	/* Write Input */
	std::cout << "\tList:";
	print_list(head);

	/* Solution */
	// if (sol.isPalindrome(head))
	// if (sol_wo_mod.isPalindrome(head))
	// if (sol_rec.isPalindrome(head))
	// if (sol_follow_up.isPalindrome(head))
	if (sol_follow_up_2.isPalindrome(head))
		std::cout << "\n\tIt is INDEED a Palindrome!\n\n";
	else
		std::cout << "\n\tIt is NOT a Palindrome!\n\n";


	return 0;
}
