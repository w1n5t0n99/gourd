#pragma once
#include <random>

int CoinToss();

// So we can set the height based on template size argument
// at compile time
template <int x>
struct Log2 { enum { value = 1 + Log2<x / 2>::value }; };

template <> struct Log2<1> { enum { value = 1 }; };

template <typename T, size_t size>
class SkipList
{
public:
	SkipList() : sentinel_(nullptr), size_(0), max_size(size), max_height(Log2<size>::value)
	{
		// T may not have a default ctor, so we just want to allocate the memory
		nodes_ = static_cast<Node<T, Log2<size>::value>>(new char[sizeof(Node<T, Log2<size>::value>)* size]);
		assert(nodes_);

		sentinel_ = new Node<T, Log2<size>::value>;
		sentinel_->height = max_height;
		for (int i = 0; i < max_height; ++i)
			sentinel_->next[i] = nullptr;
	}

	void Insert(const T& data)
	{
		Node<T, Log2<size>::value>* node = CreateNode();
		node->data = data;

		InsertNode(node, sentinel_, 0);
	}

private:
	template <typename T, size_t max_height>
	struct Node
	{
		T data;
		size_t height;
		Node* next[max_height];
	};

	void InsertNode(Node<T, Log2<size>::value>* node, Node<T, Log2<size>::value>* cur_node, size_t level)
	{
		Node<T, Log2<size>::value>* right_of_cur_node = nullptr;
		// nodes cannot be create above the max height
		if (level < node->height)
			right_of_cur_node = cur_node->next[level];
		else
			return;

		if (right_of_cur_node != nullptr && right_of_cur_node->data < node->data)
		{
			// we overshot keep moving right
			InsertNode(node, right_of_cur_node, level);
		}
		else
		{
			cur_node->next[level] = node;
			node->next[level] = right_of_cur_node;
			// we have reached the inserted nodes height yet,
			// check next level
			InsertNode(node, sentinel_, ++level);
		}		
	}

	Node<T, Log2<size>::value>* CreateNode()
	{
		Node<T, Log2<size>::value>* node = new Node<T, Log2<size>::value>;
		int i = 1;
		int toss = 1;
		while (i < max_height && toss > 0)
		{
			++i;
			toss = CoinToss();
		}

		node->height = i;
		for (int i = 0; i < max_height; ++i)
			node->next[i] = nullptr;

		return node;
	}
	
	const size_t max_height;
	const size_t max_size;

	Node<T, Log2<size>::value>* sentinel_;
	Node<T, Log2<size>::value>* nodes_;
	size_t size_;

	friend void TestSkipList(const SkipList<T, size>& sl);
};



int CoinToss()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	return dis(gen);
}
