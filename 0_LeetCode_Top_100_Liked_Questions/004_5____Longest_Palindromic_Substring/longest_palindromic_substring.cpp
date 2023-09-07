#include <iostream>
#include <cstring>

/*
	==============
	=== MEDIUM ===
	==============

	================================
	5) Longest Palindromic Substring
	================================

	Given a string s, return the longest palindromic substring in s

	--- Example 1 ---
	Input: s = "babad"
	Output: "bab"
	Explanation: "aba" is also a valid answer

	--- Example 2 ---
	Input: s = "cbbd"
	Output: "bb"

	*** Constraints ***
	1 <= s.length <= 1000
	s consists of only digits and English letters
*/


using namespace std;

/*
	Possible Time Complexities Solutions:
	O(n^3) -> O(n^2 * logn) -> O(n^2) -> O(n)

	O(n) -> Manacher's Algorithm
*/

/* ------------------------------------------------------------------------- */

/*
	==============
	=== O(n^3) ===
	==============
*/

bool is_palindrome(string s) // bool is_palindrome(const string& s)
{
	string reversed = string(s.rbegin(), s.rend()); // O(n)
	
	return s == reversed;
}

class Solution_n3 {
public:
	string longestPalindrome(string s)
	{
		int n = s.length();
		int longest = 0;
		string longest_substr = "";

		for (int L = 0; L < n; L++)
		{
			for (int R = L; R < n; R++)
			{
				int length = R - L + 1;
				string substr = s.substr(L, length);

				/*
					C++ has lazy if statements so it's faster to check for the
					lenght first
				*/
				if (length > longest && is_palindrome(substr))
				{
					longest = length;
					longest_substr = substr; // O(n); Improved version looks like:
					// longest_substr = s.substr(L, R);
					// longest_start = L;
					// longest_end   = R;
				}
			}
		}
		// Improved:
		// return s.substr(longest_start, longest_end);
		// Now the "copying" still has to go through an entire string
		// but now it happens only once. At the very end. So it's constant.

		return longest_substr;
	}
	
};

/* ------------------------------------------------------------------------- */

/*
	=====================
	=== O(n^2 * logn) ===
	=====================
*/

/*
bool is_palindrome(string s) // bool is_palindrome(const string& s)
{
	string reversed = string(s.rbegin(), s.rend()); // O(n)
	
	return s == reversed;
}
*/


// Palindrome substring exist of length x
int palindrome_substring_exist(int x, string s)
{
	int n = s.length();
	for (int L = 0; L + x <= n; L++)
	{
		if (is_palindrome(s.substr(L, x)))
			return L;
	}

	return -1;
}

class Solution_nlogn {
public:
	string longestPalindrome(string s)
	{
		int longest = 0;
		string longest_substr = "";
		int n = s.length();

		for (int parity: {0, 1})
		{
			int low  = 1;
			int high = n;

			if (low % 2 != parity)
				low++;

			if (high % 2 != parity)
				high--;

			while (low <= high)
			{
				int mid = (low + high) / 2;

				if (mid % 2 != parity)
					mid++;

				if (mid > high)
					break;

				int found = palindrome_substring_exist(mid, s);
				if (found != -1)
				{
					if (mid > longest)
					{
						longest = mid;
						longest_substr = s.substr(found, mid);
					}
					low = mid + 2;
				}
				else
					high = mid - 2;
			}
		}

		return longest_substr;
	}
};

/* ------------------------------------------------------------------------- */

/*
	==============
	=== O(n^2) ===
	==============
*/

class Solution_n2 {
public:
	string longestPalindrome(string s)
	{
		int longest = 0;
		string longest_substr = "";
		int n = s.length();

		for (int mid = 0; mid < n; mid++)
		{
			for (int x = 0; mid - x >= 0 && mid + x < n; x++)
			{
				if (s[mid - x] != s[mid + x])
					break;

				int length = 2 * x + 1;
				if (length > longest)
				{
					longest = length;
					longest_substr = s.substr(mid - x, length);
				}
			}
		}
		
		for (int mid = 0; mid < n - 1; mid++)
		{
			for (int x = 1; mid - x + 1 >= 0 && mid + x < n; x++)
			{
				if (s[mid - x + 1] != s[mid + x])
					break;

				int length = 2 * x;
				if (length > longest)
				{
					longest = length;
					longest_substr = s.substr(mid - x + 1, length);
				}
			}
		}

		return longest_substr;
	}
};

/* ------------------------------------------------------------------------- */

/*
	==============
	=== O(n^2) ===
	==============
*/

/* Time  Beats: 84.01% */
/* Space Beats: 60.55% */
class Solution_easier_for_me {
public:
	std::string longestPalindrome(std::string s)
	{
		int n = s.length();

		std::string odd_str = "";
		for (int i = 0; i < n; i++)
		{
			int count = 1;

			for (int j = 0; i-j-1 >= 0 && i+j+1 < n; j++)
			{
				if (s[i-j-1] != s[i+j+1])
					break;
				else
					count += 2;
			}

			if (count > odd_str.length())
				odd_str = s.substr(i - count/2, count);
		}

		std::string even_str = "";
		for (int i = 0; i < n-1; i++)
		{
			int count = 0;
			for (int j = 0; i-j >= 0 && i+j+1 < n; j++)
			{
				if (s[i-j] != s[i+j+1])
					break;
				else
					count += 2;
			}

			if (count > even_str.length())
				even_str = s.substr(i - count/2 + 1, count);
		}

		if (odd_str.length() >= even_str.length())
			return odd_str;

		return even_str;
	}
};

/* ------------------------------------------------------------------------- */

/*
	==============
	=== O(n^2) ===
	==============
*/

class Solution_n2_table{
public:
	string longestPalindrome(string s)
	{
		int n = s.length();
		int longest = 1;
		int start = 0;

		bool dp[n][n];
		memset(dp, 0, sizeof(dp));

		// Fill the diagonal
		for (int i = 0; i < n; ++i)
			dp[i][i] = true;

		// Fill with substrings of length 2
		for (int i = 0; i < n - 1; ++i)
		{
			if (s[i] == s[i + 1])
			{
				dp[i][i + 1] = true;
				start = i;
				longest = 2;
			}
		}

		// Find all substrings of length >= 3 and <= n
		for (int k = 3; k <= n; ++k)
		{
			for (int i = 0; i < n - k + 1; ++i)
			{
				int j = i + k - 1;

				if (dp[i + 1][j - 1] && s[i] == s[j]) // Reverse operations?
				{
					dp[i][j] = true;

					if (k > longest)
					{
						start = i;
						longest = k;
					}
				}
			}
		}

		string longest_substr = s.substr(start, longest);

		return longest_substr;
	}

};

/* ------------------------------------------------------------------------- */

/*
	============
	=== O(n) ===
	============
*/

/*
	Note: 'Position' pertains to expanded string. The one where separator
	      character is added between every character in the original string
		  plus two more(one at the very beginning and one at the very end)

		  'Index', on the other hand, pertains to the original string.
	
             a b a a b
Indexes ->   0 1 2 3 4

             $ a $ b $ a $ a $ b $
Positions -> 0 1 2 3 4 5 6 7 8 9 10

*/


class Solution_manacher{
public:
	string longestPalindrome(string s)
	{
		if (s.length() == 1)
			return s;

		int N = 2 * s.length() + 1;

		int LPS[N];
		LPS[0] = 0;
		LPS[1] = 1;

		int center_position = 1;       // center_position_position
		int right_border_position = 2; // center_position_right_position
		int i = 0;                     // current_right_position
		int i_mirror;                  // current_left_position

		int max_LPS_length = 0;
		int max_LPS_center_position = 0;

		int start_index = -1;
		int end_index   = -1;

		int difference = -1;
		int expand     = -1;

		for (i = 2; i < N; i++)
		{
			i_mirror = 2 * center_position - i;

			expand = 0;
			difference = right_border_position - i;

			if (difference >= 0)
			{
				// Case 1
				if (LPS[i_mirror] < difference)
					LPS[i] = LPS[i_mirror];

				// Case 2
				else if (LPS[i_mirror] == difference && right_border_position == N - 1)
					LPS[i] = LPS[i_mirror];

				// Case 3
				else if (LPS[i_mirror] == difference && right_border_position < N - 1)
				{
					LPS[i] = LPS[i_mirror];

					// Expansions required
					expand = 1;
				}

				// Case 4
				else if (LPS[i_mirror] > difference)
				{
					LPS[i] = difference;

					// Expansion required
					expand = 1;
				}
			}
			else
			{
				LPS[i] = 0;

				// Expansion required
				expand = 1;
			}

			// Expansion required
			if (expand == 1)
			{
				while (
						(
							(i + LPS[i]) < N
							&&
							(i - LPS[i]) > 0
						)
						&&
						(
							((i + LPS[i] + 1) % 2 == 0)
							||
							(s[(i + LPS[i] + 1) / 2] == s[(i - LPS[i] - 1) / 2])
						)
					)
				{
					LPS[i]++;
				}
			}

			if (LPS[i] > max_LPS_length)
			{
				max_LPS_length = LPS[i];
				max_LPS_center_position = i;
			}

			if (i + LPS[i] > right_border_position)
			{
				center_position = i;
				right_border_position = i + LPS[i];
			}
		}

		// Real indexes in string 's', that is -> w/o separator characters
		start_index = (max_LPS_center_position - max_LPS_length) / 2;
		end_index   = start_index + max_LPS_length - 1;

		string longest_pal_substr = "";

		for (i = start_index; i <= end_index; i++)
			longest_pal_substr += s[i];

		return longest_pal_substr;
	}

};


int
main()
{
	// Solution_n3 sol_n3;             // O(n^3)
	// Solution_nlogn sol_nlogn;       // O(n^2 * logn)
	// Solution_n2 sol_n2;             // O(n^2)
	// Solution_n2_table sol_n2_table; // O(n^2)
	Solution_manacher sol_manacher;    // O(n)

	/* Example 1 */
	// string s = "babad";

	/* Example 2 */
	// string s = "cbbd";

	/* Example 3 */
	// string s = "abaxabaxabb";

	/* Example 4 */
	string s = "abaxabaxabybaxabyb";

	cout << "\n\t=====================================";
	cout << "\n\t=== LONGEST PALINDROMIC SUBSTRING ===";
	cout << "\n\t=====================================\n\n";


	cout << "\n\t--- String --- \n\t\"" << s << "\"";

	// cout << "\n\n\n\t--- Longest palindromic substring --- \n\t\"" << sol_n3.longestPalindrome(s) << "\"";       // O(n^3)
	// cout << "\n\n\n\t--- Longest palindromic substring --- \n\t\"" << sol_nlogn.longestPalindrome(s) << "\"";    // O(n^2 * logn)
	// cout << "\n\n\n\t--- Longest palindromic substring --- \n\t\"" << sol_n2.longestPalindrome(s) << "\"";       // O(n^2)
	// cout << "\n\n\n\t--- Longest palindromic substring --- \n\t\"" << sol_n2_table.longestPalindrome(s) << "\""; // O(n^2)
	cout << "\n\n\n\t--- Longest palindromic substring --- \n\t\"" << sol_manacher.longestPalindrome(s) << "\"";    // O(n)

	cout << "\n\n\n";

	return 0;
}
