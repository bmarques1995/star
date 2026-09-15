ASAN_OPTIONS=detect_leaks=1 \
LSAN_OPTIONS=verbosity=1:log_threads=1 \
./out/build/linux-vcpkg-debug/bin/star samples/leak.st