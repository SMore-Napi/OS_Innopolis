# Roman Soldatov BS19-02
# Exercise 2

# ex2.c will behave like tee command.
# So, firstly we need to make the executable file
gcc ex2.c -o ex2

# The lab task asks for outputting /proc/cpuinfo
# However, MacOS doesn't support this command.
# So, I used this one 'sysctl -a | grep machdep.cpu'
# I took it from here:
# https://apple.stackexchange.com/questions/352769/does-macos-have-a-command-to-retrieve-detailed-cpu-information-like-proc-cpuinf

# Write this command to append info to the output
sysctl -a | grep machdep.cpu | ./ex2 -a ex2.txt
# Write this command to overwrite existing file
#sysctl -a | grep machdep.cpu | ./ex2 ex2.txt

# Remove temporary executable file
rm ex2
