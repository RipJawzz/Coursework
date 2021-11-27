import sys
import numpy as np
from math import sqrt
from pyspark import SparkContext
from pyspark.mllib.clustering import KMeans

S3_DATA_SOURCE_PATH="s3://awsbucketboi/adultdata.txt"
s3_DATA_OUTPUT_PATH="s3://awsbucketboi/output/"



if __name__ == "__main__":
    sc = SparkContext(appName="EMRClust")
    data = sc.textFile(S3_DATA_SOURCE_PATH)
    parsedData = data.map(lambda line: np.array([x for x in line.split(', ')])[np.array([0,2,11])].astype(float))
    
    
    clusters = KMeans.train(parsedData, 2, maxIterations=20, initializationMode="random")
    cluster_center=clusters.centers
    cluster_center.saveAsTextFile(s3_DATA_OUTPUT_PATH)
    print("Centers:",clusters.centers,file=sys.stdout)
    def error(point):
        center = clusters.centers[clusters.predict(point)]
        return sqrt(sum([x**2 for x in (point - center)]))

    WSSSE = parsedData.map(lambda point: error(point)).reduce(lambda x, y: x + y)
    print("Within Set Sum of Squared Error = " + str(WSSSE),file=sys.stdout)
   
    sc.stop()
