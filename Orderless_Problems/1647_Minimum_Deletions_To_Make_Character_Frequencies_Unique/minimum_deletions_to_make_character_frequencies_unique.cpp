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
#include <vector>
#include <algorithm>
using namespace std;

/* Time  Beats: 32.12% */
/* Space Beats: 89.44% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minDeletions(string s) 
    {
        const int ALPHABET_CHARACTERS = 26;
        vector<int> freq(26, 0);

        for (const char& chr : s) 
            freq[chr - 'a']++;

        /* Sort */
        sort(freq.begin(), freq.end());

        int deletions = 0;
        for (int i = ALPHABET_CHARACTERS - 2; i >= 0; i--) 
        {
            if (freq[i] == 0)
                break;

            if (freq[i] >= freq[i + 1]) 
            {
                int prev = freq[i];
                freq[i] = max(0, freq[i + 1] - 1);
                deletions += prev - freq[i];
            }
        }

        return deletions;
    }
};
