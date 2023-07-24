#include <iostream>
#include <vector>

/*
	============
	=== HARD ===
	============

	===========================
	140) Word Break II
	===========================

	============
	Description:
	============

	Given a string s and a dictionary of strings wordDict, add spaces in s to
	construct a sentence where each word is a valid dictionary word. Return all
	such possible sentences in any order.

	=====
	Node: that the same word in the dictionary may be reused multiple times in 
	      the segmentation.
	=====

	=======================================================================
	FUNCTION: vector<string> wordBreak(string s, vector<string>& wordDict);
	=======================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "catsanddog",
	       wordDict = ["cat","cats","and","sand","dog"]

	Output: ["cats and dog","cat sand dog"]




	--- Example 2 ---
	Input: s = "pineapplepenapple",
	       wordDict = ["apple","pen","applepen","pine","pineapple"]

	Output:["pine apple pen apple","pineapple pen apple","pine applepen apple"]

	Explanation: Note that you are allowed to reuse a dictionary word.




	--- Example 3 ---
	Input: s = "catsandog",
	       wordDict = ["cats","dog","sand","and","cat"]

	Output: []



	*** Constraints ***
    1 <= s.length <= 20
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 10
    s and wordDict[i] consist of only lowercase English letters.
    All the strings of wordDict are unique.
    Input is generated in a way that the length of the answer doesn't exceed 10^5.

*/

/*
	------------
	--- IDEA ---
	------------

	It's pretty much a standard Bactracking approach. I'm not sure why is this
	a HARD problem.

	You should try to simulate the very first Example and it'll be obvious:

	Example 1:
	Input: s = "catsanddog",
	       wordDict = ["cat","cats","and","sand","dog"]

	Output: ["cats and dog","cat sand dog"]

	
	Simulation:

	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	         i

		
		std::string str = s.substr(start, i - start + 1);

		Which means that str in this case is only letter 'c'.
		It starts at index "start", then
		takes (i - start + 1) characters including the starting index
		Therefore it's only letter 'c'.

		Does "c" exist as a word in wordDict?
			No! Then i++.

	
	    result  = [""]
	    current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	           i

		std::string str = s.substr(start, i - start + 1);

		str is now "ca"

		Does "ca" exist as a word in wordDict?
			No! Then i++.


	
	    result  = [""]
	    current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	             i

		std::string str = s.substr(start, i - start + 1);

		str is now "cat"

		Does "cat" exist as a word in wordDict?
			Yes!
			Put it in vector "current" where we'll keep track of all the
			separate words in a sentence.

			call backtracking with same argument, but "start" will be "i + 1".


				result  = [""]
				current = ["cat"]
				start = 3;
				 |
				 |__________
				           |
				           v
				s = "c a t s a n d d o g"
				     0 1 2 3 4 5 6 7 8 9
				           i

				std::string str = s.substr(start, i - start + 1);

				str is now "s"

				Does "s" exist as a word in wordDict?
					No! Then i++.



				result  = [""]
				current = ["cat"]
				start = 3;
				 |
				 |__________
				           |
				           v
				s = "c a t s a n d d o g"
				     0 1 2 3 4 5 6 7 8 9
				             i

				std::string str = s.substr(start, i - start + 1);

				str is now "sa"

				Does "sa" exist as a word in wordDict?
					No! Then i++.


				result  = [""]
				current = ["cat"]
				start = 3;
				 |
				 |__________
				           |
				           v
				s = "c a t s a n d d o g"
				     0 1 2 3 4 5 6 7 8 9
				               i

				std::string str = s.substr(start, i - start + 1);

				str is now "san"

				Does "san" exist as a word in wordDict?
					No! Then i++.


				result  = [""]
				current = ["cat"]
				start = 3;
				 |
				 |__________
				           |
				           v
				s = "c a t s a n d d o g"
				     0 1 2 3 4 5 6 7 8 9
				                 i

				std::string str = s.substr(start, i - start + 1);

				str is now "sand"

				Does "sand" exist as a word in wordDict?
					Yes!

					Put it in vector "current" where we'll keep track of all the
					separate words in a sentence.

					call backtracking with same argument, but "start" will be "i + 1".

						result  = [""]
						current = ["cat", "sand"]
						start = 7;
						 |
						 |__________________
						                   |
						                   v
						s = "c a t s a n d d o g"
						     0 1 2 3 4 5 6 7 8 9
						                     i

						std::string str = s.substr(start, i - start + 1);

						str is now "d"

						Does "d" exist as a word in wordDict?
							No! Then i++.


						result  = [""]
						current = ["cat", "sand"]
						start = 7;
						 |
						 |__________________
						                   |
						                   v
						s = "c a t s a n d d o g"
						     0 1 2 3 4 5 6 7 8 9
						                     i

						std::string str = s.substr(start, i - start + 1);

						str is now "do"

						Does "do" exist as a word in wordDict?
							No! Then i++.



						result  = [""]
						current = ["cat", "sand"]
						start = 7;
						 |
						 |__________________
						                   |
						                   v
						s = "c a t s a n d d o g"
						     0 1 2 3 4 5 6 7 8 9
						                       i

						std::string str = s.substr(start, i - start + 1);

						str is now "dog"

						Does "dog" exist as a word in wordDict?
							Yes!

							Put it in vector "current" where we'll keep track of all the
							separate words in a sentence.

							current = ["cat", "sand", "dog"]

							call backtracking with same argument, but "start" will be "i + 1".

								start = 10;
								 |
								 |_________________________
								                          |
								                          v (index: s.length())
								s = "c a t s a n d d o g"
								     0 1 2 3 4 5 6 7 8 9
								                          i (10)

								Is "start" greater or equal than string s?
								Yes! That means we've found one sentence.

								All the words in a sentence are in vector "current"
								Iterate through that vector and concatenate the
								words in one string with a " "(Space) in between.
								(Since we'll concatenate a " "(Space) at the
								end as well, remove it after the for loop)

								Put that string(sentence) in vector "results".
								That is one sentence.

								result = ["cat sand dog"]

								Now return from this function.
						
						Since we are now back from the "backtracking" we called
						from this functions, now we have to pop the last word
						in "current" since maybe there is some longer word that
						starts with 7th index 'd'.

						pop "dog" from current:
						Before: current = ["cat", "sand", "dog"]
						After : current = ["cat", "sand"]

						Since there is not, return from this function as well.


				Since we are now back from the "backtracking" we called
				from this functions, now we have to pop the last word
				in "current" since maybe there is some longer word that
				starts with 4th index 's'.

				pop "sand" from current:
				Before: current = ["cat", "sand"]
				After : current = ["cat"]

				Since there is not, return from this function as well.


		Since we are now back from the "backtracking" we called
		from this functions, now we have to pop the last word
		in "current" since maybe there is some longer word that
		starts with 0th index 'c'.

		pop "sand" from current:
		Before: current = ["cat"]
		After : current = []

		(We just popped "cat") There is a longer one named "cats". Push that
		to "current" and call backtracking from 5th index "a".

		result = ["cat sand dog"]
		current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	               i


		std::string str = s.substr(start, i - start + 1);

		str is now "a"

		Does "a" exist as a word in wordDict?
			Yes!

			Put it in vector "current" where we'll keep track of all the
			separate words in a sentence.

			call backtracking with same argument, but "start" will be "i + 1".

				result = ["cat sand dog"]
				current = ["cats"]
				start = 4;
				 |
				 |____________
				             |
				             v
				s = "c a t s a n d d o g"
				     0 1 2 3 4 5 6 7 8 9
				             i

				std::string str = s.substr(start, i - start + 1);

				str is now "a"

				Does "a" exist as a word in wordDict?
					No! Then i++.


				result = ["cat sand dog"]
				current = ["cats"]
				start = 4;
				 |
				 |____________
				             |
				             v
				s = "c a t s a n d d o g"
				     0 1 2 3 4 5 6 7 8 9
				               i

				std::string str = s.substr(start, i - start + 1);

				str is now "an"

				does "an" exist as a word in worddict?
					No! then i++.



				result = ["cat sand dog"]
				current = ["cats"]
				start = 4;
				 |
				 |____________
				             |
				             v
				s = "c a t s a n d d o g"
				     0 1 2 3 4 5 6 7 8 9
				                 i

				std::string str = s.substr(start, i - start + 1);

				str is now "and"

				Does "and" exist as a word in wordDict?
					Yes!
					Put it in vector "current" where we'll keep track of all the
					separate words in a sentence.

					call backtracking with same argument, but "start" will be "i + 1".

						result = ["cat sand dog"]
						current = ["cats", "and"]
						start = 7;
						 |
						 |__________________
						                   |
						                   v
						s = "c a t s a n d d o g"
						     0 1 2 3 4 5 6 7 8 9
						                   i

						std::string str = s.substr(start, i - start + 1);

						str is now "d"

						does "d" exist as a word in worddict?
							No! then i++.


						result = ["cat sand dog"]
						current = ["cats", "and"]
						start = 7;
						 |
						 |__________________
						                   |
						                   v
						s = "c a t s a n d d o g"
						     0 1 2 3 4 5 6 7 8 9
						                     i

						std::string str = s.substr(start, i - start + 1);

						str is now "do"

						does "do" exist as a word in worddict?
							No! then i++.


						result = ["cat sand dog"]
						current = ["cats", "and"]
						start = 7;
						 |
						 |__________________
						                   |
						                   v
						s = "c a t s a n d d o g"
						     0 1 2 3 4 5 6 7 8 9
						                       i

						std::string str = s.substr(start, i - start + 1);

						str is now "dog"

						does "dog" exist as a word in worddict?
							Yes!
							Put it in vector "current" where we'll keep track of all the
							separate words in a sentence.

							current = ["cats", "and", "dog"]

							call backtracking with same argument, but "start" will be "i + 1".

								start = 10;
								 |
								 |_________________________
								                          |
								                          v (index: s.length())
								s = "c a t s a n d d o g"
								     0 1 2 3 4 5 6 7 8 9
								                          i (10)


								Is "start" greater or equal than string s?
								Yes! That means we've found one sentence.

								All the words in a sentence are in vector "current"
								Iterate through that vector and concatenate the
								words in one string with a " "(Space) in between.
								(Since we'll concatenate a " "(Space) at the
								end as well, remove it after the for loop)

								Put that string(sentence) in vector "results".
								That is one sentence.

								result = ["cat sand dog", "cats and dog"]

								Now return from this function.


	   result  = ["cat sand dog", "cats and dog"]
	   current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	                 i

		std::string str = s.substr(start, i - start + 1);

		str is now "catsa"

		does "catsa" exist as a word in worddict?
			No! then i++.



	   result  = ["cat sand dog", "cats and dog"]
	   current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	                   i

		std::string str = s.substr(start, i - start + 1);

		str is now "catsan"

		does "catsan" exist as a word in worddict?
			No! then i++.


	   result  = ["cat sand dog", "cats and dog"]
	   current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	                     i

		std::string str = s.substr(start, i - start + 1);

		str is now "catsand"

		does "catsand" exist as a word in worddict?
			No! then i++.


	   result  = ["cat sand dog", "cats and dog"]
	   current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	                       i

		std::string str = s.substr(start, i - start + 1);

		str is now "catsandd"

		does "catsandd" exist as a word in worddict?
			No! then i++.


	   result  = ["cat sand dog", "cats and dog"]
	   current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	                         i

		std::string str = s.substr(start, i - start + 1);

		str is now "catsanddo"

		does "catsanddo" exist as a word in worddict?
			No! then i++.


	   result  = ["cat sand dog", "cats and dog"]
	   current = [""]
	    start = 0;
	     |
	     |____
	         |
	         v
	    s = "c a t s a n d d o g"
	         0 1 2 3 4 5 6 7 8 9
	                           i

		std::string str = s.substr(start, i - start + 1);

		str is now "catsanddog"

		does "catsanddog" exist as a word in worddict?
			No! then i++.


		We've come to the end, return to main function.
		Return vector "results" which is now:
			result = ["cat sand dog", "cats and dog"]

*/

/* Time  Beats: 100% */
/* Space Beats: 85.88% */

/* Time  Complexity: O((s.length)^2 * wordDict.length) */
/* Space Complexity: O(s.length()) */
class Solution{
public:
	std::vector<std::string> wordBreak(std::string s, std::vector<std::string>& wordDict)
	{
		std::vector<std::string> results;
		std::vector<std::string> current;

		backtracking(s, wordDict, 0, current, results);

		return results;
	}

	void backtracking(std::string& s,
	                  std::vector<std::string>& wordDict,
					  int start,
					  std::vector<std::string>& current,
					  std::vector<std::string>& results)
	{
		// If such sentence exist
		if (start >= s.length())
		{
			std::string tmp;

			for (std::string& x : current)
			{
				tmp += x;
				tmp += " ";
			}
			
			// Removing trailing whitespace character
			tmp.pop_back();

			// Store in results
			results.push_back(tmp);

			return;
		}

		for (int i = start; i < s.length(); i++)
		{
			std::string str = s.substr(start, i - start + 1);

			for(std::string& word : wordDict)
			{
				if(word == str)
				{
					current.push_back(str);
					backtracking(s, wordDict, i + 1, current, results);
					current.pop_back();
					break;
				}
			}
		}

	}
};
