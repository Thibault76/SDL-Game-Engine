#pragma once

#include "../core.h"

typedef struct{
	uint32_t size;
	uint32_t used;
	uint32_t step;
	float* content;
} CeosFloatDynamicArray;

/**
 * @brief create a dynamic float array
 * @param size the size of the array
 * @return CeosFloatDynamicArray* 
 */
CeosFloatDynamicArray* CeosFloatDynamicArrayCreate(uint32_t size);

/**
 * @brief destroy a dynamic float array
 * @param arr the array to destroy
 * @return CeosFloatDynamicArray* 
 */
CeosFloatDynamicArray* CeosFloatDynamicArrayDestroy(CeosFloatDynamicArray *arr);

/**
 * @brief insert data at the back of the dynamuc array
 * @param arr the destination array
 * @param value the value to insert
 */
void* CeosFloatDynamicArrayInsert(CeosFloatDynamicArray* arr, float value);

/**
 * @brief get the raw array
 * @return float* 
 */
float* CeosFloatDynamicArrayGetData(CeosFloatDynamicArray* arr);

/**
 * @brief get the count of elements in the dynamic array
 * @return uint32_t 
 */
uint32_t CeosFloatDynamicArrayGetSize(CeosFloatDynamicArray* arr);

/**
 * @brief clear all the elements from the dynamic array
 * @param arr the array to clear
 */
void CeosFloatDynamicArrayClear(CeosFloatDynamicArray* arr);

/**
 * @brief crop the dynamic array to the exact count of elements
 * @param arr the array to crop
 */
void CeosFloatDynamicArrayCropToContent(CeosFloatDynamicArray* arr);

/**
 * @brief get the pointer of the first element of the dynamic array
 * @return float* 
 */
float* CeosFloatDynamicArrayGetBegin(CeosFloatDynamicArray* arr);

/**
 * @brief get the pointer of the last element of the dynammic array
 * @return float* 
 */
float* CeosFloatDynamicArrayGetEnd(CeosFloatDynamicArray* arr);
