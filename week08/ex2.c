#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define    MEM_SIZE 10*1024*1024    // 10MB

/**
 * Roman Soldatov BS19-02
 * Exercise 2
 */
int main() {
    for (int i = 0; i < 10; i++) {
        int *p = (int *) malloc(MEM_SIZE);
        memset(p, 0, MEM_SIZE);
        sleep(1);
    }

    return 0;
}


/** My findings about exercise 2:
 * So, I ran this command in terminal: ./ex2 & vm_stat 1
 * and got this infinite output (the beginning of it is shown bellow)
 * It updates the memory statistics every second.
 *
 * I was checking the 'swapins' and 'swapouts' columns.
 * Here is what I found.
 * Every 10 seconds 'swapins' and 'swapouts' has 324562 and 464661 values respectively.
 * On other iterations they have zero values.
 * Also, when the program finished, i.e. on the 10th iteration, last columns had 0 values,
 * but on other next 10th iterations they have 324562 and 464661 values.
 *
 * I run this program allocating 100MB every second instead of 10MB and got the same result.
 * Also, I changed the number of loop iterations inside the program: run i < 5, instead of i < 10
 * and got that 'swapins' and 'swapouts' columns had zero values and had nonzero values every 20th iteration
 */

/** My findings about exercise 3:
 * I used this command: ./ex2 & top -i 1
 * Also, this command worked at the same way: ./ex2 & top
 * And this one: run ./ex2, then run top
 *
 * So, the ex2 process was approaching to the top of the table
 * because the 'MEM' column was increasing. In the end it was showing 100M+ (which looks logically correct)
 * and then disappeared because the program was finished.
 * Also, it took 0.6% of CPU resources during all execution
 * The top processes from the table when this program was running are provided below:
 *
 * This description for the Exercise 3 is also duplicated in ex3.txt file
 */

/**  The beginning of the output */
/*
 [1] 2163
Mach Virtual Memory Statistics: (page size of 4096 bytes)
    free   active   specul inactive throttle    wired  prgable   faults     copy    0fill reactive   purged file-backed anonymous cmprssed cmprssor  dcomprs   comprs  pageins  pageout  swapins swapouts
   43766   697487     2665   661159        0   443203   138361 34650582   837480 28738444  1846285  2782684      421182    940129   919633   248451  1861962  3974569  2905299    18353   324562   464661
   39710   690260     2666   667080        0   448676   137471     2711       33     4146        0        0      421183    938823   919633   248451        0        0        0        0        0        0
   45221   679292     2666   679786        0   441357   136308     2611        0     2602        0        0      421183    940561   919633   248451        0        0        0        0        0        0
   44298   682040     2666   679633        0   439824   136305     3854        0     3844        0        0      421183    943156   919633   248451        0        0        0        0        0        0
   41546   683490     2666   680067        0   440533   134772     2645        0     2622        0        0      421183    945040   919631   248451        2        0        0        0        0        0
   39020   685358     2666   680840        0   440539   134782     2675        0     2667        0        0      421183    947681   919631   248451        0        0        0        0        0        0
   36871   687190     2666   683977        0   437777   135917     2610        0     2604        6        0      421183    952650   919631   248451        0        0        0        0        0        0
   34211   687597     2666   684584        0   439319   134394     2607        0     2572        0        0      421183    953664   919631   248451        0        0        0        0        0        0
   32896   686746     2666   685161        0   440945   131633     2592        0     2586        0        0      421183    953390   919631   248451        0        0        0        0        0        0
   30277   689581     2666   686442        0   439365   133156     2603        0     2598        0        0      421183    957506   919631   248451        0        0        0        0        0        0
   27860   690092     2666   686879        0   440986   131633     2580        0     2570        0        0      421183    958454   919628   248451        3        0        0        0        0        0
[1]  + done       ./ex2
   53353   675863     2666   675557        0   440918   131633      267        4      181        0        0      421183    932903   919599   248451       29        0        0        0        0        0
   53529   677403     2666   675557        0   439238   133166       38        0       33        0        0      421183    934443   919599   248451        0        0        0        0        0        0
   53534   676077     2695   675490        0   440646   131697     1297        0     1286        0        0      421212    933050   919596   248451        3        0        0        0        0        0
   60020   674301     2697   671435        0   440051   131697       73        0       54        0        0      421214    927219   919596   248451        0        0        0        0        0        0
   60075   675077     2697   672221        0   438445   133187       13        0        6        0        0      421214    928781   919595   248451        1        0        0        0        0        0
   59989   673541     2697   672207        0   439981   131654       27        0       22        0        0      421214    927231   919595   248451        0        0        0        0        0        0
   61523   673496     2698   670711        0   440010   131600       27        0       19        0        0      421215    925690   919594   248451        1        0        0        0        0        0
   61590   674274     2698   671413        0   438474   133133       11        0        7        0        0      421215    927170   919594   248451        0        0        0        0        0        0
   61612   672751     2698   671413        0   440009   131600       34        0       26        0        0      421215    925647   919592   248451        2        0        0        0        0        0
   61620   672742     2698   671333        0   440100   131590       13        0        8        0        0      421215    925558   919592   248451        0        0        0        0        0        0
Mach Virtual Memory Statistics: (page size of 4096 bytes)
    free   active   specul inactive throttle    wired  prgable   faults     copy    0fill reactive   purged file-backed anonymous cmprssed cmprssor  dcomprs   comprs  pageins  pageout  swapins swapouts
   61519   674242     2698   671373        0   438554   133133 34679890   837517 28768913  1846291  2782684      421215    927098   919592   248451  1862003  3974569  2905299    18353   324562   464661
 */

/** The top processes from the table when this program was running*/
/*
 PID   COMMAND      %CPU TIME     #TH   #WQ  #PORT MEM    PURG   CMPRS  PGRP PPID STATE    BOOSTS           %CPU_ME %CPU_OTHRS UID  FAULTS   COW    MSGSENT   MSGRECV   SYSBSD
2602  top          11.8 00:01.19 1/1   0    26    5044K  0B     0B     2602 2524 running  *0[1]            0.00000 0.00000    0    4647+    109    231790+   115881+   12599+
0     kernel_task  3.6  15:57.45 178/4 0    0     168M   0B     0B     0    0    running   0[0]            0.00000 0.00000    0    82209    0      22014076+ 17863270+ 0
1916  Terminal     2.3  00:41.34 9     2    312-  122M   65M-   5100K- 1916 1    sleeping *0[749]          0.19108 0.05125    501  831151+  984    253776+   55754+    187427+
1     launchd      2.2  00:20.91 3     2    3383+ 22M+   0B     10M    1    0    sleeping  0[0]            0.00000 0.00000    0    32425+   1797   315740    89142     430582+
1714  clion        1.9  10:20.76 75    2    552   1459M  3200K  305M   1714 1    sleeping *0[1555+]        0.00000 0.00575    501  3370708+ 77635  1038748+  318543+   2646526+
220   WindowServer 0.9  21:34.04 11    5    2886+ 664M-  18M-   43M    220  1    sleeping *0[1]            0.45426 0.00225    88   3217470+ 141693 16265594+ 7282826+  9842545+
383   DashlaneAgen 0.6  01:33.75 10    2    327   16M    0B     12M    383  1    sleeping *0[1]            0.14495 0.00000    501  50119+   713    471126+   313327+   1012178+
2601  ex2          0.6  00:00.06 1     0    10    90M+   0B     0B     2601 2524 sleeping *0[1]            0.00000 0.00000    501  23412+   99     45+       22+       116+
714   Trello Helpe 0.5  01:28.86 13    1    140   38M+   0B     26M    709  709  sleeping *0[1]            0.00000 0.00000    501  32917    1435   646679+   264409+   691438+
421   com.apple.ge 0.5  00:03.31 6     4    93+   6980K+ 0B     3836K  421  1    sleeping  0[118]          0.39533 0.00000    501  12262+   249    30728+    5489+     86344+
710   Trello Helpe 0.5  01:21.72 8     1    177   170M   1024K  29M    709  709  sleeping *0[4]            0.00000 0.00000    501  116929   1506   1082424+  528550+   449160+
403   Macs Fan Con 0.3  00:45.82 6     1    230   16M+   40K-   10M    403  1    sleeping *0[1088]         0.05343 0.00000    501  18385    477    247686+   105288+   310238+
551   DashlanePlug 0.3  00:59.47 6     1    168   10M    0B     7536K  551  1    sleeping *0[149387+]      0.00000 0.14495    501  9367     470    625814+   162269+   767571+
713   Trello Helpe 0.3  00:48.60 15    2    176   136M+  0B     50M    709  709  sleeping *0[1]            0.00000 0.00000    501  387150+  4265   193900+   123110+   384645+
151   hidd         0.3  05:49.95 6     3    245   2880K  0B     696K   151  1    sleeping *0[1]            0.02030 0.13717    261  143325+  169    1217415+  1033901+  9457000+
371   useractivity 0.3  00:05.95 4     3    111+  3868K+ 0B     2048K  371  1    sleeping *14+[1205]       0.40941 0.10846    501  7462+    222    15558+    8937+     50133+
150   bluetoothd   0.3  00:26.70 4     2    179   3268K+ 0B     952K   150  1    sleeping *0[1]            0.00000 0.28525    0    14430+   269    602680+   379370+   206191+
390   sharingd     0.1  00:19.91 4     2    249+  35M+   0B     22M    390  1    sleeping *0[1]            0.00000 0.08258    501  217972+  9015   80115+    27616+    303644+
709   Trello       0.1  00:53.72 26    1    395   67M    0B     28M    709  1    sleeping *0[936]          0.00000 0.00000    501  191817+  2634   513203+   249613+   520461+
499   Telegram     0.1  09:49.94 31    6    1853- 763M   1732K- 327M   499  1    sleeping *0[2316]         0.00000 0.00000    501  5605814  31108  2609298+  683710    4675319+
 */
