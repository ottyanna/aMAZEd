# aMAZEd

aMAZEd is a C++ little program that lets you create a maze with DFS and then solves it with either DFS,BFS,Dijkstra and A*search.

## Installation

Before installing create a conda env and install the libraries contenute qui usando consa install (sono quelle dello yaml e cmake e boost forse args)

To install clonate this repo and then run

`cmake -DBUILD_SHARED_LIBS=ON ..`

if you want to develop add -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug

## Usage

```python
import foobar

# returns 'words'
foobar.pluralize('word')

# returns 'geese'
foobar.pluralize('goose')

# returns 'phenomenon'
foobar.singularize('phenomena')
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)