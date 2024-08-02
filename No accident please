import matplotlib.pyplot as plt
from shapely.geometry import LineString, Point

# Function to check if two line segments intersect
def do_intersect(p1, q1, p2, q2):
    line1 = LineString([p1, q1])
    line2 = LineString([p2, q2])
    return line1.intersects(line2)

# Function to adjust the path slightly to avoid intersections
def adjust_path(path, epsilon=1):
    adjusted_path = []
    for p in path:
        adjusted_path.append(Point(p.x + epsilon, p.y + epsilon))
        epsilon += 0.1  # Increment to ensure separation
    return adjusted_path

# Function to check and adjust paths for all flights
def adjust_paths(all_flights, max_iterations=100):
    adjusted = True
    iterations = 0

    while adjusted and iterations < max_iterations:
        adjusted = False
        iterations += 1
        # Check all pairs of flights
        for i in range(len(all_flights)):
            for j in range(i + 1, len(all_flights)):
                flight1 = all_flights[i]
                flight2 = all_flights[j]
                # Check all pairs of segments
                for k in range(len(flight1) - 1):
                    for l in range(len(flight2) - 1):
                        if do_intersect(flight1[k], flight1[k+1], flight2[l], flight2[l+1]):
                            all_flights[j] = adjust_path(flight2)  # Adjust the second path to avoid intersection
                            adjusted = True
                            break  # Break early to recheck all intersections
                    if adjusted:
                        break
                if adjusted:
                    break
    return all_flights

# Define flights with their respective paths
flight1 = [Point(1, 1), Point(2, 2), Point(3, 3)]
flight2 = [Point(1, 1), Point(2, 4), Point(3, 2)]
flight3 = [Point(1, 1), Point(4, 2), Point(3, 4)]

# List of all flights
all_flights = [flight1, flight2, flight3]

# Adjust paths to avoid intersections
adjusted_flights = adjust_paths(all_flights)

# Plotting the adjusted paths
fig, ax = plt.subplots()
colors = ['r', 'g', 'b']

for i, flight in enumerate(adjusted_flights):
    x, y = zip(*[(p.x, p.y) for p in flight])
    ax.plot(x, y, marker='o', color=colors[i], label=f'Flight {i+1}')

ax.legend()
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Adjusted Flight Paths')
plt.grid(True)
plt.show()
