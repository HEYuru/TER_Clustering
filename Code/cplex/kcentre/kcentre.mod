/*********************************************
 * OPL 12.7.1.0 Model
 * Author: yuru.he
 * Creation Date: Mar 27, 2019 at 5:45:24 PM
 *********************************************/




 int dimension = ...;
 int nbPoints = ...;
 int nbCluster = ...;
 
 range Dim = 1..dimension;
 range Pts = 1..nbPoints;
 
 /*float points[Pts][Dim] = [
 [1,2,3],
 [2,3,4],
 [6,6,6],
 [6,7,8],
 [6,7,7]
 ];*/
 float points[Pts][Dim] =...;
 
 float dist[p1 in Pts][p2 in Pts] = sqrt( sum(d in Dim) 
 pow(points[p1][d] - points[p2][d], 2) );
 //int dist[p1 in Pts][p2 in Pts] = ftoi(round(sqrt( sum(d in Dim) 
 //pow(points[p1][d] - points[p2][d], 2) ) ) );
 
 
dvar boolean zVar [Pts][Pts];
dvar float z [Pts];



minimize  sum (p in Pts) z[p];



// Les contraintes
subject to {


forall (p1 in Pts,p2 in Pts) {
         dist[p1][p2] * zVar[p1][p2]<= z[p2];        
}
 
forall (p in Pts) {
        unicite_rep2: sum(p1 in Pts) zVar[p][p1] == 1;        
}

forall (p1 in Pts,p2 in Pts) {
        c_rep:  zVar[p1][p2] <= zVar[p2][p2];        
} 
 
        p_rep: sum(p2 in Pts) zVar[p2][p2] == nbCluster;        
    
} 

execute AFFICHAGE_SOLUTION {
writeln("AFFICHAGE DES REPRESENTANTS\n")
var n1,n2,p;
var compt =0;

for( p in Pts){
		if (zVar[p][p]>0.5) {
		compt ++;		
		writeln("CLUSTER ",compt," REPRESENTANT ", points[p]," POINTS:");		
		}

    for(n2 in Pts){
			if (zVar[n2][p]>0.5) write(points[n2],",");	
    }
    writeln();
}
    
}