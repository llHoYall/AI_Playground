from collections import OrderedDict
import numpy as np
import activation_function.affine as affine
import activation_function.relu as relu
import activation_function.softmax as softmax
import loss_function as lf


class NeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size, weight_init=0.01):
        self.params = {}
        self.params['W1'] = weight_init *   \
            np.random.randn(input_size, hidden_size)
        self.params['b1'] = np.zeros(hidden_size)
        self.params['W2'] = weight_init *   \
            np.random.randn(hidden_size, output_size)
        self.params['b2'] = np.zeros(output_size)

        self.layers = OrderedDict()
        self.layers['Affine1'] = affine.Affine(
                self.params['W1'], self.params['b1'])
        self.layers['Relu1'] = relu.Relu()
        self.layers['Affine2'] = affine.Affine(
                self.params['W2'], self.params['b2'])

        self.lastlayer = softmax.SoftmaxWithLoss()

    def predict(self, x):
        for layer in self.layers.values():
            x = layer.forward(x)
        return x

    def loss(self, x, t):
        y = self.predict(x)
        return self.lastlayer.forward(y, t)

    def accuracy(self, x, t):
        y = self.predict(x)
        y = np.argmax(y, axis=1)
        if t.ndim != 1:
            t = np.argmax(t, axis=1)

        accuracy = np.sum(y == t) / float(x.shape[0])
        return accuracy

    def numerical_gradient(self, x, t):
        loss_W = lambda W: self.loss(x, t)

        grads = {}
        grads['W1'] = lf.numerical_gradient(loss_W, self.params['W1'])
        grads['b1'] = lf.numerical_gradient(loss_W, self.params['b1'])
        grads['W2'] = lf.numerical_gradient(loss_W, self.params['W2'])
        grads['b2'] = lf.numerical_gradient(loss_W, self.params['b2'])
        return grads

    def gradient(self, x, t):
        self.loss(x, t)

        dout = 1
        dout = self.lastlayer.backward(dout)

        layers = list(self.layers.values())
        layers.reverse()
        for layer in layers:
            dout = layer.backward(dout)

        grads = {}
        grads['W1'] = self.layers['Affine1'].dW
        grads['b1'] = self.layers['Affine1'].db
        grads['W2'] = self.layers['Affine2'].dW
        grads['b2'] = self.layers['Affine2'].db
        return grads
