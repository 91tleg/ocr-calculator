from data_loader import load_mnist_data
from model import create_model

(x_train, y_train), (x_test, y_test) = load_mnist_data()

model = create_model()
model.summary()

model.fit(
    x_train, y_train,
    epochs=10,
    batch_size=32,
    validation_split=0.1
)

loss, acc = model.evaluate(x_test, y_test)
print(f"Test Accuracy: {acc*100:.2f}%")

model.save("model.h5")