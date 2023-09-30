#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============

	===============================
	981) Time Based Key-Value Store
	===============================

	============
	Description:
	============

	Design a time-based key-value data structure that can store multiple values
	for the same key at different time stamps and retrieve the key's value at a
		certain timestamp.

	Implement the TimeMap class:

		- TimeMap() Initializes the object of the data structure. 

		- void set(String key, String value, int timestamp) Stores the key key
		  with the value value at the given time timestamp.

		- String get(String key, int timestamp) Returns a value such that set
		  was called previously, with timestamp_prev <= timestamp. If there are
		  multiple such values, it returns the value associated with the
		  largest timestamp_prev. If there are no values, it returns "".


	===============================
	CLASS:
	class TimeMap {
	public:
		TimeMap()
		{}

		void set(string key, string value, int timestamp)
		{}

		string get(string key, int timestamp)
		{}
	};

	// Your TimeMap object will be instantiated and called as such:
	// TimeMap* obj = new TimeMap();
	// obj->set(key,value,timestamp);
	// string param_2 = obj->get(key,timestamp);
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input
	["TimeMap", "set", "get", "get", "set", "get", "get"]
	[[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4],
	["foo", 4], ["foo", 5]]

	Output:
	[null, null, "bar", "bar", null, "bar2", "bar2"]

	Explanation
	TimeMap timeMap = new TimeMap();

	timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along
	                                  with timestamp = 1.

	timeMap.get("foo", 1);         // return "bar"

	timeMap.get("foo", 3);         // return "bar", since there is no value
	                                  corresponding to foo at timestamp 3 and
	                                  timestamp 2, then the only value is at
	                                  timestamp 1 is "bar".

	timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2"
	                                  along with timestamp = 4.

	timeMap.get("foo", 4);         // return "bar2"

	timeMap.get("foo", 5);         // return "bar2"


	*** Constraints ***
	1 <= key.length, value.length <= 100
	key and value consist of lowercase English letters and digits.
	1 <= timestamp <= 107
	All the timestamps timestamp of set are strictly increasing.
	At most 2 * 105 calls will be made to set and get.

*/

/*
	------------
	--- IDEA ---
	------------

	NOTE: We don't have to do it this way since in the "constraints" we're told
	that:
		"All the timestamps timestamp of set are strictly increasing."
	
	Which means that we don't have to keep them sorted manually by having a
	Map(Red-Black tree) since it will be sorted anyway.

	However, I wanted to have this implementation as well because you must show
	that you know how to use both unordered_map and map in C++ and you have to
	know how to use iterators in the right way.

	So it's good to go through this Solution as well.

	It's important to know how both "unordered_map" and "map" work.

	First, "unordered_map" is a basic Hash Map. It hashes the keys to give you
	access to desired values.

	On the other hand, "map" is a BST, implemented as a Red-Black Tree,
	therefore all the elements in it are sorted by the key(if a key is of
	primitive type, otherwise you have to provide the comparator).

	So what we have here is this:

	    Unordered Map
	     (Hash Map)
	|    Key  :           Value             |
	+---------------------------------------|
	|         |                             |
	|         |             Map             |
	|         |       (Sorted by keys)      |
	|         |      |  Key  :  Value |     |
    |         |      +----------------|     |
    |                |   10  : "high" |     |
    |  "love" :      +----------------|     |
    |                |   20  : "low"  |     |
    |         |      +----------------|     |
    |         |      |      ...       |     |
    |         |      +----------------|     |
	+---------------------------------------|
	|         |                             |
	|         |             Map             |
	|         |       (Sorted by keys)      |
	|         |      |  Key  :  Value |     |
    |         |      +----------------|     |
    |                |   1   : "water"|     |
    |  "apex" :      +----------------|     |
    |                |   7   : "fire" |     |
    |         |      +----------------|     |
    |         |      |   55  : "rock" |     |
    |         |      +----------------|     |
	+---------------------------------------|
	|         |                             |
	|         |             Map             |
	|         |       (Sorted by keys)      |
	|         |      |  Key  :  Value |     |
    |         |      +----------------|     |
    |                |   8   :  "sky" |     |
    |  "cake" :      +----------------|     |
    |                |   2   :  "fog" |     |
    |         |      +----------------|     |
    |         |      |      ...       |     |
    |         |      +----------------|     |
	+---------------------------------------|

	
*/

/* Time  Beats: 27.11% */
/* Space Beats: 18.80% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(n) */
class TimeMap {
public:
	TimeMap() {}

	void set(std::string key, std::string value, int timestamp)
	{
		if (umap.count(key) == 0)
			umap[key].insert({timestamp, value});
		else
		{
			if (umap.at(key).count(timestamp) == 0)
				umap[key].insert({timestamp, value});
			else
				umap.at(key).at(timestamp) = value;
		}
	}

	std::string get(std::string key, int timestamp)
	{
		if (umap.count(key) == 0)
			return "";

		if (umap.at(key).find(timestamp) != umap.at(key).end())
			return umap.at(key).at(timestamp);

		// auto it = umap.at(key).rbegin();
		auto it = umap.at(key).lower_bound(timestamp);

		if (it-- != umap.at(key).begin())
			return it->second;

		return "";
	}

private:
	std::unordered_map<std::string, std::map<int, std::string>> umap;
};




/*
	------------
	--- IDEA ---
	------------

	This is a much more elegant way of writing the above Solution. I wanted to
	imeplement both just so you can see the difference and different
	approaches.

*/

/* Time  Beats: 41.42% */
/* Space Beats: 17.05% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(n) */
class TimeMap_Elegant {
public:
	TimeMap_Elegant() {}

	void set(std::string key, std::string value, int timestamp)
	{
		umap[key].insert({ timestamp, value });
	}

	std::string get(std::string key, int timestamp)
	{
		auto it = umap[key].upper_bound(timestamp);

		return it == umap[key].begin() ? "" : std::prev(it)->second;
	}

private:
	std::unordered_map<std::string, std::map<int, std::string>> umap;
};




/*
    ------------
    --- IDEA ---
    ------------

    In the "Constraints" it is explicitly said that:
        "All the timestamps timestamp of set are strictly increasing."

    Thus, we can simplify we Solution, but using only a vector and then we can
    use a Binary Search to Iterate over this vector and find the given
    timestamp or, if it doesn't exist, then return the first lower. If there is
    no any lower, simply return an empty string.

    std::upper_bound is implemented using a Binary Search.

*/

/* Time  Beats: 77.38% */
/* Space Beats: 44.62% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(n) */
class TimeMap_Vector {
public:

    TimeMap_Vector() {}

    void set(std::string key, std::string value, int timestamp)
    {
        umap[key].push_back({ timestamp, value });
    }

    std::string get(std::string key, int timestamp)
    {
        auto it = std::upper_bound(std::begin(umap[key]),
                                   std::end(umap[key]),
                                   std::make_pair(timestamp, ""),
                                   [](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b)
                                     {
                                         return a.first < b.first;
                                     });

        return it == umap[key].begin() ? "" : std::prev(it)->second;
    }

private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> umap;
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, just uses my own Binary Search instead of std's upper_bound.

*/

/* Time  Beats: 56.02% */
/* Space Beats: 41.66% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(n) */
class TimeMap_Vector_My_Binary_Search {
public:

    TimeMap_Vector_My_Binary_Search() {}

    void set(std::string key, std::string value, int timestamp)
    {
        umap[key].push_back({ timestamp, value.empty() ? "" : value});
    }

    std::string get(std::string key, int timestamp)
    {
        if (umap.count(key) == 0)
            return "";

        auto binary_search = [](std::vector<std::pair<int, std::string>>& vec, int timestamp)
                               {
                                   int left  = 0;
                                   int right = vec.size() - 1;
                                   
                                   std::string result = "";
                                   while (left <= right)
                                   {
                                       int mid = left + (right - left) / 2;
                                       if (vec[mid].first <= timestamp)
                                       {
                                           result = vec[mid].second;
                                           left = mid + 1;
                                       }
                                       else
                                           right = mid - 1;
                                   }

                                   return result;
                               };

        return binary_search(umap.at(key), timestamp);
    }

private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> umap;
};


int
main()
{
	// TimeMap                       timeMap;
	// TimeMap_Elegant               timeMap;
	// TimeMap_Vector                timeMap;
    TimeMap_Vector_My_Binary_Search  timeMap;

	std::cout << "\n\t==================================";
	std::cout << "\n\t=== TIME BASED KEY-VALUE STORE ===";
	std::cout << "\n\t==================================\n\n";

	/* Example 1 */
	// timeMap.set("foo", "bar", 1);

	// std::cout << "\n\tString: " << timeMap.get("foo", 1);
	// std::cout << "\n\tString: " << timeMap.get("foo", 3);

	// timeMap.set("foo", "bar2", 4);

	// std::cout << "\n\tString: " << timeMap.get("foo", 4);
	// std::cout << "\n\tString: " << timeMap.get("foo", 5);




	/* Example 2 */
	timeMap.set("love", "high", 10);
	timeMap.set("love", "low", 20);

	std::cout << "\n\tString: " << timeMap.get("love",  5) << "\n" ;
	std::cout << "\n\tString: " << timeMap.get("love", 10) << "\n" ;
	std::cout << "\n\tString: " << timeMap.get("love", 15) << "\n" ;
	std::cout << "\n\tString: " << timeMap.get("love", 20) << "\n" ;
	std::cout << "\n\tString: " << timeMap.get("love", 25) << "\n\n" ;

	return 0;
}
