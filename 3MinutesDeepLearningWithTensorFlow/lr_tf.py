###############################################################################
#   @file       lr_tf.py
#   @brief      Linear Regression with TensorFlow
#   @author     llHoYall <hoya128@gmail.com>
#   @version    v1.0
#   @note
#       - 2018.03.06    Created.
###############################################################################

# Import Packages ------------------------------------------------------------#
import tensorflow as tf

# Input Data -----------------------------------------------------------------#
x_data = [1, 2, 3]
y_data = [4, 5, 6]

# Algorithm ------------------------------------------------------------------#
W = tf.Variable(tf.random_uniform([1], -1.0, 1.0))
b = tf.Variable(tf.random_uniform([1], -1.0, 1.0))

X = tf.placeholder(tf.float32, name='X')
Y = tf.placeholder(tf.float32, name='Y')

hypothesis = W * X + b

cost = tf.reduce_mean(tf.square(hypothesis - Y))
optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.1)
train_op = optimizer.minimize(cost)

# Training -------------------------------------------------------------------#
with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())

    for step in range(100):
        _, cost_val = sess.run([train_op, cost],
                               feed_dict={X: x_data, Y: y_data})
        print(step, cost_val, sess.run(W), sess.run(b))

# Testing --------------------------------------------------------------------#
    print("X: 5, Y: ", sess.run(hypothesis, feed_dict={X: 5}))
    print("X: 2.5, Y: ", sess.run(hypothesis, feed_dict={X: 2.5}))
