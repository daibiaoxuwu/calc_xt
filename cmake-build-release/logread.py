import os
import time
lines = []
results = []
flag = False
mname=["1W","2W","3W","4W","5W","6W","7W","8W","9W","1B","2B","3B","4B","5B","6B","7B","8B","9B","1T","2T","3T","4T","5T","6T","7T","8T","9T","EST","STH","WST","NTH","BAI","FA","ZHO"]
oldline = ''
with open('..\\log.csv') as f:
    for line in f.readlines():
        if('0' <= line[0] <= '9' and ',' in line and len(line) >= 103):
            lines.append(line)
            if(len(line)!=103 and not('-' in line)):
                print(len(line))
                print(line)
            flag = True
        elif('Mar' in line and flag):
            results.append(oldline)
            flag = False
        oldline = line
print(len(lines),len(results)*3)            
for i in range(32,len(results)): 
    print('-------------------',i,'------------------')
    if('-' in lines[3*i]):continue
    if('-' in lines[3*i+1]):continue
    if('-' in lines[3*i+2]):continue
    hand = lines[3*i].split(',')
    outstr = ''
    breakflag = False
    for k in range(34):
        for r in range(int(hand[k])):
            outstr += mname[k] + ' '
            if(k >= 27 and (int(hand[k]))%3 == 1): breakflag = True
    print(outstr)
    if(breakflag):continue
    for j in range(34):
        if(mname[j] in results[i]):
            with open('input.txt','w') as g:
                g.write('69\n')
                for t in range(3):
                    g.write(lines[3*i+t].replace(',',''))
            start = time.time()
            res = os.system('calc_xt.exe')
            print("time:",time.time()-start)
            if(not (res == j or res == -1000)):
                for t in range(3):
                    print(lines[3*i+t].replace(',',''),end='')
            if(res >= 0):
                print(results[i],'newres:',mname[res],'oldres:',mname[j])
            break



