import matplotlib.pyplot as plt

filename = 'allocation_times.txt'
sizes = []
mallocs = []
callocs = []
reallocs = []
with open(filename, 'r') as file:
    label0, label1, label2, label3 = file.readline().strip().split(';')
    for line in file:
        size, malloc, calloc, realloc = line.strip().split(';')
        sizes.append(int(size))
        mallocs.append(int(malloc))
        callocs.append(int(calloc))
        reallocs.append(int(realloc))
plt.plot(sizes, mallocs, label=label1)
plt.plot(sizes, callocs, label=label2)
plt.plot(sizes, reallocs, label=label3)
plt.xlabel('Размер памяти (байты)')
plt.ylabel('Время выделения (секунды)')
plt.title('Зависимость времени выделения от размера памяти')
plt.grid(True)
plt.legend()
plt.savefig('chart.png')
plt.show()
