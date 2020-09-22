#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 2
 */

/**
 * I run this program using the terminal.
 * However, the command 'pstree' was called from this program.

 * Each fork() function divide the current process by two processes.
 * Therefore, calling n times fork() function will give us 2^n processes.

 * For i = 3 in the loop there will be 8 processes created.
 * For i = 5 in the loop there will be 32 processes created.
 */
int main() {
    for (int i = 0; i < 3; i++) {
        fork();
        sleep(5);
        // Print processes starting from 1 pid
        system("pstree -p 1");

        // Or we can print only processes related to this program.
        // I found its pid by calling the command above.
        // system("pstree -p 4856");
    }

    return 0;
}

/**
 * As for each iteration this program invokes 'pstree' command,
 * and there are several same 2^i processes which call this command because of forks,
 * I got several messages (i.e. for the i-th iteration the tree of processors was printed i times).
 * So, I deleted duplicates from the output.
 * Also, I removed other processors which are not related to this program (otherwise it will be so big)
 */

// Output for i = 3 by calling 'pstree' command on each iteration
/*
-+= 00001 root /sbin/launchd
 \-+= 04855 smore /System/Applications/Utilities/Terminal.app/Contents/MacOS/Terminal
   \-+= 04856 root login -pf smore
     \-+= 04857 smore -zsh
       \-+= 08690 smore ./ex2
         |-+- 08691 smore ./ex2
         | \-+- 08692 smore pstree -p 4856
         |   \--- 08694 root ps -axwwo user,pid,ppid,pgid,command
         \-+- 08693 smore pstree -p 4856
           \--- 08695 root ps -axwwo user,pid,ppid,pgid,command
-+= 00001 root /sbin/launchd
 \-+= 04855 smore /System/Applications/Utilities/Terminal.app/Contents/MacOS/Terminal
   \-+= 04856 root login -pf smore
     \-+= 04857 smore -zsh
       \-+= 08690 smore ./ex2
         |-+- 08691 smore ./ex2
         | |-+- 08697 smore ./ex2
         | | \-+- 08699 smore pstree -p 4856
         | |   \--- 08704 root ps -axwwo user,pid,ppid,pgid,command
         | \-+- 08700 smore pstree -p 4856
         |   \--- 08703 root ps -axwwo user,pid,ppid,pgid,command
         |-+- 08696 smore ./ex2
         | \-+- 08698 smore pstree -p 4856
         |   \--- 08705 root ps -axwwo user,pid,ppid,pgid,command
         \-+- 08701 smore pstree -p 4856
           \--- 08702 root ps -axwwo user,pid,ppid,pgid,command
-+= 00001 root /sbin/launchd
 \-+= 04855 smore /System/Applications/Utilities/Terminal.app/Contents/MacOS/Terminal
   \-+= 04856 root login -pf smore
     \-+= 04857 smore -zsh
       \-+= 08690 smore (ex2)
         |-+- 08691 smore (ex2)
         | |-+- 08697 smore (ex2)
         | | |-+- 08707 smore (ex2)
         | | | \-+- 08713 smore (pstree)
         | | |   \--- 08721 root (ps)
         | | \-+- 08711 smore (pstree)
         | |   \--- 08718 root (ps)
         | |-+- 08708 smore (ex2)
         | | \-+- 08714 smore (pstree)
         | |   \--- 08725 root (ps)
         | \-+- 08715 smore (pstree)
         |   \--- 08720 root (ps)
         |-+- 08696 smore (ex2)
         | |-+- 08706 smore (ex2)
         | | \-+- 08710 smore (pstree)
         | |   \--- 08722 root (ps)
         | \-+- 08712 smore (pstree)
         |   \--- 08719 root (ps)
         |-+- 08709 smore ./ex2
         | \-+- 08716 smore pstree -p 4856
         |   \--- 08724 root ps -axwwo user,pid,ppid,pgid,command
         \-+- 08717 smore (pstree)
           \--- 08723 root (ps)
 */
