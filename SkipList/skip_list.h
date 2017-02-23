#pragma once
#include <random>


template <typename T, size_t size>
class SkipList
{
public:
	SkipList() : size_(0), cap_(0)
	{
		// add root node
		CreateNode();
	}

	void Insert(const T& data)
	{
		//make sure node doesnt exist before adding 
		if (Contains(data))
			return;

		Node<>* node = CreateNode();
		node->data = data;

		InsertNode(std::make_pair(node, cap_ - 1), std::make_pair(&nodes_[KRoot_Index], KRoot_Index), 0);
	}

	bool Contains(int value)
	{
		if (FindNode(value) == nullptr)
			return false;
		else
			true;
	}

	//============================
	//============================
	size_t Size()
	{
		return size_;
	}

private:
	//===================================================================
	// compile time way to generate proper height based on max list size
	//===================================================================
	template <int x>
	struct Log2 { enum { value = 1 + Log2<x / 2>::value }; };

	template <> struct Log2<1> { enum { value = 1 }; };

	//==============================
	// node object 
	//===============================
	template <typename S = T, size_t size  = Log2<size>::value>
	struct Node
	{
		uint8_t height;
		uint16_t next[size];
		S data;
	};

	using NodePair = std::pair<Node<>*, uint16_t>;

	//=================================
	// create a node in array
	//==================================
	Node<>* CreateNode()
	{
		// 0 reserved for sentinel value
		// and 0xffff reserved for tombstone
		assert(size_ < KMax_Size - 2);

		int i = 1;
		int toss = 1;

		while (i++ < KMax_Height && toss > 0)
			toss = CoinToss();

		Node<>* node = new(nodes_.data() + cap_) Node<>;
		node->height = i;
		std::fill(std::begin(node->next), std::end(node->next), KTombstone);

		++cap_;
		++size_;
		return node;
	}

	NodePair NextNode(Node<>* cur_node, int level)
	{
		auto next_index = cur_node->next[level];
		return next_index != KTombstone ? std::make_pair(&nodes_[next_index], next_index)
			: std::make_pair(nullptr, KTombstone);
	}

	//========================================
	// search node for value
	//========================================
	Node<>* FindNode(const T& search_value)
	{
		auto level = KMax_Height - 1;
		auto* cur_node = &nodes_[KRoot_Index];
		Node<>* right_of_node = nullptr;
		while (level > 0)
		{
			if (!(right_of_node = NextNode(cur_node, level).first))
				--level;
			else if (right_of_node->data == search_value)
				return right_of_node;
			else if (right_of_node->data > search_value)
				--level;
			else
				cur_node = right_of_node;
		}

		return nullptr;
	}

	//====================================================
	// insert node at end of array and just move indices
	//====================================================
	void InsertNode(NodePair insert_node, NodePair cur_node, int level)
	{
		printf("insert_node %d\n", insert_node.first->data);
		NodePair right_of_node;
		// reached nodes height so finished inserting
		if (level > insert_node.first->height)
			return;

		if(level < cur_node.first->height)
			right_of_node = NextNode(cur_node.first, level);
		else
			right_of_node = std::make_pair(nullptr, KTombstone);
		
		if (right_of_node.first && right_of_node.first->data < insert_node.first->data)
		{
			// we overshot keep moving right
			InsertNode(insert_node, right_of_node, level);
		}
		else
		{
			cur_node.first->next[level] = insert_node.second;
			insert_node.first->next[level] = right_of_node.second;
			// we have reached not the inserted nodes height yet,
			// check next level
			InsertNode(insert_node, std::make_pair(&nodes_[KRoot_Index], KRoot_Index), ++level);
		}
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

private:
	static const size_t KMax_Size = size;
	// height = log2(max size)
	static const size_t KMax_Height = Log2<size>::value;
	// null value
	static const uint16_t KTombstone = 0xffff;
	// root node index
	static const uint16_t KRoot_Index = 0;
	// array of nodes for better cache
	std::array<Node<>, KMax_Size> nodes_;

	size_t size_;
	size_t cap_;

	friend void Test(const SkipList<T, size>& sl);
};











template <typename T, size_t Chunk_Size, size_t Max_Level = 16>
class ChunkSkipList
{
public:

private:

	//==============================
	// node object 
	//===============================
	template <typename S = T, size_t Chunks = Chunk_Size>
	struct Node
	{
		virtual  Node<> const * const Next(size_t level) = 0;
		virtual bool SetNext(Node<>* next_node, size_t level) = 0;
		size_t size = 0;
		S values[Chunks];
	};

	template <size_t shortcuts>
	struct LevelNode : Node<>
	{
		virtual Node<> const * const Next(size_t level) override
		{
			if (level < shortcuts)
				return next[level];
			else
				return nullptr;
		}

		virtual bool SetNext(Node<>* next_node, size_t level) override
		{
			bool success = true;
			if (level < shortcuts)
				next[level] = next_node;
			else
				success = false;

			return success;
		}
	
		Node<>* next[shortcuts];
	};

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

	//=================================
	// create a node in array
	//==================================
	Node<>* CreateNode()
	{
		int i = 1;
		int toss = 1;

		while (i++ < KMax_Height && toss > 0)
			toss = CoinToss();


		LevelNode<i> node = new LevelNode<i>;
		std::fill(std::begin(node->nextext), std::end(node->next), nullptr);
		return node;
	}

	static const size_t KMax_Chunk = Chunk_Size;
	// height = log2(max size)
	static const size_t KMax_Height = Max_Level;

};