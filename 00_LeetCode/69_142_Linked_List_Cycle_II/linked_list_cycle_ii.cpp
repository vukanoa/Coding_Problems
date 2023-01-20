#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	142) Linked List Cycle II
	===========================

	============
	Description:
	============

	Given the "head" of a linked list, return the code where teh cycle begins.
	If there is no cycle, return null.

	There is a cycle in a linked list if there is some node in the list that
	can be reached again by continuously following the "next" pointer.
	Internally, "pos" is used to denote the index of the node that tail's
	"next" pointer is connected to(0-indexed). It is -1 if there is no cycle.

	Note that "pos" is not passed as a parameter.

	=====
	Node: Do not modify the linked list.
	=====

	================================================
	FUNCTION: ListNode *detectCycle(ListNode *head);
	================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  head = [3, 2, 0, -4], pos = 1
	Output: tail connects to node index 1
	Explanation: There is a cycle in the linked list, where tail connects to
	the second node.

	--- Example 2 ---
	Input:  head = [1, 2], pos = 0
	Output: tail connects to node index 0
	Explanation: There is a cycle in the linked list, where tail connects to
	the first node.

	--- Example 3 ---
	Input: head = [1], pos = -1
	Output: no cycle

	*** Constraints ***
	The number of the nodes in the list is in the range [0, 10^4]
	-10^5 <= Node.val <= 10^5
	pos is -1 or a valid index in the linked-list.

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


/*
	------------
	--- IDEA ---
	------------

	An astute reader may wonder if "fast" might 'hop over' "slow" completely,
	without ever colliding. That is NOT possible.

	Suppose that "fast" did hope over "slow", such that:
		slow is at spot "i"
		fast is at spot "i + 1"

	In the previous step:
		slow would be at spot "i - 1"
		fast would be at spot "(i + 1) - 2" => "i - 1"

	That is, they would have collided.


	When do they Collide?
	Let's assume that the linked list has a "non-looped" part of size k.

	If we apply our algorithm from part 1, when will "fast" and "slow" collide?

	We know that for every "p" steps that "slow" takes, "fast" has taken "2p"
	steps. Therefore, when "slow" enters the looped portion after "k" steps,
	"fast" has taken "2k" steps total and must be "2k - k" steps, or "k" steps,
	into the looped portion. Since "k" might be much larger than the loop
	length, we should actually write this as mod(k, LOOP_SIZE) steps, which we
	will denote as K.

	At each subsequent step, "fast" and "slow" get either one step farther away
	or one step closer, depending on your perspective. That is, because we are
	in a circle, when A moves "q" steps away from B, it is also moving "q"
	steps closer to B.

	So now we know the following facts:
		1. "slow" is 0 steps into the loop
		2. "fast" is K steps into the loop
		3. "slow" is K steps behind "fast"
		4. "fast" is LOOP_SIZE - k steps behind "slow"
		5. "fast" catches up to "slow" at a rate of 1 step per unit of time.

	So, when do they meet? Well, if "fast" is LOOP_SIZE - K steps behind
	"slow", and "fast" catches up at a rate of 1 step per unit of time, then
	they meet after LOOP_SIZE - K steps.
	At this point they will be K steps before the head of the loop. Let's call
	this point Collision Spot.

     "slow" and "fast" will meet here --
                                       |
                                       v
	X -> X -> X -> X -> X -> X -> X -> X -> X -> X -> X
                   ^                                  |
                   |                                  |
                   ------------------------------------

	(Another representation)

	X -> X -> X -> X  ->  X  ->   X
                   ^              |
                   |              v
                   X              X
                   ^              |
                   |              v
                   X  <-  X  <-   X
                          ^
                          |
                          -------------
                                       |
                                       |
     "slow" and "fast" will meet here --


	How Do You Find The Start of the Loop?
	We now know that CollisionSpot is K nodes before the start of the loop.
	Because K = mod(k, LOOP_SIZE) (or, in other words, k = K + M * LOOP_SIZE),
	for any integer M), it is also correct to say that it is "k" nodes from the
	loop start. For example, if node N is 2 nodes into a 5 node loop, it is
	also correct to say that it is 7, 12, or even 397 nodes into the loop.

	Therefore, both Collision Spot and "head" are "k" nodes from the start of
	the loop.

	Now, if we keep one pinter at Collision Spot and move the other to "head",
	they will each be "k" nodes from Loop Start. Moving the two pointers at the
	same speed will cause them to collide again - this time after "k" steps, at
	which point they will boh be at LoopStart. All weh ave to do is return this
	node.

	To summarize:
	We move "fast" twice as fast as "slow". When "slow" enters the loop, after
	"k" nodes, "fast" is k nodes into the loop. This means that "fast" and
	"slow" are LOOP_SIZE - k nodes away from each other.

	Next, if "fast" moves two nodes for each node that "slow" moves, they move
	one nodes closer to each other on each turn. Therefore, they will meet
	after LOOP_SIZE - k turns. Both will be k nodes from the front of the loop.

	The head of the linked list is also k nodes from the front of the loop. So,
	if we keep one pointer where it is, and move theo ther points to the "head"
		of the linked list, then they will meet at the front of the loop.

	Algorithm:
		1. Create two pointers: "fast" and "slow".
		2. Move "fast" at a rate of 2 steps and "slow" at a rate of 1 step.
		3. When they collide, move "slow" to "head". Keep "fast" where it is.
		4. move "slow" and "fast" at a rate of one step. Return the new
		   collision point.

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	ListNode *detectCycle(ListNode *head)
	{
		struct ListNode* slow = head;
		struct ListNode* fast = head;

		while (fast != NULL && fast->next != NULL)
		{
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast)
				break;
		}

		if (fast == NULL || fast->next == NULL)
			return NULL;

		slow = head;
		while (slow != fast)
		{
			slow = slow->next;
			fast = fast->next;
		}

		return slow;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	/*
		3 -> 2 -> 0 -> -4
		^---------------|
	*/
	// struct ListNode minus_four(-4);
	// struct ListNode zero(0);
	// struct ListNode two(2);
	// struct ListNode three(3);
	// minus_four.next = &three;
	// zero.next       = &minus_four;
	// two.next        = &zero;
	// three.next      = &two;
	// struct ListNode* head = &minus_four;



	/* Example 2 */
	/*
		1 -> 2
		^----|
	*/
	// struct ListNode two(2);
	// struct ListNode one(1);
	// two.next = &one;
	// one.next = &two;
	// struct ListNode* head = &one;



	/* Example 3 */
	/*
		1 -> NULL
	*/
	// struct ListNode one(1);
	// struct ListNode* head = &one;



	/* Example 4 */
	/*
								 -----
								 v   |
		1 -> 2 -> 3 -> 4 -> 5 -> 6   |
								 -----
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &six;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;


	/* Example 5 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		                    ^----|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &five;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;



	/* Example 6 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		               ^---------|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &four;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;

	/* Example 7 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		          ^--------------|
	*/
	struct ListNode six(6);
	struct ListNode five(5);
	struct ListNode four(4);
	struct ListNode three(3);
	struct ListNode two(2);
	struct ListNode one(1);
	six.next   = &three;
	five.next  = &six;
	four.next  = &five;
	three.next = &four;
	two.next   = &three;
	one.next   = &two;
	struct ListNode* head = &one;


	/* Example 8 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		     ^-------------------|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &two;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;


	/* Example 9 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		^------------------------|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &one;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;


	std::cout << "\n\t=========================";
	std::cout << "\n\t=== LINKED LIST CYCLE ===";
	std::cout << "\n\t=========================\n\n";


	/* Solution */
	struct ListNode* cycle = sol.detectCycle(head);

	if (cycle)
		std::cout << "\n\tCycle begins at node: " << cycle->val << "\n\n";
	else
		std::cout << "\n\tThere is NO Cycle in this Linked List!\n\n";

	return 0;

}
