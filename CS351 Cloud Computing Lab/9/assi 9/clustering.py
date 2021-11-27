import pandas as pd
import numpy as np
from sklearn import preprocessing
from sklearn.metrics import silhouette_score
import math


df = pd.read_csv('col_name.csv',header=0)
print('Attributes are:')
print(df)
mat=df.to_numpy()

df= pd.read_csv('adults.csv',header=0)
mat=df.to_numpy()
print("Shape of matrix loaded:",mat.shape)

print("Using the following attributes: Age, Education Number, Hours per week")
mat=mat[:,[0,4,12,-1]]

def EuclideanDistance(x, y):
    S = 0 
    for i in range(len(x)):
        S += math.pow(x[i] - y[i], 2)
    return S

def errClustering(X,Y,centers):
    error=0
    for i in range(X.shape[0]):
        error+=EuclideanDistance(centers[int(Y[i][0])],X[i])
    return error

def Clustering(X,Y,centers):
    count=np.zeros(shape=(len(centers)))
    for i in range(X.shape[0]):
        for ci in range(len(centers)):
            dist=EuclideanDistance(X[i],centers[ci])
            if Y[i][1]==0 or Y[i][0]>dist:
                Y[i][0]=dist
                Y[i][1]=ci+1
    
    for i in range(len(centers)):
        centers[i]=np.zeros(shape=(X.shape[1]))

    for i in range(X.shape[0]):
        centers[int(Y[i][1])-1]=np.add(centers[int(Y[i][1])-1],X[i])
        count[int(Y[i][1])-1]+=1

    for i in range(len(centers)):
        if count[i]!=0:
            centers[i]=centers[i]/count[i]

    return Y,centers



X=mat[:,:-1]
X = preprocessing.normalize(X)
numItr=20
for i in range(2,3):
    Y=np.zeros(shape=(X.shape[0],2))
    np.random.shuffle(X)
    centroids=[]
    for ithCent in range(i):
        centroids.append(X[ithCent].copy())
    Y,centroids=Clustering(X,Y,centroids)
    #print(Y)
    print("k = ",i,"\nError(SSE) =",errClustering(X,Y,centroids))
    print("k = ",i,"\nsilhouette_score =",silhouette_score(X,Y[:,1]))
    

