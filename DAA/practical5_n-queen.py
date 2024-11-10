import time


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

    # Print all solutions
    for sol in res:
        for row in sol:
            print(row)
        print()

    # Return the total number of solutions found
    return len(res)


if __name__ == "__main__":
    # Taking user input for the size of the board
    n = int(input("Enter the number of queens (board size): "))

    # Measure the start time
    start_time = time.time()

    num_solutions = n_queens(n)

    # Measure the end time
    end_time = time.time()

    # Print the total number of solutions and execution time
    print(f"Total solutions for {n}-queens:", num_solutions)
    print("Execution time:", end_time - start_time, "seconds")