@echo off
echo Attempting to execute /cygwin64/bin/bash. If the executable does not exist, we will fall back to /cygwin/bin/bash.
/cygwin64/bin/bash --login "%cd%\ant.sh" || /cygwin/bin/bash --login "%cd%\ant.sh"