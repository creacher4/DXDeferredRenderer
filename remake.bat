@echo off
setlocal enabledelayedexpansion

echo Rebuilding Graphite

cmake --build build

echo.
echo Build completed
echo Running Graphite...

.\bin\Debug\graphite.exe