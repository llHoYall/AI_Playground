import numpy as np


def identity(x):
    return x


def step(x):
    return np.array(x > 0, dtype=np.int)


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def relu(x):
    return np.maximum(0, x)


def softmax(x):
    # Preventing overflow
    exp_x = np.exp(x - np.max(x))
    sum_exp_x = np.sum(exp_x)
    y = exp_x / sum_exp_x
    return y
