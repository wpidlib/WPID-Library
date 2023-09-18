import pandas as pd
import matplotlib.pyplot as plt

def graphColumn():
    allData = pd.read_csv("LoggedData398.csv")
    allData["Time"] = allData["Time"] - allData["Time"][0]
    
    plt.plot(allData["Time"], allData["Error"])
    
    plt.xlabel('Time')
    plt.ylabel('Error')
    plt.title('Error Over Time')
    plt.show()
    
    plt.plot(allData["Time"], allData["Speed"])
    
    plt.xlabel('Time')
    plt.ylabel('Speed')
    plt.title('Speed Over Time')
    plt.show()
    
    plt.plot(allData["Time"], allData["Proportional"])
    
    plt.xlabel('Time')
    plt.ylabel('Proportional')
    plt.title('Proportional Over Time')
    plt.show()
    
    plt.plot(allData["Time"], allData["Integral"])
    
    plt.xlabel('Time')
    plt.ylabel('Integral')
    plt.title('Integral Over Time')
    plt.show()
    
    plt.plot(allData["Time"], allData["Derivative"])
    
    plt.xlabel('Time')
    plt.ylabel('Derivative')
    plt.title('Derivative Over Time')
    plt.show()
    
    plt.plot(allData["Time"], allData["Proportional"])
    plt.plot(allData["Time"], allData["Integral"])
    plt.plot(allData["Time"], allData["Derivative"])
    
    plt.xlabel('Time')
    plt.ylabel('P I and D')
    plt.title('PID Over Time')
    plt.show()
    
    

    
    
    
    
    
    
graphColumn()