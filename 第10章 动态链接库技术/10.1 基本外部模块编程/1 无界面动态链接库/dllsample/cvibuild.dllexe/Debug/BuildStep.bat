<<<<<<< HEAD
@call %1.bat > %1.out
@if %errorlevel% neq 0 (
  @echo Build Step failed for %1
  @exit %errorlevel%)
@echo Build Step complete for %1
=======
@call %1.bat > %1.out
@if %errorlevel% neq 0 (
  @echo Build Step failed for %1
  @exit %errorlevel%)
@echo Build Step complete for %1
>>>>>>> 6cb5d42fc5d5a1f945cc808ffbde2a6f84a8e888
