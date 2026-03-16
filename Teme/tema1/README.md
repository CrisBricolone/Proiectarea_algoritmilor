# Assignment Template

This repository serves as a template for new assignments, providing a standard directory structure and an automated grading configuration.

## Directory Structure

- **`in/`**: Contains the input data files for all the test cases.
- **`out/`**: Target directory where the student's program output will be generated and saved during testing.
- **`ref/`**: Contains the reference (expected) output files used to verify the correctness of the student's output.
- **`src/`**: The directory that contains the source code for the assignment.
- **`tests.json`**: The configuration file that defines how the assignment checker should evaluate the submission.

## Configuring `tests.json`

The `tests.json` file controls the behavior of the assignment checker. Here is a breakdown of its main sections:

- **`temp_path`**: The directory path used by the checker to store temporary files (e.g., `./.checker_temp`).
- **`macros`**: A collection of reusable string replacements (variables) to avoid hardcoding paths multiple times.
- **`tests`**: An array of individual test case objects. Each test case specifies:
  - `displayName`: The name of the test shown in the checker output.
  - `file`: The base file name for the input/reference files.
  - `args`: Command-line arguments passed to the executed program (often using macros like `$IN` and `$OUT`).
  - `score`: The points awarded for passing this specific test.
- **`ref_checker`**: Configuration for validating the program's output against the `ref/` directory. The `grade` field represents the weight of this check in the final score.
- **`commit_checker`**: Ensures the student has used version control properly. You can configure `minCommits` to require a certain number of commits, and assign a `grade` weight.
- **`memory_checker`**: Uses `valgrind` to penalize memory leaks or errors. You can configure `maxWarnings`, `maxLeak` (in MB), and the `grade` associated with memory safety.
- **`style_checker`**: Uses `cppcheck` to enforce code quality. You can define specific point distributions based on the number of style issues found inside the `thresholds` array.
