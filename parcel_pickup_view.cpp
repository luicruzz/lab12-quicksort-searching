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

    // --- STEP D1: Activate after completing the search function ---
    /*
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
    */

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
    // TODO (Part D): Implement iterative binary search by pickupCode on the sorted view.

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
 * Trace code 505 and absent code 460.
 * Answer:
 *
 * D4 - Time and auxiliary space
 * Compare sorting once + binary search vs repeated scanning.
 * Answer:
 */