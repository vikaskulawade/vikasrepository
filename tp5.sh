#!/bin/bash
sed -n 's/REQ_END/REQ_END/p'  error_log_1>error1.txt
cut -d':' -f5 error1.txt>error2.txt
sort -n -k1 error2.txt>error3.txt
