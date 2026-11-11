# Lab 12 - Project Application

## E1 - Filter and ownership

The selected order IDs are 420, 180, 310, and 205 because they are DELIVERY orders and their status is either PENDING or IN_PROGRESS.

Order 650 is excluded because it is DINE_IN.

Order 900 is excluded because it is COMPLETED.

The original orders array owns the OrderPreview objects. The delivery view only stores borrowed pointers to those objects, so the view does not delete them.

## E2 - Report order and algorithm

The observed report order is:

205, 310, 420, 180

The report first sorts by building in ascending order.

Inside the same building, higher priority comes first.

If the building and priority are the same, the lower order ID comes first.

I used quicksort on the pointer view.

Balanced quicksort takes O(n log n) time.

In the worst case, quicksort can take O(n^2) time.

The pointer view uses O(n) additional storage.

The recursive quicksort calls use O(log n) space with balanced partitions and O(n) in the worst case.

## E3 - Lookup choice and tests

Binary search by orderId cannot be used on this report because the view is not sorted globally by orderId.

The report is sorted by building, then priority, and then orderId only as a tie breaker.

Because of this, the search by ID uses linear search.

Found test:
205 was found in Biblioteca with priority 3.

Excluded test:
900 was not found because it is completed and is not included in the active delivery report.

Nonexistent test:
999 was not found because no order has that ID.

A second view sorted only by orderId would require additional memory and extra sorting work, but it would allow binary search by ID.

## E4 - Evidence and project connection

Source: delivery_report_practice.cpp

Output: delivery_report_output.txt

I verified that the original orders stayed in the same order by printing them before and after creating and sorting the delivery view.

The field values also remained the same because only the pointers inside the view were moved.

This protects the operational FIFO sequence because the original order collection is not reorganized when the temporary report is sorted.