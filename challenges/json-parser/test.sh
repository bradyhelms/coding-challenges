#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
EXECUTABLE="./json-parser"
TEST_DIR="tests"
STEPS=("step1" "step2" "step3" "step4")

# Test counters
total_tests=0
passed_tests=0
failed_tests=0

usage() {
    echo "Usage: $0 [-s step_number] [-h]"
    echo "Options:"
    echo "  -s <number>    Run tests only for specific step (1-4)"
    echo "  -h            Show this help message"
    echo "Example:"
    echo "  $0            Run all tests"
    echo "  $0 -s 2       Run only step 2 tests"
    exit 1
}

# Function to run test for a single file
run_test() {
    local step=$1
    local file=$2
    local expected_result=$3  # 0 for valid, non-zero for invalid
    
    echo -e "${BLUE}Testing $file${NC}"
    
    $EXECUTABLE "$file" > /dev/null 2>&1
    local result=$?
    
    ((total_tests++))
    
    if [ $result -eq $expected_result ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((passed_tests++))
        return 0
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo -e "${RED}Expected return code $expected_result, got $result${NC}"
        ((failed_tests++))
        return 1
    fi
}

# Function to run tests for a specific step
run_step_tests() {
    local step=$1
    echo -e "\n${BLUE}Running tests for $step${NC}"
    echo "----------------------------------------"
    
    # Check if directory exists
    if [ ! -d "$TEST_DIR/$step" ]; then
        echo -e "${RED}Error: Directory $TEST_DIR/$step not found${NC}"
        return 1
    fi
    
    # Run tests for valid files
    for file in "$TEST_DIR/$step"/valid*.json; do
        if [ -f "$file" ]; then
            run_test "$step" "$file" 0
        fi
    done
    
    # Run tests for invalid files
    for file in "$TEST_DIR/$step"/invalid*.json; do
        if [ -f "$file" ]; then
            run_test "$step" "$file" 1
        fi
    done
}

# Parse command line arguments
specific_step=""
while getopts "s:h" opt; do
    case $opt in
        s)
            if [[ $OPTARG =~ ^[1-4]$ ]]; then
                specific_step="step$OPTARG"
            else
                echo "Error: Step must be between 1 and 4"
                usage
            fi
            ;;
        h)
            usage
            ;;
        \?)
            echo "Invalid option: -$OPTARG"
            usage
            ;;
    esac
done

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable '$EXECUTABLE' not found${NC}"
    echo "Make sure you have compiled the json-parser and it's in the current directory"
    exit 1
fi

# Run tests
if [ -n "$specific_step" ]; then
    run_step_tests "$specific_step"
else
    for step in "${STEPS[@]}"; do
        run_step_tests "$step"
    done
fi

# Print summary
echo -e "\n${BLUE}Test Summary:${NC}"
echo "----------------------------------------"
echo "Total tests:  $total_tests"
echo -e "${GREEN}Passed tests: $passed_tests${NC}"
if [ $failed_tests -gt 0 ]; then
    echo -e "${RED}Failed tests: $failed_tests${NC}"
fi

# Exit with status code based on test results
if [ $failed_tests -eq 0 ]; then
    echo -e "\n${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "\n${RED}Some tests failed!${NC}"
    exit 1
fi
