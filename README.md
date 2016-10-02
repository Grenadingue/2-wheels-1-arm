# 2-wheels-1-arm
A genetic algorithm searching for solutions to move a simple robot

## Dependencies
* [v-rep](http://www.coppeliarobotics.com) (virtual robot experimentation platform)

## How to
### Use the sample code?
#### Setup virtual environment
* Download and install __v-rep__
* Open __v-rep__ then load `2w1a.ttt`

#### Python
* You need __python 2.7__
* OS X users, you need to copy the library `remoteApi.dylib` (for the appropriate architecture) from the v-rep folder in `programming/remoteApiBindings/lib/lib/` to `sample_code/python/`
* `$> cd sample_code/python/`
* `$> python 2w1aTest.py`

#### C++
* For now you need a Unix environment (should work on Windows with Cygwin)
* You need `gcc` and `g++`
* `$> cd sample_code/`
* `$> make`
* `$> ./2w1a_test`
