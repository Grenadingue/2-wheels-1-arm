# 2-wheels-1-arm
A genetic algorithm searching for solutions to move a simple robot straightforward in a virtual environment

## Dependencies
* [v-rep pro edu](http://www.coppeliarobotics.com/downloads.html) (virtual robot experimentation platform)
* __node.js__ + __npm__ + __node-gyp__
* __g++__ / __clang++__
* __cmake__ + __make__
* __boost__ libraries

## Documentation
* [Class diagram](documents/class_diagram/software_diagram.class.yuml.png)

## How to
*/!\ Important note: `npm` commands should be executed from repository root directory*

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
#### How to launch server in dev mode?
* v-rep virtual environment need to be setup
* `npm run dev`

*Note: Server will automaticaly restart after file change*
*Note2: Works for node.js files, does not work for c++ files*

#### How to build/rebuild C++ side?
##### Node.js algorithm module
* `npm run build_algo`
* `npm run rebuild_algo`

##### Executable development algorithm
* `npm run build_algo_dev`
* `npm run rebuild_algo_dev`

#### How to launch development executable algorithm?
* v-rep virtual environment need to be setup
* Execute `algorithm/build_dev/2w1a_dev`

#### Config file
* You have to do your own config file using the config/base.example.json
* `cp config/base.example.json config/base.json`