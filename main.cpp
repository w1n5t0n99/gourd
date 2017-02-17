#include <iostream>
#include <typeinfo>
#include <datetime.h>

#include "doubly_linked_list.h"
#include "skip_list.h"


void TestSkipList(const SkipList<int, 5>& sl)
{
	int level = 0;
	while (level < sl.max_height)
	{
		printf("level %d - ", level);
		auto right_of = sl.sentinel_->next[level];
		while (right_of != nullptr)
		{
			printf(" %d ", right_of->data);
			right_of = right_of->next[level];
		}
		printf("\n");
		++level;
	}
}


int main()
{
	DoublyLinkedList<int> linked_list;
	linked_list.InsertTail(55);
	linked_list.InsertTail(33);
	linked_list.InsertTail(4565);
	linked_list.InsertTail(887);
	linked_list.InsertTail(6554);
	linked_list.InsertTail(5466);

	DoublyLinkedList<int> ll(std::move(linked_list));

	//printf("%d size: %d\n", ll.Get(3), ll.Size());

	SkipList<int, 5> skip_list;
	skip_list.Insert(55);
	skip_list.Insert(33);
	skip_list.Insert(4565);
	skip_list.Insert(887);
	skip_list.Insert(6554);
	skip_list.Insert(5466);

	TestSkipList(skip_list);

	std::cin.get();
	return 0;
}