#include "engine/dataStructure/floatDynamicArray.h"
#include <assert.h>

EngineFloatDynamicArray* EngineFloatDynamicArrayCreate(uint32_t size){
	EngineFloatDynamicArray* arr = malloc(sizeof(EngineFloatDynamicArray));
	MALLOC_CHECK(arr);
	
	arr->content = malloc(sizeof(float) * size);
	MALLOC_CHECK(arr->content);
	arr->used = 0;
	arr->size = size;
	arr->step = 150;
	return arr;
}

EngineFloatDynamicArray* EngineFloatDynamicArrayDestroy(EngineFloatDynamicArray *arr){
	assert(arr != NULL && "cannot destroy a NULL dynamic array");
	if (arr->size){
		free(arr->content);
		arr->content = NULL;
	}
	free(arr);
	arr = NULL;
	return arr;
}

void* EngineFloatDynamicArrayInsert(EngineFloatDynamicArray* arr, float value){
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

float* EngineFloatDynamicArrayGetData(EngineFloatDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return arr->content;
}

uint32_t EngineFloatDynamicArrayGetSize(EngineFloatDynamicArray* arr){
	assert(arr != NULL && "cannot get the size of a NULL dynamic array");
	return arr->used;
}

void EngineFloatDynamicArrayClear(EngineFloatDynamicArray* arr){
	assert(arr != NULL && "cannot clear a NULL dynamic array");
	arr->used = 0;
}

void EngineFloatDynamicArrayCropToContent(EngineFloatDynamicArray* arr){
	assert(arr != NULL && "cannot set the size of a NULL dynamic array");
	arr->size = arr->used;
	arr->content = realloc(arr->content, arr->used * sizeof(float));
}

float* EngineFloatDynamicArrayGetBegin(EngineFloatDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return arr->content;
}

float* EngineFloatDynamicArrayGetEnd(EngineFloatDynamicArray* arr){
	assert(arr != NULL && "cannot get the data of a NULL dynamic array");
	return &arr->content[arr->used];
}