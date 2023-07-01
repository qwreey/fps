# fps: File locking ProcesseS (CLI version of Powertoys FileLocksmith)
Which process using folder or file?

In windows, when you move file, delete file or eject disk, probably, you can see error messgae 'File Is Open in Another Program' which very annoying.
Fps was designed for this situation, you can automate taskkill, and automate safe eject. like

```bat
@echo off
@rem the fps.exe file should be next to bat

@rem get bat's disk
set "HERE=%~dp0."
set DISK=%HERE:~0,3%

@rem get pid of this script selfs (for exclude)
title diskkill
for /f "tokens=2 delims=," %%a in ('tasklist /v /fo csv ^| findstr /i "diskkill"') do set "mypid=%%~a"

@rem kill all of tasks which running on disk
set TRY=0
:KILL
set /a "c=%TRY%+1"
set ARGS=
for /F "tokens=*" %%B in ('%HERE%\fps.exe -f pid -H') do call :AddArgs %%B
if DEFINED ARGS if "x%TRY%" != "x5" ( taskkill /T%ARGS% & goto :KILL )

@rem Eject target disk
powershell -NoProfile "$disk = (New-Object -ComObject Shell.Application).Namespace(17).ParseName('%DISK%'); $disk.InvokeVerb('Eject'); do { Sleep 1 } until ($disk.Type.Equals('Removable Disk') )"

exit 0
:AddArgs
if "x%1" == "x%mypid%" exit /b 0
set "ARGS=%ARGS% /PID %1"
exit /b 0
```

Or, you can create simple embedable script like lua too.

# Uses

```
Usage:   fps [-HA] [-f pid,image,...] ...[<File|Directory>]
Defualt: fps -f "pid,image,user" .

Report processes which using specific file or directory.
If filter option not given, prints pid, name and user as default.
The output order of each element follows the order of the given options.
Options can be combined into a single argument like 'fps -HA'
example: fps -f "pid,image" .

General options
 -h, --help, -?  Show this messages.
 -H, --headless  Print results without heading.
 -a, --all       Use all filter options, output order follows the order of help.
 -f, --filter [filter,filter,...]
                 Use filters to show. see 'Filter options'
 -v, --version   Show version of fps
 -V, --verbose   Verbose mode for debugging (Not used for now)
 -c  --count     Count number of processes and print it as last line

Filter options
 pid    PID of found process.
 image  Image name of found process.
        This is the executable file name rather than the full path.
 user   Username of who the found process runs.
 path   Full path of found process
 files  Full paths of files which found process uses.

Exit status:
 0: if found processes
 1: if has no processes
 2: commandline arguments is invalid
```

# Build

Open sln with visual studio, and build. You should install C++ 20, Windows SDK 10.0.19041.0 or up.

# Todo

Add selector like --select "image" "equal" "..."
