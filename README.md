# 2-wheels-1-arm
A genetic algorithm searching for solutions to move a simple robot

## Dependencies
* [v-rep pro edu](http://www.coppeliarobotics.com/downloads.html) (virtual robot experimentation platform)
* __node.js__
* __npm__
* A __C++__ compiler

## Documentation
* [Class diagram](documents/class_diagram/software_diagram.class.yuml.png)

## How to
### Setup virtual environment
* Download and install __v-rep__
* Open __v-rep__ then load `2w1a.ttt`

### Build and use sample code?
Available sample projects:
* v-rep remote api test with 2w1a in __python__ and __c++__
* String finder genetic algorithm in __c++__

See [sample code README](sample_code/README.md)

### Use project?
#### Install
* `npm install`

#### Launch
* v-rep virtual environment need to be setup
* `npm start`

### Development notes
### How to launch server in dev mode?
* v-rep virtual environment need to be setup
* `npm run dev` (server automaticaly restarts after file change; does not work for c++ files)

### How to rebuild C++ algorithm node module?
* `npm run build` *(not on `master` yet!)*

### Build C++ algorithm for development? *(not on `master` yet!)*
* `$> cd algorithm/`
* `$> make`
* `$> ./2w1a`
Note: It simulates a __node.js__ server running along the algorithm, just let the main thread doing nothing for ever
