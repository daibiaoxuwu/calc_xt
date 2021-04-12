import os

hai = [0]*34
code = input()
#code = '2277m22478s12356p'
base = 0
for i in code:
    if i < '0' or i > '9':
        if i != ' ':
            base += 9
    elif i == '0':
        hai[base + 4]+=1
    else:
        hai[base + int(i) - int('1')]+=1


f = open("input.txt", "w")
f.write("69\n")
for i in range(34):
    f.write("%d " % hai[i])
f.write("\n")
for i in range(34):
    f.write("%d " % (4-hai[i]))
f.write("\n")
for i in range(34):
    f.write("0 ")
f.write("\n")
f.close()
os.system("calc_xt.exe")
os.system("calc_xt0.exe")
