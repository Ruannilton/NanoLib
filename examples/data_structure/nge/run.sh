rm -r build
premake5 gmake2
cd ./build
make
cd ./bin/Debug/
./data_structure