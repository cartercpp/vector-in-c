#include <stdio.h>
#include "vector.h"

int main()
{
	Vector vec;

	VecInit(&vec, 5, 1, 2, 3, 4, 5);
	int size = VecSize(&vec);
	for (int i = 0; i < size; ++i)
		printf("%d", VecGet(&vec, i)); // 12345
	printf("\n");

	VecPushBack(&vec, 6);
	size = VecSize(&vec);
	for (int i = 0; i < size; ++i)
		printf("%d", VecGet(&vec, i)); // 123456
	printf("\n");

	VecPopBack(&vec);
	size = VecSize(&vec);
	for (int i = 0; i < size; ++i)
		printf("%d", VecGet(&vec, i)); // 12345
	printf("\n");

	VecInsert(&vec, 0, 0);
	size = VecSize(&vec);
	for (int i = 0; i < size; ++i)
		printf("%d", VecGet(&vec, i)); // 012345
	printf("\n");
	
	Vector vec2;
	VecInit(&vec2, 3, 6, 7, 8);
	VecInsertVec(&vec, size, &vec2);
	size = VecSize(&vec);
	for (int i = 0; i < size; ++i)
		printf("%d", VecGet(&vec, i)); // 012345678
	printf("\n");
	VecClear(&vec2);

	VecErase(&vec, 0);
	size = VecSize(&vec);
	for (int i = 0; i < size; ++i)
		printf("%d", VecGet(&vec, i)); // 12345678
	printf("\n");

	VecEraseRange(&vec, 0, 3);
	size = VecSize(&vec);
	for (int i = 0; i < size; ++i)
		printf("%d", VecGet(&vec, i)); // 45678
	printf("\n");

	VecClear(&vec);
}
