#include <iostream>
#include <unordered_map>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	146) LRU Cache
	===========================

	============
	Description:
	============

	Design a data structure that follows the constraints of a Least Recently
	Used(LRU) cache.

	Implement the LRUCache class:
		- "LRUCache(int capacity)"
		      Initialize the LRU cache with positive size "capacity".

		- "int get(int key)"
		      Return the value of the "key" if the key exists, otherwise
			  return -1.

		- "void put(int key, int value)"
		      Update the value of the "key" if the "key" exists. Otherwise, add
			  the key-value pair to the cache. If the number of keys exceeds
			  the "capacity" from this operation, evict the least recently used
			  key.

	=====
	Node: The functions "get" and "put" must each run in O(1) average time
	      complexity.
	=====

	===============================
	CLASS:
	class LRUCache{
	public:
		LRUCache(int capacity);
		int get(int key);
		int put(int key, int value);
	};
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:
	["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
	[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]

	Output:
	[null, null, null, 1, null, -1, null, -1, 3, 4]

	Explanation:
	LRUCache lRUCache = new LRUCache(2);
	lRUCache.put(1, 1); // cache is {1=1}
	lRUCache.put(2, 2); // cache is {1=1, 2=2}
	lRUCache.get(1);    // return 1
	lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
	lRUCache.get(2);    // reurns -1 (not found)
	lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
	lRUCache.get(1);    // return -1(not found)
	lRUCache.get(3);    // return 3
	lRUCache.get(4);    // return 4

	*** Constraints ***
	1 <= capacity <= 3000
	0 <= key <= 10^4
	0 <= value <= 10^5
	At most 2 * 10^5 calls will be made to "get" and "put".

*/

// Definition for doubly-linked list.
struct Node {
	int key;
    int val;
    Node *prev;
    Node *next;

    Node(int k, int v): key(k), val(v), prev(nullptr), next(nullptr) {}
};

void print_list(Node* head);


/*
	------------
	--- IDEA ---
	------------

	Since it is said that we need to have an average time Complexity of O(1),
	that strongly indicates that we need to use a Hash Map.

	However, since we're dealing with Least Recently Used items, we need to
	implement it in a way that we know Recency times of using these items and
	we need to update that every time we use "put" or "get" functions.

	So how do we fulfill all these requirements?
	Hash Map + Doubly Linked List.

	First, in the Constructor, we'll assign the given capacity to the capacity
	of our cache(Hash Map).

	Then we'll make 2 dummy nodes: head & tail.
	head's next will point to LRU(Least Recently Used item).
	tail's prev will point to MRU(Most  Recently Used item)

	We'll immediately link head's next to tail and tail's prev to head since
	at the very beginning there are no items(Nodes) in our cache.

	int get(int key):
		If a key doesn't exist:
			return -1;
		else
			Remove that Node(Remember that Node is the value in our Hash Map)
			from the list.

			Insert it again, in the list.(Now at position MRU since we've
			just used it)

			return that node's value.

	void put(int key, int value):
		If a key doesn't exist:
			make a new Node and insert its pointer in the hashmap at cache[key]
				cache[key] = new Node(key, value);

			insert that newly made Node in the list as MRU(at tail->prev, since
			we've just used it).

			Check if by inserting this Node, we've gone out of bounds.

			If we have gone out of bounds then we have to remove the LRU(Least
			Recently Used) Node form the list. (i.e. Remove head's next)
			And remove that key from the hashmap "cache".

		else:
			Remove the Node with that key from the list and then do the same
			as if the key doesn't exist.

			What this does, essentially, is making sure that the Updated key
			(Updated means that the key exists, otherwise we wouldn't be able
			to update it)gets put at MRU position in the list(i.e. tail's prev)


	remove_from_list(struct Node* node) & insert_in_list(struct Node* node)
	are just doing what the name suggest, respectively.

*/


/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class LRUCache{
public:
	struct Node* head;
	struct Node* tail;
	int cache_capacity;
	std::unordered_map<int, struct Node*> cache;

	LRUCache(int capacity)
	{
		cache_capacity = capacity;

		head = new Node(0, 0); // dummy node
		tail = new Node(0, 0); // dummy node
		head->next = tail;
		tail->prev = head;
	}

	int get(int key)
	{
		std::cout << "\tGet: (" << key << ")\n";

		if (cache.find(key) != cache.end())
		{
			remove_from_list(cache.at(key));
			insert_in_list(cache.at(key));

			print_list(head);
			return cache.at(key)->val;
		}

		print_list(head);
		return -1;
	}

	void put(int key, int value)
	{
		std::cout << "\tPut: [" << key << ", " << value << "]\n";

		if (cache.find(key) != cache.end())
			remove_from_list(cache.at(key));

		cache[key] = new Node(key, value);
		insert_in_list(cache.at(key));

		if (cache.size() > cache_capacity)
		{
			// Remove from the list and delete the LRU from the hashmap
			struct Node* lru = head->next;
			remove_from_list(lru);
			cache.erase(lru->key);
		}
		print_list(head);
	}

	void remove_from_list(struct Node* node)
	{
		struct Node* prev_node = node->prev;
		struct Node* next_node = node->next;

		prev_node->next = next_node;
		next_node->prev = prev_node;

		// delete node;
	}

	void insert_in_list(struct Node* node)
	{
		struct Node* prev_node = tail->prev;
		struct Node* next_node = tail;

		prev_node->next = node;
		next_node->prev = node;

		node->next = next_node;
		node->prev = prev_node;
	}
};

bool final_output = false;

void
print_list(Node* head)
{
	if (head->next == nullptr)
	{
		std::cout << "\n\tEmpty!\n\n";
		return;
	}

	struct Node* tmp = head->next;

	if (final_output)
		std::cout << "\n\tList:\n\t\t";
	else
		std::cout << "\n\t\tList:\n\t\t\t";

	while (tmp->next)
	{
		if (tmp->next->next == nullptr) // Last element
		{
			std::cout << "[key: " << tmp->key << ", value: " << tmp->val << "]";
			break;
		}
		else
			std::cout << "[key: " << tmp->key << ", value: " << tmp->val << "] -> ";

		tmp = tmp->next;
	}
	std::cout << "\n\n";
}


int
main()
{
	std::cout << "\n\t=================";
	std::cout << "\n\t=== LRU CACHE ===";
	std::cout << "\n\t=================\n\n";

	/* Example 1 & Solution*/
	LRUCache lRUCache(2);
	lRUCache.put(1, 1); // cache is {1=1}
	lRUCache.put(2, 2); // cache is {1=1, 2=2}
	lRUCache.get(1);    // return 1
	lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
	lRUCache.get(2);    // reurns -1 (not found)
	lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
	lRUCache.get(1);    // return -1(not found)
	lRUCache.get(3);    // return 3
	lRUCache.get(4);    // return 4

	/* Final Output */
	final_output = true;
	std::cout << "\n\t\t --------------------";
	std::cout << "\n\t\t *** FINAL OUTPUT ***";
	std::cout << "\n\t\t --------------------";
	print_list(lRUCache.head);

	return 0;
}
