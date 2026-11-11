/*
 * Course: COEN 2220 - Programming 2
 * Name: [Luis D. Cruz]
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Preserve parcel arrival records and search a ready-only view
 * Due date: [11/11/2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct Parcel
{
    int pickupCode;
    string locker;
    bool ready;
};

void displayParcels(const Parcel parcels[], int count);
void displayReady(Parcel *view[], int count);
void swapParcelPointers(Parcel *&left, Parcel *&right);
int partitionReady(Parcel *view[], int first, int last);
void quickSortReady(Parcel *view[], int first, int last);
int binaryFindReady(Parcel *view[], int count, int target);

int main()
{
    const int CAPACITY = 8;

    Parcel parcels[CAPACITY] = {
        {640, "L-4", true},
        {215, "L-8", false},
        {580, "L-2", true},
        {325, "L-6", true},
        {710, "L-1", true},
        {460, "L-5", false},
        {190, "L-3", true},
        {505, "L-7", true}
    };

    Parcel *readyView[CAPACITY];
    int readyCount = 0;

    cout << boolalpha << "Original arrival records:" << endl;
    displayParcels(parcels, CAPACITY);

    for (int index = 0; index < CAPACITY; index++)
    {
        if (parcels[index].ready)
        {
            readyView[readyCount] = &parcels[index];
            readyCount++;
        }
    }

    quickSortReady(readyView, 0, readyCount - 1);

    cout << "Ready parcels by pickup code:" << endl;
    displayReady(readyView, readyCount);

    cout << "Original arrival records after sorting:" << endl;
    displayParcels(parcels, CAPACITY);

     //--- STEP D1: Activate after completing the search function ---
    
    int target;

    cout << "Enter a pickup code: ";

    if (!(cin >> target))
    {
        cout << "Invalid code input." << endl;
        return 1;
    }

    int position = binaryFindReady(readyView, readyCount, target);

    if (position == -1)
    {
        cout << "No ready parcel with that code." << endl;
    }
    else
    {
        cout << "Pickup code "
             << readyView[position]->pickupCode
             << " | Locker: "
             << readyView[position]->locker
             << endl;
    }
    

    return 0;
}


// ===== Resolve only these TODOs now (Part C) =====

void swapParcelPointers(Parcel *&left, Parcel *&right)
{
    Parcel *saved = left;
    left = right;
    right = saved;
}

int partitionReady(Parcel *view[], int first, int last)
{
    int middle = first + (last - first) / 2;

    swapParcelPointers(view[first], view[middle]);

    int pivotCode = view[first]->pickupCode;
    int boundary = first;

    for (int scan = first + 1; scan <= last; scan++)
    {
        if (view[scan]->pickupCode < pivotCode)
        {
            boundary++;

            swapParcelPointers(
                view[boundary],
                view[scan]
            );
        }
    }

    swapParcelPointers(
        view[first],
        view[boundary]
    );

    return boundary;
}

void quickSortReady(Parcel *view[], int first, int last)
{
    if (first >= last)
    {
        return;
    }

    int pivotIndex =
        partitionReady(view, first, last);

    quickSortReady(
        view,
        first,
        pivotIndex - 1
    );

    quickSortReady(
        view,
        pivotIndex + 1,
        last
    );
}


// ===== Resolve this TODO later (Part D) =====

int binaryFindReady(Parcel *view[], int count, int target)
{
    int first = 0;
    int last = count - 1;

    while (first <= last)
    {
        int middle = first + (last - first) / 2;

        if (view[middle]->pickupCode == target)
        {
            return middle;
        }

        if (view[middle]->pickupCode < target)
        {
            first = middle + 1;
        }
        else
        {
            last = middle - 1;
        }
    }

    return -1;
}

void displayParcels(const Parcel parcels[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Code: "
             << parcels[index].pickupCode
             << " | Locker: "
             << parcels[index].locker
             << " | Ready: "
             << parcels[index].ready
             << endl;
    }
}

void displayReady(Parcel *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "View index: "
             << index
             << " | Code: "
             << view[index]->pickupCode
             << " | Locker: "
             << view[index]->locker
             << endl;
    }
}

/*
 * Analysis Answers
 *
 * C3 - Partition decisions
 *
 * Initial ready view:
 * 640, 580, 325, 710, 190, 505
 *
 * first = 0
 * last = 5
 * middle = 2
 * pivotCode = 325
 *
 * Move the middle pointer to the first position:
 * 325, 580, 640, 710, 190, 505
 *
 * boundary = 0
 *
 * scan = 1, code = 580
 * 580 < 325 is false.
 * boundary stays 0.
 *
 * scan = 2, code = 640
 * 640 < 325 is false.
 * boundary stays 0.
 *
 * scan = 3, code = 710
 * 710 < 325 is false.
 * boundary stays 0.
 *
 * scan = 4, code = 190
 * 190 < 325 is true.
 * boundary becomes 1.
 * Swap view[1] and view[4]:
 * 325, 190, 640, 710, 580, 505
 *
 * scan = 5, code = 505
 * 505 < 325 is false.
 * boundary stays 1.
 *
 * The next loop test is scan = 6.
 * 6 <= 5 is false, so the loop ends.
 *
 * Finally, swap the pivot with view[1]:
 * 190, 325, 640, 710, 580, 505
 *
 * The pivot 325 finishes at index 1.
 *
 *
 * C4 - Data and memory
 *
 * Swapping two Parcel pointers changes only the addresses stored
 * inside readyView. The Parcel objects themselves are not moved
 * or modified.
 *
 * The parcels array in main owns the Parcel objects.
 * readyView only borrows their addresses.
 *
 * The view must not delete the pointers because it did not create
 * the objects with new. The Parcel objects remain owned by parcels.
 *
 *
 * D3 - Search positions and absence
 *
 * Search for code 505:
 *
 * Sorted ready view:
 * 190, 325, 505, 580, 640, 710
 *
 * first = 0, last = 5, middle = 2
 * Code at view[2] is 505.
 * 505 == 505, so the function returns view index 2.
 *
 * Code 505 is originally stored in a different position inside
 * the parcels array. The returned value is an index of readyView,
 * not an index of parcels.
 *
 *
 * Search for code 460:
 *
 * first = 0, last = 5, middle = 2, code = 505
 * 505 > 460, so last becomes 1.
 *
 * first = 0, last = 1, middle = 0, code = 190
 * 190 < 460, so first becomes 1.
 *
 * first = 1, last = 1, middle = 1, code = 325
 * 325 < 460, so first becomes 2.
 *
 * Now first = 2 and last = 1.
 * Since first > last, the search ends and returns -1.
 *
 * Code 460 exists in the original parcels array, but it is not ready,
 * so it was never added to readyView.
 *
 * A view index cannot be used directly as an index into parcels because
 * readyView is filtered and reordered. Each view position stores a pointer
 * to the original Parcel object.
 *
 *
 * D4 - Time and auxiliary space
 *
 * If the ready view is scanned for every query:
 * q searches take O(qn) time.
 *
 * If the view is sorted once and then binary search is used:
 *
 * Quicksort worst case:
 * O(n^2)
 *
 * Quicksort with balanced partitions:
 * O(n log n)
 *
 * Each binary search:
 * O(log n)
 *
 * Balanced total for q searches:
 * O(n log n + q log n)
 *
 * Worst-case total:
 * O(n^2 + q log n)
 *
 * Iterative binary search uses O(1) auxiliary space.
 *
 * The pointer view itself uses O(n) storage.
 * Quicksort also uses recursive call space:
 * O(log n) with balanced partitions and O(n) in the worst case.
 */