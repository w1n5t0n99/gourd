#pragma once
#include <cinttypes>
#include <array>
#include <random>
#include <assert.h>

inline int CoinToss()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	return dis(gen);
}

class TestSkipList
{
public:
	TestSkipList() : size_(0), nodes_{}, prev_nodes_{}, values_{}
	{

	}

	void Insert(int data)
	{
		assert(size_ < KMax_Size - 1);
		auto node_index = CreateNode();
		values_[node_index] = data;

		InsertNode(node_index, 0, 0);
	}

private:

	uint16_t CreateNode()
	{
		int i = 1;
		int toss = 1;
		if (size_ == 0)
		{
			nodes_[size_].height = KMax_Height;
		}
		else
		{
			while (i < KMax_Height && toss > 0)
			{
				++i;
				toss = CoinToss();
			}

			nodes_[size_].height = i;
		}

		for (int i = 0; i < KMax_Height; ++i)
		{
			nodes_[size_].next[i] = KTombstone;
			prev_nodes_[size_][i] = KTombstone;
		}

		return size_++;
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

	static const size_t KMax_Size = 64;
	// height = log2(max size)
	static const size_t KMax_Height = 6;
	// null value
	static const uint16_t KTombstone = 0xffff;

	struct Node
	{
		uint8_t height;
		uint16_t next[KMax_Height];
	};

	std::array<Node, KMax_Size> nodes_;
	std::array<int, KMax_Size> values_;
	std::array<uint8_t[KMax_Height], KMax_Size> prev_nodes_;

	size_t size_;

	friend void Test(const TestSkipList& sl);
};
