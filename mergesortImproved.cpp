// Ahmad Yousif, CSS 342, Assignment 4, 6/1/2020
// mergesortImproved.cpp

#include <iostream> 
#include <vector> 
#include <math.h>
using namespace std;

// <summary>
// Merges two sub-sections of the source vector: "A" and "B", into the destination array.
// </summary>
//
// <parameter = "source">
// Source vector. Contains the elements to be sorted.
// </parameter>
//
// <parameter = "dest">
// Destination vector. Sorted elements are placed in this vector.
// </parameter>
//
// <parameter = "startA">
// Integer value representing the first index of the "A" sub-section.
// </parameter>
//
// <parameter = "endA">
// Integer value representing the last index of the "A" sub-section.
// </parameter>
//
// <parameter = "startB">
// Integer value representing the first index of the "B" sub-section.
// </parameter>
//
// <parameter = "endB">
// Integer value representing the last index of the "B" sub-section.
// </parameter>
template<class Comparable>
void merge(vector<Comparable>& source, vector<Comparable>& dest, int startA, int endA, int startB, int endB)
{
	int aIndex = startA;
	int bIndex = startB;
	int mergeIndex = startA;

	while (aIndex <= endA && bIndex <= endB) {
		if (source[aIndex] <= source[bIndex])
		{
			dest[mergeIndex++] = source[aIndex];
			aIndex++;
		}
		else if (source[aIndex] > source[bIndex]) {
			dest[mergeIndex++] = source[bIndex];
			bIndex++;
		}
	}

	for (int i = aIndex; aIndex <= endA; aIndex++) {
		dest[mergeIndex++] = source[aIndex];
	}

	for (int i = bIndex; bIndex <= endB; bIndex++) {
		dest[mergeIndex++] = source[bIndex];
	}
}

// <summary>
// Moves the leftover elements that have not been merged from the source to the destination.
// </summary>
//
// <parameter = "source">
// Source vector. Contains the elements to be sorted.
// </parameter>
//
// <parameter = "dest">
// Destination vector. Sorted elements are placed in this vector.
// </parameter>
//
//<parameter = "dest">
// Destination vector. Sorted elements are placed in this vector.
// </parameter>
template<class Comparable>
void moveRemainingItems(vector<Comparable>& source, vector<Comparable>& dest, int startIndex) {
	for (int i = startIndex; i < source.size(); i++) {
		dest[i] = source[i];
	}
}

// <summary>
// Performs the improved mergesort algorithm.
// </summary>
//
// <parameter = "primaryArray">
// Primary vector consisting of the first segment "A".
// </parameter>
template<class Comparable>
void mergesortImproved(vector<Comparable>& primaryArray)
{
	int arraySize = primaryArray.size();
	vector<Comparable> secondaryArray(arraySize);

	bool usePrimaryArray = true;

	int segmentCount = 0;
	int iteration = 0;
	do
	{
		int segmentSize = pow(2, iteration++);

		// This is use to break the iteration loop for the do-while.
		// When the segmentCount is less than 1, there is nothing to merge
		// anymore, and we will be done processing.
		segmentCount = ceil(arraySize / segmentSize);

		for (int startA = 0; startA < arraySize; startA += segmentSize * 2)
		{
			int endA = startA + segmentSize - 1;
			int startB = endA + 1;
			int endB = startB + segmentSize - 1;

			if (startB >= arraySize) {
				if (usePrimaryArray)
				{
					moveRemainingItems(primaryArray, secondaryArray, startA);
				}
				else
				{
					moveRemainingItems(secondaryArray, primaryArray, startA);
				}
				break;
			}

			// Reset the starting index for the second array segement if is passes the length of the array
			// This ensure the array segment stays in the array range
			if (startB >= arraySize) {
				startB = arraySize - 1;
			}

			// Reset the end index for the second array segement if is passes the length of the array
			// This ensure the array segment stays in the array range
			if (endB >= arraySize) {
				endB = arraySize - 1;
			}

			// Merge array segment using the appropriate Primary and Secondary arrays
			if (usePrimaryArray)
			{
				merge(primaryArray, secondaryArray, startA, endA, startB, endB);
			}
			else
			{
				merge(secondaryArray, primaryArray, startA, endA, startB, endB);
			}
		}

		// switch arrays after completeing the merge operation
		usePrimaryArray = !usePrimaryArray;
	} while (segmentCount > 0);

	if (!usePrimaryArray)
	{
		// copy secondary to primary
		for (int i = 0; i < secondaryArray.size(); i++)
		{
			primaryArray[i] = secondaryArray[i];
		}
	}
}