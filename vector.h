#pragma once

typedef struct {
	int* m_data;
	int m_size,
		m_capacity;
} Vector;

int VecInit(Vector*, int, ...);
int VecPushBack(Vector*, int);
int VecPopBack(Vector*);
int VecInsert(Vector*, int, int);
int VecInsertVec(Vector*, int, const Vector*);
int VecErase(Vector*, int);
int VecEraseRange(Vector*, int, int);
int VecGet(const Vector*, int);
int VecSize(const Vector*);
void VecClear(Vector*);
