@echo on
copy LICENSE.LGPL liteide
copy LGPL_EXCEPTION.TXT liteide
copy README.TXT liteide
copy CHANGES.TXT liteide 
copy GOCODE.TXT liteide
xcopy deploy liteide  /e /y /i
xcopy os_deploy\win32 liteide /e /y  /i
pause