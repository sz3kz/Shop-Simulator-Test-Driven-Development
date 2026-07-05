# Cash Register
Cash Register Functionality Implementation via Test Driven Development.

## Usage

1. Clone the repository
```bash
git clone git@github.com:sz3kz/Shop-Simulator-Test-Driven-Development.git 
cd Shop-Simulator-Test-Driven-Development/workspace/
```
2. Depending how you want to use it:
#### Raw
If you have everything installed already and don't really care about versions of compiler etc. then:
```bash
# pre-commit install                        # Set up clang-format and cppcheck hook via .yaml
# pre-commit install --hook-type pre-push   # Set up clang-tidy hook via .yaml
cmake -S . -B build/ -G "Ninja"
cd build/
ninja run_tests
```
### Compilation + tests
To compile and run the tests just
> make run_tests

or

> ninja run_tests
