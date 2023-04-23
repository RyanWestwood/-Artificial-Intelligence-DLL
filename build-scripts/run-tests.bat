cd ../
set working_dir=%cd%
set generator="-G Visual Studio 17 2022"
set cmake="cmake"
set ctest="ctest"
set configuration="Release"

cd build/tests
%cmake% %generator% -A x64 -DCMAKE_BUILD_TYPE=%configuration% -S ./ -B "build"
%cmake% --build build --config %configuration% --parallel
cd build
%ctest% -C %configuration%
echo Project built successfully
pause