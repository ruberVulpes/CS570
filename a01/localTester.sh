#!/bin/bash
PROG="./tokenizer"
`make`
echo First Case
echo g++ -o tokenizer tokenizer.cpp -lreadline | $PROG
echo "[{g++},{-o},{tokenizer},{tokenizer.cpp},{-lreadline}]"

echo Second Case
echo ssh theoden@edoras.rohan | $PROG
echo "[{ssh},{theoden@edoras.rohan}]"

echo Third Case
echo "echo There's the rub" | $PROG
echo "[{echo},{There's the rub}]"

echo Fourth Case
echo "echo 'There's the rub' penned Shakespeare." | $PROG
echo "[{echo},{Theres},{the},{rub penned Shakespeare.}]"

echo Fifth Case
echo cat names.txt \| sort \| cut -f2 -d\ | $PROG
echo "[{cat},{names.txt},{|},{sort},{|},{cut},{-f2},{-d }]"

echo Sixth Case
echo "emacs&" | $PROG
echo "[{emacs},{&}]"

echo Seventh Case
echo "cd /etc; cat passwd ; cd -" | $PROG
echo "[{cd},{/etc},{;},{cat},{passwd},{;},{cd},{-}]"

echo Eight Case
echo "find . -name '*.txt' -exec grep {} /dev/null \; " | $PROG
echo "[{find},{.},{-name},{*.txt},{-exec},{grep},{{}},{/dev/null},{;}]"

echo Ninth Case
echo "	passwd" | $PROG
echo "[{passwd}]"

echo Tenth Case
echo grep "\"Holy Trickery Batman!\" said Robin" foobar.txt | $PROG
echo "[{grep},{"Holy Trickery Batman!" said Robin},{foobar.txt}]"

echo 11th Case
echo "grep "Martin Luther Kings work on" biographies.txt" | $PROG
echo "[{grep},{Martin Luther King's work on},{biographies.txt}]"

echo 12th Cases
echo "cd 'Joseph "Buster" Keaton'" | $PROG
echo "[{cd},{Joseph "Buster" Keaton}]"

echo 13th Case
echo "echo 'backslash doesn\'t work here'" | $PROG
echo "[{echo},{backslash doesn\t},{work},{here}]"

#echo 14th Case
#echo "for $d in $(ls) ; do echo $d; ls $d; done" | $PROG
#echo "[{for},{$d},{in},{$(ls)},{;},{do},{echo},{$d},{;},{ls},{$d},{;},{done}]"

echo 15th Case
echo "cat <read_me_a_story.txt" | $PROG
echo "[{cat},{<},{read_me_a_story.txt}]"

echo 16th Case
echo "echo Once upon a time >bedtime.txt" | $PROG
echo "[{echo},{Once},{upon},{a},{time},{>},{bedtime.txt}]"

