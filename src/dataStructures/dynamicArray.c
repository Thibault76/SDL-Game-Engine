#include "engine/dataStructure/DynamicArray.h"
#include <assert.h>

CeosDynamicArray* CeosDynamicArrayCreate(uint32_t size){
	CeosDynamicArray* arr = malloc(sizeof(CeosDynamicArray));
	MALLOC_CHECK(arr);
	
	arr->content = malloc(sizeof(void*) * size);
	MALLOC_CHECK(arr->content);
	arr->used = 0;
	arr->size = size;
	return arr;
}

CeosDynamicArray* CeosDynamicArrayDestroy(CeosDynamicArray *arr){
	assert(arr != NULL && "cannot destroy a NULL dynamic array");
	if (arr->size){
		free(arr->content);
		arr->content = NULL;
	}
	free(arr);
	arr = NULL;
	return arr;
}

void* CeosDynamicArrayInsert(CeosDynamicArray* arr, void* value){
	assert(arr != NULL && "cannot insert data in a NULL dynamic array");
	if (arr->used+1 == arr->size){
		arr->size *= 2;
		arr->content = realloc(arr->content, arr->size * sizeof(void*));
		MALLOC_CHECK(arr->content);
	}
	arr->content[arr->used] = value;
	void* data = &arr->content[arr->used];
	arr->used++;
	return data;
}

void** CeosDynamicArrayGetData(CeosDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return arr->content;
}

uint32_t CeosDynamicArrayGetSize(CeosDynamicArray* arr){
	assert(arr != NULL && "cannot get the size of a NULL dynamic array");
	return arr->used;
}

void CeosDynamicArrayClear(CeosDynamicArray* arr){
	assert(arr != NULL && "cannot clear a NULL dynamic array");
	arr->used = 0;
}

void CeosDynamicArrayCropToContent(CeosDynamicArray* arr){
	assert(arr != NULL && "cannot set the size of a NULL dynamic array");
	arr->size = arr->used;
	arr->content = realloc(arr->content, arr->used * sizeof(void*));
}

void* CeosDynamicArrayGetBegin(CeosDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return arr->content;
}

void* CeosDynamicArrayGetEnd(CeosDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return &arr->content[arr->used];
}