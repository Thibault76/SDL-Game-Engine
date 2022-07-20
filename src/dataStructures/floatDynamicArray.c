#include "engine/dataStructure/floatDynamicArray.h"
#include <assert.h>

CeosFloatDynamicArray* CeosFloatDynamicArrayCreate(uint32_t size){
	CeosFloatDynamicArray* arr = malloc(sizeof(CeosFloatDynamicArray));
	MALLOC_CHECK(arr);
	
	arr->content = malloc(sizeof(float) * size);
	MALLOC_CHECK(arr->content);
	arr->used = 0;
	arr->size = size;
	arr->step = 150;
	return arr;
}

CeosFloatDynamicArray* CeosFloatDynamicArrayDestroy(CeosFloatDynamicArray *arr){
	assert(arr != NULL && "cannot destroy a NULL dynamic array");
	if (arr->size){
		free(arr->content);
		arr->content = NULL;
	}
	free(arr);
	arr = NULL;
	return arr;
}

void* CeosFloatDynamicArrayInsert(CeosFloatDynamicArray* arr, float value){
	assert(arr != NULL && "cannot insert data in a NULL dynamic array");
	if (arr->used+1 >= arr->size){
		arr->size += arr->step;
		printf("arr : %d\n", arr);
		arr->content = realloc(arr->content, arr->size * sizeof(float));
		MALLOC_CHECK(arr->content);
	}
	arr->content[arr->used] = value;
	void* data = &arr->content[arr->used];
	arr->used++;
	return data;
}

float* CeosFloatDynamicArrayGetData(CeosFloatDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return arr->content;
}

uint32_t CeosFloatDynamicArrayGetSize(CeosFloatDynamicArray* arr){
	assert(arr != NULL && "cannot get the size of a NULL dynamic array");
	return arr->used;
}

void CeosFloatDynamicArrayClear(CeosFloatDynamicArray* arr){
	assert(arr != NULL && "cannot clear a NULL dynamic array");
	arr->used = 0;
}

void CeosFloatDynamicArrayCropToContent(CeosFloatDynamicArray* arr){
	assert(arr != NULL && "cannot set the size of a NULL dynamic array");
	arr->size = arr->used;
	arr->content = realloc(arr->content, arr->used * sizeof(float));
}

float* CeosFloatDynamicArrayGetBegin(CeosFloatDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return arr->content;
}

float* CeosFloatDynamicArrayGetEnd(CeosFloatDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return &arr->content[arr->used];
}