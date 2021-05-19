cd ./test

echo "Test help command:"
../autcel -h
echo " "

echo "Test version command:"
../autcel -V
echo " "

echo "Test 30 rule, 80 iterations: "
../autcel 30 80 inicial_30_80 -o evolucion_30_80

echo "Test 30 rule, 110 iterations: "
../autcel 30 110 inicial_30_110 -o evolucion_30_110

echo "Test 30 rule, 126 iterations: "
../autcel 30 126 inicial_30_126 -o evolucion_30_126

echo "Test invalid file1: "
../autcel 30 80 invalid_file1 -o evolucion_30_80

echo "Test invalid file2: "
../autcel 30 80 invalid_file2 -o evolucion_30_80

echo "Test empty file: "
../autcel 30 80 empty_file -o empty_file