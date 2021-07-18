import subprocess
import re
import csv
import os.path
from os import path

f_results = []
execution_times =[]
logs = []
hit = 0
loop_size = 10
total_time=0
hitflag=[]
count = 0
with open("query1.txt","r") as file1:
    Lines = file1.readlines()
    for line in Lines:
        count +=1
        with open("query.txt","w+") as file2:
            file2.write(line)

        for x in range(loop_size):
            cp = subprocess.run("./m.o -i lineitem1GB.csv -o s_lineitem.csv -s .005", shell = True, stdout=subprocess.PIPE)

            results = cp.stdout.decode("utf-8")
            results = re.findall(r"\d*\.\d*|\d+",results)
            f_results.append([float(i) for i in results])

            
            
        #print(f_results)
        for i in  range(0,len(f_results)):
            if f_results[i][5] < f_results[i][1]< f_results[i][6]:
                hit += 1
                hitflag.append(1)
            else:
                hitflag.append(0)

            execution_times.append(f_results[i][8])
        print("number of hit: ", hit)
        hitpercent= hit*100/loop_size
        print("percentage: ",hitpercent)
        print(execution_times)
        for j in range(len(execution_times)):
            total_time += execution_times[j]
        print(total_time)

        for k in range(0,len(f_results)):
            logs.append([k])
            logs[k].append(count)
            logs[k].append(f_results[k][1])
            logs[k].append(f_results[k][0])
            logs[k].append(f_results[k][4])
            logs[k].append(f_results[k][5])
            logs[k].append(f_results[k][6])
            logs[k].append(f_results[k][3])
            logs[k].append(f_results[k][2])
            logs[k].append(f_results[k][8])
            logs[k].append(hitflag[k])
        #print(logs)
        fields = ['Run number', 'Query Number','GT', 'EST','STD', 'Lower_CI','Upper_CI','RNG_Time','FA_time','Total_Time','Hit']
        if not path.exists('Logs.csv'):
            with open('Logs.csv', 'w', newline='') as file:
                writer = csv.writer(file, delimiter =',')
                writer.writerow(fields)

        with open('Logs.csv', 'a', newline='') as file:
            writer = csv.writer(file, delimiter =',')
            for l in range(0,len(logs)):
                writer.writerow(logs[l])
        f_results.clear()
        logs.clear()
        execution_times.clear()
        hitflag.clear()


            
                
