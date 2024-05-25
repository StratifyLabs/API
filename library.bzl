"""
Helper for declaring an API library
"""

load("@toolchains//toolchain.bzl", "select_toolchain")

def api_library(name, srcs, header_namespace = None, exported_headers = [], headers = [], exported_deps = [], deps = []):

    header_namespace_effective = name if header_namespace == None else header_namespace;

    native.cxx_library(
        name = name,
        srcs = srcs,
        headers = headers,
        exported_headers = exported_headers,
        header_namespace = header_namespace_effective,
        deps = [],
        exported_deps = exported_deps,
        visibility = ["PUBLIC"],
        _cxx_toolchain = select_toolchain()
    )