#pragma once
#include <cinttypes>
#include <array>
#include <random>
#include <assert.h>
#include <vector>

template <typename T>
class SSkipList
{
public:
	SSkipList()
	{
		for (int i = 0; i < KMax_Height; ++i)
			root[i] = nullptr;

	}

	//====================================
	// used to generate randomized level
	//=====================================
	int CoinToss()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);

		return dis(gen);
	}

	//==============================
	// node object 
	//===============================
	template <typename S>
	class Node
	{
	public:
		Node(const S& value, size_t size) : value_(value), size_(size) {};
		Node(S&& value, size_t size) : value_(std::move(value)), size_(size) {};
		virtual ~Node() {};

		S& Value() { return value_; }
		size_t Size() { return size_; }

		virtual  Node<S> const * const Next(size_t level) = 0;
		virtual bool BindNext(Node<S>* next_node, size_t level) = 0;

	private:
		size_t size_ = 0;
		S value_;
	};

	template <size_t shortcuts>
	class LevelNode : public Node<T>
	{
	public:
		LevelNode(const T& t) : Node<T>(t, shortcuts) {};
		LevelNode(T&& t) : Node<T>(std::move(t), shortcuts) {};

		virtual ~LevelNode() {};
		virtual Node<T> const * const Next(size_t level) override
		{
			if (level < shortcuts)
				return next[level];
			else
				return nullptr;
		}

		virtual bool BindNext(Node<T>* next_node, size_t level) override
		{
			bool success = true;
			if (level < shortcuts)
				next[level] = next_node;
			else
				success = false;

			return success;
		}

	private:
		Node<T>* next[shortcuts];
	};

	using Level_1_Node = LevelNode<1>;
	using Level_2_Node = LevelNode<2>;
	using Level_3_Node = LevelNode<3>;
	using Level_4_Node = LevelNode<4>;
	using Level_5_Node = LevelNode<5>;
	using Level_6_Node = LevelNode<6>;
	using Level_7_Node = LevelNode<7>;
	using Level_8_Node = LevelNode<8>;
	using Level_9_Node = LevelNode<9>;
	using Level_10_Node = LevelNode<10>;
	using Level_11_Node = LevelNode<11>;
	using Level_12_Node = LevelNode<12>;
	using Level_13_Node = LevelNode<13>;
	using Level_14_Node = LevelNode<14>;
	using Level_15_Node = LevelNode<15>;
	using Level_16_Node = LevelNode<16>;

	//============================================
	// Create node with randomized height
	//============================================
	Node<T>* CreateNode(const T& t)
	{
		int i = 1;
		int toss = 1;

		while (i++ < KMax_Height && toss > 0)
			toss = CoinToss();

		Node<T>* node = nullptr;

		switch (i)
		{
		case 1:
			node = new Level_1_Node(t);
			break;
		case 2:
			node = new Level_2_Node(t);
			break;
		case 3:
			node = new Level_3_Node(t);
			break;
		case 4:
			node = new Level_4_Node(t);
			break;
		case 5:
			node = new Level_5_Node(t);
			break;
		case 6:
			node = new Level_6_Node(t);
			break;
		case 7:
			node = new Level_7_Node(t);
			break;
		case 8:
			node = new Level_8_Node(t);
			break;
		case 9:
			node = new Level_9_Node(t);
			break;
		case 10:
			node = new Level_10_Node(t);
			break;
		case 11:
			node = new Level_11_Node(t);
			break;
		case 12:
			node = new Level_12_Node(t);
			break;
		case 13:
			node = new Level_13_Node(t);
			break;
		case 14:
			node = new Level_14_Node(t);
			break;
		case 15:
			node = new Level_15_Node(t);
			break;
		case 16:
			node = new Level_16_Node(t);
			break;
		}

		for (int i = 0; i < KMax_Height; ++i)
			node->BindNext(nullptr, i);

		return node;
	}

	void Insert(Node<T>* insert_node, Node<T>* cur_node)
	{
		std::vector<Node<T>*> update_nodes;
		//start at insert nodes highest level
		size_t level = insert_node->Size() - 1;
		Node<T>* right_of_node = nullptr;
		while (level > 0)
		{
			right_of_node = root[level];
			if (right_of_node == nullptr)
			{
				update_nodes.push_back(right_of_node);
			}
		}
	}

	static const size_t KMax_Height = 16;
	Node<T>* root[KMax_Height];
};