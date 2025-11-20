from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

NUM_CLASSES = 10

def create_model(input_shape=(28*28,)):
    model = Sequential([
        Dense(128, activation='relu', input_shape=input_shape),
        Dense(64, activation='relu'),
        Dense(NUM_CLASSES, activation='softmax')
    ])

    model.compile(
        optimizer='adam',
        loss='categorical_crossentropy',
        metrics=['accuracy']
    )

    return model
