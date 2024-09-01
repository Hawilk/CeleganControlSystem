@echo off
rem The only argument should be a file name with path holding version numbers.
rem If the argument contains path with spaces it should be passed quoted.

if not exist %1 (
    echo %1: Error: Version file %1 does NOT exist.
    exit /B 1
)

where /q svn >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo SVN tools were not found, ignoring error.
    exit /B 0
)

svn info %1 >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo Version file %1 seems to be not versioned, ignoring error.
    exit /B 0
)

rem `svn status` outputs either one or no line.
for /f "usebackq delims=" %%i in (`svn status -q %1`) do (
    rem One line status returned, it means the file has uncommited changes.
    echo Version was updated correctly.
    exit /B 0
)

rem No output from `svn status`, there are no uncommitted changes.
rem The command below shows an error in VS error list pointing to the version.h file,
rem user can just doubleclick the error and VS will open the file with version for editing.
rem If we ever want the error to point to this batch file then replace %~1 with %~f0.
rem The %~1 removes quotation marks if any. VS does not recognizes the error with quotes.
echo %~1: Error: Version number WAS NOT updated! Please update the %1 file and build again.
exit /B 1
