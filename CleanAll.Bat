rmdir /S /Q dist\Box2D

rmdir /S /Q Debug
rmdir /S /Q Release

REM rmdir /S /Q dist

del /F /S *.sdf
del /F /S /A:H *.suo

rmdir /S /Q src\sb6\Debug
rmdir /S /Q src\Debug

cd .\Box2D
call CleanMe.bat
cd ..

