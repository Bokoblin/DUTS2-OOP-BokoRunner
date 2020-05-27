#!/bin/bash

###############################################################################
# Arguments check
###############################################################################
if [[ $# -eq 1 ]] && { [[ $1 == "-h" ]] || [[ $2 == "--help" ]]; }; then
    echo "Usage :"
    echo "$0"
    echo "$0 -c <clang|gnu>"
    exit 0
elif [[ $# -eq 2 ]] && [[ $1 == "-c" ]]; then
    echo "[INFO] Compiling with $2 was requested..."
    if [[ $2 == "gnu" ]]; then
        export CC=/usr/bin/gcc
        export CXX=/usr/bin/g++
    elif [[ $2 == "clang" ]]; then
        export CC=/usr/bin/clang
        export CXX=/usr/bin/clang++
    fi
else
    echo "[WARN] No specific compiler was requested. Using default system settings..."
fi

###############################################################################
# Working directory configuration
###############################################################################
working_dir=$(pwd)
res_dir="${working_dir}/res"
build_dir="${working_dir}/build"
install_dir="${working_dir}/bin"

if [[ ! -d "$res_dir" ]]; then
    echo "[ERROR] Please run this script from project root. Aborting..."
    exit 1
fi

if [[ -d "$build_dir" ]]; then
    echo "[ERROR] Build directory '$build_dir' already exists. Aborting..."
    exit 1
fi

if [[ -d "$install_dir" ]]; then
    echo "[ERROR] Install directory '$install_dir' already exists. Aborting..."
    exit 1
fi

mkdir "$build_dir"
cd "$build_dir" || (echo "[ERROR] Failed changing directory to build dir. Aborting..." && exit)

###############################################################################
# Project configuration
###############################################################################
echo "[INFO] Starting project configuration with default CMake settings..."
cmake ..

###############################################################################
# CPU configuration
###############################################################################
echo "[INFO] Checking CPU configuration..."
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    core_number=$(grep ^cpu\\scores /proc/cpuinfo | uniq | awk '{print $4}')
elif [[ "$OSTYPE" == "darwin"* ]]; then
    core_number=$(sysctl -a | grep machdep.cpu.core_count | awk '{print $2}')
else
    core_number=2
fi
jobs_number=$(awk "BEGIN {print 1.5 * $core_number}")

###############################################################################
# Project compiling
###############################################################################
echo "[INFO] Starting project building with ${jobs_number} cores..."

if make -j "${jobs_number}"; then
    echo "[INFO] Building complete."
else
    echo "[ERROR] Couldn't compile project. Aborting..."
    exit 1
fi

###############################################################################
# Installation
###############################################################################
echo "[INFO] Starting project installation..."

mkdir "$install_dir"
cd "$install_dir" || (echo "[ERROR] Failed changing directory to install dir. Aborting..." && exit)
cp "$build_dir/src/bokorunner" "$install_dir/bokorunner"

echo "[INFO] Installation complete. Please run project from this directory to avoid any issue: '$install_dir'"
