class Weights:
    def __init__(self, weight, profit):
        self.weight = weight
        self.profit = profit
        self.pw_ratio = profit / weight


def print_weights(arr):
    print("-----------")
    print(" W  P  P/W")
    for w in arr:
        print(w.weight, w.profit, round(w.pw_ratio, 2))
    print("-----------")


def cmp(item):
    return item.pw_ratio


def f_knapsack(arr, capacity):
    arr.sort(key=cmp, reverse=True)
    remaining_capacity = capacity
    total_profit = 0

    for w in arr:
        print("Selected -> Weight:", w.weight, "Profit:", w.profit, "P/W Ratio:", round(w.pw_ratio, 2))
        if w.weight <= remaining_capacity:
            remaining_capacity -= w.weight
            total_profit += w.profit
        else:
            total_profit += w.pw_ratio * remaining_capacity
            remaining_capacity = 0
            break
        print("Capacity Remaining:", remaining_capacity, "Profit:", total_profit)

    return total_profit


def main():
    n = int(input("Enter Number of Weights: "))
    arr = []

    for i in range(n):
        weight = int(input("Enter Weight " + str(i + 1) + ": "))
        profit = int(input("Enter Profit " + str(i + 1) + ": "))
        arr.append(Weights(weight, profit))

    print()
    print_weights(arr)

    capacity = int(input("Enter Capacity: "))
    print()

    max_profit = f_knapsack(arr, capacity)
    print("Maximum Profit:", max_profit)


if __name__ == "__main__":
    main()
