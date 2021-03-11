package(default_visibility = ["//visibility:public"])

cc_import(
	name = "redis_acl",
	static_library = "lib/libacl_all.a",
	hdrs = glob([
		"include/acl_cpp/**/*.hpp",
		"include/acl_cpp/**/*.ipp",
	])
)

cc_library(
	name = "redis_client",
    srcs = ["redis_client.cc"],
    hdrs = ["redis_client.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":redis_acl",
    ],
	copts = [
    	"-Itensorflow_recommenders_addons/dynamic_embedding/core/lib/redis/include/",
    	"-Ltensorflow_recommenders_addons/dynamic_embedding/core/lib/redis/lib/",
  	]
)

cc_binary(
	name = "redis_data",
	srcs = ["redis_data.cc"],
	deps = [":redis_client"],
)
