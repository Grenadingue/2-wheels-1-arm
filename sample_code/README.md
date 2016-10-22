# Sample code

## How to use?

### Vrep remote API python sample
* You need __python 2.x__
* Open __v-rep__ then load `2w1a.ttt`
* OS X users, you need to copy the library `remoteApi.dylib` (for the appropriate architecture) from the v-rep folder in `programming/remoteApiBindings/lib/lib/` to `sample_code/python/`
* `$> cd sample_code/vrep_python/`
* `$> python 2w1aTest.py`

### Vrep remote API c++ sample
* You need a Unix environment (should work on Windows with Cygwin)
* Open __v-rep__ then load `2w1a.ttt`
* You need `gcc` and `g++`
* `$> cd sample_code/vrep_cpp`
* `$> make`
* `$> ./vrep_sample`

### Genetic algorithm c++ sample
* You need __Qt 5.x__
* Open __v-rep__ then load `2w1a.ttt`
* `$> qmake`
* *If Linux/OS X* `$> make`
* *If Windows* Compile `.vcxproj` with Visual Studio
* `$> ./hello_genetic_algo`
