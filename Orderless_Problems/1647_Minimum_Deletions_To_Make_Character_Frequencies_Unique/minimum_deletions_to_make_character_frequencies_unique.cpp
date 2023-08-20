#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	============================================================
	1647) Minimum Deletions To Make Character Frequencies Unique
	============================================================

	============
	Description:
	============

	A string s is called good if there are no two different characters in s
	that have the same frequency.

	Given a string s, return the minimum number of characters you need to
	delete to make s good.

	The frequency of a character in a string is the number of times it appears
	in the string. For example, in the string "aab", the frequency of 'a' is 2,
	while the frequency of 'b' is 1.


	=====================================
	FUNCTION: int minDeletions(string s);
	=====================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "aab"
	Output: 0
	Explanation: s is already good.

	--- Example 2 ---
	Input: s = "aaabbbcc"
	Output: 2
	Explanation: You can delete two 'b's resulting in the good string "aaabcc".
	Another way it to delete one 'b' and one 'c' resulting in the good string
	"aaabbc".

	--- Example 3 ---
	Input: s = "ceabaacb"
	Output: 2
	Explanation: You can delete both 'c's resulting in the good string "eabaab"
	Note that we only care about characters that are still in the string at the
	end (i.e. frequency of 0 is ignored).

	*** Constraints ***
	1 <= s.length <= 105
	s contains only lowercase English letters.

*/


/* Time  Beats: 80.98% */
/* Space Beats: 52.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int minDeletions(std::string s)
	{
		std::unordered_map<int,int> map_freq;
		std::vector<int> vec(26,0);

		for(const char& c : s)
			vec[c - 'a']++;

		for(int i = 0; i < 26; i++)
			map_freq[vec[i]]++;

		map_freq[0] = 0;
		int deletions = 0;

		for(int i = 0; i < 26; i++)
		{
			int freq = vec[i];

			if(map_freq[freq] > 1)
			{                        
				for(int j = freq-1; j >= 0; j--)
				{
					if(j == 0)
						deletions += freq;
					else if(map_freq.count(j) == 0)
					{
						map_freq[j] = 1;
						deletions += freq - j;

						break;
					} 
				}

				map_freq[freq]--;
			}   
		} 

		return deletions;
	}
};
