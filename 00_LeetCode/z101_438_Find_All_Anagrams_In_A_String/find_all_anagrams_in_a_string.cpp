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
	FUNCTION: vector<int> findAnagrams(string s, string );
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

	First, we have to make a Hash Map of our string 'p'.

	Let's conisder Example 1:
		s = "cbaebabacd", p = "abc"

	After "converting" string 'p' into a Hash Map, our HashMap looks like this:
	a : 1
	b : 1
	c : 1

	Now let's go through the Brute Force Solution first(It gives us TLE):

	Code for Brute Force:

	// Time Limit Exceeded
    vector<int> findAnagrams(string s, string p)
    {
        std::unordered_map<char, int> map;
        std::unordered_map<char, int> tmp_map;
        int p_length = 0;

        std::vector<int> ret;

        for (auto& x : p)
        {
            p_length++;
            map[x]++;
        }

        tmp_map = map;

        int count = 0;
        for (int i = 0; i < s.size(); i++)
        {
            int j = i;
            while (j < s.size() && tmp_map[s[j]] != 0 && count < p.length())
            {
                tmp_map[s[j]]--;
                count++;

                j++;
            }

            if (count == p.length())
                ret.push_back(i);

            count = 0;
            tmp_map = map;
        }

        return ret;
    }

	s = "cbaebabacd"
	We start with 0th element and if that element exists in the Hash Map
	we go further with an index 'j' since if it turns out that the sequence of
	characters were to fulfill the string 'p', we would have to push the
	starting index into vector "ret" which we return at the very end.

	So, we start with 'c'(in this example)
	'c' is indeed in our Hash map
		count++; // How many consecutive characters of string p, have we
		         // stumbled upon yet
		tmp_map[s[j]]--;

	Now our Hash map looks like this:
	a : 1
	b : 1
	c : 0

	j++; // continue down this path, (this is only considering string that
	     // starts at index i)

	after 3 cycles, s[j] would be 'e' which isn't in a Hash Map, thus we
	go out of the while loop and check:
		if (count == p_length)
                ret.push_back(i);

	In any way, reset count variable to 0 and restore tmp_map to the original
	map we've constructed at the very beginning.

	(We have to restored the map, since we've possibly decremented values of
	certain keys, thus we have to have the original values starting from the
	next i)


	This gives us TLE(Time Limit Exceeded), so let's look at it and try to see
	where could we optimize our solution.

	Time Complexity for this Brute Force Solution would be: O(N * M)
	Where N is the length of string 's', and M is the length of string 'p'.

	Again, let's consider Example 1:
		s = "cbaebabacd", p = "abc"

	// BEGINNING
	s = "cbaebabacd",
	count = 0
	Initial Hash Map:
		a : 1
		b : 1
		c : 0


	i = 0
		s = "cbaebabacd"
			 j

		count = 1
		Hash Map:
			a : 1
			b : 1
			c : 0


		s = "cbaebabacd"
			  j

		count = 2
		Hash Map:
			a : 1
			b : 0
			c : 0


		s = "cbaebabacd"
			   j

		count = 3
		Hash Map:
			a : 0
			b : 0
			c : 0


		s = "cbaebabacd"
			    j

		Go out of while loop because 'e' isn't in HashMap.

		if (count == p.length())
			ret.push_back(i);

		count = 0;
		tmp_map = map;




	i = 1
		s = "cbaebabacd"
			  j

		count = 0
		Hash Map:
			a : 1
			b : 0
			c : 1

		... etc.

	Do you see it?

	We would have to go over "ba" at position 1 and 2 respectively, AGAIN.
	This is repeated calculations.

	What can we conclude here?
	For this example, after we've found our first anagram, starting at index 0
	"cba" we don't have to reset everything and start at 'b'.

	We can only "pop" the front of the anagram, that is 'c'. And we can
	continue on 'e'.

	Imagine if we had:
		s = "cbacbabacd"
			Instead of
		s = "cbaebabacd"

	For i == 0, we would still go out of while loop at j == 3, since 'c' would
	not be present in a Hash Map in that state. BUT, if we were to start with
	'b' at position 1, then 'c' would be present and this would result in our
	second solution, now starting with index 1.

	So the idea is that, first, if we get our anagram, don't reset everything,
	just "pop" the front and continue where j broke the condition of a while
	loop. s[j] will break the while loop be it in the original map or not
	since if we have found our anagram, our HashMap would be all 0's, because
	we have used every letter of 'p'.

	Thus we don't have to reset everything and do repeated calculations. We
	can just "pop" the front(index i) and continue where j points right now.



	So this is our first optimization, but it's still not complete.
	Consider this part of our example:
		s = "cbacbabacd"
		        i

	Again, we would find our second solution and would just pop 'c' at position
	i and our i would continue on from here:
		s = "cbacbabacd"
		           i

	In this case we will immediately break out of the while loop(won't even get
	in for this 'i' since our 'b' has already been used), we will check:
		if (count == p_length) // FALSE

	Thus we would reset it again when we, again, don't have to.

	So we can add an additional condition in our if:
		if (count == p_length || (count > 0 && map[s[j]] != 0))

	Why are we doing this?
		if count > 0 that indicates that we don't have to start all over again
		since we have our HashMap at a certain state which we don't want to
		calucate to again. Thus we can just pop the front and continue.

		However we cannot just simply check if count > 0 since we could stop
		at a character that is not only absent in the tmp_map due to an earlier
		iteration usage, but because that character (such as 'e' in this case)
		does not belong to our originally constructed HashMap "map".

		In that case we don't have to "pop" the front and continue with a
		partly calculated state since we are certain that this character will
		always prevent us from collecting all the consecutive anagram
		characters of string 'p', thus we can just cut it here and start with
		i + 1 which will be, in case of 'e', the right character of e.


	However, this is not all. There's one more caveat. If it was 'b', as it is
	in our original example, we would pop our 'left' b(the one that caused the
	HashMap to have a value 0) but not because that is the front, but on
	accident. Remember, our current 'i' is "right 'b'"

	So we would do tmp_map[s[j]]++;
	However s[j] is our RIGHT b. It would work in this case, but was it 'a' or
	some other character, that would mean we wouldn't pop our front 'b'(the
	index we started this path from) but either some random character that
	doens't even exist in the "map" or non-front character.

	So how do we solve this?
	We have to make a new variable. We'll call it "pop".

	"pop" will either be -1, in that case we'll do:
		tmp_map[s[j]]++;

	or it could point at the front that is next to be popped if needed, so:
		tmp_map[s[pop++]]++;

	Why pop++?
	After we "gave" back the front, now the front is the very next character.

	if pop was -1 and we did:
			tmp_map[s[j]]++
	set "pop" to i + 1


	If neither if these two conditions were true:
		count == p_length || (count > 0 && map[s[j]] != 0)

	Then reset everything. Reset counter. Reset tmp_map to point to original
	one. Set pop to -1.
	Move i to i + 1;

	After we've finished the for loop, return vector "ret".

	This way we have reduced the Time Complexity:
		from O(N * M) to O(N)
	which is huge if M is anywhere near N.


*/


/* Time  Complexity: O(N) */ /* Time  Beats: 21% */
/* Space Complexity: O(N) */ /* Space Beats: 16% */
class Solution{
public:
	std::vector<int> findAnagrams(std::string s, std::string p)
	{
		std::unordered_map<char, int> map;
		std::unordered_map<char, int> tmp_map;

		std::vector<int> ret;

		for (auto& x : p)
			map[x]++;

		tmp_map = map;

		int count = 0;
		int pop = -1;
		for (int i = 0; i < s.size();)
		{
			int j = i;
			while (j < s.size() && tmp_map[s[j]] != 0)
			{
				tmp_map[s[j]]--;
				count++;

				j++;
			}

			if (count == p.length() || (count > 0 && map[s[j]] != 0))
			{
				if (count == p.length())
				{
					if (pop != -1)
						ret.push_back(pop);
					else
						ret.push_back(i);
				}

				if (pop != -1)
					tmp_map[s[pop++]]++;
				else
				{
					pop = i + 1;
					tmp_map[s[i]]++;
				}

				count--;
				i = j;
			}
			else
			{
				count = 0;
				tmp_map = map;
				i++;
				pop = -1;
			}
		}

		return ret;
	}
};




/*
	------------
	--- IDEA ---
	------------

	The idea is similar to the one above.

	Instead of a Hash Map, we use a vector, since we are told that both 's' and
	'p' are consisted of only lowercase English letters.

	Now we have two of those vectors. Why?
	Because we will use "window" as a current window that we're sliding. It
	will always have p.length() sum of values.

	Each time we just compare these two vectors. In C++ it is possible to just
	compare it like this:
		if(freq_p == window)

	We have to go through the first p.lenght() characters in string 's' to
	'construct' the window. Then we just move one-by-one.
	We pop from the from the front, add to the back and compare.

	If they are the same, push index 'i' in vector "ret".

	At the end, just return the vector "ret".
*/


/* Time  Complexity: O(N) */ /* Time  Beats: 70% */
/* Space Complexity: O(1) */ /* Space Beats: 77% */
class Solution_Sliding_Window{
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


int
main()
{
	Solution sol;
	Solution_Sliding_Window sol_win;

	/* Example 1 */
	std::string s = "cbaebabacd";
	std::string p = "abc";

	/* Example 2 */
	// std::string s = "abab";
	// std::string p = "ab";

	/* Example 3 */

	std::cout << "\n\t=====================================";
	std::cout << "\n\t=== FIND ALL ANAGRAMS IN A STRING ===";
	std::cout << "\n\t=====================================\n";

	/* Write Input */
	std::cout << "\n\ts = \"" << s << "\"";
	std::cout << "\n\tp = \"" << p << "\"\n";

	/* Solution */
	// std::vector<int> ret = sol.findAnagrams(s, p);
	std::vector<int> ret = sol_win.findAnagrams(s, p);

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
