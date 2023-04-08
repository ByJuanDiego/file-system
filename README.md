# File system
Mini file management system for fixed and variable length records

## Run the project

The project do not use any third-party library, just the `C++ STL`.

```zsh
git clone https://github.com/ByJuanDiego/file-system.git
cd file-system
```

### Run in terminal

```zsh
g++ -std=c++17 ./src/main.cpp -o main
```

After compiling, pass the test number directly to ```main``` by using ```argv``` to run a test:

```zsh
./main <i> # where <i> is the number of the test
```

### Run with `CMake`

```zsh
chmod +x run.zsh
./run.zsh -t <i> # where <i> is the number of the test
```
