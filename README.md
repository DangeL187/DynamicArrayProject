# DynamicArrayProject
C++ dynamic array class for Python

# Before building
Download [pybind11](https://github.com/swansontec/map-macro)
```
git clone https://github.com/pybind/pybind11.git
```

# How to build
```
mkdir build
cd build
cmake ..
make
```

# How to use
1. Copy the generated `.so` file to the same folder as the `.py` file that you want to use
2. Rename the generated file to `DynamicArrayProject.so`
3. Run your python script or [cpp.py](https://github.com/DangeL187/DynamicArrayProject/blob/main/python/cpp.py)
