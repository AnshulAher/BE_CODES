def knapsack_01(weights, profits, n, m, dp):
    # Base case: no items left
    if n < 0:
        return 0

    # If already calculated, return the stored value
    if dp[n][m] != -1:
        return dp[n][m]

    # If the current item's weight exceeds the remaining capacity, skip it
    if weights[n] > m:
        dp[n][m] = knapsack_01(weights, profits, n - 1, m, dp)
    else:
        # Choose the maximum of either including or excluding the current item
        include = knapsack_01(weights, profits, n - 1, m - weights[n], dp) + profits[n]
        exclude = knapsack_01(weights, profits, n - 1, m, dp)
        dp[n][m] = max(include, exclude)

    return dp[n][m]

def main():
    weights = []
    profits = []

    # Input number of items and capacity of the sack
    n = int(input("Enter number of items: "))
    m = int(input("Enter capacity of sack: "))

    # Input the weights and profits of the items
    for i in range(n):
        weight = int(input("Enter weight " + str(i + 1) + ": "))
        profit = int(input("Enter profit " + str(i + 1) + ": "))
        weights.append(weight)
        profits.append(profit)

    # Initialize DP table with -1
    dp = [[-1 for _ in range(m + 1)] for _ in range(n)]

    # Get the maximum profit
    max_profit = knapsack_01(weights, profits, n - 1, m, dp)
    print("Maximum Profit:", max_profit)

if __name__ == "__main__":
    main()
