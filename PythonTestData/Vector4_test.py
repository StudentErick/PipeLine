import numpy as np

# v1 = np.array([1, 12.2, 3])
# v2 = np.array([-2, -8, 8.4])
#
# v3 = np.array([10, -4.6, 11.6])
# v4 = np.array([0, 0, 0])
#
# print(np.linalg.norm(v3))
# print(np.linalg.norm(v4))

# v1 = np.array([2.3, 4.5, 6.99])
# v2 = np.array([-3, -7, -10.3])
#
# y = np.linalg.norm(v1)
# v1 /= y
# print(v1)
# y = np.linalg.norm(v2)
# v2 /= y
# print(v2)
# m1 = [[0] * 4 for i in range(4)]
# m2 = [[0] * 4 for i in range(4)]
# m1 = np.array(m1)
# m2 = np.array(m2)
# for i in range(4):
#     for j in range(4):
#         m1[i][j] = i + i * 7 - 5
#         m2[i][j] = i + j * 3 + 10
#
# print(m1)
# print(m2)
# print(np.matmul(m1, m2))

m1 = np.arange(16).reshape(4, 4)
m2 = np.arange(4).reshape(4, 1)

for i in range(4):
    for j in range(4):
        m1[i][j] = i + i * 7 - 5
    m2[i] = (i + 7) / 3 + 9
print(np.matmul(m1, m2))
