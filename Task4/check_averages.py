import csv

vals = []

with open("scores.csv","r") as csvfile:
    reader = csv.reader(csvfile, delimiter=' ')
    for row in reader:
        vals.append([int(entry) for entry in row[0].split(',')[:-1]])

vals = [x for x in zip(*vals)]
averages = [sum(vals[i])/len(vals) for i in range(len(vals[0]))]
for i in range(len(averages)):
    print("Assignement {} Average: {}".format(i, averages[i]))

# import pandas as pd
# import numpy as np
#
# df = pd.read_csv("scores.csv",header=None)
# vals = df.iloc[:,:-1].values
#
# print([sum(vals[:,i])/len(vals) for i in range(len(vals[0]))])
