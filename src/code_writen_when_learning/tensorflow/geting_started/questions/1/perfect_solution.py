#!/usr/bin/python3
import tensorflow as tf
# Task 2: Simulate 10 throws of two six-sided dice. Store the results
# in a 10x3 matrix.

# We're going to place dice throws inside two separate
# 10x1 matrices. We could have placed dice throws inside
# a single 10x2 matrix, but adding different columns of
# the same matrix is tricky. We also could have placed
# dice throws inside two 1-D tensors (vectors); doing so
# would require transposing the result.
dice1 = tf.Variable(tf.random_uniform([10, 1], minval = 1, maxval = 7, dtype = tf.int32))
dice2 = tf.Variable(tf.random_uniform([10, 1], minval = 1, maxval = 7, dtype = tf.int32))

# We may add dice1 and dice2 since they share the same shape
# and size.
dice_sum = tf.add(dice1, dice2)

# We've got three separate 10x1 matrices. To produce a single
# 10x3 matrix, we'll concatenate them along dimension 1.
resulting_matrix = tf.concat(values = [dice1, dice2, dice_sum], axis = 1)

with tf.Session() as sess:
    tf.global_variables_initializer().run()
    print(resulting_matrix.eval())
