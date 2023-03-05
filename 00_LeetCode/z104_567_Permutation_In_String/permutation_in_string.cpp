#include <iostream>
#include <unordered_map>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	567) Permutation In String
	===========================

	============
	Description:
	============

	Given two strings s1 and s1, return true if s2 contains a permutation of
	s1, or false otherwise.

	In other words, return true if one of s1's premutations is the substring of
	s2.

	====================================================
	FUNCTION: bool checkInclusion(string s1, string s2);
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  s1 = "ab", s2 = "eidbaooo"
	Output: true
	Explanation: s2 contains one permutation of s1 ("ba").

	--- Example 2 ---
	Input:  s1 = "ab", s2 = "eidboaoo"
	Output: false

	*** Constraints ***
	1 <= s1.length, s2.length <= 10^4
	s1 and s2 consist of lowercase English letters

*/


/*
	------------
	--- IDEA ---
	------------

	We make a Hash Map out of string s1.
	Example s1 = "cabc", s2 = "bbcbca"

	Hash Map:
	{ Key : Value }
	|  b  |   1   |
	|  c  |   2   |
	|  a  |   1   |
	|     |       |

	Then Iterate through string s2.
	Check if current character in s2 is present in Hash Map "tmp_map".

	Why are we using both tmp_map and map?
	Because we will be making changes to tmp_map but if we conclude that we
	haven't found the permutation we have to revert it to the original one.
	Thus, we keep "map" as our Original Hash Map.

	If we find that current character exists in tmp_map then enter the
	while loop and count how many consecutive characters are present in
	tmp_map.

	Once we stumble upon a character that has a value of 0 in tmp_map we end
	the while loop.

	Check if count is equal to s1.length(that would mean we have found a
	permutation inside the s2 string). If we did - return true;

	Once we're out of the while loop:
	check if the j > i. Why? Because that would indicate that at least
	one character starting from the index "i" was and is present in tmp_map and
	map.

	If that is the case then we have to set tmp_map back to map(to the Original
	Hash Map).

	In that if statement we also have to check if the character that ended the
	while loop is in the ORIGINAL HASH MAP.
	If it is that indicates that we should start from the i + 1 for a next
	check-up and if it is not then start from that character that ended up our
	while loop since any starting permutation is guaranteed to fail since that
	same character will "cut-off" before it complete.

	Consider this example:

		s1 = "dac"
		s2 = "ddcda"

	Once we start from i = 1 and enter the while loop, we will remove first 'd'
	and first 'c', but second 'd' will end the while loop.
	Now if we immediately set i to j(j at this point is at index 3) then
	we at the very end of the function would return false which is not correct
	since "cda" starting from index i = 2 would return true.

	So to overcome cases like these, we have to do this if-else "fine-tuning".

	If j == 1
		i++; // Just start over from the very next character.

*/


/* Time  Beats: 5.3%   */
/* Space Beats: 37.94% */
/*	Time  Complexity: O(~N^2, but not always) */
/*
	Space Complexity: O(M)
	M is s1.length
	N is s2.length
*/
class Solution {
public:
	bool checkInclusion(std::string s1, std::string s2)
	{
		std::unordered_map<char, int> map;
		std::unordered_map<char, int> tmp_map;

		// Fill the Hash Map
		for (auto& x : s1)
		    map[x]++;

		tmp_map = map;

		int count = 0;
		for (int i = 0; i < s2.size();)
		{
		    int j = i;
		    while (j < s2.size() && tmp_map[s2[j]] != 0)
		    {
		        tmp_map[s2[j]]--;
		        count++;

		        j++;
		    }

		    if (count == s1.length())
		        return true;

		    count = 0;

		    if (j > i)
		    {
		        tmp_map = map;

				// If we had stopped on a character that exist in original map
		        if (map[s2[j]] != 0)
		            i++;
		        else
		            i = j;
		    }
		    else
		        i++;
		}

		return false;
	}
};



/*
	------------
	--- IDEA ---
	------------

	Idea is THE SAME as for LeetCode Problem 438 find all Anagrams in a string.
	The only thing that differs is the return type.

	In the 438-th Problem we needed to count all the anagrams, while in this
	one we only have to tell if there is a permuration of s1 in s2.

	So it's even simpler.

*/



/* Time  Beats: 75.31% */
/* Space Beats: 93.20% */
/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window
{
public:
	bool checkInclusion(std::string s1, std::string s2)
	{
		if(s2.length() < s1.length())
			return false;

		std::vector<int> freq_s1(26,0);
		std::vector<int> window(26,0);

		/* First window */
		for(int i = 0; i < s1.length() ; i++)
		{
			freq_s1[s1[i]-'a']++;
			window[s2[i]-'a']++;
		}

		if(freq_s1 == window)
			return true;

		/* Sliding Window */
		for(int i = s1.length(); i < s2.length(); i++)
		{
			window[s2[i - s1.length()] - 'a']--;
			window[s2[i] - 'a']++;

			if(freq_s1 == window)
				return true;
		}

		return false;
	}
};


int
main()
{
	Solution sol;
	Solution_Sliding_Window sol_win;

	/* Example 1 */
	// std::string s1 = "ab";
	// std::string s2 = "eidbaooo";

	/* Example 2 */
	// std::string s1 = "ab";
	// std::string s2 = "eidboaoo";

	/* Example 3 */
	std::string s1 = "abc";
	std::string s2 = "bbbca";

	std::cout << "\n\t=============================";
	std::cout << "\n\t=== PERMUTATION IN STRING ===";
	std::cout << "\n\t=============================\n";

	/* Write Input */
	std::cout << "\n\ts1 = \"" << s1 << "\"";
	std::cout << "\n\ts2 = \"" << s2 << "\"\n";

	/* Solution */
	// bool b = sol.checkInclusion(s1, s2);
	bool b = sol_win.checkInclusion(s1, s2);

	/* Write Output */
	if (b)
		std::cout << "\n\tOutput: True\n\n";
	else
		std::cout << "\n\tOutput: False\n\n";

	return 0;
}
