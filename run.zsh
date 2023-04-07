getopts "t:" opt
case "$opt"
  in t) test="$OPTARG"
esac

cmake -Bbuild -H.
cmake --build build --target all
echo "running test $test";

if [ -z "$test" ]
then
    ./build/file_system
else
    ./build/file_system "$test"
fi
