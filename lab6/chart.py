import matplotlib.pyplot as plt

filename = 'allocation_times.txt'
sizes = []
times = []
with open(filename, 'r') as file:
    next(file)  # Пропускаем заголовок файла
    for line in file:
        size, time = line.strip().split(';')        
        sizes.append(int(size))
        times.append(float(time))
plt.plot(sizes, times)
plt.xlabel('Размер памяти (байты)')
plt.ylabel('Время выделения (секунды)')
plt.title('Зависимость времени выделения от размера памяти')
plt.grid(True)
plt.savefig('chart.png')
plt.show()
