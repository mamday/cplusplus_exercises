cc_library(
    name="RandStats",
    hdrs=["get_rand_stats.h"],
    srcs=["get_rand_stats.cxx"],
    visibility = ["//visibility:public"],
)
cc_library(
    name="IntStats",
    hdrs=["int_rnd_list.h"],
    srcs=["int_rnd_list.cxx"],
    deps = [":RandStats"],
    visibility = ["//visibility:public"],
)
