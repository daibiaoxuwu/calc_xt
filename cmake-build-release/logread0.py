import os
lines = []
results = []
flag = False
mname=["1W","2W","3W","4W","5W","6W","7W","8W","9W","1B","2B","3B","4B","5B","6B","7B","8B","9B","1T","2T","3T","4T","5T","6T","7T","8T","9T","EST","STH","WST","NTH","BAI","FA","ZHO"]

with open('..\\log.csv') as f:
    for line in f.readlines():
        if('0' <= line[0] <= '9' and ',' in line):
            lines.append(line)
            flag = True
        elif('discard' in line and flag):
            results.append(line)
            flag = False
print(len(lines),len(results)*3)            
for i in range(len(results)): 
    for j in range(34):
        if(mname[j] in results[i]):
            with open('input.txt','w') as g:
                g.write('69\n')
                for t in range(3):
                    g.write(lines[3*i+t].replace(',',''))
            res = os.system('calc_xt.exe')
            if(not (res == j or res == -1000)):
                for t in range(3):
                    print(lines[3*i+t].replace(',',''))
                print(results[i], print('res:',mname[res],'j:',mname[j])
            break



