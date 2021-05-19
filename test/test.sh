cd ./test

echo "Test help command:"
../autcel -h
echo " "

echo "Test version command:"
../autcel -V
echo " "

echo "Test 1: 30 rule, 80 iterations: "
../autcel 30 80 inicial_30_80 -o evolucion_test_1

echo "Test 2: 30 rule, 110 iterations: "
../autcel 30 110 inicial_30_110 -o evolucion_test_2

echo "Test 3: 30 rule, 126 iterations: "
../autcel 30 126 inicial_30_126 -o evolucion_test_3

echo "Test 4: invalid file1: "
../autcel 30 80 invalid_file1 -o evolucion_test_4

echo "Test 5: invalid file2: "
../autcel 30 2 invalid_file2 -o evolucion_test_5

echo "Test 6: empty file: "
../autcel 30 80 empty_file -o evolucion_test_6