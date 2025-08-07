/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    2456) Most Popular Video Creator
    ================================

    ============
    Description:
    ============

    You are given two string arrays creators and ids, and an integer array
    views, all of length n. The ith video on a platform was created by
    creators[i], has an id of ids[i], and has views[i] views.

    The popularity of a creator is the sum of the number of views on all of
    the creator's videos. Find the creator with the highest popularity and the
    id of their most viewed video.

        + If multiple creators have the highest popularity, find all of them.

        + If multiple videos have the highest view count for a creator, find
          the lexicographically smallest id.

    Return a 2D array of strings answer where answer[i] = [creatorsi, idi]
    means that creatorsi has the highest popularity and idi is the id of their
    most popular video. The answer can be returned in any order.

    =====
    Note: It is possible for different videos to have the same id, meaning that
          ids do not uniquely identify a video. For example, two videos with
          the same ID are considered as distinct videos with their own
          viewcount.
    =====

    =======================================================================================================================
    FUNCTION: vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views);
    =======================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: creators = ["alice","bob","alice","chris"], ids = ["one","two","three","four"], views = [5,10,5,4]
    Output: [["alice","one"],["bob","two"]]
    Explanation:
    The popularity of alice is 5 + 5 = 10.
    The popularity of bob is 10.
    The popularity of chris is 4.
    alice and bob are the most popular creators.
    For bob, the video with the highest view count is "two".
    For alice, the videos with the highest view count are "one" and "three".
    Since "one" is lexicographically smaller than "three", it is included in
    the answer.

    --- Example 2 ---
    Input: creators = ["alice","alice","alice"], ids = ["a","b","c"], views = [1,2,2]
    Output: [["alice","b"]]
    Explanation:
    The videos with id "b" and "c" have the highest view count.
    Since "b" is lexicographically smaller than "c", it is included in the answer.


    *** Constraints ***
    n == creators.length == ids.length == views.length
    1 <= n <= 10^5
    1 <= creators[i].length, ids[i].length <= 5
    creators[i] and ids[i] consist only of lowercase English letters.
    0 <= views[i] <= 10^5

*/

#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.32% */
/* Space Beats: 46.54% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
private:
    static bool compare_videos_by_views_then_id(const pair<int, string>& video1, const pair<int, string>& video2)
    {
        if (video1.first != video2.first)
            return video1.first > video2.first; // Higher views first

        
        return video1.second < video2.second; // Lexicographically smaller ID
    }

public:
    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) 
    {
        const int N = ids.size();
        vector<vector<string>> result;

        map<string, vector<pair<int, string>>> map_creator_to_videos;
        map<string, long long> map_creator_to_total_views;

        for (int i = 0; i < N; i++)
        {
            map_creator_to_total_views[creators[i]] += views[i];
            map_creator_to_videos[creators[i]].push_back( {views[i], ids[i]} ); 
        }

        long long max_popularity = 0;
        for (const auto& it : map_creator_to_total_views)
        {
            long long curr_popularity = it.second;

            max_popularity = max(max_popularity, curr_popularity);
        }

        for (const auto& it : map_creator_to_total_views)
        {
            string creator       = it.first;
            long long popularity = it.second;

            if (popularity == max_popularity)
            {
                // Sort all the videos of the current creator
                sort(map_creator_to_videos[creator].begin(), map_creator_to_videos[creator].end(), compare_videos_by_views_then_id);

                string most_viewed = map_creator_to_videos[creator][0].second;
                result.push_back( {creator, most_viewed} );
            }
        }

        return result;
    }
};
