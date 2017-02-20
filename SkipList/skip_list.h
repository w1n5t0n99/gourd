#pragma once
#include <random>
/*
inline int SuperCoinToss()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	return dis(gen);
}

// So we can set the height based on template size argument
// at compile time
template <int x>
struct Log2 { enum { value = 1 + Log2<x / 2>::value }; };

template <> struct Log2<1> { enum { value = 1 }; };

template <typename T, size_t size>
class SkipList
{
public:
	SkipList() : sentinel_(nullptr), nodes_(nullptr), node_values_(nullptr), size_(0)
	{
		// T may not have a default ctor, so we just want to allocate the memory
		node_values_ = reinterpret_cast<T*>(new char[sizeof(T) * size]);
		nodes_ = new Node<KMax_Height>[size];

		assert(nodes_ && node_values_);

		sentinel_ = new Node<KMax_Height>;
		sentinel_->height = KMax_Height;
		for (int i = 0; i < KMax_Height; ++i)
			sentinel_->next[i] = nullptr;

	}

	void Insert(const T& data)
	{
		assert(size_ < KMax_Size);
		Node<KMax_Height>* node = CreateNode();

		InsertNode(node, sentinel_, 0);
	}

private:

	static const size_t KMax_Height = Log2<size>::value;
	static const size_t KMax_Size = size;

	template <size_t max_height>
	struct Node
	{
		size_t height;
		Node* next[max_height];
	};

	void InsertNode(Node<KMax_Height>* node, Node<KMax_Height>* cur_node, size_t level)
	{
		Node<KMax_Height>* right_of_cur_node = nullptr;
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

	Node<KMax_Height>* CreateNode()
	{
		Node<KMax_Height>* node = new Node<KMax_Height>;
		int i = 1;
		int toss = 1;
		while (i < KMax_Height && toss > 0)
		{
			++i;
			toss = SuperCoinToss();
		}

		node->height = i;
		for (int i = 0; i < KMax_Height; ++i)
			node->next[i] = nullptr;

		return node;
	}

	Node<KMax_Height>* nodes_;
	T* node_values_;

	Node<KMax_Height>* sentinel_;
	size_t size_;

	friend void TestSkipList(const SkipList<T, size>& sl);
};

*/