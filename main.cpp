#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//- Global Variables
const int MAX = 40;
const int MIN = 5;

//- Function Prototypes
void PrintArray (const int arr[], const int size);
void Insert (int arr[], int& size, int newValue, int index);
void Shift (int arr[], int size, int shiftAmount);
void Delete (int arr[], int& size, int index);
void Reverse (int arr[], int size);
void GrowArray (int arr[], int& size);
void ShrinkArray (int& size);


int main()
{
    srand(time(NULL));
    int list[MAX]; //creation of array named list, with allocated size MAX.
    int newValue;
    int index;
    int currentSize;
    int shiftSize;
    int sum = 0;
    int arrAverage;
    int arrHighest;
    char menuChoice;

    cout << "To begin, enter the starting current size for your array.\n";
    do
    {
        cout << "Enter a value " << MIN << " --> " << MAX << ":";
        cin >> currentSize;
    } while (currentSize < MIN or currentSize > MAX or currentSize % 5 != 0);

    cout << "\n-------------------MENU-------------------\n";
    cout << "F - Fill Array: RANDOM values 1 - 100\n";
    cout << "R - Reverse Array Contents\n";
    cout << "X - Shift Right\n";
    cout << "I - Insert Array Element\n";
    cout << "D - Delete Array Element\n";
    cout << "A - Print Average\n";
    cout << "M - Print Max Value\n";
    cout << "G - Grow Array Size by 5\n";
    cout << "S - Shrink Array Size by 5\n";
    cout << "P - Print Array\n";
    cout << "Q - QUIT\n";
    cout << "------------------------------------------\n";
    cout << "Selection >";
    cin >> menuChoice;

    do
    {
        switch (menuChoice)
        {
            case 'F':
            case 'f':
                cout << "Randomizing Array Data...";
                for (int i = 0; i < MAX; i++)
                {
                    list[i] = (1 + (rand() % 100));
                }
                break;

            case 'R':
            case 'r':
                cout << "Reversing Array Data...";
                Reverse(list, currentSize);
                break;

            case 'X':
            case 'x':
                cout << "Shift right by: ";
                cin >> shiftSize;
                Shift(list, currentSize, shiftSize);
                break;

            case 'I':
            case 'i':
                cout << "Value to add to list: ";
                cin >> newValue;
                cout << "Index to add to: ";
                cin >> index;
                cout << "Inserting " << newValue << " at index " << index << "...";
                Insert(list, currentSize, newValue, index);
                break;

            case 'D':
            case 'd':
                cout << "Index you would like to remove: ";
                cin >> index;
                cout << "Deleting value at index " << index << "...";
                Delete(list, currentSize, index);
                break;

            case 'A':
            case 'a':
                for (int i = 0; i < currentSize; i++) {
                    sum += list[i];
                }
                arrAverage = sum / currentSize;
                cout << "Array Average: " << arrAverage;
                break;

            case 'M':
            case 'm':
                arrHighest = list[0];
                for (int i = 0; i < currentSize; i++) {
                    if (list[i] > arrHighest) {
                        arrHighest = list[i];
                    }
                }
                cout << "Highest Value in Array: " << arrHighest;
                break;

            case 'G':
            case 'g':
                cout << "Growing array by 5...";
                GrowArray(list, currentSize);
                break;

            case 'S':
            case 's':
                cout << "Shrinking array by 5...";
                ShrinkArray(currentSize);
                break;

            case 'P':
            case 'p':
                PrintArray(list, currentSize);
                break;
        }
        cout << "\n\nSelection >";
        cin >> menuChoice;
    } while (menuChoice != 'Q' and menuChoice != 'q');

    return 0;
}


//- Function Definitions

// Function Use: Print out the array contents
void PrintArray(const int arr[], const int size)
{
    cout << "\nThe array:\n { ";
    for (int i = 0; i < size-1; i++)	// for loop, prints all items except last with commas
        cout << arr[i] << ", ";

    cout << arr[size-1] << " }\n\n";	// prints last item , no comma
}

// Function Use: Insert a new element value at a given index.
// Notes: Given an index, we want to add a number 'newValue' into the array AT that index, and push the numbers starting at that index back one in the array.
//       - This should only be possible / should be nested in an if statement, IF, adding one more element will not exceed the max size
void Insert (int arr[], int& size, int newValue, int index)
{
    if (size + 1 <= MAX ) {
        /* what this for loop is essentially doing is it is starting at the back of the array, and it is making the last element the value of the one before it, meaning the value that was originally the last value of the
            array, is now in empty space within memory UNTIL we increase the size of the array to INCLUDE that value once again.
            we basically cause a mini error that goes undetected and then fix it with the size++ at line 150 */
        for (int i = size; i > index; i--) {
            arr[i] = arr[i-1];
        }
        arr[index] = newValue;
        size++;
    }
    else {
        cout << "\nInserting a new element will out of bound the array.\n";
    }
}

// Function Use: Shift the entire array by an amount of elements.
void Shift (int arr[], int size, int shiftAmount)
{
    int temp[size];

    for (int i = 0; i < size; i++) {
        // Calculate the new index value using modulo arithmetic
        int newIndex = (i + shiftAmount) % size;

        // Copy the value to the new index
        temp[newIndex] = arr[i];
    }

    // Copy the shifted values back to the original array
    for (int i = 0; i < size; i++) {
        arr[i] = temp[i];
    }
}

// Function Use: Given an index, we want to delete the number at that index, and then push the numbers after it backwards into the array.
void Delete (int arr[], int& size, int index)
{
    for (int i = index; i <= size; i++) {
        arr[i] = arr[i+1];
    }
    size--;
}

// Function Use: Reverse the contents of the array
void Reverse (int arr[], int size)
{
    int temp;

    for (int i = 0, j = size-1; i < j; i++, j--)
    {
        temp = arr[i];              // Set a temporary integer to the current array index value
        arr[i] = arr[j];            // Set the current array index value, represented with i, equal to j, which represents the opposite end of the array
        arr[j] = temp;              // Set the opposite side of the array equal to the beginning values of the array
    }
}

// Function Use: Grow Array by 5.
void GrowArray (int arr[], int& size) {
    int oldSize = size;
    size += 5;
    for (int i = oldSize; i <= size; i++) {
        arr[i] = 0;
    }
}

// Function Use: Shrink Array by 5.
void ShrinkArray (int& size) {
    size = size - 5;
}