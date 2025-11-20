import tensorflow as tf
import numpy as np
from data_loader import load_mnist_data

model = tf.keras.models.load_model("model.h5")

(x_train, y_train), _ = load_mnist_data()
x_train = x_train.astype(np.float32) / 255.0

def representative_dataset():
    for i in range(100):
        yield [x_train[i:i+1]]

converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset = representative_dataset
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.uint8
converter.inference_output_type = tf.uint8

tflite_model = converter.convert()

with open("model.tflite", "wb") as f:
    f.write(tflite_model)

print("Saved as model.tflite")

# Dump details
interpreter = tf.lite.Interpreter(model_path="model.tflite")
interpreter.allocate_tensors()
print(interpreter.get_tensor_details())