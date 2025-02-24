if [ "$1" == "Debug" ] || [ "$1" == "Release" ] && [ ! -z "$2" ] && [ ! -z "$3" ]; then
    git clone --recursive https://github.com/Neargye/magic_enum.git "$3/modules/magic_enum"
    cmake -S "$3/modules/magic_enum" -B "$3/dependencies/linux/magic_enum" -DCMAKE_INSTALL_PREFIX="$2" -DCMAKE_BUILD_TYPE="$1"
    cmake --build "$3/dependencies/linux/magic_enum" --target install
else
    echo "Invalid build type or install path. Please provide either 'Debug' or 'Release' and a valid prefix path"
fi
