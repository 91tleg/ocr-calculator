import sys
import numpy as np
from PIL import Image

IMG_SIZE = 28
ARRAY_NAME = "test_image"

def image_to_c_array(input_path, output_path, var_name=ARRAY_NAME):
    img = Image.open(input_path).convert("L")  # Greyscale
    img = img.resize((IMG_SIZE, IMG_SIZE))
    data = np.array(img, dtype=np.uint8)
    flat = data.flatten()

    lines = []
    for i in range(0, len(flat), 12):
        chunk = ", ".join(f"0x{v:02X}" for v in flat[i:i+12])
        lines.append("  " + chunk + ",")

    with open(output_path, "w") as f:
        f.write("#pragma once\n\n")
        f.write("#include <stdint.h>\n\n")
        f.write(f"const uint8_t {var_name}[{len(flat)}] = {{\n")
        f.write("\n".join(lines))
        f.write("\n};\n")

    print(f"Generated {output_path}")
    print(f"Array name: {var_name}")
    print(f"Size: {len(flat)} bytes")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 image_to_array.py <input path> <output path> <array_name>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = sys.argv[2]
    array_name = sys.argv[3] if len(sys.argv) > 3 else ARRAY_NAME

    image_to_c_array(input_path, output_path, array_name)
