/*
 * Course: COEN 2220 - Programming 2
 * Name: [Luis D. Cruz]
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Guided equipment catalog and code lookup
 * Due date: [11/11/2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct Equipment
{
    int assetCode;
    string cabinet;
};

void displayEquipment(const Equipment equipment[], int count);
void swapEquipment(Equipment& left, Equipment& right);
int partitionEquipment(Equipment equipment[], int first, int last);
void quickSortEquipment(Equipment equipment[], int first, int last);
int binaryFindEquipment(const Equipment equipment[], int first, int last, int target);

int main()
{
    const int COUNT = 8;

    Equipment equipment[COUNT] = {
        {48, "C-4"},
        {21, "A-2"},
        {63, "D-1"},
        {35, "B-3"},
        {57, "C-2"},
        {14, "A-1"},
        {72, "D-4"},
        {29, "B-1"}
    };

    cout << "Inspection order:" << endl;
    displayEquipment(equipment, COUNT);

    // B2 later
quickSortEquipment(equipment, 0, COUNT - 1);

cout << "Sorted by asset code:" << endl;
displayEquipment(equipment, COUNT);
    // B3 later
    int target;

cout << "Enter an asset code: ";

if (!(cin >> target))
{
    cout << "Invalid code input." << endl;
    return 1;
}

int position = binaryFindEquipment(
    equipment,
    0,
    COUNT - 1,
    target
);

if (position == -1)
{
    cout << "Equipment not found." << endl;
}
else
{
    cout << "Found code "
         << equipment[position].assetCode
         << " in cabinet "
         << equipment[position].cabinet
         << endl;
}

    return 0;
}

void displayEquipment(const Equipment equipment[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Code: " << equipment[index].assetCode
             << " | Cabinet: " << equipment[index].cabinet
             << endl;
    }
}

void swapEquipment(Equipment& left, Equipment& right)
{
    Equipment saved = left;
    left = right;
    right = saved;
}

int partitionEquipment(Equipment equipment[], int first, int last)
{
    int middle = first + (last - first) / 2;

    swapEquipment(equipment[first], equipment[middle]);

    int pivotCode = equipment[first].assetCode;
    int boundary = first;

    for (int scan = first + 1; scan <= last; scan++)
    {
        if (equipment[scan].assetCode < pivotCode)
        {
            boundary++;
            swapEquipment(equipment[boundary], equipment[scan]);
        }
    }

    swapEquipment(equipment[first], equipment[boundary]);

    return boundary;
}

void quickSortEquipment(Equipment equipment[], int first, int last)
{
    if (first >= last)
    {
        return;
    }

    int pivotIndex = partitionEquipment(equipment, first, last);

    quickSortEquipment(equipment, first, pivotIndex - 1);
    quickSortEquipment(equipment, pivotIndex + 1, last);
}

int binaryFindEquipment(
    const Equipment equipment[],
    int first,
    int last,
    int target
)
{
    if (first > last)
    {
        return -1;
    }

    int middle = first + (last - first) / 2;

    if (equipment[middle].assetCode == target)
    {
        return middle;
    }

    if (equipment[middle].assetCode < target)
    {
        return binaryFindEquipment(
            equipment,
            middle + 1,
            last,
            target
        );
    }

    return binaryFindEquipment(
        equipment,
        first,
        middle - 1,
        target
    );
}

/*
 * Analysis Answers
 *
 * B4 - Partition and recursive control
 *
 * The first pivot is 35 and it finishes at index 3.
 * The next ranges are 0..2 and 4..7.
 *
 * After the first partition the array is:
 * 29, 21, 14, 35, 57, 63, 72, 48
 *
 * The whole array is not sorted yet because the left side
 * and the right side still have values out of order.
 * Quicksort still has to sort both ranges recursively.
 *
 *
 * B5 - A search that fails
 *
 * Search for code 36:
 *
 * first=0, last=7, middle=3, code=35
 * 35 < 36, so search 4..7
 *
 * first=4, last=7, middle=5, code=57
 * 57 > 36, so search 4..4
 *
 * first=4, last=4, middle=4, code=48
 * 48 > 36, so search 4..3
 *
 * Now first > last, so the range is empty and the function
 * returns -1. Each previous recursive call returns that same
 * -1 until it reaches main. No invalid array position is accessed.
 */