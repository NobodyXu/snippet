#!/usr/bin/env py

import sys
import numpy as np

def exchange_row(arr, x, y):
    arr[x], arr[y] = arr[y], np.array(arr[x], copy=True)

# find searches from the start_row the the last row of a np.narray to find a
# row that satisfy comp(row).
# If it is not found. None is returned.
def find(matrix, start_row, comp):
    for row in range(start_row, np.shape(matrix)[0]):
        if comp(matrix[row]):
            return row
    return None

# Get matrix
m = np.array(np.mat(input("Please enter a 2-dimension augmented matrix\n\
                          (in matlib form, eg 1 2; 3 4)\n")),
             dtype = float, order = "C")
row, column = np.shape(m)

#  Check input matrix
if np.ndim(m) != 2:
    print("Not a 2-dimension matrix!\nQuit!")
    sys.exit()

if column < 2:
    print("Not an augmented marix!\nQuit!")
    sys.exit()

rows_to_be_reduced = min(row, column - 1)
for i in range(rows_to_be_reduced):
    ## Make the i-th element of the i-th row != 0 by searching from row i to the end
    row_to_exchange = find(m, i, lambda row, col=i: row[col] != 0)
    if row_to_exchange is None:# A row satisfies that condition cannot be found
        continue
    exchange_row(m, i, row_to_exchange)
    ## Make i-th element of the row == 1
    m[i] /= m[i][i]
    ## Then eliminate the i-th element of all other rows to 0
    for j in (k for k in range(row) if k != i):
        m[j] -= m[j][i] * m[i]

# Move all-zero rows to bottom
i = rows_to_be_reduced
line_for_all_zeros = row - 1
while i < line_for_all_zeros:
    if np.count_nonzero(m[i]) == 0:
        exchange_row(m, i, line_for_all_zeros)
        line_for_all_zeros -= 1
    else:
        i += 1

print(m)
