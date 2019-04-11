del /S *.ilk
del /S *.pdb
del /S *.sdf
del /S *.ncb
del /S *.bak
del /S *.sln
del /S *.suo
del /S *.vcproj*
del /S *.vcxproj*
del /S *.filters
del /S *.idb
del /S *makefile*
del /S *.ipch
del /S *.db
del /S *.suo
del /S *.qmake.stash

for /R %%s in (.) do ( 
echo %%s
cd %%s
rd /s /q debug
rd /s /q release
rd /s /q X64
rd /s /q .vs
) 

cd ../..