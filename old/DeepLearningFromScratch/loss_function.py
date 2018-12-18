import numpy as np


def mean_squared_error(y, t):
    return 0.5 * np.sum((y - t) ** 2)


def cross_entropy_error(y, t):
    # preventing -INF
    delta = 1e-7
    return -np.sum(t * np.log(y + delta))


def numerical_diff(f, x):
    h = 1e-4
    return (f(x + h) - f(x - h)) / (2 * h)


def numerical_gradient(f, x):
    h = 1e-4
    grad = np.zeros_like(x)

    for idx in range(x.size):
        tmp = x[idx]
        x[idx] = tmp + h
        fxh1 = f(x)

        x[idx] = tmp - h
        fxh2 = f(x)

        grad[idx] = (fxh1 - fxh2) / (2 * h)
        x[idx] = tmp

    return grad


def gradient_descent(f, init_x, lr=0.01, step=100):
    x = init_x
    for i in range(step):
        grad = numerial_gradient(f, x)
        x -= lr * grad
    return x
