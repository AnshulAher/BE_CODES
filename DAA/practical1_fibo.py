# Non-Recursive (Iterative) Fibonacci with iteration count
def fibonacci_non_recursive(n, counter=0):
    if n <= 0:
        return 0, counter
    elif n == 1:
        return 1, counter
    a, b = 0, 1
    for _ in range(2, n + 1):
        counter += 1
        a, b = b, a + b
    return b, counter

# Recursive Fibonacci with call count
def fibonacci_recursive(n, counter=0):
    counter += 1
    if n <= 0:
        return 0, counter
    elif n == 1:
        return 1, counter
    fib1, counter = fibonacci_recursive(n - 1, counter)
    fib2, counter = fibonacci_recursive(n - 2, counter)
    return fib1 + fib2, counter

n = int(input("Enter a number: "))

# Non-Recursive Fibonacci
fib_non_recursive, non_recursive_counter = fibonacci_non_recursive(n)
print("Fibonacci of", n, "(Non-Recursive):", fib_non_recursive)
print("Non-Recursive Iterations:", non_recursive_counter)

# Recursive Fibonacci
fib_recursive, recursive_counter = fibonacci_recursive(n)
print("Fibonacci of", n, "(Recursive):", fib_recursive)
print("Recursive Function Calls:", recursive_counter)
