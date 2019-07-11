import random
import math
import numpy as np
import time


def choose_initial(data, k):
    res = set()
    res = random.sample(data, k);
    return list(res)


def euclidean_dis(p1, p2):
    x = p1[0] - p2[0]
    y = p1[1] - p2[1]
    return (x * x + y * y)**0.5


def loss(data, centers_belongto, centers, f_dis):
    allloss = 0
    for d, c in zip(data, centers_belongto):
        allloss += f_dis(d, centers[c])
    return allloss


def new_centers(data, centers_belongto, centers, k):
    new_centers = []
    for i in range(k):
        is_belong = [True if center_index == i else False for center_index in centers_belongto]
        sum_x = 0
        sum_y = 0
        card_cluster = 0
        for d_index in range(len(data)):
            if is_belong[d_index]:
                card_cluster += 1
                sum_x += data[d_index][0]
                sum_y += data[d_index][1]
        new_centers.append((sum_x / card_cluster, sum_y / card_cluster))
    return new_centers


def icenter(data, centers_belongto, new_centers, k):
    icenters = [1] * k
    for i in range(k):
        is_belong = [True if center_index == i else False for center_index in centers_belongto]
        d = 0
        dmin = 99999
        for d_index in range(len(data)):
            if is_belong[d_index]:
                d = euclidean_dis(data[d_index], new_centers[i])
                if d < dmin:
                    dmin = d
                    icenters[i] = data[d_index]
    return icenters


def partition_into_clusters(data, centers, f_dis):
    centers_belongto = []
    for d in data:
        dis_with_centers = [f_dis(d, center) for center in centers]
        center_index_belong = np.argmin(dis_with_centers)
        # centers_belongto[data.index(d)] = center_index_belong
        centers_belongto.append(center_index_belong)
    return centers_belongto


def kmeans(data, k, t, maxiter, f_dis):
    centers = choose_initial(data, k)
    # partition the data into clusters having the centers
    # return the list in which the element of i_th == the index of list centers
    # this indique that in list data, the i-th points belongs to the center of i-th element ...
    centers_belongto = partition_into_clusters(data, centers, f_dis)
    loss_0 = loss(data, centers_belongto, centers, f_dis)
    while maxiter > 0:
        maxiter -= 1
        # calculate new centers
        newcenters = new_centers(data, centers_belongto, centers, k)
        centers = icenter(data, centers_belongto, newcenters, k)
        centers_belongto = partition_into_clusters(data, centers, f_dis)
        loss_1 = loss(data, centers_belongto, centers, f_dis)
        if abs(loss_0 - loss_1) <= t:
            break
        loss_0 = loss_1
    return centers_belongto, centers, loss_0


def loadDataSet(fileName):
    dataMat = []
    from itertools import islice
    fr = open(fileName)
    line_num = 0
    # for line in fr.readlines():
    for line in islice(fr, 1, None):
        curLine = line.strip().split()
        a = list(map(float, curLine))
        b = tuple(a)
        dataMat.append(b)

        # fltLine= map(float, curLine)
        # dataMat.append(fltLine)
    return dataMat


data1 = loadDataSet('dataAlea2_50_ex1.txt')
start = time.clock()
centers_belongto, centers, loss = kmeans(data1, 4, 0.001, 100000, euclidean_dis)
end = time.clock()
time = end - start
print("Running time=", time)
print("cout= ", loss)

print(centers_belongto)
print(centers)
