<h1 align="center"> aMAZEd </h1>

![Static Badge](https://img.shields.io/badge/made%20with-C%2B%2B-gold?labelColor=indigo)
![Static Badge](https://img.shields.io/badge/license-GNU_GPLv3-gold?labelColor=indigo)
![Static Badge](https://img.shields.io/badge/works%20on%20-my%20machine-gold?labelColor=indigo)
![Static Badge](https://img.shields.io/badge/status-WIP-gold?labelColor=indigo)
![GitHub last commit](https://img.shields.io/github/last-commit/ottyanna/aMAZEd?labelColor=indigo&color=gold)


aMAZEd is a c++ program that lets you create and solve a rectangular maze rendered using OpenGL. It can be watched as it processes the maze itself. 

The algorithms used for this project are RandomDFS for generation and A* search, DFS, BFS and Dijkstra for solving. It can be used as a tool for visualizing these algorithms as they work. See [Example and Description](#examples-and-description) section for a better understanding of colors.

## Demo-Preview
![mazeA*](/Presentazione/images/AStar.png)

# Table of contents 
- [Demo-Preview](#demo-preview)
- [Installation](#installation)
- [Usage](#usage)
- [Examples and description](#examples-and-description)
- [Additional material (Italian only)](#additional-material-italian-only)
- [Contribute](#contribute)
- [Release History](#release-history)
- [License](#license)

## Installation 
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
<!--<details>
  <summary>For developers</summary>
If you want to look at the code with the right json run flag etc e debug etc and then move .json to main folder. Forse meglio se lo includo lo stesso alla prima release
if you want to develop add -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug
Move compile commands to main folder
</details>
-->

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

Feel free to tweak the [`main.cpp`](/src/main.cpp) to set the delay variables and watch how the path finding algorithms work or change the dimension or the starting and ending point of the maze.

## Examples and description
[&uarr; Back to top](#table-of-contents)

Running `./exe a` will generate the following:

- the 50x50 maze with loops, where green and cyan represent the starting and ending points, respectively.

   ![maze](/Presentazione/images/README/Screenshot%20from%202024-04-05%2012-40-52.png)

- the shortest path in pink found by A*, where the violet and yellow represent the explored nodes.

   ![solution](/Presentazione/images/README/Screenshot%20from%202024-04-05%2012-40-53.png)


## Additional material (Italian only)
[&uarr; Back to top](#table-of-contents)

There is a little presentation of the project in the [Presentation folder](/Presentazione). Feel free to check that out.

<!--## Further Developments
[&uarr; Back to top](#table-of-contents)

-->

## Contribute
[&uarr; Back to top](#table-of-contents)

If you wish to contribute or you found any bug, feel free to open an issue or a pull request on the GitHub repository.

## Release History
[&uarr; Back to top](#table-of-contents)

See [CHANGELOG](/CHANGELOG.md) file.

## License 
[&uarr; Back to top](#table-of-contents)

[GNU GPLv3.0](https://choosealicense.com/licenses/gpl-3.0/)

---
<p align="center"> 
<img alt="Static Badge" src="https://img.shields.io/badge/made%20with-%09%E2%99%A5%20-%20green?labelColor=indigo&color=salmon">
</p>