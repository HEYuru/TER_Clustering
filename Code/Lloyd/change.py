
def loadDataSet(fileName):  
    dataMat = []  
    from itertools import islice  
    fr = open(fileName)
    line_num = 0
    #for line in fr.readlines():
    for line in islice(fr, 0, 1):
		curLine = line.strip().split()
		N = curLine[0]
		d = curLine[1]
    for line in islice(fr, 1, None):
        curLine = line.strip().split()
        a = list(map(float,curLine))
        b = list(a)
        dataMat.append(b)
          
        #fltLine= map(float, curLine)
        #dataMat.append(fltLine)
    return dataMat ,N ,d
    
    
def writedata(fileName,data,n,d):
 fo = open(fileName+".dat", "w")
 fo.write(" dimension = ")
 fo.write(d) 
 fo.write("; \n") 
 
 fo.write(" nbPoints = ")
 fo.write(n)
 fo.write("; \n")
 
 fo.write(" nbCluster = 4")
 fo.write("; \n")
 
 fo.write("\n")   
 fo.write(" points = ")
 fo.write(str(data)) 
 fo.write(";")
 
 fo.close()   
    
fliename = "data50"
data,n,d = loadDataSet("dataAlea2_50_ex1.txt")  
writedata(fliename,data,n,d);
