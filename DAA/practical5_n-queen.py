import time

def check(i, j, board):
    for r in range(0, n):
        row = board[r].replace(" ", "")
        for c in range(0, n):
            if row[c] == "1" and r == i and c == j:
                return True

def n_queens(n):
    col = set()
    posDiag = set()  # (r + c)
    negDiag = set()  # (r - c)

    res = []
    board = [["0"] * n for _ in range(n)]

    def backtrack(r):
        if r == n:
            copy = [" ".join(row) for row in board]
            res.append(copy)
            return

        for c in range(n):
            if c in col or (r + c) in posDiag or (r - c) in negDiag:
                continue

            # Place queen and mark attack zones
            col.add(c)
            posDiag.add(r + c)
            negDiag.add(r - c)
            board[r][c] = "1"

            backtrack(r + 1)

            # Remove queen and unmark attack zones
            col.remove(c)
            posDiag.remove(r + c)
            negDiag.remove(r - c)
            board[r][c] = "0"

    # Start the backtracking process
    backtrack(0)

    # Count and print all solutions that match the given position (I, J)
    count = 0
    for sol in res:
        if check(I, J, sol):
            count += 1
            for row in sol:
                print(row)
            print()

    # Return the total number of solutions found
    return count


# Taking user input for the size of the board
n = int(input("Enter the number of queens (board size): "))
# Get starting queen pos
I = int(input("Enter the first queen's row: "))
J = int(input("Enter the first queen's col: "))

# Measure the start time
start_time = time.time()

# Get the total number of solutions
num_solutions = n_queens(n)

# Print the total number of solutions without formatted strings
print("Total number of solutions:", num_solutions)

# Measure the end time
end_time = time.time()

print("Execution time:", end_time - start_time, "seconds")
