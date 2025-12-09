import matplotlib.pyplot as plt
import sys

points = []

for line in sys.stdin:
    line = line.strip()
    a, b = map(int, line.split(','))
    points.append((a, b))

points.append(points[0])

# Unzip into two coordinate lists
xs, ys = zip(*points)

plt.figure(figsize=(6,6))

# Plot line segments
plt.plot(xs, ys, marker='o')

# Make it look nicer, keep asepct ratio
plt.grid(True)
plt.axis('equal')

plt.show()
