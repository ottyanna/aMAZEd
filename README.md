# aMAZEd

![Static Badge](https://img.shields.io/badge/made%20with-C%2B%2B-violet)
![Static Badge](https://img.shields.io/badge/license-GNU_GPLv3-yellow) 
![Static Badge](https://img.shields.io/badge/works%20on%20-my%20machine-blue)
![GitHub last commit](https://img.shields.io/github/last-commit/ottyanna/aMAZEd?color=purple)
![Static Badge](https://img.shields.io/badge/status-WIP-yellow)


aMAZEd is a c++ program that lets you create and solve a rectangular maze rendered using OpenGL. It can be watched as it process the maze itself. 

The algorithms used for this project are RandomDFS for generation and A* search, DFS, BFS and Dijkstra for solving. It can be used as a tool for visualizing these algorithms as they work.

## Demo-Preview
Immaginetta gif

# Table of contents 
- [Demo-Preview](#demo-preview)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Additional material (Italian only)](#additional-material-italian-only)
- [Further developments](#further-developments)
- [Contribute](#contribute)
- [Release History](#release-history)
- [License](#license)

## Installation

Scriptino?

[&uarr; Back to top](#table-of-contents)

### Dependencies

   - C++ Compiler (at least C++17)
   - [CMake](https://cmake.org/) (at least version 3.12)
   - [GLFW](https://www.glfw.org/docs/latest/quick.html) (at least version 3.4)
   - [Boost](https://www.boost.org/) (at least version 1.84)

If you're willing to use [`conda`](https://docs.conda.io/en/latest/), or if you already do, all the above dependencies can be installed via

```sh
$ conda env create -f requirements.yaml
```
You must do this after the [downloading](#download-and-building) part.

Nota son stranges sti requirements ultima riga----

Note that this creates a `maze` conda environment that needs to be activated.

### Download and building


You can download the last release [here](https://github.com/ottyanna/aMAZEd/releases) and unpack it
   ``` sh
   $ tar -xvf /path/to/tar #or zip file -C /path/to/your/directory
   ```
or if you want, you can clone this repository
   ``` sh
   $ git clone https://github.com/ottyanna/aMAZEd.git
   ```

Once done this, follow the instructions below in order to compile this code in your own directory.
``` sh
$ cd /path/to/your/directory  
$ # (if you're using conda -> conda activate <envname>)
$ mkdir build
$ cd build
$ cmake -DBUILD_SHARED_LIBS=ON ..
$ make
```
<details>
  <summary>For developers</summary>
If you want to look at the code with the right json run flag etc e debug etc and then move .json to main folder. Forse meglio se lo includo lo stesso alla prima release
</details>

## Usage
[&uarr; Back to top](#table-of-contents)
To execute the program run
```sh
$ ./exe [OPTIONS]
```

The `[OPTIONS]` are:
- `0` to generate a simple 50x50 maze without solving it. The program also adds some loops.
- `a` to generate and solve (A* search) a 50x50 maze with fixed delay of generation
- `b` to generate a 180x100 maze with loops and solve it with all the algorithms with fixed delay in between to see the result
- `c` same as `b` to time the solving algorithms without the visualizing part
- `d` same as `b` but without loops
- `e` same as `c` but without loops 

Feel free to tweak the [`main.cpp`](/src/main.cpp) to set the delay variables and watch how the path finding algorithms work.

## Examples
[&uarr; Back to top](#table-of-contents)

## Additional material (Italian only)
[&uarr; Back to top](#table-of-contents)

There is a little presentation of the project in the [Presentation folder](/Presentazione). Feel free to check that out.

## Further Developments
[&uarr; Back to top](#table-of-contents)

## Contribute
[&uarr; Back to top](#table-of-contents)

If you wish to contribute or you found any bug, feel free to open an issue or a pull request on the GitHub repository.

## Release History
[&uarr; Back to top](#table-of-contents)

See changelooggggggg file

## License 
[&uarr; Back to top](#table-of-contents)

[GNU GPLv3.0](https://choosealicense.com/licenses/gpl-3.0/)

---






aMAZEd is a C++ little program that lets you create a maze with DFS and then solves it with either DFS,BFS,Dijkstra and A*search.

## Installation

Before installing create a conda env and install the libraries contenute qui usando consa install (sono quelle dello yaml e cmake e boost forse args)

To install clonate this repo and then run

`cmake -DBUILD_SHARED_LIBS=ON ..`

if you want to develop add -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug

Move compile commands to main folder