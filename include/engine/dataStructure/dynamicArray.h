#pragma once

#include "../core.h"

typedef struct{
	uint32_t size;
	uint32_t used;
	void** content;
} CeosDynamicArray;

/**
 * @brief create a dynamic void array
 * @param size the size of the array
 * @return CeosDynamicArray* 
 */
CeosDynamicArray* CeosDynamicArrayCreate(uint32_t size);

/**
 * @brief destroy a dynamic void array
 * @param arr the array to destroy
 * @return CeosDynamicArray* 
 */
CeosDynamicArray* CeosDynamicArrayDestroy(CeosDynamicArray *arr);

/**
 * @brief insert data at the back of the dynamuc array
 * @param arr the destination array
 * @param value the value to insert
 */
void* CeosDynamicArrayInsert(CeosDynamicArray* arr, void* value);

/**
 * @brief get the raw array
 * @return void* 
 */
void** CeosDynamicArrayGetData(CeosDynamicArray* arr);

/**
 * @brief get the count of elements in the dynamic array
 * @return uint32_t 
 */
uint32_t CeosDynamicArrayGetSize(CeosDynamicArray* arr);

/**
 * @brief clear all the elements from the dynamic array
 * @param arr the array to clear
 */
void CeosDynamicArrayClear(CeosDynamicArray* arr);

/**
 * @brief crop the dynamic array to the exact count of elements
 * @param arr the array to crop
 */
void CeosDynamicArrayCropToContent(CeosDynamicArray* arr);

/**
 * @brief get the pointer of the first element of the dynamic array
 * @return void* 
 */
void* CeosDynamicArrayGetBegin(CeosDynamicArray* arr);

/**
 * @brief get the pointer of the last element of the dynammic array
 * @return void* 
 */
void* CeosDynamicArrayGetEnd(CeosDynamicArray* arr);
