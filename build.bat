@echo off
setlocal enabledelayedexpansion

echo Cleaning and rebuilding Graphite

:: delete build directory if exists

if exist build (
    echo Removing previous build folder...
    rmdir /s /q build
)

:: recreate and configure build
echo Creating new build folder...
mkdir build
cd build
cmake ..
cmake --build .

echo Build completed

:: run the program
echo Running Graphite

cd ..
.\bin\Debug\graphite.exe