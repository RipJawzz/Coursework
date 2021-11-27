#!/usr/bin/python3
import sys
current_word=None
current_count=0
words=[]
for line in sys.stdin:
    line=line.strip().split(',')            
    words.append(line[0])
    
for i in words:
    print(i)