#!/bin/bash

shopt -s nullglob
SOLUTIONS=(*.c)

# Test definitions: each entry is "name|input|expected"
TESTS=(
  "missing_open_paren|int main;)|Error: Missing 1 opening '('"
  "missing_closing_paren|int main(;|Error: Missing 1 enclosing ')'"
  "missing_open_bracket|int a];|Error: Missing 1 opening '['"
  "missing_closing_bracket|int a[;|Error: Missing 1 enclosing ']'"
  "missing_open_brace|}|Error: Missing 1 opening '{'"
  "missing_closing_brace|{|Error: Missing 1 enclosing '}'"
  "open_comment|/* never closed|Error: Missing multiline comment enclosing"
  "open_double_quote|char *s = \"hi;|Error: Missing enclosing '\"'"
  "open_single_quote|char c = 'a;|Error: Missing enclosing '''"
  "multiple_missing_open|)]}|Error: Missing 1 opening '('\nError: Missing 1 opening '['\nError: Missing 1 opening '{'\n"
  "escape_in_quote|char *s = \"hi\\\"world\";|"
  "comment_skipped|// ( { [ \" \nint main(){}|"
)

run_test() {
  local bin="$1"
  local name="$2"
  local input=$3
  local expected=$(printf "%b" "$4")

  # Run the program with input, capture stdout and stderr
  printf "%b" "$input" | "./$bin" > out 2>&1
  local status=$?

  # Check output
  if [ -z "$expected" ]; then
    # Expected no error – output should be empty
    if [ ! -s out ]; then
      echo "PASS $name"
    else
      echo "FAIL $name (unexpected output):"
      cat out
    fi
  else
    if grep -qF "$expected" out; then
      echo "PASS $name"
    else
      echo "-----------------------------------------------------"
      echo "FAIL $name"
      echo "Expected fragment:"
      echo "$expected"
      echo "Actual output:"
      echo "-----------------------------------------------------"
      cat out
    fi
  fi

  rm -f out
}

for sol_file in "${SOLUTIONS[@]}"; do
  bin_name="${sol_file%.c}.out"
  echo "SOLUTION: $sol_file"

  gcc -Wall -g "$sol_file" -o "$bin_name"
  if [ $? -ne 0 ]; then
    echo "ERROR: Compilation failed for $sol_file. Skipped"
    continue
  fi

  for test in "${TESTS[@]}"; do
    # Split test entry into name, input, expected using '|' delimiter
    IFS='|' read -r name input expected <<< "$test"
    run_test "$bin_name" "$name" "$input" "$expected"
  done

  rm -f "$bin_name"
  echo
done
