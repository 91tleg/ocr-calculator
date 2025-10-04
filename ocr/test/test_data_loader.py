from src.data_loader import load_mnist_data

def test_data_shapes():
    (x_train, y_train), (x_test, y_test) = load_mnist_data()
    assert x_train.shape[1] == 28*28
    assert y_train.shape[1] == 14
    assert x_test.shape[1] == 28*28
    assert y_test.shape[1] == 14
    print("Data loader test passed.")

test_data_shapes()