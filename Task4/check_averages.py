import pandas as pd
import numpy as np

df = pd.read_csv("scores.csv",header=None)
vals = df.iloc[:,:-1].values

print([sum(vals[:,i])/len(vals) for i in range(len(vals[0]))])
