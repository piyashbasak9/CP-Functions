set -e

# Compile programs
g++ gen.cpp -o gen
g++ code.cpp -o code
g++ brute.cpp -o brute

# Run test cases until a difference is found
for ((i = 1; ; ++i)); do
    echo "Passed on TestCase: $i"
    
    # Generate input and run both solutions
    ./gen $i > in
    ./code < in > out1
    ./brute < in > out2
    
    # Compare outputs
    diff -Z out1 out2 || break
done

# Display the failing test case and results
echo -e "WA on the following test:"
cat in
echo -e "\nYour Answer is:"
cat out1
echo -e "\nCorrect answer is:"
cat out2
