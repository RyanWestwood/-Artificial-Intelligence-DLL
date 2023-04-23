cd ../
set working_dir=%cd%
set library_binaries=%working_dir%/library_binaries
set generator="-G Visual Studio 17 2022"
set test="-DTESTS=ON"

echo Creating Home for libs
cd %working_dir%
if not exist "library_binaries" mkdir library_binaries

if not exist "build" mkdir build
cd build
cmake %generator% -A x64 -DCMAKE_BUILD_TYPE=Release -S %working_dir% -B %working_dir%/build %test%
cmake --build %working_dir%/build --config Release --parallel
cmake --install %working_dir%/build --prefix %library_binaries% --config Release 
echo Project built successfully
pause