#include <iostream>

template<class ItemType>
void bubbleSort(ItemType theArray[], int n)
{
    bool sorted = false;
    int pass = 1;
    while (!sorted && (pass < n))
    {
        sorted = true;
        for (int index = 0; index < n - pass; index++)
        {
            int nextIndex = index + 1;
            if (theArray[index] > theArray[nextIndex])
            {
                std::swap(theArray[index], theArray[nextIndex]);
                sorted = false;
            }
        }
        pass++;
    }
}
template<class ItemType>
void rippleSort(ItemType theArray[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (theArray[i] > theArray[j])
            {
                swap(theArray[i], theArray[j]);
            }
        }
    }
}
template<class ItemType>
void insertionSort(ItemType theArray[], int n)
{
    for (int unsorted = 1; unsorted < n; unsorted++)
    {
        ItemType nextItem = theArray[unsorted];
        int loc = unsorted;
        while ((loc > 0) && (theArray[loc - 1] > nextItem))
        {
            theArray[loc] = theArray[loc - 1];
            loc--;
        }
        theArray[loc] = nextItem;
    }
}
template<class ItemType>
void m_sort(ItemType theArray[], int first, int mid, int last, int size)
{
    ItemType *tempArray = new ItemType[size];
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = first1;
    while ((first1 <= last1) && (first2 <= last2))
    {
        if (theArray[first1] <= theArray[first2])
        {
            tempArray[index] = theArray[first1];
            first1++;
        }
        else
        {
            tempArray[index] = theArray[first2];
            first2++;
        }
        index++;
    }
    while (first1 <= last1)
    {
        tempArray[index] = theArray[first1];
        first1++;
        index++;
    }
    while (first2 <= last2)
    {
        tempArray[index] = theArray[first2];
        first2++;
        index++;
    }
    for (index = first; index <= last; index++)
        theArray[index] = tempArray[index];
    delete[] tempArray;
    tempArray = NULL;
}
template<class ItemType>
void mergeSort(ItemType theArray[], int first, int last, int size)
{
    if (first < last)
    {
        int mid = first + (last - first) / 2;
        mergeSort(theArray, first, mid, size);
        mergeSort(theArray, mid + 1, last, size);
        m_sort(theArray, first, mid, last, size);
    }
}
template<class ItemType>
void q_sort(ItemType theArray[], int left, int right, bool random)
{
    int pivot, l_hold, r_hold;
    l_hold = left;
    r_hold = right;
    if (random == false)
        pivot = theArray[left];
    else
        pivot = theArray[lrand(left, right)];
    while (left < right)
    {
        while ((theArray[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            theArray[left] = theArray[right];
            left++;
        }
        while ((theArray[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            theArray[right] = theArray[left];
            right--;
        }
    }
    theArray[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        q_sort(theArray, left, pivot - 1, random);
    if (right > pivot)
        q_sort(theArray, pivot + 1, right, false);
}
template<class ItemType>
void quickSort(ItemType theArray[], int n, bool random)
{
    q_sort(theArray, 0, n - 1, random);
}
template<class ItemType>
int findIndexofLargest(const ItemType theArray[], int size)
{
    int indexSoFar = 0;
    for (int currentIndex = 1; currentIndex < size; currentIndex++)
    {
        if (theArray[currentIndex] > theArray[indexSoFar])
            indexSoFar = currentIndex;
    }
    return indexSoFar;
}
template<class ItemType>
void selectionSort(ItemType theArray[], int n)
{
    for (int last = n - 1; last >= 1; last--)
    {
        int largest = findIndexofLargest(theArray, last + 1);
        std::swap(theArray[largest], theArray[last]);
    }
}
template<class ItemType>
void shellSort(ItemType theArray[], int n)
{
    for (int h = n / 2; h > 0; h = h / 2)
    {
        for (int unsorted = h; unsorted < n; unsorted++)
        {
            ItemType nextItem = theArray[unsorted];
            int loc = unsorted;
            while ((loc >= h) && (theArray[loc - h] > nextItem))
            {
                theArray[loc] = theArray[loc - h];
                loc = loc - h;
            }
            theArray[loc] = nextItem;
        }
    }
}
template<class ItemType>
void heapDown(ItemType theArray[], int root, int bottom)
{
    int maxChild, leftChild, rightChild;
    leftChild = root * 2 + 1;
    rightChild = root * 2 + 2;
    if (leftChild <= bottom)
    {
        if (leftChild == bottom)
            maxChild = leftChild;
        else
        {
            if (theArray[leftChild] <= theArray[rightChild])
                maxChild = rightChild;
            else
                maxChild = leftChild;
        }
        if (theArray[root] < theArray[maxChild])
        {
            swap(theArray[root], theArray[maxChild]);
            heapDown(theArray, maxChild, bottom);
        }
    }
}
template<class ItemType>
void heapSort(ItemType theArray[], int n)
{
    int s;
    for (s = (n / 2) - 1; s >= 0; s--)
        heapDown(theArray, s, n);
    for (s = n - 1; s >= 1; s--)
    {
        swap(theArray[0], theArray[s]);
        heapDown(theArray, 0, s - 1);
    }
}


#if 0 // #if 1 to compile as a standalone program, not a library
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <climits>
#include <cmath>
#include <sys/timeb.h>

#ifndef DRAND_H
#define DRAND_H

void initrand(unsigned long seed);    // initializing RNG with seed
long lrand(long min, long max);        // returns a random natural number between min and max, inclusive

#endif

using namespace std;
int increm(int num);
unsigned short sort(char type, int theArray[], int size);
unsigned short timer(_timeb start, _timeb end);
static bool z;
#define MIN_SIZE 1000 // min size array
#define MAX_SIZE 100000 // max size array
#define NUM_PASS 5 // number of passes for average
#define SET_WIDTH 10 // column width of time output
// returns a greater selection of array sizes
// eg: 1000...5000...10000...50000...100000...
int increm(int num)
{
    if (z == true)
    {
        z = false;
        return num * 5; // eg: 1000 * 5 = 5000
    } //  10000 * 5 = 50000
    else
    {
        z = true;
        return num * 2; // eg: 5000 * 2 = 10000
    } //  50000 * 2 = 100000
}
// sorting user interface
unsigned short sort(char type, int theArray[], int size)
{
    struct _timeb start, end;
    int *copy = new int[size + 1];
    for (int i = 0; i < size; i++) // copy original array to do sort on
        copy[i] = theArray[i];
    switch (type)
    {
        case 'm': // Merge Sort
            _ftime(&start);
            mergeSort(copy, 0, size - 1, size);
            _ftime(&end);
            break;
        case 'q': // Quick Sort an Unsorted Array with First Index as Pivot
            _ftime(&start);
            quickSort(copy, size, false);
            _ftime(&end);
            break;
        case 'Q': // Quick Sort an Unsorted Array with Random Index as Pivot
            _ftime(&start);
            quickSort(copy, size, true);
            _ftime(&end);
            break;
        case 'u': // Quick Sort a Sorted Array with First Index as Pivot
            quickSort(copy, size, false); // sort the array first
            _ftime(&start);
            quickSort(copy, size, false); // perform sort on sorted array
            _ftime(&end);
            break;
        case 'U': // Quick Sort a Sorted Array with Random Index as Pivot
            quickSort(copy, size, false); // sort the array first
            _ftime(&start);
            quickSort(copy, size, true); // perform sort on sorted array
            _ftime(&end);
            break;
        case 'h': // Heap Sort
            _ftime(&start);
            heapSort(copy, size);
            _ftime(&end);
            break;
        case 's': // Shell Sort
            _ftime(&start);
            shellSort(copy, size);
            _ftime(&end);
            break;
        case 'b': // Bubble Sort
            _ftime(&start);
            bubbleSort(copy, size);
            _ftime(&end);
            break;
        case 'r': // Ripple Sort
            _ftime(&start);
            rippleSort(copy, size);
            _ftime(&end);
            break;
        case 'i': // Insertion Sort
            _ftime(&start);
            insertionSort(copy, size);
            _ftime(&end);
            break;
        case 'S': // Selection Sort
            _ftime(&start);
            selectionSort(copy, size);
            _ftime(&end);
            break;
        default:
            delete[] copy;
            return 0;
    }
    delete[] copy; // dispose copied array; only concerned about the time to sort
    copy = NULL;
    return timer(start, end);
}
// timer
unsigned short timer(_timeb start, _timeb end)
{
    if (start.time != end.time)
        return ((unsigned short)(end.time - start.time) * 1000) + (end.millitm - start.millitm);
    else
        return (end.millitm - start.millitm);
}
int main()
{
    // seeding the RNG using current time
    time_t seed;
    time(&seed);
    initrand(seed);
    // creating an array with random elements
    static int *a = new int[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
        a[i] = lrand(0, INT_MAX);
    // SORT TYPES
    char m = 'm'; // Merge Sort
    char q = 'q'; // Quick Sort a Unsorted Array with First Index as Pivot
    char Q = 'Q'; // Quick Sort a Unsorted Array with a Random Index as Pivot
    char u = 'u'; // Quick Sort a Sorted Array with First Index as Pivot
    char U = 'U'; // Quick Sort a Sorted Array with a Random Index as Pivot
    char h = 'h'; // Heap Sort
    char s = 's'; // Shell Sort
    char b = 'b'; // Bubble Sort
    char r = 'r'; // Ripple Sort
    char i = 'i'; // Insertion Sort
    char S = 'S'; // Selection Sort
    // To use the sorting user interface...
    // sort( <sort type> , <the array> , <the array's size> )
    cout << "Sort times are in milliseconds (Average of " << NUM_PASS << " passes)..." << endl;
    cout << "Merge\t\t\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(m, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Quick(Unsorted/First)\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(q, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Quick(Unsorted/Random)\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(Q, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Quick(Sorted/First)\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(u, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Quick(Sorted/Random)\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(U, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Heap\t\t\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(h, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Shell\t\t\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(s, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Bubble\t\t\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(b, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Ripple\t\t\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(r, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Insertion\t\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(i, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Selection\t\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
    {
        double avg = 0.0;
        for (int y = 1; y <= NUM_PASS; y++)
            avg += sort(S, a, x);
        cout << right << setw(SET_WIDTH) << lround(avg / NUM_PASS) << flush;
    }
    cout << endl;
    cout << "Num Elements\t\t";
    z = true;
    for (int x = MIN_SIZE; x <= MAX_SIZE; x = increm(x))
        cout << right << setw(SET_WIDTH) << x << flush;
    cout << endl;
    delete[] a;
    a = NULL;
    int stop;
    cin >> stop;
    return 0;
}
#endif
