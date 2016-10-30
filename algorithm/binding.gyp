{
	"targets": [
	{
		"target_name": "algoGen",
		"sources": [
			   "lib/vrep/extApi.c",
			   "lib/vrep/extApiPlatform.c",
			   "source/binding.cc",
			   "source/MainController.cpp",
			   "source/AThreadedDataHandler.cpp",
			   "source/WebServerBridge.cpp",
			   "source/BackupDataController.cpp",
			   "source/GeneticAlgoController.cpp",
			   "source/AlgoParameters.cpp",
			   "source/Client.cpp",
			   "source/ResultModel.cpp",
			   "source/WritableResultModel.cpp",
			   "source/World.cpp",
			   "source/MotherNature.cpp",
			   "source/Random.cpp",
			   "source/Individual.cpp",
			   "source/Genome.cpp",
			   "source/_2w1a.cpp",
			   "source/VrepAPI.cpp",
			   "source/Physics.cpp",
			   "source/Object.cpp",
			   "source/Articulation.cpp",
			   "source/Maths.cpp"
		],
		"include_dirs": [
			"lib/socket.io-client/socket.io-client-cpp/src",
			"lib/socket.io-client/socket.io-client-cpp/lib/rapidjson/include",
			"lib/socket.io-client/socket.io-client-cpp/lib/websocketpp",
			"lib/vrep"
		],
		"defines": [ "NON_MATLAB_PARSING", "MAX_EXT_API_CONNECTIONS=255" ],
		"link_settings": {
					"libraries": [
								"-lpthread",
								"-lboost_system", "-lboost_date_time", "-lboost_random",
								"-lsioclient", "-L../lib/socket.io-client/build/"
					]
		},
		"conditions": [
			[ 'OS=="linux"', {
								"cflags!": [ "-O3" ],
								"cflags_cc+": [ "-std=c++11" ]
							}
			],
			[ 'OS=="mac"', {
								"xcode_settings": {
													"OTHER_CPLUSPLUSFLAGS" : [ "-std=c++11", "-stdlib=libc++" ],
													"OTHER_LDFLAGS": [ "-stdlib=libc++" ],
													},
							}
			],
        ],
	}]
}
