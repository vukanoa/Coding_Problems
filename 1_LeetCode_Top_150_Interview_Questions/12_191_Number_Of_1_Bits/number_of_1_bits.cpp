#include <iostream>

/*
	============
	=== EASY ===
	============

	===========================
	191) Number Of 1 Bits
	===========================

	============
	Description:
	============

	Write a function that takes the binary representation of an unsigned
	integer and returns the number of '1' bits it has (also known as the
	Hamming weight)

	Follow up: If this function is called many times, how would you optimize
	it?

	========================================
	FUNCTION: int hammingWeight(uint32_t n);
	========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 00000000000000000000000000001011
	Output: 3
	Explanation: The input binary string
	00000000000000000000000000001011 has a total of three '1' bits.

	--- Example 2 ---
	Input: n = 00000000000000000000000010000000
	Output: 1
	Explanation: The input binary string
	00000000000000000000000010000000 has a total of one '1' bit.

	--- Example 3 ---
	Input: n = 11111111111111111111111111111101
	Output: 31
	Explanation: The input binary string
	11111111111111111111111111111101 has a total of thirty one '1' bits.

	*** Constraints ***
	The input must be a binary string of length 32.

*/




/*
	------------
	--- IDEA ---
	------------

	Self-Explanaotry. Just look at the code.
	
*/

/* Time  Beats:  100% */
/* Space Beats: 74.56% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int num = 0;

        for (int i = 0; i < 32; i++)
        {
            num += n % 2 ? 1 : 0;
            n >>= 1;
        }

        return num;
    }
};
