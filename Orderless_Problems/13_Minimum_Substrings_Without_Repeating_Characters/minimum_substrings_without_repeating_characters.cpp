#include <iostream>
#include <unordered_set>

/*
	Given a string s, find the minimum number of substrings you can create
	without having the same letters repeating in each substring.

	Example 
    E.g world -> 5, as the string has no letters that occur more than once.
    dddd -> 4, as you can only create substring of each character.
    abba -> 2, as you can make substrings of ab, ba.
    cycle-> 2, you can create substrings of (cy, cle) or (c, ycle)

	--- Example 1 ---
	Input:  str = "world"
	Output: 5
	Explanation: As the string has no leters that occur more than once.

	--- Example 2 ---
	Input:  str = "dddd"
	Output: 4
	Explanation: As you can only create substring of each character.

	--- Example 3 ---
	Input:  str = "abba"
	Output: 2
	Explanation: As you can make substrings of (ab, ba).

	--- Example 5 ---
	Input:  str = "cycle"
	Output: 2
	Explanation: As you can create substrings of (cy, cle) or (c, ycle).

*/

/* Sliding Window Technique */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
int solution(std::string& str)
{
	if (str.empty())
		return 0;

	int left  = 0;
	int right = 0;

	int count = 0;

	std::unordered_set<char> uset;

	while (right < str.length())
	{
		while (uset.find(str[right]) != uset.end())
		{
			uset.erase(str[left]);
			left++;
		}

		uset.insert(str[right]);
		count++;

		right++;
	}

	return count;
}
