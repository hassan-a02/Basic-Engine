# Basic Engine

A minimal C++/OpenGL demo showcasing a simple rendering pipeline.

## Features

### Implemented
- Camera movement
- Cube and Plane primitives
- Basic lighting
- ImGui UI
- Uses GLFW, GLAD, GLM, and stb_image (all bundled)

### Planned
- More primitive types
- Texture selection
- Model loading
- Collision
- Advanced lighting techniques

## Screenshots
 
![Main View](readme_assets/blocks.png)

![Lighting](readme_assets/lights.png)


## Build

All platforms require **cmake** and a working C++ compiler.

- **Linux** – `apt install cmake` and `apt install gcc` in the terminal should be enough to build. A minimal install may lack X11/Wayland/OpenGL development headers, so you might need packages such as `libx11-dev`, `libgl1-mesa-dev` or others. CMake will complain about the missing headers and you can `apt install` them.

- **macOS** – Install the Command Line Tools (`xcode-select --install`) to get `clang`, `make`, and the SDK headers.

- **Windows** – Installing Visual Studio with the C++ workload gives you both `cmake` and an MSVC compiler. Or you can use a standalone MinGW/Clang toolchain plus cmake prebuilt binary.


In the directory of the CMakeLists.txt file:
```sh
mkdir build && cd build
cmake ..
cmake --build .
```

Once built, run the executable (`build/PrimitiveShowcase` on Linux, `build.exe` on Windows).

---

### Notes

If you just want to look at the code or see the visuals, building is optional.
There is a demo video in the readme_asset directory. 

