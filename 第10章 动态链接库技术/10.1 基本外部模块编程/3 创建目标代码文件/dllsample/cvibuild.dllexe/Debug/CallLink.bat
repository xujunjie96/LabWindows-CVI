<<<<<<< HEAD
@"d:\program files (x86)\national instruments\cvi2017\bin\cvilink.exe" -cmd:link_options.txt -flags:0 -expiry:0 > Link.out 2>&1
@if errorlevel 1 goto err
@echo Link success
@echo Link complete
@exit 0
:err
@echo Link complete
@echo Link failed
@exit 1
=======
@"d:\program files (x86)\national instruments\cvi2017\bin\cvilink.exe" -cmd:link_options.txt -flags:0 -expiry:0 > Link.out 2>&1
@if errorlevel 1 goto err
@echo Link success
@echo Link complete
@exit 0
:err
@echo Link complete
@echo Link failed
@exit 1
>>>>>>> 6cb5d42fc5d5a1f945cc808ffbde2a6f84a8e888
