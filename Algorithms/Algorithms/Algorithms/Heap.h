#pragma once
#include "vector"

int Parent(int i);
int Left(std::vector<int>*, int i);
int Right(std::vector<int>*, int i);


void insert(std::vector<int>* vec, int x);
void extract(std::vector<int>* vec);

void heapify(std::vector<int>* vec, int i);

