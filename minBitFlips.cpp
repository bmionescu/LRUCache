#include <cmath>

class Solution {
private:
    void convertToBinary(int num, int numBits, int numBitsDiff, int* binaryArray) {
        if (numBitsDiff > 0) { // Pad the smaller array with leading 0s
            for (int i = 0; i < numBitsDiff; i++) {
                binaryArray[i] = 0;
            }
        }
        if (num == 0) {
            binaryArray[numBitsDiff] = 0;
	    return;
	}	
        while (num >= 1) {
            binaryArray[numBits + numBitsDiff-1] = num % 2;
            num = int(num/2);
            numBits--;
        }
    }
    int countDifferentDigits(int* array1, int* array2, int size) {
        int count = 0;
        for (int i = 0; i < size; i++) {
	    if (array1[i] != array2[i]) {
                count++;
	    }
	}
	return count;
    }
    int computeNumberOfBits(int num) {
        if (num == 0) {
            return 1;
	} else {
            return log2(num) + 1;
	}
    }
public:
    int minBitFlips(int start, int goal) {

        int numBitsStart = computeNumberOfBits(start);
        int numBitsGoal = computeNumberOfBits(goal);
        if (numBitsStart > numBitsGoal) {
            int startArray[numBitsStart];
            int goalArray[numBitsStart];  
            convertToBinary(start, numBitsStart, 0, startArray);
            convertToBinary(goal, numBitsGoal, numBitsStart - numBitsGoal, goalArray);
	    return countDifferentDigits(startArray, goalArray, numBitsStart); 
        } else {
            int startArray[numBitsGoal];
            int goalArray[numBitsGoal];  
            convertToBinary(start, numBitsStart, numBitsGoal - numBitsStart, startArray);
            convertToBinary(goal, numBitsGoal, 0, goalArray);
	    return countDifferentDigits(startArray, goalArray, numBitsGoal);
        }
    }
};
