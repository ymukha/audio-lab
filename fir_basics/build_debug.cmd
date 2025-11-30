rmdir /S /Q build
cmake --preset fir_basics
cd build
cmake --build . --config Debug
cd ..