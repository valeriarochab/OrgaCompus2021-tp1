cd ./test

echo "Test help command:"
../autcel -h
echo " "

echo "Test version command:"
../autcel -V
echo " "

echo "Test 1: 30 rule, 80 iterations: "
../autcel 30 80 inicial_30_80 -o evolucion_test_1

echo "Test 2: 110 rule, 80 iterations: "
../autcel 110 80 inicial_110_80 -o evolucion_test_2

echo "Test 3: 126 rule, 80 iterations: "
../autcel 126 80 inicial_126_80 -o evolucion_test_3

echo "Test 4: invalid file1: "
../autcel 30 80 invalid_file1 -o evolucion_test_4

echo "Test 5: invalid file2, N < 3: "
../autcel 30 2 invalid_file2 -o evolucion_test_5

echo "Test 6: empty file: "
../autcel 30 80 empty_file -o evolucion_test_6

echo "Test 7: Not -o argument, use input file as prefix: "
../autcel 60 80 inicial_60_80