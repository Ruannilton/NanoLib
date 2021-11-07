rm -r build
premake5 gmake2
cd ./build
make config=test
cd ./bin/Test/
./data_structure