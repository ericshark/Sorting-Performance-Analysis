#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

const int MAX = 100; //Element Size

void InsertionSort(int A[], int n, unsigned long long &stepCount);
void SelectionSort(int A[], int n, unsigned long long &stepCount);
void BubbleSort(int A[], int n, unsigned long long &stepCount);
void MergeSort(int A[], int begin, int end, unsigned long long &stepCount);
void Merge(int A[], int begin, int mid, int end, unsigned long long &stepCount);
void QuickSort(int A[], int begin, int end, unsigned long long &stepCount);
int Lpartition(int A[], int l, int r, unsigned long long &stepCount);
void HeapSort(int A[], int n, unsigned long long &stepCount);
void Heapify(int A[], int n, int k, unsigned long long &stepCount);
void generateRandomData(int A[], int n);

int main()
{
    int A[MAX], B[MAX];
    // Initialize array B with randomly generated numbers from the range 1 to n
    generateRandomData(B, MAX);
    clock_t start, end;
    unsigned long long stepCount;
    // Reset and Sort using Insertion Sort
    for (int i = 0; i < MAX; i++)
        A[i] = B[i]; // Reset A
    stepCount = 0;
    start = clock();
    InsertionSort(A, MAX, stepCount);
    end = clock();
    cout << "Time taken by Insertion Sort: " << fixed << setprecision(6)
         << double(end - start) / double(CLOCKS_PER_SEC) << " seconds" << endl;
    cout << "Number of steps for Insertion Sort: " << stepCount << endl;

    // Reset and Sort using Selection Sort
    for (int i = 0; i < MAX; i++)
        A[i] = B[i]; // Reset A
    stepCount = 0;
    start = clock();
    SelectionSort(A, MAX, stepCount);
    end = clock();
    cout << "Time taken by Selection Sort: " << fixed << setprecision(6)
         << double(end - start) / double(CLOCKS_PER_SEC) << " seconds" << endl;
    cout << "Number of steps for Selection Sort: " << stepCount << endl;

    // Reset and Sort using Bubble Sort
    for (int i = 0; i < MAX; i++)
        A[i] = B[i]; // Reset A
    stepCount = 0;
    start = clock();
    BubbleSort(A, MAX, stepCount);
    end = clock();
    cout << "Time taken by Bubble Sort: " << fixed << setprecision(6)
         << double(end - start) / double(CLOCKS_PER_SEC) << " seconds" << endl;
    cout << "Number of steps for Bubble Sort: " << stepCount << endl;

    // Reset and Sort using Merge Sort
    for (int i = 0; i < MAX; i++)
        A[i] = B[i]; // Reset A
    stepCount = 0;
    start = clock();
    MergeSort(A, 0, MAX - 1, stepCount);
    end = clock();
    cout << "Time taken by Merge Sort: " << fixed << setprecision(6)
         << double(end - start) / double(CLOCKS_PER_SEC) << " seconds" << endl;
    cout << "Number of steps for Merge Sort: " << stepCount << endl;

    // Reset and Sort using Quick Sort
    for (int i = 0; i < MAX; i++)
        A[i] = B[i]; // Reset A
    stepCount = 0;
    start = clock();
    QuickSort(A, 0, MAX - 1, stepCount);
    end = clock();
    cout << "Time taken by Quick Sort: " << fixed << setprecision(6)
         << double(end - start) / double(CLOCKS_PER_SEC) << " seconds" << endl;
    cout << "Number of steps for Quick Sort: " << stepCount << endl;

    // Reset and Sort using Heap Sort
    for (int i = 0; i < MAX; i++)
        A[i] = B[i]; // Reset A
    stepCount = 0;
    start = clock();
    HeapSort(A, MAX, stepCount);
    end = clock();
    cout << "Time taken by Heap Sort: " << fixed << setprecision(6)
         << double(end - start) / double(CLOCKS_PER_SEC) << " seconds" << endl;
    cout << "Number of steps for Heap Sort: " << stepCount << endl;

    return 0;
}

void InsertionSort(int A[], int n, unsigned long long &stepCount)
{
    stepCount += 2;
    for (int i = 1; i < n; i++)
    {
        int tmp = A[i], j = i - 1;
        stepCount += 6;
        while (j >= 0 && A[j] > tmp)
        {

            A[j + 1] = A[j];
            j--;
            stepCount += 2; // Increment step count
        }
        A[j + 1] = tmp;
    }
}

void SelectionSort(int A[], int n, unsigned long long &stepCount)
{
    stepCount += 2; // initialization of i and end of loop comparison for i < n-1
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        stepCount += 6; // i<n-1, i++, min_index = i, j = i+1, end of inner loop comparison, swap at end
        for (int j = i + 1; j < n; j++)
        {
            if (A[j] < A[min_index])
            {
                min_index = j;
                stepCount++; // min_index = j
            }
            stepCount += 3; // j<n comparison, j++, A[j] < A[min_index] comparison
        }
        swap(A[i], A[min_index]);
    }
}

void BubbleSort(int A[], int n, unsigned long long &stepCount)
{
    stepCount += 2; // initialization of i and end of loop comparison for i < n-1
    for (int i = 0; i < n - 1; i++)
    {
        stepCount += 4; // i<n-1, i++, int j = 0, end of inner loop comparison for j < n-i-1
        for (int j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(A[j], A[j + 1]);
                stepCount++; // swap
            }
            stepCount += 3; // j < n-i-1, i++, comparison of A[j] > A[j+1]
        }
    }
}

void MergeSort(int A[], int begin, int end, unsigned long long &stepCount)
{
    stepCount++; // comparison of if(begin < end)
    if (begin < end)
    {
        int mid = (begin + end) / 2;
        stepCount++; // mid = (begin + end) / 2
        MergeSort(A, begin, mid, stepCount);
        stepCount++; // Recursive of 1st half
        MergeSort(A, mid + 1, end, stepCount);
        stepCount++; // Recursive of 2nd half
        Merge(A, begin, mid, end, stepCount);
        stepCount++; // Merging of arrays
    }
}

void Merge(int A[], int begin, int mid, int end, unsigned long long &stepCount)
{
    int *B = new int[end - begin + 1];
    int i = begin, j = mid + 1, k = 0;
    stepCount += 4; // initialization of *B, i, j, k
    while (i <= mid && j <= end)
    {
        if (A[i] < A[j])
        {
            B[k++] = A[i++];
            stepCount++; // B[k++] = A[i++];
        }
        else
        {
            B[k++] = A[j++];
            stepCount++; // else
        }
        stepCount += 2; // while loop comparison, A[i] < A[j] comparison
    }
    while (i <= mid)
    {
        B[k++] = A[i++];
        stepCount += 2; // comparison of i <= mid, B[k++] = A[i++]
    }
    stepCount++; // breaking out of while loop
    while (j <= end)
    {
        B[k++] = A[j++];
        stepCount += 2; // comparison of j<=end, B[k++] = A[j++]
    }
    stepCount++; // breaking out of while loop
    stepCount += 2;
    for (i = begin, k = 0; i <= end; i++, k++)
    {
        A[i] = B[k];
        stepCount += 3; // i <= end comparison
    }
    delete[] B;
    stepCount++; // delete[] B
}

void QuickSort(int A[], int begin, int end, unsigned long long &stepCount)
{
    stepCount += 1; // Increment at the beginning
    if (begin < end)
    {
        int p = Lpartition(A, begin, end, stepCount);
        stepCount++; // partition
        QuickSort(A, begin, p - 1, stepCount);
        stepCount++; // quicksort recursive
        QuickSort(A, p + 1, end, stepCount);
        stepCount++; // quicksort recursive
    }
}

int Lpartition(int A[], int l, int r, unsigned long long &stepCount)
{
    int pivot = A[r];
    int i = l - 1;
    stepCount += 3; // pivot, i initialization and j initialization
    for (int j = l; j < r; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            swap(A[i], A[j]);
            stepCount += 2; // i++, swap
        }
        stepCount += 3; // j<r, j++, comparison of A[j] < pivot
    }
    swap(A[i + 1], A[r]);
    stepCount++; // swap
    return i + 1;
}

void HeapSort(int A[], int n, unsigned long long &stepCount)
{
    stepCount += 2; // initialization of n and end of loop comparison for i >= 0
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        Heapify(A, n, i, stepCount);
        stepCount += 3; // i >= 0, i--, heapify
    }
    stepCount += 2; // Initialization and increment for end of loop
    for (int i = n - 1; i > 0; i--)
    {
        swap(A[0], A[i]);
        Heapify(A, i, 0, stepCount);
        stepCount += 4; // i > 0, i--, swap, heapify
    }
}

void Heapify(int A[], int n, int i, unsigned long long &stepCount)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    stepCount += 6; // Increment for initial assignments and comparisons

    if (left < n && A[left] > A[largest])
    {
        largest = left;
        stepCount++; // largest = left
    }

    if (right < n && A[right] > A[largest])
    {
        largest = right;
        stepCount++; // largest = right
    }

    if (largest != i)
    {
        swap(A[i], A[largest]);
        Heapify(A, n, largest, stepCount);
        stepCount += 2; // swap and heapify
    }
}

void generateRandomData(int A[], int n)
{
    srand(time(NULL)); // makes sure that the random data aren't in same sequence
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % n + 1; // Random number in [1, n]
    }
}