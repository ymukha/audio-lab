rmdir /S /Q build
cmake --preset fir_q15
cd build
cmake --build . --config Debug
cd ..