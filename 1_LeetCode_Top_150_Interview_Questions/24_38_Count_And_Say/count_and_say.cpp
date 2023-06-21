#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	38) Count And Say
	===========================

	============
	Description:
	============

	The count-and-say sequence is a sequence of digit strings defined by the
	recursive formula:

	countAndSay(1) = "1"
	countAndSay(n) is the way you would "say" the digit string from
	countAndSay(n-1), which is then converted into a different digit string.

	To determine how you "say" a digit string, split it into the minimal number
	of substrings such that each substring contains exactly one unique digit.
	Then for each substring, say the number of digits, then say the digit.
	Finally, concatenate every said digit.

	For example, the saying and conversion for digit string "3322251":

					"3322251"
		two 3's, three 2's, one 5, and one 1

			2 3 + 3 2 + 1 5 + 1 1

					"23321511"


	Given a positive integer n, return the nth term of the count-and-say
	sequence.

	====================================
	FUNCTION: string countAndSay(int n);
	====================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 1
	Output: "1"
	Explanation: This is the base case.	

	--- Example 2 ---
	Input: n = 4
	Output: "1211"
	Explanation:
	countAndSay(1) = "1"
	countAndSay(2) = say "1" = one 1 = "11"
	countAndSay(3) = say "11" = two 1's = "21"
	countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"	

	*** Constraints ***
	1 <= n <= 30	

*/


/*
	------------
	--- IDEA ---
	------------

	Go up the stack until n is 1. Once we have that, we return "1".

	Next, we need to iterate through the string and "say" those numbers.
	As it's said in the description of a problem:

	~~~~~~~~~~~~
	To determine how you "say" a digit string, split it into the minimal number
	of substrings such that each substring contains exactly one unique digit.
	Then for each substring, say the number of digits, then say the digit.
	Finally, concatenate every said digit.
	~~~~~~~~~~~~

	So how are we going to do that?

	We'll make a for loop that starts on index 1. Why 1? Because that way we
	can immediately see if the first one is a unique number. How?
	Just ask if the previous, meaning say[i - 1] is different than say[i].

	If it is, then we need to say how much of those numbers were before this
	current new number. How can we do that?

	We can make a use of a variable called "index_last_unique" which does what
	it says: It keeps track of the index of the last unique number until this
	point.

	For example:

	                  i
	say = " 3 3 3 3 3 4 4 1 5"
	        0 1 2 3 4 5 6 7 8
	
	While say[i] == say[i - 1]
		continue
	
	...
	
	                  i
	say = " 3 3 3 3 3 4 4 1 5"
	        0 1 2 3 4 5 6 7 8


	say[i] != say[i - 1], but how many 3's were there?

	Let's use our variable "index_last_unique". It's 0 at the beginning. Why?
	Because that's the index of the last unique element before the for loop.

	So now we have to "say": "five 3's", right?

	That means we, first, have to add "5" and then "3".

	So what does "5" represents? It represents the number of 4's. How can we
	get that information?

	Let's user our variable "index_last_unique".

	Current index "i" minus "index_last_unique".

	In this case:
		i - index_last_unique ===> 5 - 0 = 5
	
	Then we append that to our string "result" which we will return at the very
	end of the funciton.

	Next, we need to add the number 3 itself. How can we obtain that
	information?

	Well, since the number we're currently at is different than the previous,
	previous elements is what we need and that is at index "i - 1".

	So we just append say[i - 1], and we've ended up with this:
		"53"
	
	But, now there's a VERY important thing we MUST do.
	We MUST update our "index_last_unique" to our current index.

	Why?
	So that we can do this "thing" again for other unique numbers.

	Let's continue with this example:

	index_last_unique = 5

	                  i
	say = " 3 3 3 3 3 4 4 1 5"
	        0 1 2 3 4 5 6 7 8

	                    i
	say = " 3 3 3 3 3 4 4 1 5"
	        0 1 2 3 4 5 6 7 8

	                      i
	say = " 3 3 3 3 3 4 4 1 5"
	        0 1 2 3 4 5 6 7 8

	Now say[i] != say[i - 1], so we need to say "two 4's", right?

	First we have to "count" how many of the previously unique numbers are
	there.

	Remember how we did it?

	i - index_last_unique ===> 7 - 5 = 2

	So we ad that "two" part.

	And now we need to add that previously unique number, which was 4 and we
	get that information from say[i - 1].

	And now we have:
		"5324"
	
	If we failed to update the "index_last_unique" we wouldn't get the right
	number of 4's. We would've get: 7 - 0 = 7, which is not true.

	That's why it's IMPORTANT to update the "index_last_unique" variable.

	At the very end we do the same concatenation, but ouside of the for loop.
	why?

	Because to concatenate we have to find that the current element is
	different than the previous. However, we cannot do that for the very last
	unique element, since there is no "next to check the previous from".

	Thus, we have to do it once again once we finish with the for loop.
	
*/

/* Time  Beats: 90.39% */
/* Space Beats: 74.70% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	std::string countAndSay(int n)
	{
		if (n == 1)
			return "1";

		std::string say = countAndSay(n - 1);
		std::string result = "";

		int index_last_unique = 0;
		for (int i = 1; i < say.length(); i++)
		{
			if (say[i] != say[i - 1])
			{
				result += std::to_string(i - index_last_unique);
				result += say[i - 1];

				index_last_unique = i; // Update
			}
		}

		result += std::to_string(say.length() - index_last_unique);
		result += say[say.length() - 1]; // Last element of "say"

		return result;
	}
};
