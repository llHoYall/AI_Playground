# Import Packages ------------------------------------------------------------#
from keras import layers, models
from keras import datasets
from keras.utils import np_utils
import graph


# Modeling -------------------------------------------------------------------#
# Distributed Modeling, Functional Programming
def ANN_Model1(nin, nh, nout):
    x = layers.Input(shape=(nin, ))
    h = layers.Activation('relu')(layers.Dense(nh)(x))
    y = layers.Activation('softmax')(layers.Dense(nout)(h))
    model = models.Model(x, y)
    model.compile(loss='categorical_crossentropy', optimizer='adam',
                  metrics=['accuracy'])
    return model


# Chaining Modeling, Functional Programming
def ANN_Model2(nin, nh, nout):
    model = models.Sequential()
    model.add(layers.Dense(nh, activation='relu', input_shape=(nin, )))
    model.add(layers.Dense(nout, activation='softmax'))
    model.compile(loss='categorical_crossentropy', optimizer='adam',
                  metrics=['accuracy'])
    return model


# Distributed Modeling, Object-Oriented Programming
class ANN_Model3(models.Model):
    def __init__(self, nin, nh, nout):
        hidden = layers.Dense(nh)
        output = layers.Dense(nout)
        relu = layers.Activation('relu')
        softmax = layers.Activation('softmax')

        x = layers.Input(shape=(nin, ))
        h = relu(hidden(x))
        y = softmax(output(h))

        super().__init__(x, y)
        self.compile(loss='categorical_crossentropy', optimizer='adam',
                     metrics=['accuracy'])


# Chainig Modeling, Object-Oriented Programming
class ANN_Model4(models.Sequential):
    def __init__(self, nin, nh, nout):
        super().__init__()
        self.add(layers.Dense(nh, activation='relu', input_shape=(nin, )))
        self.add(layers.Dense(nout, activation='softmax'))
        self.compile(loss='categorical_crossentropy', optimizer='adam',
                     metrics=['accuracy'])


# Training -------------------------------------------------------------------#
# Datasets
def Data():
    (x_train, y_train), (x_test, y_test) = datasets.mnist.load_data()

    y_train = np_utils.to_categorical(y_train)
    y_test = np_utils.to_categorical(y_test)

    L, W, H = x_train.shape
    x_train = x_train.reshape(-1, W * H)
    x_test = x_test.reshape(-1, W * H)

    x_train = x_train / 255.0
    x_test = x_test / 255.0

    return (x_train, y_train), (x_test, y_test)


# Training & Evaluation
def Main():
    # Hyper-Parameters
    nin = 784
    nh = 100
    number_of_class = 10
    nout = number_of_class

    # Modeling
    model = ANN_Model1(nin, nh, nout)
    (x_train, y_train), (x_test, y_test) = Data()

    history = model.fit(x_train, y_train, epochs=15, batch_size=100,
                        validation_split=0.2)
    performance = model.evaluate(x_test, y_test, batch_size=100)
    print('Test Loss and Accuracy ->', performance)

    graph.plot_loss(history)
    graph.plot_acc(history)


# Main Routine ---------------------------------------------------------------#
if __name__ == '__main__':
    Main()
