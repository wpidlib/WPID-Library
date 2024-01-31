import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
import sys

def graphMotorGroup(dataframe, motorName, arguments):

    figure, axis = plt.subplots(4, 1)

    axis[0].plot(dataframe["Time"], dataframe["Error"])
    axis[0].axhline(y=0.0, color='gray', linestyle='--')

    axis[0].set_xlabel('Time')
    axis[0].set_ylabel('Error')
    axis[0].set_title('Error Over Time for '+motorName)

    axis[1].plot(dataframe["Time"], dataframe["Speed"])
    axis[1].axhline(y=0.0, color='gray', linestyle='--')


    axis[1].set_xlabel('Time')
    axis[1].set_ylabel('Speed')
    axis[1].set_title('Speed Over Time for '+motorName)

    pidLegendPlots = []
    pidLegendNames = []

    if 'P' in arguments:
        P, = axis[2].plot(dataframe["Time"], dataframe["Proportional"], color = 'tab:red')
        pidLegendPlots.append(P)
        pidLegendNames.append("P")
    if 'I' in arguments:
        I, = axis[2].plot(dataframe["Time"], dataframe["Integral"], color = 'tab:blue')
        pidLegendPlots.append(I)
        pidLegendNames.append("I")
    if 'D' in arguments:
        D, = axis[2].plot(dataframe["Time"], dataframe["Derivative"], color = 'tab:green')
        pidLegendPlots.append(D)
        pidLegendNames.append("D")

    axis[2].axhline(y=0.0, color='gray', linestyle='--')


    axis[2].set_xlabel('Time')
    axis[2].set_ylabel('P I D')
    axis[2].set_title('PID Over Time for '+motorName)
    axis[2].legend(pidLegendPlots, pidLegendNames)

    axis[3].plot(dataframe["Time"], dataframe["Error"], color = 'tab:red')
    axis[3].axhline(y=0.0, color='gray', linestyle='--')

    axis[3].set_xlabel('Time')
    axis[3].set_ylabel('Distance to Target')
    axis[3].set_title('Distance to Target for '+motorName)

    figure.tight_layout()
    manager = plt.get_current_fig_manager()
    manager.window.state('zoomed')

    plt.show()


arguments = []

if len(sys.argv) > 1:
    for argument in sys.argv:
        arguments.append(argument)

if(len(sys.argv)==1):
    arguments = ['P', 'I', 'D']

allFiles =  os.listdir("VexLogs/")
allFiles.sort(key = len)

dFs = []

for file in allFiles:
    if file.endswith(".csv"):
        data = pd.read_csv("VexLogs/"+file)
        name = data["Name"].iloc[0]
        time = data["Time"].tail(1)
        #print(time+1)
        data.loc[len(data.index)] = [time+1, np.NaN, np.NaN, np.NaN, np.NaN, np.NaN, name]
        #print(name)
        dFs.append(data)

result = pd.concat(dFs)

dFs = [result[result['Name'] == 'LEFT'], result[result['Name'] == 'RIGHT'], result[result['Name'] == 'CENTER'], result[result['Name'] == 'MECHANISM']]

for frame in dFs:
    if(not frame.empty):
        graphMotorGroup(frame, frame['Name'].iloc[0], arguments)
