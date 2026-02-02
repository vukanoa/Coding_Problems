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

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

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

    You need to know:
        + How to use a HashMap
        + How to use a Map(i.e. sorted map which is a Red-Black tree)
        + How to user iterators
        + How to do upper_bound on a container such a sorted Map.
        + How to manipulate iterators, i.e. prev(iter).

    So it's good to go through this Solution as well.

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

/* Time  Beats: 43.54% */
/* Space Beats: 14.59% */

/* Time  Complexity: O(logN)  */ // N <==> Total number of values
/* Space Complexity: O(M * N) */ // M <==> Total number of keys
class TimeMap {
public:
    TimeMap() {
        
    }
    
    // O(1)
    void set(string key, string value, int timestamp)
    {
        umap[key].insert( {timestamp, value} );
    }
    
    // O(logN)
    string get(string key, int timestamp)
    {
        /* Upper Bound */
        auto iter = umap[key].upper_bound(timestamp); // O(logN)

        return iter == umap[key].begin() ? "" : prev(iter)->second;
    }

private:
    unordered_map<string, map<int,string>> umap;
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

    upper_bound is implemented using a Binary Search.

*/

/* Time  Beats: 77.38% */
/* Space Beats: 44.62% */

/* Time  Complexity: O(logN)  */ // N <==> Total number of values
/* Space Complexity: O(M * N) */ // M <==> Total number of keys
class TimeMap_Vector {
private:
    struct CompareByTimestamp {
        const bool operator()(const pair<int, string>& a,
                              const pair<int, string>& b) const
        {
            return a.first < b.first;
        }
    };

public:

    TimeMap_Vector() {}

    // O(1)
    void set(string key, string value, int timestamp)
    {
        umap[key].push_back( {timestamp, value} );
    }

    // O(logN) (entire block)
    string get(string key, int timestamp)
    {
        // O(logN)
        auto iter = upper_bound(begin(umap[key]),          // Start
                                end(umap[key]),            // End
                                make_pair(timestamp, ""),  // Target_pair
                                CompareByTimestamp{});     // Comparator

        return iter == umap[key].begin() ? "" : prev(iter)->second;
    }

private:
    unordered_map<string, vector<pair<int, string>>> umap;
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is EQUVALENT to the above one TimeMap_Vector, however here I am
    implementing my own "upper_bound" instead of using the C++'s built-in one.

*/

/* Time  Beats: 87.26% */
/* Space Beats: 80.45% */

/* Time  Complexity: O(logN)  */ // N <==> Total number of values
/* Space Complexity: O(M * N) */ // M <==> Total number of keys
class TimeMap_Vector_Custom_Upper_Bound {
public:

    TimeMap_Vector_Custom_Upper_Bound() {}

    // O(1)
    void set(string key, string value, int timestamp)
    {
        umap[key].push_back( {timestamp, value} );
    }

    // O(logN) (entire block)
    string get(string key, int timestamp)
    {
        vector<pair<int,string>>& vec_of_pairs = umap[key];

        /* Upper Bound */
        // O(logN)
        int idx = my_upper_bound(vec_of_pairs, timestamp);

        return idx <= 0 ? "" : vec_of_pairs[idx - 1].second;
    }

private:
    unordered_map<string, vector<pair<int, string>>> umap;

    int my_upper_bound(vector<pair<int,string>>& vec_of_pairs, int& target)
    {
        /*
           In order to make an "upper_bound" implementation, we can use our
           "lower_bound" implementation by simply passing "target + 1" as a 
           target in "lower_bound".

           Think about it. If we have a "lower_bound" implementation that will
           return first GREATER THAN OR EQUALS(!!) TO "target", then why not
           just use that to get the "FIRST STRICTLY GREATER" than some value?

        */
        return my_lower_bound(vec_of_pairs, target + 1);
    }

    int my_lower_bound(vector<pair<int,string>>& vec_of_pairs, int target)
    {
        if (vec_of_pairs.empty())
            return -1;

        const int N = vec_of_pairs.size();

        int low  = 0;
        int high = N; // Because idx "N" can be a VALID answer
        while (low < high)
        {
            int mid = low + (high - low) / 2;

            /*
                vec_of_pairsmid]   <==> {timestamp, str_value}
                
                vec_of_pairs.first  <==> timestamp
                vec_of_pairs.second <==> str_value
            */
            if (target > vec_of_pairs[mid].first)
                low = mid + 1; // Indices from [low, mid], inclusive, are NOT
                               // the answer, therefore cut them off.
            else
                high = mid;    // "mid" still MIGHT be the answer
        }

        return low; // Or "high" it does NOT matter
    }
};
