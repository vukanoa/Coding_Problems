#include <iostream>
#include <vector>
#include <algorithm>

/*
	============
	=== EASY ===
	============

	===========================
	125) Valid Palindrome
	===========================

	============
	Description:
	============

	A phrase is a palindrome if, after converting all uppercase letters into
	lowercase letters and removing all non-alphanumeric characters, it reads
	the same forward and backward. Alphanumeric characters include letters and
	numbers.

	Given a string s, return true if it is a palindrome, or false otherwise.

	=================================
	FUNCTION: isPalindrome(string s);
	=================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "A man, a plan, a canal: Panama"
	Output: true
	Explanation: "amanaplanacanalpanama" is a palindrome.


	--- Example 2 ---
	Input: s = "race a car"
	Output: false
	Explanation: "raceacar" is not a palindrome.


	--- Example 3 ---
	Input: s = " "
	Output: true
	Explanation: s is an empty string "" after removing non-alphanumeric
	characters. Since an empty string reads the same forward and backward, it
	is a palindrome.

	*** Constraints ***
    1 <= s.length <= 2 * 105
    s consists only of printable ASCII characters.

*/


/*
	------------
	--- IDEA ---
	------------

	Make a new vector and fill it only with alphanumeric characters from the
	string 's'.

	Use Two pointers at the end toe check if the vector "vec" is a palindrome.
	
*/

/* Time  Beats: 33.48% */
/* Space Beats: 46.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_1{
public:
	bool isPalindrome(std::string& s)
	{
		std::vector<char> vec;

		for (int i = 0; i < s.length(); i++)
		{
			if (isupper(s[i]))       // Uppercase letter
			{
				vec.push_back(s[i] + 32); // Convert to lowercase
			}
			else if (islower(s[i]) || isdigit(s[i])) // Lowercase letter
			{
				vec.push_back(s[i]);
			}
			else
			{
				continue;
			}
		}

		int left  = 0;
		int right = vec.size() - 1;

		if (vec.size() % 2 == 0)
		{
			while (left < right)
			{
				if (vec[left++] != vec[right--])
					return false;
			}
		}
		else
		{
			int mid = (left + right) / 2;

			while (left != mid) // Or right
			{
				if (vec[left++] != vec[right--])
					return false;
			}
		}

		return true;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Make a new vector and fill it only with alphanumeric characters from the
	string 's'.

	Reverse that string and compare the original copy and the reverse copy.
	
*/

/* Time  Beats: 14.22% */
/* Space Beats:  7.92% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2{
public:
	bool isPalindrome(std::string& s)
	{
		std::vector<char> str;
		std::vector<char> rev_str;

		for (char& c : s)
		{
			if (isalnum(c))
				str.push_back(isdigit(c) ? c : islower(c) ? c : c+32);
		}

		rev_str = str;
		std::reverse(str.begin(), str.end());

		return str == rev_str;
	}
};




/*
	------------
	--- IDEA ---
	------------

	We don't have to make a new String. Just use Two Pointers within string s
	and "jump over" non-alphanumberic characters.
	
*/

/* Time  Beats: 91.68% */
/* Space Beats: 74.62% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient{
public:
	bool isPalindrome(std::string s)
	{
		int left  = 0;
		int right = s.length() - 1;

		while (left < right)
		{
			while (left < right && !alpha_num(s[left]))
				left++;

			while (right > left && !alpha_num(s[right]))
				right--;

			if (std::tolower(static_cast<unsigned char>(s[left])) != std::tolower(static_cast<unsigned char>(s[right])))
				return false;

			left++;
			right--;
		}

		return true;
	}

private:
	bool alpha_num(char& c)
	{
		return (c >= 65 && c <= 90)  ||
		       (c >= 97 && c <= 122) ||
		       (c >= 48 && c <= 57);
	}
};


int
main()
{
	Solution_1         sol_1;
	Solution_2         sol_2;
	Solution_Efficient sol_eff;


	/* Example 1 */
	std::string s = "A man, a plan, a canal: Panama";

	/* Example 2 */
	// std::string s = "race a car";

	/* Example 3 */
	// std::string s = " ";


	std::cout << "\n\t========================";
	std::cout << "\n\t=== VALID PALINDROME ===";
	std::cout << "\n\t========================\n";


	/* Write Input */
	std::cout << "\n\tString: \"" << s << "\"\n";


	/* Solution */
	bool result = sol_eff.isPalindrome(s);


	/* Write Output */
	if (result)
		std::cout << "\n\tOutput: Palindrome!";
	else
		std::cout << "\n\tOutput: NOT a Palindrome!";
	std::cout << "\n\n";


	return 0;
}
