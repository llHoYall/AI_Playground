# Import Packages ------------------------------------------------------------#
import numpy as np
import scipy.special
# import matplotlib.pyplot
# for Jupyter
# %matplotlib inline


# Neural Network Class Definition --------------------------------------------#
class NeuralNetwork:
    def __init__(self, input_nodes, hidden_nodes, output_nodes, learning_rate):
        self.inodes = input_nodes
        self.hnodes = hidden_nodes
        self.onodes = output_nodes

        self.wih = np.random.normal(0.0, pow(self.hnodes, -0.5),
                                    (self.hnodes, self.inodes))
        self.who = np.random.normal(0.0, pow(self.onodes, -0.5),
                                    (self.onodes, self.hnodes))

        # Sigmoid function
        self.activation_function = lambda x: scipy.special.expit(x)

        self.lr = learning_rate

    def train(self, inputs_list, targets_list):
        inputs = np.array(inputs_list, ndmin=2).T
        targets = np.array(targets_list, ndmin=2).T

        hidden_inputs = np.dot(self.wih, inputs)
        hidden_outputs = self.activation_function(hidden_inputs)

        final_inputs = np.dot(self.who, hidden_outputs)
        final_outputs = self.activation_function(final_inputs)

        output_errors = targets - final_outputs
        hidden_errors = np.dot(self.who.T, output_errors)

        self.who += self.lr * np.dot((output_errors * final_outputs *
                                     (1.0 - final_outputs)),
                                     np.transpose(hidden_outputs))
        self.wih += self.lr * np.dot((hidden_errors * hidden_outputs *
                                     (1.0 - hidden_outputs)),
                                     np.transpose(inputs))

    def query(self, inputs_list):
        inputs = np.array(inputs_list, ndmin=2).T

        hidden_inputs = np.dot(self.wih, inputs)
        hidden_outputs = self.activation_function(hidden_inputs)

        final_inputs = np.dot(self.who, hidden_outputs)
        final_outputs = self.activation_function(final_inputs)
        return final_outputs


# Application ----------------------------------------------------------------#
# Hyper-Parameter Config
input_nodes = 784
hidden_nodes = 200
output_nodes = 10
learning_rate = 0.1

# Neural Network
nn = NeuralNetwork(input_nodes, hidden_nodes, output_nodes, learning_rate)

# Training
# with open('dataset/mnist_train_100.csv', 'r') as f:
with open('dataset/mnist_train.csv', 'r') as f:
    data = f.readlines()

epochs = 5
for e in range(epochs):
    for record in data:
        all_values = record.split(',')
        inputs = (np.asfarray(all_values[1:]) / 255.0 * 0.99) + 0.01
        targets = np.zeros(output_nodes) + 0.01
        targets[int(all_values[0])] = 0.99
        nn.train(inputs, targets)

# Test
# with open('dataset/mnist_test_10.csv', 'r') as f:
with open('dataset/mnist_test.csv', 'r') as f:
    test_data = f.readlines()

score = []
for record in test_data:
    all_values = record.split(',')
    target_label = int(all_values[0])
    print("Target: ", target_label)

    inputs = (np.asfarray(all_values[1:]) / 255.0 * 0.99) + 0.01
    outputs = nn.query(inputs)
    result_label = np.argmax(outputs)
    print("Result: ", result_label)

    if (result_label == target_label):
        score.append(1)
    else:
        score.append(0)

score_array = np.asarray(score)
print("Accuracy: ", score_array.sum() / score_array.size)
