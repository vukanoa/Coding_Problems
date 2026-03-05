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

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.94% */
/* Space Beats: 86.38% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
static int my_time = 0;

class Twitter {
public:
    Twitter()
    {

    }
    
    void postTweet(int userId, int tweetId)
    {
        user_to_tweets[userId].push_back( {my_time++, tweetId} ); // O(1)
    }
    
    vector<int> getNewsFeed(int userId)
    {
        priority_queue<pair<int,int>> max_heap;
        for (const auto& [time_posted, tweetId] : user_to_tweets[userId])
        {
            max_heap.push( {time_posted, tweetId} );
        }

        // O(N * logN) (entire block)
        for (const auto& folowee : user_to_folowees[userId])
        {
            for (const auto& [time_posted, tweetId] : user_to_tweets[folowee])
            {
                max_heap.push( {time_posted, tweetId} ); // O(logN)
            }
        }

        vector<int> news_feed;

        int tweet_count = 0;
        while ( ! max_heap.empty() && tweet_count < 10)
        {
            auto [time_posted, tweetId] = max_heap.top();
            news_feed.push_back(tweetId);
            max_heap.pop(); // O(logN)

            tweet_count++;
        }

        return news_feed;
    }

    void follow(int followerId, int followeeId)
    {
        user_to_folowees[followerId].insert(followeeId); // O(1)
    }
    
    void unfollow(int followerId, int followeeId)
    {
        user_to_folowees[followerId].erase(followeeId); // O(1)
    }

private:
    unordered_map<int, vector<pair<int,int>>> user_to_tweets;
    unordered_map<int, unordered_set<int>> user_to_folowees;
};


/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */




/*
    ------------
    --- IDEA ---
    ------------

    This one does NOT push ALL of the tweets of all of the followees. Instead
    it pushes, to max_heap, only one per followee and then each time the tweet
    is pushed in "news_feed", it pushes its earlier tweet to max_heap if it has
    one.

    This way, we're, at worst, going to push 1 tweet per followee or at best
    only <= 10 tweets just enough to populate our news_feed.

*/

/* Time  Beats: 93.94% */
/* Space Beats: 64.28% */

/* Time  Complexity: O((10 + F) * logF) */
/* Space Complexity: O(F)               */
class Twitter_Optimal {
public:
    Twitter_Optimal ()
    {

    }

    void postTweet(int userId, int tweetId)
    {
        user_to_tweets[userId].push_back( {my_time++, tweetId} ); // O(1)
    }
    
    vector<int> getNewsFeed(int userId)
    {
        vector<int> news_feed;

        struct Node {
            int time_posted;
            int tweetId;
            int userId;
            int internal_tweet_idx;

            Node (int time_posted, int tweetId, int userId, int internal_tweet_idx)
                : time_posted(time_posted), tweetId(tweetId), userId(userId), internal_tweet_idx(internal_tweet_idx)
            {

            }
        };

        auto comparator = [](const Node* a, const Node* b) {
            return a->time_posted < b->time_posted;
        };

        priority_queue<Node*, vector<Node*>, decltype(comparator)> max_heap(comparator);

        if ( ! user_to_tweets[userId].empty())
        {
            auto [time_posted, tweetId] = user_to_tweets[userId].back();
            int internal_tweet_idx = user_to_tweets[userId].size() - 1;

            max_heap.push( new Node(time_posted, tweetId, userId, internal_tweet_idx) );
        }

        for (const auto& followee : user_to_folowees[userId])
        {
            if ( ! user_to_tweets[followee].empty())
            {
                auto [time_posted, tweetId] = user_to_tweets[followee].back();
                int internal_tweet_idx = user_to_tweets[followee].size() - 1;

                max_heap.push( new Node(time_posted, tweetId, followee, internal_tweet_idx) );
            }
        }

        while ( ! max_heap.empty() && news_feed.size() < 10)
        {
            Node* node = max_heap.top();
            max_heap.pop();

            int prev_internal_tweet_idx = node->internal_tweet_idx - 1;
            if (prev_internal_tweet_idx >= 0)
            {
                auto [time_posted, tweetId] = user_to_tweets[node->userId][prev_internal_tweet_idx];
                max_heap.push( new Node(time_posted, tweetId, node->userId, prev_internal_tweet_idx) );
            }

            news_feed.push_back(node->tweetId);

            delete node; // To prevent Memory Leak
        }

        while ( ! max_heap.empty())
        {
            delete max_heap.top();
            max_heap.pop();
        }

        return news_feed;
    }

    void follow(int followerId, int followeeId)
    {
        user_to_folowees[followerId].insert(followeeId); // O(1)
    }
    
    void unfollow(int followerId, int followeeId)
    {
        user_to_folowees[followerId].erase(followeeId); // O(1)
    }

private:
    unordered_map<int, vector<pair<int,int>>> user_to_tweets;
    unordered_map<int, unordered_set<int>> user_to_folowees;
};




/*
    ------------
    --- IDEA ---
    ------------

    Important note:

    This version only keeps the last 10 tweets per user, so getNewsFeed never
    looks at more than 10 per followee.

    That INDEED makes it fast for small F (number of followees).

    However the truly optimal approach is the above "k-way merge" with a
    max-heap.

    That way, each user can have any number of tweets, and getNewsFeed looks
    ONLY at the NEWEST tweets from each followee using a heap.



    This is fast and memory-efficient only if the contraint it "last 10 tweets
    per user". Otherwise, if a user posts hundreds or thousands of tweets, then
    the heap-based "k-way merge" is strictly better.

*/

/* Time  Beats: 38.76% */
/* Space Beats: 43.93% */

/* Time  Complexity: O(F) */
/* Space Complexity: O(F) */
class Twitter_Most_Optimal {
public:
    Twitter_Most_Optimal ()
    {

    }

    void postTweet(int userId, int tweetId)
    {
        if (user_to_tweets[userId].size() >= 10)
            user_to_tweets[userId].pop_front(); // Keep only last 10 tweets

        user_to_tweets[userId].push_back( {my_time++, tweetId} ); // O(1)
    }

    vector<int> getNewsFeed(int userId)
    {
        vector<int> news_feed;

        user_to_folowees[userId].insert(userId); // Always follow self

        // Keep iterators for reversed deques
        unordered_map<int, deque<pair<int,int>>::reverse_iterator> iterators;
        unordered_map<int, deque<pair<int,int>>::reverse_iterator> iterators_end;
        unordered_map<int, pair<int,int>> current_tweets;

        for (int followee : user_to_folowees[userId])
        {
            if ( ! user_to_tweets[followee].empty())
            {
                iterators[followee] = user_to_tweets[followee].rbegin();
                iterators_end[followee] = user_to_tweets[followee].rend();
                current_tweets[followee] = *iterators[followee];
            }
        }

        while (news_feed.size() < 10)
        {
            int best_time = -1;
            int best_followee = -1;

            for (const auto& [followee, tweet_info] : current_tweets)
            {
                if (tweet_info.first > best_time)
                {
                    best_time = tweet_info.first;
                    best_followee = followee;
                }
            }

            if (best_followee == -1)
                break;

            news_feed.push_back(current_tweets[best_followee].second);

            iterators[best_followee]++;

            if (iterators[best_followee] != iterators_end[best_followee])
                current_tweets[best_followee] = *iterators[best_followee];
            else
                current_tweets[best_followee] = {-1, -1}; // Exhausted
        }

        return news_feed;
    }

    void follow(int followerId, int followeeId)
    {
        user_to_folowees[followerId].insert(followeeId);
        user_to_folowees[followerId].insert(followerId); // Follow self
    }

    void unfollow(int followerId, int followeeId)
    {
        if (followerId == followeeId)
            return;

        user_to_folowees[followerId].erase(followeeId);
    }

private:
    unordered_map<int, deque<pair<int,int>>> user_to_tweets; // Stores ONLY LAST 10 tweets per user
    unordered_map<int, unordered_set<int>> user_to_folowees;
};
