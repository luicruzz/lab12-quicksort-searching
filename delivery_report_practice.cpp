/*
 * Course: COEN 2220 - Programming 2
 * Name: [Luis D. Cruz]
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Delivery report sorting and ID lookup practice
 * Due date: [11/11/2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct OrderPreview
{
    int orderId;
    string orderType;
    string status;
    string building;
    int priority;
};

void displayOrders(const OrderPreview orders[], int count);
void displayView(OrderPreview *view[], int count);

void swapOrderPointers(OrderPreview *&left, OrderPreview *&right);

bool comesBefore(const OrderPreview *left, const OrderPreview *right);

int partitionOrders(OrderPreview *view[], int first, int last);
void quickSortOrders(OrderPreview *view[], int first, int last);

int findOrderInView(OrderPreview *view[], int count, int targetId);

int main()
{
    const int COUNT = 6;

    OrderPreview orders[COUNT] = {
        {420, "DELIVERY", "PENDING", "Biblioteca", 1},
        {180, "DELIVERY", "IN_PROGRESS", "Ingenieria", 3},
        {650, "DINE_IN", "PENDING", "Cafeteria-Lunch", 1},
        {310, "DELIVERY", "PENDING", "Biblioteca", 3},
        {205, "DELIVERY", "PENDING", "Biblioteca", 3},
        {900, "DELIVERY", "COMPLETED", "Ingenieria", 2}
    };

    OrderPreview *deliveryView[COUNT];
    int viewCount = 0;

    cout << "Original orders:" << endl;
    displayOrders(orders, COUNT);

    for (int index = 0; index < COUNT; index++)
    {
        bool active =
            orders[index].status == "PENDING" ||
            orders[index].status == "IN_PROGRESS";

        if (orders[index].orderType == "DELIVERY" && active)
        {
            deliveryView[viewCount] = &orders[index];
            viewCount++;
        }
    }

    quickSortOrders(deliveryView, 0, viewCount - 1);

    cout << endl;
    cout << "Delivery report:" << endl;
    displayView(deliveryView, viewCount);

    int targetId;

    cout << endl;
    cout << "Enter an order ID: ";
    cin >> targetId;

    int position =
        findOrderInView(deliveryView, viewCount, targetId);

    if (position == -1)
    {
        cout << "Order not found in delivery report." << endl;
    }
    else
    {
        cout << "Order ID: "
             << deliveryView[position]->orderId
             << " | Building: "
             << deliveryView[position]->building
             << " | Status: "
             << deliveryView[position]->status
             << " | Priority: "
             << deliveryView[position]->priority
             << endl;
    }

    cout << endl;
    cout << "Original orders after report:" << endl;
    displayOrders(orders, COUNT);

    return 0;
}

void displayOrders(const OrderPreview orders[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "ID: " << orders[index].orderId
             << " | Type: " << orders[index].orderType
             << " | Status: " << orders[index].status
             << " | Building: " << orders[index].building
             << " | Priority: " << orders[index].priority
             << endl;
    }
}

void displayView(OrderPreview *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "ID: " << view[index]->orderId
             << " | Building: " << view[index]->building
             << " | Priority: " << view[index]->priority
             << " | Status: " << view[index]->status
             << endl;
    }
}

void swapOrderPointers(OrderPreview *&left, OrderPreview *&right)
{
    OrderPreview *saved = left;
    left = right;
    right = saved;
}

bool comesBefore(const OrderPreview *left, const OrderPreview *right)
{
    if (left->building < right->building)
    {
        return true;
    }

    if (left->building > right->building)
    {
        return false;
    }

    if (left->priority > right->priority)
    {
        return true;
    }

    if (left->priority < right->priority)
    {
        return false;
    }

    return left->orderId < right->orderId;
}

int partitionOrders(OrderPreview *view[], int first, int last)
{
    int middle = first + (last - first) / 2;

    swapOrderPointers(view[first], view[middle]);

    OrderPreview *pivot = view[first];
    int boundary = first;

    for (int scan = first + 1; scan <= last; scan++)
    {
        if (comesBefore(view[scan], pivot))
        {
            boundary++;
            swapOrderPointers(view[boundary], view[scan]);
        }
    }

    swapOrderPointers(view[first], view[boundary]);

    return boundary;
}

void quickSortOrders(OrderPreview *view[], int first, int last)
{
    if (first >= last)
    {
        return;
    }

    int pivotIndex =
        partitionOrders(view, first, last);

    quickSortOrders(view, first, pivotIndex - 1);
    quickSortOrders(view, pivotIndex + 1, last);
}

int findOrderInView(OrderPreview *view[], int count, int targetId)
{
    for (int index = 0; index < count; index++)
    {
        if (view[index]->orderId == targetId)
        {
            return index;
        }
    }

    return -1;
}