#!/bin/sh

set -eu

CC=${CC:-gcc}
CXX=${CXX:-g++}

CFLAGS=${CFLAGS:--I. -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Wpedantic}
CXXFLAGS=${CXXFLAGS:--I. -std=c++11 -Wall -Wextra -Wpedantic}

C_EXAMPLES="
    examples/01_basic
    examples/02_cli
    examples/03_manual
    examples/04_callbacks
    examples/05_long_names
    examples/07_custom_asserts
    examples/08_context
"
CXX_EXAMPLES="
    examples/06_C++
"
TESTS="
    tests/exam
"

usage() {
    echo "usage: $0 [all|examples|tests|clean]" >&2
}

build_c() {
    echo "CC  $1.c"
    $CC $CFLAGS -o "$1" "$1.c"
}

build_cxx() {
    echo "CXX $1.cpp"
    $CXX $CXXFLAGS -o "$1" "$1.cpp"
}

build_examples() {
    for e in $C_EXAMPLES; do build_c "$e"; done
    for e in $CXX_EXAMPLES; do build_cxx "$e"; done
}

build_tests() {
    for t in $TESTS; do build_c "$t"; done
}

clean() {
    for f in $C_EXAMPLES $CXX_EXAMPLES $TESTS; do
        rm -f "$f"
    done
}

target=${1:-all}
case "$target" in
    all)      build_examples; build_tests ;;
    examples) build_examples ;;
    tests)    build_tests ;;
    clean)    clean ;;
    -h|--help) usage ;;
    *)        usage; exit 1 ;;
esac
