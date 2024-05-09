from sklearn.datasets import load_iris
import numpy as np
import matplotlib.pyplot as plt

x, y = load_iris(return_X_y=True)

k = 4

def total_inertia(points, closest, centroids):
    total = 0
    for i in range(centroids.shape[0]):
        cluster_points = points[closest == i]
        if len(cluster_points) > 0:
            total += np.sum((cluster_points - centroids[i])**2)
    print("Total Inertia:", total)
    return total

def initialize_centroids(points, k):
    centroids = points.copy()
    np.random.shuffle(centroids)
    return centroids[:k]

def closest_centroid(points, centroids):
    distances = np.sqrt(((points - centroids[:, np.newaxis])**2).sum(axis=2))
    return np.argmin(distances, axis=0)

def move_centroids(points, closest, centroids):
    return np.array([points[closest==k].mean(axis=0) for k in range(centroids.shape[0])])

def k_means(points, k, max_iters=1000):
    centroids = initialize_centroids(points, k)
    closest = np.zeros(points.shape[0])
    for _ in range(max_iters):
        old_centroids = centroids.copy()
        closest = closest_centroid(points, centroids)
        centroids = move_centroids(points, closest, centroids)
        total_inertia(x, closest, centroids)
        if np.all(old_centroids == centroids):
            break
    return centroids, closest

centroids, closest = k_means(x, k)

# 计算总内聚度


inertia = total_inertia(x, closest, centroids)
print("Total Inertia:", inertia)

points = x
colors = ['r', 'g', 'b', 'y']

fig, ax = plt.subplots()

for i in range(k):
    points_in_cluster = points[closest == i]
    ax.scatter(points_in_cluster[:, 0], points_in_cluster[:, 1], s=30, c=colors[i], label=f'Cluster {i+1}')
    ax.scatter(centroids[i][0], centroids[i][1], s=100, c=colors[i], marker='x', linewidths=3)

plt.legend()
plt.show()
