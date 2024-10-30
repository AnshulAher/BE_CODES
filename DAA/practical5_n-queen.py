def is_safe(board, row, col, n):
    # Check the row on the left side
    for i in range(col):
        if board[row][i] == 1:
            return False

    # Check the upper diagonal on the left side
    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False

    # Check the lower diagonal on the left side
    for i, j in zip(range(row, n, 1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False

    return True

def solve_nqueens(board, col, n, first_queen_row, first_queen_col, solutions):
    # Base case: All queens are placed
    if col >= n:
        # Append a copy of the board to the solutions list
        solutions.append([row.copy() for row in board])
        return

    # Skip the column where the first queen is already placed
    if col == first_queen_col:
        solve_nqueens(board, col + 1, n, first_queen_row, first_queen_col, solutions)
        return

    # Try placing a queen in each row for the current column
    for i in range(n):
        # Ensure no queen is placed in the row of the initially fixed queen
        if i != first_queen_row and is_safe(board, i, col, n):
            # Place the queen
            board[i][col] = 1

            # Recur to place the rest of the queens
            solve_nqueens(board, col + 1, n, first_queen_row, first_queen_col, solutions)

            # Backtrack if placing queen doesn't lead to a solution
            board[i][col] = 0

def print_board(board):
    for row in board:
        print(' '.join(str(x) for x in row))
    print()  # Blank line between solutions

def nqueens(n, first_queen_row, first_queen_col):
    # Initialize the board with all 0's
    board = [[0 for _ in range(n)] for _ in range(n)]

    # Place the first queen
    board[first_queen_row][first_queen_col] = 1

    # List to hold all solutions
    solutions = []

    # Start solving from the first column
    solve_nqueens(board, 0, n, first_queen_row, first_queen_col, solutions)

    # Print the results based on the number of solutions found
    if not solutions:
        print("Solution does not exist")
    elif len(solutions) == 1:
        print("One solution found:")
        print_board(solutions[0])
    else:
        print(f"{len(solutions)} solutions found:")
        for idx, solution in enumerate(solutions):
            print(f"Solution {idx + 1}:")
            print_board(solution)

# Example usage (Dynamic input)
n = int(input("Enter the value of n: "))  # Size of the board
first_queen_row = int(input("Enter the row index of the first queen (0-based): "))
first_queen_col = int(input("Enter the column index of the first queen (0-based): "))

nqueens(n, first_queen_row, first_queen_col)
