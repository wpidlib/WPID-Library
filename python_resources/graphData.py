import pandas as pd
import matplotlib.pyplot as plt
import os

def graphColumn(fileName, runNum):
    allData = pd.read_csv("VexLogs/"+fileName)
    allData["Time"] = allData["Time"] - allData["Time"][0]
    
    figure, axis = plt.subplots(4, 1)
    
    
    axis[0].plot(allData["Time"], allData["Error"])
    
    axis[0].set_xlabel('Time')
    axis[0].set_ylabel('Error')
    axis[0].set_title('Error Over Time on Instruction '+runNum)
    
    
    axis[1].plot(allData["Time"], allData["Speed"])
    
    axis[1].set_xlabel('Time')
    axis[1].set_ylabel('Speed')
    axis[1].set_title('Speed Over Time on Instruction '+runNum)
    
    axis[2].plot(allData["Time"], allData["Proportional"], color = 'tab:red')
    axis[2].plot(allData["Time"], allData["Integral"], color = 'tab:blue')
    axis[2].plot(allData["Time"], allData["Derivative"], color = 'tab:green')
    
    axis[2].set_xlabel('Time')
    axis[2].set_ylabel('P I and D')
    axis[2].set_title('PID Over Time on Instruction '+runNum)
    
    axis[3].plot(allData["Time"], abs(allData["Error"]-allData["Error"][0]), color = 'tab:red')
    axis[3].set_xlabel('Time')
    axis[3].set_ylabel('Distance to Target')
    axis[3].set_title('Distance to Target on Instruction '+runNum)
    
    figure.tight_layout()

    plt.show()
    

allFiles =  os.listdir("VexLogs/")
allFiles.sort(key = len)

count = 1
for file in allFiles:
    graphColumn(file, str(count))
    count+=1