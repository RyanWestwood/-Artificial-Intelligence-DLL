import os
import subprocess
import argparse
import shutil

working_dir = os.path.dirname(os.getcwd())
library_binaries = os.path.join(working_dir, "library_binaries")
build_dir = os.path.join(working_dir, "build")
generator = "-G Visual Studio 17 2022"

def copy_file(source_path, destination_path):
    try:
        shutil.copy(source_path, destination_path)
        print(f"File copied successfully from '{source_path}' to '{destination_path}'")
    except Exception as e:
        print(f"File copy failed: {str(e)}")

def create_build_dir():
    print(f"Creating home for build and binaries!")
    os.makedirs(library_binaries, exist_ok=True)
    os.makedirs(build_dir, exist_ok=True)

def install_lib(library, build_type, install_dir, configure="", build="", install=""):
    print(f"\nInstalling {library}...")
    library_dir = os.path.join(working_dir, "external", library)
    build_dir = os.path.join(library_dir, "build")
    os.makedirs(build_dir, exist_ok=True)
    os.chdir(build_dir)

    try:
        cmake_command = f'cmake "{generator}" -S "{library_dir}" -B "{build_dir}" {configure}'
        subprocess.run(cmake_command, shell=True, check=True)
        build_command = f'cmake --build . --config {build_type} --parallel'
        subprocess.run(build_command, shell=True, check=True)
        install_command = f'cmake --install . --prefix {install_dir} --config {build_type}'
        subprocess.run(install_command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        error_message = e.stderr
        print(f"Command execution failed: {error_message}")

    print(f"{library} Installed!\n")

def build_benchmarks(build_type):
    print(f"\nbulding benchmarks...")
    library_dir = os.path.join(working_dir, "benchmarks")
    build_dir = os.path.join(library_dir, "build")
    os.makedirs(build_dir, exist_ok=True)
    os.chdir(build_dir)    
    copy_file(f'{library_binaries}/bin/AIL.dll', f'{build_dir}/{build_type}/AIL.dll')

    try:
        cmake_command = f'cmake "{generator}" -S "{library_dir}" -B "{build_dir}"'
        subprocess.run(cmake_command, shell=True, check=True)
        build_command = f'cmake --build . --config {build_type} --parallel'
        subprocess.run(build_command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        error_message = e.stderr
        print(f"Command execution failed: {error_message}")

    print(f"Benhcmarks Built!\n")

def install_project(build_type, install_dir):
    print(f"Building project...")
    build_dir = os.path.join(working_dir, "build")
    os.makedirs(build_dir, exist_ok=True)
    os.chdir(build_dir)
    
    try:
        cmake_command = f'cmake "{generator}" -S "{working_dir}" -B "{build_dir}"'
        subprocess.run(cmake_command, shell=True, check=True)
        build_command = f'cmake --build . --config {build_type} --parallel'
        subprocess.run(build_command, shell=True, check=True)
        install_command = f'cmake --install . --prefix {install_dir} --config {build_type}'
        subprocess.run(install_command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        error_message = e.stderr
        print(f"Command execution failed: {error_message}")

    print("Project built successfully!")

def main():
    parser = argparse.ArgumentParser(description="Build and install libraries and project.")
    parser.add_argument("--build-type", choices=["Release", "Debug"], default="Release", help="Build type (Release or Debug)")
    parser.add_argument("--test", choices=["ON", "OFF"], default="OFF", help="Build Tests (ON or OFF)")
    parser.add_argument("--benchmark", choices=["ON", "OFF"], default="OFF", help="Build Tests (ON or OFF)")
    parser.add_argument("--install-dir", default=library_binaries, help="Installation directory path")

    args = parser.parse_args()

    if args.test == "ON":
        install_lib("googletest", args.build_type, args.install_dir)
        
    if args.benchmark == "ON":
        install_lib("googlebenchmark", args.build_type, args.install_dir, configure="-DBENCHMARK_DOWNLOAD_DEPENDENCIES=on")
        build_benchmarks(args.build_type)

    
    install_project(args.build_type, args.install_dir)

    input("Press Enter to exit...")

if __name__ == "__main__":
    main()