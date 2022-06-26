#include "engine/dataStructure/DynamicArray.h"
#include <assert.h>

EngineDynamicArray* EngineDynamicArrayCreate(uint32_t size){
	EngineDynamicArray* arr = malloc(sizeof(EngineDynamicArray));
	MALLOC_CHECK(arr);
	
	arr->content = malloc(sizeof(void*) * size);
	MALLOC_CHECK(arr->content);
	arr->used = 0;
	arr->size = size;
	return arr;
}

EngineDynamicArray* EngineDynamicArrayDestroy(EngineDynamicArray *arr){
	assert(arr != NULL && "cannot destroy a NULL dynamic array");
	if (arr->size){
		free(arr->content);
		arr->content = NULL;
	}
	free(arr);
	arr = NULL;
	return arr;
}

void* EngineDynamicArrayInsert(EngineDynamicArray* arr, void* value){
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

void** EngineDynamicArrayGetData(EngineDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return arr->content;
}

uint32_t EngineDynamicArrayGetSize(EngineDynamicArray* arr){
	assert(arr != NULL && "cannot get the size of a NULL dynamic array");
	return arr->used;
}

void EngineDynamicArrayClear(EngineDynamicArray* arr){
	assert(arr != NULL && "cannot clear a NULL dynamic array");
	arr->used = 0;
}

void EngineDynamicArrayCropToContent(EngineDynamicArray* arr){
	assert(arr != NULL && "cannot set the size of a NULL dynamic array");
	arr->size = arr->used;
	arr->content = realloc(arr->content, arr->used * sizeof(void*));
}

void* EngineDynamicArrayGetBegin(EngineDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return arr->content;
}

void* EngineDynamicArrayGetEnd(EngineDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return &arr->content[arr->used];
}