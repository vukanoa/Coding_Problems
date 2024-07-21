#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    355) Design Twitter
    ===========================

    ============
    Description:
    ============

    Design a simplified version of Twitter where users can post tweets,
    follow/unfollow another user, and is able to see the 10 most recent tweets
    in the user's news feed.

    Implement the Twitter class:

        + Twitter() Initializes your twitter object.

        + void postTweet(int userId, int tweetId) Composes a new tweet with ID
          tweetId by the user userId. Each call to this function will be made
          with a unique tweetId.

        + List<Integer> getNewsFeed(int userId) Retrieves the 10 most recent
          tweet IDs in the user's news feed. Each item in the news feed must be
          posted by users who the user followed or by the user themself. Tweets
          must be ordered from most recent to least recent.

        + void follow(int followerId, int followeeId) The user with ID
          followerId started following the user with ID followeeId.

        + void unfollow(int followerId, int followeeId) The user with ID
          followerId started unfollowing the user with ID followeeId.


    ===============================
    CLASS:
    class Twitter {
    public:
        Twitter() {

        }

        void postTweet(int userId, int tweetId) {

        }

        vector<int> getNewsFeed(int userId) {

        }

        void follow(int followerId, int followeeId) {

        }

        void unfollow(int followerId, int followeeId) {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Example 1:

    Input
    ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet",
    "getNewsFeed", "unfollow", "getNewsFeed"]

    [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]

    Output
    [null, null, [5], null, null, [6, 5], null, [5]]

    Explanation
    Twitter twitter = new Twitter();
    twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
    twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
    twitter.follow(1, 2);    // User 1 follows user 2.
    twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
    twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
    twitter.unfollow(1, 2);  // User 1 unfollows user 2.
    twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.


    *** Constraints ***
    1 <= userId, followerId, followeeId <= 500
    0 <= tweetId <= 10^4
    All the tweets have unique IDs.
    At most 3 * 10^4 calls will be made to postTweet, getNewsFeed, follow, and unfollow.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   7.03% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Twitter {
public:
    Twitter()
        : time(1)
    {
    }

    void postTweet(int userId, int tweetId)
    {
        max_heap_tweets.push( {time++, userId, tweetId} );
    }

    vector<int> getNewsFeed(int userId)
    {
        vector<int> most_recent_ten_or_less_tweets;
        priority_queue<vector<int>, vector<vector<int>>> tweets_copy = max_heap_tweets;

        int taken_tweets = 0;
        while ( ! tweets_copy.empty() && taken_tweets < 10)
        {
            auto top = tweets_copy.top();
            tweets_copy.pop();

            int posted_at_time = top[0];
            int posted_by_user = top[1];
            int posted_tweetId = top[2];

            // If it's his own tweet or a tweet of one of the people he follows
            if (posted_by_user == userId)
            {
                most_recent_ten_or_less_tweets.push_back(posted_tweetId);
                taken_tweets++;
            }
            else if (umap_user_follows.find(userId) != umap_user_follows.end()
                     &&
                     umap_user_follows[userId].count(posted_by_user))
            {
                most_recent_ten_or_less_tweets.push_back(posted_tweetId);
                taken_tweets++;
            }
        }

        return most_recent_ten_or_less_tweets;
    }

    void follow(int followerId, int followeeId)
    {
        if (umap_user_follows.find(followerId) == umap_user_follows.end()) // Doesn't exist in HashMap
        {
            unordered_set<int> uset;
            uset.insert(followeeId);

            umap_user_follows.insert( {followerId, uset} );
        }
        else
            umap_user_follows[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId)
    {
        if (umap_user_follows.find(followerId) == umap_user_follows.end()) // Doesn't exist in HashMap
            return;

        umap_user_follows[followerId].erase(followeeId); // If it doesn't exist - Do nothing
    }

private:
    unordered_map<int, unordered_set<int>> umap_user_follows;
    std::priority_queue<vector<int>, vector<vector<int>>> max_heap_tweets;

    int time;
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
