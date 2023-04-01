getopts "t:" opt
case "$opt"
  in t) test="$OPTARG"
esac

if [ -z "$test" ]
then
  test="1";
fi

cmake -Bbuild -H.
cmake --build build --target all
echo "running test $test";
./build/file_system "$test"
