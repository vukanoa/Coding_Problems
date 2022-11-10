#include <iostream>
#include <map>

/*
    ==============
    === MEDIUM ===
    ==============	
		
	=================================================
	3) Longest Substring Without Repeating Characters
	=================================================
	
	Given a string s, find the length of the longest substring(not a
	subsequence) without a repeating characters.


	--- Example 1 ---
	Input: s = "abcabcbb"
	Output: 3
	Explanation: The answer is "abc", with the length of 3.


	--- Example 2 ---
	Input: s = "bbbbb"
	Output: 1
	Explanation: The answer is "b", with the length of 1.


	--- Example 3 ---
	Input: s = "pwwkew"
	Output: 3
	Explanation: The answer is "wke", with the lenght of 3.

	// Notice that the answe must be a substring, "pwke" is a subsequence and
	// a substring.


	--- Example 4 ---
	Input: s = "svesvhjzhwwj"
	Output: 6
	Explanation: The answer is "esvhjz", with the length of 6.


	*** Consraints ***
		0 <= s.length <= 5 * 10^4
		s consists of English letters, digits, symbols and spaces.
*/

/*
	Even better implementation

	Note: Since it is said:
		s consists of English letters, digits, symbols and spaces.
	that means that we can have a: 
		std::vector<int> ascii(128, -1);

	Implementation:
	int lengthOfLongestSubstring(std::string s)
	{
		std::vector<int> ascii(128, -1);

		int left  = 0;
		int right = 0;

		int longest = 0;
		while (right < s.size())
		{
			char curr_char = s[right];

			int index = ascii[curr_char];
			if (index != -1 && index >= left && index < right)
				left = index + 1;

			longest = std::max(longest, right - left + 1);
			ascii[curr_char] = right;
			right++;
		}
		return longest;
	}
*/

class Solution {
public:
    int lengthOfLongestSubstring(std::string s)
    {
        int longest = 0;
        int length = s.size();

        std::map<char,int> map;
        
        int i = 0;
        for(int j = 0; j < length; j++)
        {
            if (map.find(s[j]) != map.end())
                i = std::max(map[s[j]], i);
            
            longest = std::max(longest, j - i + 1);
            map[s[j]] = j + 1;
        }

        return longest;
    }
};


int
main()
{
	/* Example 1 */
	// std::string s = "abcabcbb";

	/* Example 2 */
	// std::string s = "bbbbb";

	/* Example 3 */
	// std::string s = "pwwkew";

	/* Example 4 */
	std::string s = "svesvhjzhwwj";

	Solution sol;
	int longest = sol.lengthOfLongestSubstring(s);
	std::cout << "\n\tString: " << s << "\n";

	std::cout << "\n\tLongest is of length: " << longest << "\n\n";

	return 0;
}
