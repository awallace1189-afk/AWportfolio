function solveSudoku(grid):
    if isComplete(grid):
        return true

    row, col = findEmptyCell(grid)
    for digit from 1 to 9:
        if isValidPlacement(grid, row, col, digit):
            grid[row][col] = digit
            if solveSudoku(grid):
                return true
            grid[row][col] = 0  // backtrack

    return false

function isComplete(grid):
    for each cell in grid:
        if cell == 0:
            return false
    return true

function findEmptyCell(grid):
    for r from 0 to 8:
        for c from 0 to 8:
            if grid[r][c] == 0:
                return (r, c)
    return (-1, -1)

function isValidPlacement(grid, row, col, digit):
    return not inRow(grid, row, digit)
        and not inCol(grid, col, digit)
        and not inBox(grid, row, col, digit)

function inRow(grid, row, digit):
    for c from 0 to 8:
        if grid[row][c] == digit:
            return true
    return false

function inCol(grid, col, digit):
    for r from 0 to 8:
        if grid[r][col] == digit:
            return true
    return false

function inBox(grid, row, col, digit):
    startRow = (row // 3) * 3
    startCol = (col // 3) * 3
    for r from startRow to startRow + 2:
        for c from startCol to startCol + 2:
            if grid[r][c] == digit:
                return true
    return false