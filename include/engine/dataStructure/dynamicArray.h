#pragma once

#include "../core.h"

typedef struct{
	uint32_t size;
	uint32_t used;
	void** content;
} EngineDynamicArray;

/**
 * @brief create a dynamic void array
 * @param size the size of the array
 * @return EngineDynamicArray* 
 */
EngineDynamicArray* EngineDynamicArrayCreate(uint32_t size);

/**
 * @brief destroy a dynamic void array
 * @param arr the array to destroy
 * @return EngineDynamicArray* 
 */
EngineDynamicArray* EngineDynamicArrayDestroy(EngineDynamicArray *arr);

/**
 * @brief insert data at the back of the dynamuc array
 * @param arr the destination array
 * @param value the value to insert
 */
void* EngineDynamicArrayInsert(EngineDynamicArray* arr, void* value);

/**
 * @brief get the raw array
 * @return void* 
 */
void** EngineDynamicArrayGetData(EngineDynamicArray* arr);

/**
 * @brief get the count of elements in the dynamic array
 * @return uint32_t 
 */
uint32_t EngineDynamicArrayGetSize(EngineDynamicArray* arr);

/**
 * @brief clear all the elements from the dynamic array
 * @param arr the array to clear
 */
void EngineDynamicArrayClear(EngineDynamicArray* arr);

/**
 * @brief crop the dynamic array to the exact count of elements
 * @param arr the array to crop
 */
void EngineDynamicArrayCropToContent(EngineDynamicArray* arr);

/**
 * @brief get the pointer of the first element of the dynamic array
 * @return void* 
 */
void* EngineDynamicArrayGetBegin(EngineDynamicArray* arr);

/**
 * @brief get the pointer of the last element of the dynammic array
 * @return void* 
 */
void* EngineDynamicArrayGetEnd(EngineDynamicArray* arr);
