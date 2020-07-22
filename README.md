# C++ Hexdump

## General

This class is used to create a hex dump of any contiguous memory area.
The hex dump is stored as a string and can also be passed to an std::ostream using the << operator.
The line width for the output can be configured.

example hex dump ("random" data):
```
f0 1d bf fd 40 4e d3 46 04 4d 0a fa e6 d5 00 81 2e 34 02 d4 ....@N.F.M.......4..
2b bb 56 40 30 74 b3 9b ab 56 b9 3f b4 ab 04 dc 48 ed d7 f8 +.V@0t...V.?....H...
ef a4 e4 d7 e9 be db a3 da 93 58 2f 1b ee 47 a6 86 2f 0c 1f ..........X/..G../..
54 c7 4f a1 af a6 49 d6 7f b2 14 56 7d 94 09 59 d4 42 55 83 T.O...I....V}..Y.BU.
9d 5b 85 bd 25 ff 11 e5 82 44 ca 44 46 58 af 77 c0 e1 da 11 .[..%....D.DFX.w....
42 6b 28 b8 a4 28 33 f4 12 a4 7d cf 72 a6 6a c1 3f 24 ac 6c Bk(..(3...}.r.j.?$.l
50 e9 97 b3 90 95 10 7c                                     P......|
```

## Examples
### Create hex dump from array with default line width (80 chars)
```c++
int arr[ARR_SIZE];
...
std::cout << Hexdump(arr, ARR_SIZE) << std::endl
```

### Create hex dump from array with custom line width (4-?? chars)

```c++
int arr[ARR_SIZE];
...
std::cout << Hexdump(arr, ARR_SIZE, LINE_WIDTH) << std::endl
```

### Create hex dump from std::array and std::vector
```c++
std::array<int, ARR_SIZE> arr;
std::vector<int> vec;
...
std::cout << Hexdump(arr) << std::endl;
std::cout << Hexdump(vec) << std::endl;
```
