#!/usr/bin/python3
import tensorflow as tf
import random

def initialize(tensor):
    for x in range(0, 10):
        for y in range(0, 2):
            #tf.assign(tensor[x, y], random.randrange(1, 6)).eval()
            tensor[x, y].assign(random.randrange(1, 6)).eval()
    for x in range(0, 10):
        #tf.assign( tensor[x, 2], tf.add( tensor[x, 0].eval(), tensor[x, 1].eval() ) ).eval()
        tensor[x, 2].assign( tf.add(tensor[x, 0].eval(), tensor[x, 1].eval()) ).eval()

def run(tensor):
    with tf.Session():
        tf.global_variables_initializer().run()
        initialize(tensor)
        print(tensor.eval())

v = tf.get_variable("v", [10, 3], dtype = tf.int32)
run(v)
