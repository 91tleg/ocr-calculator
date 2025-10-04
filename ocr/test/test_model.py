from src.model import create_model
import numpy as np

def test_forward_pass():
    model = create_model()
    dummy_input = np.zeros((1, 28*28), dtype=np.float32)
    output = model.predict(dummy_input)
    assert output.shape == (1, 14)
    assert abs(output.sum() - 1.0) < 1e-6  # softmax
    print("Model forward pass test passed.")

test_forward_pass()