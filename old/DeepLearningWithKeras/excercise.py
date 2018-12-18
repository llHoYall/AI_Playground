# Import Packages ------------------------------------------------------------#
import keras
import numpy as np

# Data -----------------------------------------------------------------------#
x = np.array([0, 1, 2, 3, 4])
y = x * 2 + 1

# Modeling -------------------------------------------------------------------#
model = keras.models.Sequential()
model.add(keras.layers.Dense(1, input_shape=(1, )))
# Optimization Algorithm = Stochastic Gradient Descent
# Loss Function = Mean Square Error
model.compile('SGD', 'mse')

# Training -------------------------------------------------------------------#
model.fit(x[:2], y[:2], epochs=1000, verbose=0)

# Testing --------------------------------------------------------------------#
print('Targets: ', y[2:])
print('Predictions: ', model.predict(x[2:]).flatten())
