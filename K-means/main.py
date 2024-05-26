import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import adjusted_rand_score

# 加载并标准化数据集
x, y = load_iris(return_X_y=True)
scaler = StandardScaler()
x = scaler.fit_transform(x)

def initialize_centroids(points, k):
    """随机初始化k个质心"""
    centroids = points.copy()
    np.random.shuffle(centroids)
    return centroids[:k]

def closest_centroid(points, centroids):
    """计算每个点最近的质心"""
    distances = np.sqrt(((points - centroids[:, np.newaxis])**2).sum(axis=2))
    return np.argmin(distances, axis=0)

def move_centroids(points, closest, centroids):
    """更新质心位置"""
    new_centroids = []
    for k in range(centroids.shape[0]):
        if np.any(closest == k):
            new_centroids.append(points[closest == k].mean(axis=0))
        else:
            new_centroids.append(centroids[k])  # 保留旧质心或随机初始化新质心
    return np.array(new_centroids)

def k_means(points, k, max_iters=100):
    """K-Means聚类算法"""
    centroids = initialize_centroids(points, k)
    for _ in range(max_iters):
        closest = closest_centroid(points, centroids)
        new_centroids = move_centroids(points, closest, centroids)
        if np.all(centroids == new_centroids):
            break
        centroids = new_centroids
    return centroids, closest

def total_inertia(points, closest, centroids):
    """计算总内聚度（SSE）"""
    return sum(np.sum((points[closest == k] - centroids[k])**2) for k in range(centroids.shape[0]))

# 运行K-Means算法并评估结果
k = 3
centroids, closest = k_means(x, k)

# 可视化聚类结果
colors = ['r', 'g', 'b']
fig, ax = plt.subplots()
for i in range(k):
    points_in_cluster = x[closest == i]
    ax.scatter(points_in_cluster[:, 0], points_in_cluster[:, 1], s=30, c=colors[i], label=f'Cluster {i+1}')
    ax.scatter(centroids[i][0], centroids[i][1], s=100, c=colors[i], marker='x', linewidths=3)
plt.legend()
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.title('K-Means Clustering')
plt.show()

# 不同k值对SSE的影响
sse_values = []
k_values = range(1, 21)
for k in k_values:
    centroids, closest = k_means(x, k)
    sse = total_inertia(x, closest, centroids)
    sse_values.append(sse)

plt.plot(k_values, sse_values, marker='o')
plt.xlabel('Number of clusters (k)')
plt.ylabel('SSE')
plt.title('SSE vs. Number of clusters')
plt.show()

# 使用ARI评估不同k值的效果
ari_values = []
for k in k_values:
    centroids, closest = k_means(x, k)
    ari = adjusted_rand_score(y, closest)
    ari_values.append(ari)

plt.plot(k_values, ari_values, marker='o')
plt.xlabel('Number of clusters (k)')
plt.ylabel('ARI')
plt.title('ARI vs. Number of clusters')
plt.show()
