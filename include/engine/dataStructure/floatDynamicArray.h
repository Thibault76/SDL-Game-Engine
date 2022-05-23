#pragma once

#include "../core.h"

typedef struct{
	uint32_t size;
	uint32_t used;
	float* content;
} EngineFloatDynamicArray;

/**
 * @brief create a dynamic float array
 * @param size the size of the array
 * @return EngineFloatDynamicArray* 
 */
EngineFloatDynamicArray* EngineFloatDynamicArrayCreate(uint32_t size);

/**
 * @brief destroy a dynamic float array
 * @param arr the array to destroy
 * @return EngineFloatDynamicArray* 
 */
EngineFloatDynamicArray* EngineFloatDynamicArrayDestroy(EngineFloatDynamicArray *arr);

/**
 * @brief insert data at the back of the dynamuc array
 * @param arr the destination array
 * @param value the value to insert
 */
void EngineFloatDynamicArrayInsert(EngineFloatDynamicArray* arr, float value);

/**
 * @brief get the raw array
 * @return float* 
 */
float* EngineFloatDynamicArrayGetData(EngineFloatDynamicArray* arr);

/**
 * @brief get the count of elements in the dynamic array
 * @return uint32_t 
 */
uint32_t EngineFloatDynamicArrayGetSize(EngineFloatDynamicArray* arr);

/**
 * @brief clear all the elements from the dynamic array
 * @param arr the array to clear
 */
void EngineFloatDynamicArrayClear(EngineFloatDynamicArray* arr);

/**
 * @brief crop the dynamic array to the exact count of elements
 * @param arr the array to crop
 */
void EngineFloatDynamicArrayCropToContent(EngineFloatDynamicArray* arr);

/**
 * @brief get the pointer of the first element of the dynamic array
 * @return float* 
 */
float* EngineFloatDynamicArrayGetBegin(EngineFloatDynamicArray* arr);

/**
 * @brief get the pointer of the last element of the dynammic array
 * @return float* 
 */
float* EngineFloatDynamicArrayGetEnd(EngineFloatDynamicArray* arr);
