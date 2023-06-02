#include <iostream>
#include <vector>
#include <unordered_map>

/*
	==============
	=== MEDIUM ===
	==============

	==================================
	438) Find All Anagrams in a String
	==================================

	============
	Description:
	============

	Given two string 's' and 'p', return an array of all the start indices of
	p's anagrams in s. You may return the answer in any order.

	An Anagram is a word or phrase formed by rearranging the letters of a
	different word or phrase, typically using all the original letters exactly
	once.

	======================================================
	FUNCTION: vector<int> findAnagrams(string s, string p);
	======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  s = "cbaebabacd", p = "abc"
	Output: [0, 6]

	--- Example 2 ---
	Input:  s = "abab", p = "ab"
	Output: [0, 1, 2]

	*** Constraints ***
	1 <= s.length, p.length <= 3 * 10^4
	s and p consist of lowercase English letters

*/


/*
	------------
	--- IDEA ---
	------------

	Make a Hash Map out of the content in string 'p'.

	In the process of filling the Hash Map of 'p' with frequencies, we do the
	same for first 'p' letters in string 's'.

	Thus we covered the "first window". We immediately check if thw two Hash
	Maps are the same. If they are, then push 0 as the starting index.

	Afterwards, do these steps:
		1. Always remove the leftmost in a window by decrementing the frequency
		   of that letter by one in the Hash map.

		2. Always add the right, new one, in a window by incrementing the
		   frequencies of that letter by one in the Hash Map.

		3. Check if both Hash Maps, i.e. "freq_p" and "window" and if they are
		   push the "left" index in vector "ret" which we're returngin at the
		   end.
	

	*** OPTIMIZATION ***

	Instead of a Hash Map, we use a vector, since we are told that both 's' and
	'p' are consisted of only lowercase English letters.

	This way, we're optimized the code hugely:
		Using real Unordered Hash Map gives us: Time Beats 21%

		Using vector as a Hash Map gives us   : Time Beats 94%

	So it's a huge optimization. Also using a vector can be considered O(1)
	Space since we're told that we only have lowercase English letters, meaning
	it does not depend on the input, meaning it's constant, hence O(1) Space.
*/

/* Time  Beats: 69.31% */
/* Space Beats: 98.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window_1 {
public:
	std::vector<int> findAnagrams(std::string s, std::string p)
	{
		if(s.length() < p.length())
			return {};

		std::vector<int> freq_p(26,0);
		std::vector<int> window(26,0);

		/* First window */
		for(int i = 0; i < p.length() ; i++)
		{
			freq_p[p[i]-'a']++;
			window[s[i]-'a']++;
		}

		std::vector<int> ret;
		if(freq_p == window)
			ret.push_back(0);

		/* Sliding Window */
		for(int i = p.length(); i < s.length(); i++)
		{
			window[s[i - p.length()] - 'a']--;
			window[s[i] - 'a']++;

			if(freq_p == window)
				ret.push_back(i - p.length() + 1);
		}

		return ret;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Same as above, just done on another occasion so I wanted to have it here as
	well.
	
	Make a Hash Map out of the content in string 'p'.

	Iterate through string 's' with two pointers: "left" and "right".
	Only increment "right" until the size of window, i.e. "right - left + 1"
	becomes of equal size as string 'p'.

	Before you increment "right" you have to increment the frequency of
	repetition inside the Hash Map of the window that we are going to "slide"
	once "right - left + 1" reached the length of string 'p'.

	Once we reach that point, i.e. "right - left + 1" becomes of length 'p', 
	just start "sliding" the window by incrementing both "left"
	and "right" pointer at the same time.

	Before incrementing the "left" pointer you have to decrement the frequency
	of repetition inside the Hash Map of the window that we're "sliding".

	Frequency of repetiton is incremented in the Hash Map of the window, at the
	beginning of the while loop, before we increment "right" pointer. So that's
	taken care of, as well.
	

	*** OPTIMIZATION ***

	Instead of a Hash Map, we use a vector, since we are told that both 's' and
	'p' are consisted of only lowercase English letters.

	This way, we're optimized the code hugely:
		Using real Unordered Hash Map gives us: Time Beats 21%

		Using vector as a Hash Map gives us   : Time Beats 94%

	So it's a huge optimization. Also using a vector can be considered O(1)
	Space since we're told that we only have lowercase English letters, meaning
	it does not depend on the input, meaning it's constan, hence O(1) Space.
*/

/* Time  Beats: 94.91% */
/* Space Beats: 65.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window_2 {
public:
	std::vector<int> findAnagrams(std::string s, std::string p)
	{
		if (p.length() > s.length())
			return {};

		std::vector<int> results;

		// const num_of_lowercase_english_letters = 26
		std::vector<int> p_map      (26, 0);
		std::vector<int> window_map (26, 0);

		// Fill p_map
		for (const auto& letter : p)
			p_map[letter - 'a']++;

		int left  = 0;
		int right = 0;

		/* Sliding Window */
		while (right < s.length())
		{
			window_map[s[right] - 'a']++;

			if (window_map == p_map)
				results.push_back(left);

			/* This doesn't happen until window length is less than p.length */
			/* (right - left + 1) is the size of the window we're "sliding"  */
			/* Until we reach that size, increment only "right" boundary.    */
			if (right - left + 1 == p.length())
			{
				window_map[s[left] - 'a']--;
				left++;
			}

			right++;
		}

		return results;
	}
};


int
main()
{
	Solution_Sliding_Window_1 sol_win_1;
	Solution_Sliding_Window_2 sol_win_2;

	/* Example 1 */
	// std::string s = "cbaebabacd";
	// std::string p = "abc";

	/* Example 2 */
	// std::string s = "abab";
	// std::string p = "ab";

	/* Example 3 */
	// std::string s = "baa";
	// std::string p = "aa";

	/* Example 4 */
	std::string s = "rzzbarryrrrabis";
	std::string p = "rbra";


	std::cout << "\n\t=====================================";
	std::cout << "\n\t=== FIND ALL ANAGRAMS IN A STRING ===";
	std::cout << "\n\t=====================================\n";


	/* Write Input */
	std::cout << "\n\ts = \"" << s << "\"";
	std::cout << "\n\tp = \"" << p << "\"\n";


	/* Solution */
	// std::vector<int> ret = sol_win_1.findAnagrams(s, p);
	std::vector<int> ret = sol_win_2.findAnagrams(s, p);


	/* Write Output */
	bool first = true;
	std::cout << "\n\tIndexes: [";
	for (auto x: ret)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
