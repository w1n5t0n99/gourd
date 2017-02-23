#pragma once
#include <cinttypes>
#include <array>
#include <random>
#include <assert.h>


class TestSkipList
{
public:
	TestSkipList() : size_(0), nodes_{}, prev_nodes_{}, values_{}
	{
		nodes_[KRoot_Index].height = KMax_Height;
		for (int i = 0; i < KMax_Height; ++i)
		{
			nodes_[KRoot_Index].next[i] = KTombstone;
			prev_nodes_[0][i] = KTombstone;
		}
	}

	void Insert(int data)
	{
		// 0 reserved for sentinel value
		// and 0xffff reserved for tombstone
		assert(size_ < KMax_Size - 2);

		auto node_index = CreateNode();
		values_[node_index] = data;
		InsertNode(node_index, KRoot_Index, 0);
	}

	bool Find(int value)
	{
		if (FindNode(value) == KTombstone)
			return false;
		else
			true;
	}

	bool Remove(int value)
	{
		auto found_index = FindNode(value);
		if (found_index == KTombstone)
			return false;

		auto last_node = size_;
		auto& found_node = nodes_[found_index];
		auto& prev_nodes = prev_nodes_[found_index];
		// prepare for removal
		for (int i = 0; i < KMax_Height; ++i)
		{
			if (found_node.next[i] != KTombstone)
			{
				auto& next_prev_nodes = prev_nodes_[found_node.next[i]];
				next_prev_nodes[i] = prev_nodes[i];
			}
		}

		if (found_index != last_node)
		{
			
			found_node = nodes_[last_node];
			values_[found_index] = std::move(values_[last_node]);
			for (int i = 0; i < KMax_Height; ++i)
			{
				prev_nodes[i] = prev_nodes_[last_node][i];
			}
		}

		//values_[size_].~T();
		values_[last_node] = 0;
		--size_;
		for (int i = 0; i < KMax_Height; ++i)
		{ 
			if (prev_nodes[i] != KTombstone)
			{
				if (nodes_[prev_nodes[i]].next[i] != KTombstone)
				{
					nodes_[prev_nodes[i]].next[i] = found_index;
				}
			}
		}

	}

	size_t Size()
	{
		return size_;
	}

private:

	uint16_t CreateNode()
	{
		int i = 1;
		int toss = 1;

		while (i < KMax_Height && toss > 0)
		{
			++i;
			toss = CoinToss();
		}

		size_t last_index = size_ + 1;
		nodes_[last_index].height = i;

		for (int i = 0; i < KMax_Height; ++i)
		{
			nodes_[last_index].next[i] = KTombstone;
			prev_nodes_[last_index][i] = KTombstone;
		}

		return ++size_;
	}

	void InsertNode(uint16_t node_index, uint16_t cur_node_index, uint8_t level)
	{
		uint16_t right_of_index = KTombstone;
		// nodes cannot be create above the max height
		if (level < nodes_[node_index].height)
			right_of_index = nodes_[cur_node_index].next[level];
		else
			return;

		if (right_of_index != KTombstone && values_[right_of_index] < values_[node_index])
		{
			// we overshot keep moving right
			InsertNode(node_index, right_of_index, level);
		}
		else
		{
			nodes_[cur_node_index].next[level] = node_index;
			nodes_[node_index].next[level] = right_of_index;
			prev_nodes_[node_index][level] = cur_node_index;
			// we have reached not the inserted nodes height yet,
			// check next level
			InsertNode(node_index, 0, ++level);
		}
	}

	uint16_t FindNode(int value)
	{
		auto level = KMax_Height - 1;
		auto cur_index = KRoot_Index;
		auto* root_node = &nodes_[KRoot_Index];

		auto right_of_index = KTombstone;
		while (level > 0)
		{
			right_of_index = nodes_[cur_index].next[level];
			if (right_of_index == KTombstone)
				--level;
			else if (value == values_[right_of_index])
				return right_of_index;
			else if (value < values_[right_of_index])
				--level;
			else
				cur_index = right_of_index;
		}

		return KTombstone;
	}

	int CoinToss()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);

		return dis(gen);
	}

	static const size_t KMax_Size = 64;
	// height = log2(max size)
	static const size_t KMax_Height = 6;
	// null value
	static const uint16_t KTombstone = 0xffff;
	// root node index
	static const uint16_t KRoot_Index = 0;

	struct Node
	{
		uint8_t height;
		uint16_t next[KMax_Height];
	};

	std::array<Node, KMax_Size> nodes_;
	std::array<int, KMax_Size> values_;
	std::array<uint16_t[KMax_Height], KMax_Size> prev_nodes_;

	size_t size_;

	friend void Test(const TestSkipList& sl);
};


