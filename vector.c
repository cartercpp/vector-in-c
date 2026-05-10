#include "vector.h"
#include <stdlib.h>
#include <stdarg.h>

int VecInit(Vector* vec, int size, ...)
{
	if ((vec == NULL) || (size <= 0))
		return -1;

	vec->m_data = (int*)malloc(sizeof(int) * size);
	if (vec->m_data == NULL)
		return -1;

	va_list args;
	va_start(args, size);

	for (int i = 0; i < size; ++i)
		vec->m_data[i] = va_arg(args, int);

	va_end(args);
	vec->m_capacity = vec->m_size = size;
	return 0;
}

int VecPushBack(Vector* vec, int value)
{
	if (vec == NULL)
		return -1;

	if (vec->m_size == vec->m_capacity)
	{
		vec->m_capacity = (vec->m_capacity > 0)
			? (vec->m_capacity * 2) : 1;

		vec->m_data = (int*)realloc(
			vec->m_data,
			sizeof(int) * vec->m_capacity
		);
		if (vec->m_data == NULL)
			return -1;
	}

	vec->m_data[vec->m_size] = value;
	++vec->m_size;
	return 0;
}

int VecPopBack(Vector* vec)
{
	if ((vec == NULL) || (vec->m_size == 0))
		return -1;

	--vec->m_size;
	return 0;
}

static void ShiftRight(
	Vector* vec, int start, int count
)
{
	for (int index = vec->m_size - 1;
		index >= start; --index)
		vec->m_data[index + count]
		= vec->m_data[index];
}

int VecInsert(Vector* vec, int index, int value)
{
	if ((vec == NULL) || (index < 0)
		|| (index > vec->m_size))
		return -1;

	if (vec->m_size == vec->m_capacity)
	{
		vec->m_capacity = (vec->m_capacity > 0)
			? (vec->m_capacity * 2)
			: 1;

		vec->m_data = (int*)realloc(
			vec->m_data,
			sizeof(int) * vec->m_capacity
		);
		if (vec->m_data == NULL)
			return -1;
	}

	ShiftRight(vec, index, 1);
	vec->m_data[index] = value;
	++vec->m_size;

	return 0;
}

int VecInsertVec(Vector* vec, int index,
	const Vector* other)
{
	if ((vec == NULL) || (other == NULL)
		|| (index < 0) || (index > vec->m_size))
		return -1;

	if (vec->m_size + other->m_size >
		vec->m_capacity)
	{
		vec->m_capacity
			= vec->m_size + other->m_size;

		vec->m_data = (int*)realloc(
			vec->m_data,
			sizeof(int) * vec->m_capacity
		);
		if (vec->m_data == NULL)
			return -1;
	}

	ShiftRight(vec, index, other->m_size);
	for (int i = 0; i < other->m_size; ++i)
		vec->m_data[index + i]
		= other->m_data[i];
	vec->m_size += other->m_size;

	return 0;
}

static void ShiftLeft(Vector* vec, int start,
	int count)
{
	for (int index = start; index < vec->m_size;
		++index)
		vec->m_data[index - count]
		= vec->m_data[index];
}

int VecErase(Vector* vec, int index)
{
	if ((vec == NULL) || (index < 0)
		|| (index >= vec->m_size))
		return -1;

	ShiftLeft(vec, index + 1, 1);
	--vec->m_size;
	return 0;
}

int VecEraseRange(Vector* vec, int start,
	int end)
{
	if ((vec == NULL) || (start < 0)
		|| (start > end) || (end > vec->m_size))
		return -1;

	const int count = end - start;
	ShiftLeft(vec, end, count);
	vec->m_size -= count;
	return 0;
}

int VecGet(const Vector* vec, int index)
{
	return vec->m_data[index];
}

int VecSize(const Vector* vec)
{
	return vec->m_size;
}

void VecClear(Vector* vec)
{
	if ((vec != NULL) && (vec->m_size > 0))
	{
		free(vec->m_data);
		vec->m_data = NULL;
		vec->m_capacity = vec->m_size = 0;
	}
}
