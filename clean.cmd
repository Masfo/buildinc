
del /s /q *.ilk
del /s /q *.pdb
del /S /Q *.ipch
del /s /q temp\*.exe
del /Q /S .vs\*
del /S /Q *.iobj
del /S /Q *.obj
del /S /Q *.tlog
del /S /Q *.sarif
del /S /Q *.VC.db

set RCDIR=%cd%
pushd %CD%
cd..
robocopy %RCDIR% %RCDIR% /S /MOVE /NP /NFL /NJH /NDL /NC /NS

popd


