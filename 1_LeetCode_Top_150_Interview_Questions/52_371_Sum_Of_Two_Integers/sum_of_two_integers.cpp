#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	371) Sum Of Two Integers
	===========================

	============
	Description:
	============

	Given two integers a and b, return the sum of the two integers without
	using the operators + and -.	

	===================================
	FUNCTION: int getSum(int a, int b);
	===================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: a = 1, b = 2
	Output: 3

	--- Example 2 ---
	Input: a = 2, b = 3
	Output: 5

	*** Constraints ***
	-1000 <= a, b <= 1000
*/


/*
	------------
	--- IDEA ---
	------------

	1)
		a + b
	
	2)
		2^a * 2^b => log2(2^a * 2^b) => log2(2^(a + b)) => (a + b) * log2(2) => (a + b) * 1 => (a + b)

*/

/* Time  Beats:   100% */
/* Space Beats: 12.66% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution{
public:
	int getSum(int a, int b)
	{
		return std::log(std::pow(2, a) * std::pow(2, b)) / std::log(2);
	}
};




/*
	------------
	--- IDEA ---
	------------

	Since we are not allowed to use a + or - sign, we must get creative.

	Summing 1 and 2, in binary looks like this:
	  0001 = 1
	+ 0010 = 2
	------
	  0011 = 3
	
	So which bitwise operation could we do on these two binary values so that
	we get 3? It's XOR.

	However, there's a caveat. Consider this example:

	5 + 4:

	  0101 = 5
	+ 0100 = 4
	------
	  1001 - 9
	
	If we were to use XOR only, we would get 1(i.e 0001 in binary).

	So, the problem is - What are we supposed to do when both bits are 1?
	We have to put 0 as a result of those two bits, but we have to, somehow,
	have a carry that indicates that one bit get carried further.

	So how are we going to do that?

	If we have two 0's, we definitely don't have a carry.
	If we have a single 0, we don't have a carry either.

	However, if we have two 1's, this is the only case in which we're going to
	have a carry.

	So - How do we know if we have two 1's? It's bitwise "AND" operation.
	
	If a & b is one, then that means that we have a carry. However, that 1 has
	to be added with its left bit.

	Example:
	   0011
	+  1010
	-------
	   1101
	
	2nd from the right, we have two 1's. However, we have to add that carry
	with the 3rd pair(from the right) bits.

	So how can we ensure that?
	    (a & b) << 1
	
	This means that we're going to catch every two 1's and shift the whole
	number by one and then we're going to XOR that new number with previously
	XOR-ed value, and so on.

	We're going to have a loop.

	Let's do one example. Note that when we're doing these logical bitwise
	operators - We don't have to do them one by one.
	We can do them on entirety of 'a' and 'b' that we're given.

	Example:
	   1001 = 9
	+  1011 = 11
	-------
	  10100 = 20


	If we, firstly, XOR these two number(9 and 11), we get:
	    1001 = 9
	XOR 1011 = 11
	--------
	    0010 = 2
	
	9 + 11 is definitely not 2, what are we missing? We didn't do the AND
	operation.
	
	    1001 = 9
	AND 1011 = 11
	--------
	    1001 = 9
	<<
	--------
	   10010 = 18
	
	With "AND" we'll get all the carry bits, but we have to Shift those bits
	to the left because that's how the binary addition works.

	And now we have to add this new AND-end and Left Shifted number with the
	previously XOR-ed number.

	Again, we cannot use a '+' sign, so we have to do the same thing which is
	XOR.

	But even if we do XOR again, it won't take care of the further carry bits,
	thus we have to keep repeating this.

	We'll have a loop.

	So simulation of (9 + 11):
	     1001
	XOR  1011
	---------
	     0010
	
	     1001
	AND  1011
	---------
	     1001
	
	1001 << 1 --> 10010


	Now repeat these steps:

	a ^ b        =  0010
	(a & b) << 1 = 10010

	     0010
	XOR 10010
	---------
	    10000
	
	     0010
	AND 10010
	---------
	    00010
	
	00010 << 1 --> 00100

	a ^ b        = 10000
	(a & b) << 1 = 00100


	Repeat again:

	    10000
	XOR 00100
	---------
	    10100 = 20(Our desired result)
	
	    10000
	AND 00100
	---------
	    00000
	
	00000 << 1 --> 00000

	Since ((a & b) << 1) == 0, that means that the previous XOR did the job and
	that we should return the result;

*/

/* Time  Beats:   100% */
/* Space Beats: 15.19% */

/* Time  Complexity: O(1) since both 'a' and 'b' are [-1000, 1000] */
/* Space Complexity: O(1) */
class Solution{
public:
	int getSum(int a, int b)
	{
		while (b != 0)
		{
			int tmp = (a & b) << 1;
			a ^= a ^ b;
			b = tmp;
		}

		return a;
	}
};
