#!/usr/bin/python3
import sys
current_word=None
current_count=0
words={}
for line in sys.stdin:
    line=line.strip().split(',')            
    word=line[0]
    if word in words:
        words[word]+=1
    else:
        words[word]=1
#words.sort
for i in words:
    print(f'{i} , {words[i]}')
    