import matplotlib.pyplot as plt

# ---------- Fibonacci (OpenMP) ----------
threads = [1, 2, 4, 8]
fib_time = [0.001, 0.001, 0.002, 0.002]
fib_speedup = [fib_time[0]/t for t in fib_time]

plt.figure(figsize=(12, 5))

# Time vs Threads
plt.subplot(1, 2, 1)
plt.plot(threads, fib_time, marker='o', linestyle='-', color='blue')
plt.title("Fibonacci: Time vs Threads")
plt.xlabel("Number of Threads")
plt.ylabel("Elapsed Time (s)")
plt.grid(True)

# Speedup vs Threads
plt.subplot(1, 2, 2)
plt.plot(threads, fib_speedup, marker='o', linestyle='-', color='green')
plt.title("Fibonacci: Speedup vs Threads")
plt.xlabel("Number of Threads")
plt.ylabel("Speedup")
plt.grid(True)

plt.tight_layout()
plt.show()

# ---------- Sum (MPI) ----------
processes = [1, 2, 4, 8]
sum_time = [0.025986, 0.026809, 0.010499, 0.031174]
sum_speedup = [sum_time[0]/t for t in sum_time]

plt.figure(figsize=(12, 5))

# Time vs Processes
plt.subplot(1, 2, 1)
plt.plot(processes, sum_time, marker='o', linestyle='-', color='red')
plt.title("Sum: Time vs Processes")
plt.xlabel("Number of Processes")
plt.ylabel("Elapsed Time (s)")
plt.grid(True)

# Speedup vs Processes
plt.subplot(1, 2, 2)
plt.plot(processes, sum_speedup, marker='o', linestyle='-', color='purple')
plt.title("Sum: Speedup vs Processes")
plt.xlabel("Number of Processes")
plt.ylabel("Speedup")
plt.grid(True)

plt.tight_layout()
plt.show()
