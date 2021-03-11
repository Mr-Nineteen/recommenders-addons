licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

load("//tensorflow_recommenders_addons:tensorflow_recommenders_addons.bzl", "custom_op_library")

cc_library(
	name = "redis_client",
    srcs = ["kernels/redis_client.cc"],
    hdrs = ["kernels/redis_client.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow_recommenders_addons/dynamic_embedding/core/lib/redis:redis_acl",
    ],
	copts = [
    	"-Itensorflow_recommenders_addons/dynamic_embedding/core/lib/redis/include/",
    	"-Ltensorflow_recommenders_addons/dynamic_embedding/core/lib/redis/lib/",
  	]
)

custom_op_library(
    name = "_cuckoo_hashtable_ops.so",
    srcs = [
        "kernels/cuckoo_hashtable_op.cc",
        "kernels/cuckoo_hashtable_op.h",
        "ops/cuckoo_hashtable_ops.cc",
    ],
    deps = [
        "//tensorflow_recommenders_addons/dynamic_embedding/core/lib/cuckoo:cuckoohash",
        ":redis_client",
    ],
)
