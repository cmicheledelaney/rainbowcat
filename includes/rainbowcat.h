#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define LEN 50
#define CENTER 128
#define WIDTH 127
#define CENTER_PASTEL 200
#define WIDTH_PASTEL 55
#define FREQUENCY 0.2
#define PHASE1 0
#define PHASE2 2
#define PHASE3 4
#define RESET "\033[0m"

char *HELP = "                     ;,_\n\
                  _uP~\"b          d\"u,\n\
                 dP'   \"b       ,d\"  \"o\n\
                d\"    , `b     d\"'    \"b\n\
               l] [    \" `l,  d\"       lb\n\
               Ol ?     \"  \"b`\"=uoqo,_  \"l\n\
             ,dBb \"b        \"b,    `\"~~TObup,_\n\
           ,d\" (db.`\"         \"\"     \"tbc,_ `~\"Yuu,_\n\
         .d\" l`T'  '=                      ~     `\"\"Yu,\n\
       ,dO` gP,                           `u,   b,_  \"b7\n\
      d?' ,d\" l,                           `\"b,_ `~b  \"1\n\
    ,8i' dl   `l                 ,ggQOV\",dbgq,._\"  `l  lb\n\
   .df' (O,    \"             ,ggQY\"~  , @@@@@d\"bd~  `b \"1\n\
  .df'   `\"           -=@QgpOY\"\"     (b  @@@@P db    `Lp\"b,\n\
 .d(                  _               \"ko \"=d_,Q`  ,_  \"  \"b,\n\
 Ql         .         `\"qo,._          \"tQo,_`\"\"bo ;tb,    `\"b,\n\
(qQ         |L           ~\"QQQgggc,_.,dObc,opooO  `\"~~\";.   __,7,\n\
`qp         t\\io,_           `~\"TOOggQV\"\"\"\"        _,dg,_ =PIQHib.\n\
 `qp        `Q[\"tQQQo,_                          ,pl{QOP\"'   7AFR`\n\
   `         `tb  '\"\"tQQQg,_             p\" \"b   `       .;-.`Vl'\n\
              \"Yb      `\"tQOOo,__    _,edb    ` .__   /`/'|  |b;=;.__\n\
                            `\"tQQQOOOOP\"\"        `\"QV;qQObob\"`-._`\\_~~-._\n\
                                 \"\"\"\"    ._        /   | |oP\"\\_   ~\\ ~\\  ~\n\
                                         `~\"ic,qggddOOP\"|  |  ~\\   \\  ~-._\n\
                                           ,qP`\"\"\"|\"   | `\\ `;   `\\   `\n\
                                _        _,p\"     |    |   `\\`;    |    |\n\
                                 \"boo,._dP\"       `\\_  `\\    `\\|   `\\   ;\n\
                                  `\"7tY~\\            `\\  `\\    `|_   |\n\
                                                           `~\\  |\n\
\n\
\n\
RAINBOWCAT(1)                                                                       User Commands                                                                         RAINBOWCAT(1)\n\
\n\
NAME\n\
       rainbowcat - concatenate files and print on the standard output\n\
\n\
SYNOPSIS\n\
       rainbowcat [OPTION]... [FILE]...\n\
\n\
DESCRIPTION\n\
       Concatenate FILE(s) to standard output.\n\
\n\
       With no FILE read standard input.\n\
\n\
       --help\n\
              displays help information\n\
\n\
       --pastel\n\
              displays the output in pastel colors\n\
\n\
       --frequency [VALUE]\n\
              changes the frequency to VALUE\n\
\n\
EXAMPLES\n\
       rainbowcat kittens.txt colors.txt rainbowcat.txt\n\
              Output kittens.txt's, color.txt's and rainbowcat.txt's contents in default colors.\n\
\n\
       rainbowcat --pastel rainbowcat.txt\n\
              Output rainbowcat.txt's contents in pastel colors.\n\
\n\
       rainbowcat --frequency 1 rainbowcat.txt\n\
              Output rainbowcat.txt's contents in a low frequency (colorchanges occur less often) to standard output.\n\
\n\
AUTHOR\n\
       Written by C. Michele Delaney.\n";


