#include <iostream>
#include <typeinfo>
#include <array>

#include "test.h"
#include "skip_list.h"

void Test(const SkipList<int, 16>& sl)
{
	int level = 0;
	while (level < SkipList<int, 16>::KMax_Height)
	{
		printf("level %d - ", level);
		auto right_of = sl.nodes_[0].next[level];

		while (right_of != SkipList<int, 16>::KTombstone)
		{
			printf(" %d ", sl.nodes_[right_of].data);
			right_of = sl.nodes_[right_of].next[level];
		}
		printf("\n");
		++level;
	}
}

int* ip[4] = { nullptr, nullptr, nullptr, nullptr };

int main()
{
	/*
	SkipList<int, 16> skip_list;
	skip_list.Insert(55);
	skip_list.Insert(33);
	skip_list.Insert(4565);
	skip_list.Insert(887);
	skip_list.Insert(6554);
	skip_list.Insert(5466);

	Test(skip_list);
	
	if (skip_list.Contains(887))
		printf("Found!\n");
	else
		printf("Not found!\n");
*/
	int x = 99;
	auto i = ip[0];
	i = &x;

	printf("%d\n", ip[0]);

	//SSkipList<int> sl;
	//auto s = sl.CreateNode(55);
	//printf("Value: %d Size: %d\n", s->Value(), s->Size());

	std::cin.get();
	return 0;
}