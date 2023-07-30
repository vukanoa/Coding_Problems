#include <iostream>

/*
	***************
	*** PREMIUM ***
	***************
*/

/*
	============
	=== HARD ===
	============

	===========================
	269) Alien Dictionary
	===========================

	============
	Description:
	============

	There is a new alien language that uses the English alphabet. However, the
	order among the letters is unknown to you.

	You are given a list of strings words from the alien language's dictionary,
	where the strings in words are sorted lexicographically by the rules of
	this new language.

	Return a string of the unique letters in the new alien language sorted in
	lexicographically increasing order by the new language's rules. If there is
	no solution, return "". If there are multiple solutions, return any of
	them.

	A string s is lexicographically smaller than a string t if at the first
	letter where they differ, the letter in s comes before the letter in t in
	the alien language. If the first min(s.length, t.length) letters are the
	same, then s is smaller if and only if s.length < t.length.

	===================================================
	FUNCTION: string alienOrder(vector<string> &words);
	===================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: words = ["wrt", "wrf", "er", "ett", "rftt"]
	Output: "wertf"

	--- Example 2 ---
	<++>

	--- Example 3 ---
	<++>

	*** Constraints ***
	<++>

*/


/*
	------------
	--- IDEA ---
	------------

	Let's think about the basics - How are we going to sort these two words:
		["apple", "banana"]
	
	We're going to look at the first character of each words and we'll see that
	they are different and we know that a < b(that's how ordering works in
	english) therefore 'a' comes first in the ordering, before 'b'.

	What about this example:
		["apple", "ape"]
	
	When we look at their first character, they are the same, so we still don't
	know how to sort them. Now we look their 2nd character and they are:
		'p' and 'p'
	That doesn't help us either. We shall continue:
	Now there are 'p' and 'e', respectively, which means that 'p' comes before
	'e' since we're told that the input we're given is already sorted
	lexicographically in this alien letter system.

	There is one edge-case:
		if we're given two words where they have the exact same prefix and the
		the shorter word is a prefix of the longer word then:
			Smaller word is always going to come first in the ordering.

		Example:
			["ape", "apes"]
	
	However if we see the opposite is true, meaning the longer word comes
	before the shorter one, then that means that the input is invalid and we
	shall return an empty string as a result.


	Let's use the given Example:
	
	Input: words = ["wrt", 
	                "wrf", 
	                "er",
	                "ett",
					"rftt"]

	Output: "wertf"

	
	Worst are in sorted order, so how is it determined, for the first two words
	that they are indeed in the sorted order?

	How is it determined that "wrt" must come before "wrf"?
		It must be based on the first different character. That's what
		lexicographically ordered means.
	
	So let's just go and for every pair of words, let's go character by
	character and find the first different character and see what kind of of
	information that gives us.

	Let's look at the first two words:
		1. "wrt"
		2. "wrf

		First character is exactly the same. Same goes for second character as
		well. But the third one differs.
		't' comes before 'f'.

		So that must mean that in the Alien alphabet 't' comes before 'f'.
		(In regular English this isn't true)

		So let's just keep track of that:
			t -> f    // 't' comes before 'f'
	
	Let's look at the next two words:
		2. "wrf"
		3. "er"

		We can immediately see(the very first character) that there is already
		a difference.

		Since we know they are sorted based on Alien lexicographical order, we
		can say that:
			w -> e    // 'w' comes before 't'

		Who knows if there are some characters between 'w' and 'e', we only
		know that 'w' comes before 'e'.

	So, currently, our "map" looks like this:
			t -> f    // 't' comes before 'f'
			w -> e    // 'w' comes before 'e'

	Let's keep going.

	Let's look at the next pair of words:
		3. "er"
		4. "ett"

		First one is the same. Second one differs. That means that:
			r -> t    // 'r' comes before 't'

	So our "map" looks like this now:
			t -> f    // 't' comes before 'f'
			w -> e    // 'w' comes before 'e'
			r -> t    // 'r' comes before 't'
	
	It's obvious that we could "merge" 1st and 3rd case into one. Like this:
			r -> t -> f   // 'r' comes before 't' and 't' comes before 'f'
			w -> e        // 'w' comes before 'e'
	
	Let's look at the next pair of words:
		4. "ett"
		5. "rftt"

		Immediately we can see that first characters differ. We can see that
		'e' comes before 'r'.

	Now our map looks like this:
			r -> t -> f   // 'r' comes before 't' and 't' comes before 'f'
			w -> e        // 'w' comes before 't'
			e -> r        // 'e' comes before 'r'
	
	We can see that we can "merge" 2nd and 3rd into:
			r -> t -> f   // 'r' comes before 't' and 't' comes before 'f'
			w -> e -> r   // 'w' comes before 'e' and 'e' comes before 'r'
	
	We can merge this even further into:
			w -> e -> r -> t -> f   // 'w' comes before 't' and
			                        // 'e' comes before 'r' and
	                                // 'r' comes before 't' and
	                                // 't' comes before 'f'
	
	And that is exactly the result we should return.

	Once you recognize that you can use those relationships of characters in
	the relative order of those characters to build the graph, this problem
	becomes doable.

	Now we just have to traverse this Graphs. However, in this example it's
	pretty straightforward, but that doesn't have to be the case.

	There are a lot of different ways that this Graph can be represented and
	traversing the Graph itself is not super-intuitive and there are multiple
	ways to do it.

	You can do a either: BFS or DFS

	I think DFS is a lot easier to code up.

	So let's change our previous Graph from:
	    w -> e -> r -> t -> f

		to

	    w -> e -> r -> t -> f
	    ^                   |
	    |                   |
	    ---------------------
	
	So now if we were traversing this Graph - What the heck would the relative
	order be?

	    It's not that this has multiple solutions, it's that this is INVALID.
	

	Or what if we had this:

	    w -> e -> r -> t -> f
	    ^    |
	    |    |
	    ------
	
	Do you see how that's a contradiction?
	We can't have opposite rules. It's basically as if we had an input list of
	words that was something like this:
		["we", "ee", "we"]
	
	How could we say that the list above is sorted then? We can't. That's
	invalid. In that case we should return an empty string "",  because there
	is not real solution.


	Let's look at another variation of our original Example. What is we didn't
	have the last word in the "words" list?

	Input: words = ["wrt", 
	                "wrf", 
	                "er",
	                "ett"]

	In that case we would not have the final "merge" in our "map". We would
	have:
			r -> t -> f   // 'r' comes before 't' and 't' comes before 'f'
			w -> e        // 'w' comes before 'e'
	
	We have two separate DAGs. But there is NO contradiction here. It's just
	that now we know that there are multiple solutions.

	We could say that the relative order is either: "wertf" or "rtfwe".

	Or we could even do a BFS and have: "rwtef" or "wretf"

	All that really matters is that 'w' comes before 'e', 'r' comes before 't'
	and 't' comes before 'f'. Everything else is arbitrary.

	
	So at this point you might say:"Let's just start at the beginning of each
	of these components and then just go through them, say:
		w -> e -> r -> t -> f
	
	and just build an output string like that, but I'll show you one reason
	why that's actually not going to work.

	Example:
		words = ["a",
		         "ba",
		         "bc",
				 "c"]
	
	Our Graph would look like this:

			--------------
			|            |
			|            v
			a --> b ---> c
	
	This is a perfectly valid Graph.
	What's one valid order of this Graph?
		"abc"
	
	Let's do a DFS on this.

	First, we visit 'a', then let's say we went to 'c' first, then we a 'c' in
	our output, then we go back to 'a' and we continue through 'b', so then
	we got this:
		"acb"
	
	which is NOT valid.

	So if we are doing a DFS from the beginning how should we know which path
	should we traverse first?

	The answer is - We don't really have a good way of knowing that if we're
	doing this with DFS.

	But, there is a workaround solution to that - The Solution is Postorder DFS

	In reality, yes, we are going to start with 'a', but we're not going to
	keep adding it to our output yet. We're going to be adding 'a' at last.

	Let's traverse it again:
	We go from 'a' to 'c' again, then 'c' being the last one should be put
	into our output string, then we go back to 'a', then continu through 'b'
	and then go to 'c' where we can see that we've visited the 'c' again(we'll
	develop a way of knowing that by using an hash map) so we put 'b' and then
	get back to 'a' to print that.

	So our output string now looks like: "cba". So that is not what we need,
	therefore we should reverse the string and then return it.

	That way it's completely valid.

	It's important to emphasize the difference between "visited" and "currently
	in our traverse path".

	We first got from 'a' to 'c', then back to 'a' and then to 'b' and then
	from 'b' to 'c'. There is no loop because 'c' is not in our current
	traverse path, because it was already processed. That doesn't mean that
	there is a loop in our graph.

	So we have to keep track of 2 things:
		1. Visited
		2. Current traverse path
	
	We're going to do that using a hash map.

	Everytime we visit a node, we're going to say it's added to the map, but
	we're going to give it a "false" value in the map and once it's in the
	current path, then we're going to give it a value of "true".

*/

/* Time  Complexity: O(total num of letters in words) */
/* Space Complexity: O(total num of letters in words) */
class Solution{
public:
	std::string alienOrder(std::vector<std::string>& words)
	{
		std::unordered_map<har, std::unordered_set<char>> adj;
		for (const std::string& word : words)
		{
			for (char& c : word)
			{
				adj[c] = unordered_set<char>();
			}
		}

		for (int i = 0; i < word.size() - 1; i++)
		{
			std::string w1 = words[i];
			std::string w2 = words[i + 1];

			int min_len = std::min(w1.length(), w2.length());

			if (w1.length() > w2.length() && w1.substr(0, min_len) == w2.substr(0, min_len))
				return "";

			for (int j = 0; j < min_len; j++)
			{
				if (w1[j] != w2[j])
				{
					adj[w1[j]].insert(w2[j]);
					break;
				}
			}
		}

		std::unordered_map<char, bool> visit;
		std::string result;

		// Postorder DFS
		function<bool(char)> dfs = [&](char c)
		{
			if (visit.find(c) != visit.end())
				return visit[c];

			visit[c] = true;
			for (char nei : adj[c])
			{
				if (dfs(nei))
					return true;
			}

			visit[c] = false;
			result.push_back(c);

			return false;
		}

		for (auto& entry : adj)
		{
			if (dfs(entry.first))
				return "";
		}

		std::reverse(res.begin, res.end());

		return res;
	}
};
