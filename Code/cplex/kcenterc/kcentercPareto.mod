/*********************************************
 * OPL 12.7.1.0 Model
 * Author: yuru.he
 * Creation Date: Apr 1, 2019 at 9:34:31 AM
 *********************************************/


 int dimension = ...;
 int nbPoints = ...;
 int nbCluster = ...;
 
 range Dim = 1..dimension;
 range Pts = 1..nbPoints;
 
 /*float points[Pts][Dim] = [
 [1,2],
 [2,3],
 [6,6],
 [6,7],
 [6,9]
 ];*/
 float points[Pts][Dim] =...;
 //float points[Pts][Dim] =...;
 
 float dist[p1 in Pts][p2 in Pts] = sqrt( sum(d in Dim) 
 pow(points[p1][d] - points[p2][d], 2) );
 
 
dvar boolean xVar [Pts][Pts];


minimize sum (p2 in Pts,p3 in Pts) (1.0/2.0)*dist[p2][p3] * xVar[p2][p3];

// Les contraintes
subject to {

/*
forall (p1 in Pts,p2 in Pts,p3 in Pts) {
         dist[p2][p3] * (xVar[p1][p2]+xVar[p1][p3]-1)<= z[p1];        
}*/
 
forall (p in Pts) {
         sum(p2 in Pts,p3 in Pts: p2 <= p && p <= p3) xVar[p2][p3] == 1;        
}
       
sum (p2 in Pts,p3 in Pts)  xVar[p2][p3] == nbCluster; 
/*
forall (p1 in Pts,p2 in Pts : p1<=p2) {
                 xVar[p1][p2] <=xVar[p1][p1]  ;
}
/*
forall (p1 in Pts,p2 in Pts : p1>p2) {
                 xVar[p1][p2] <=0  ;
}
 */              
    
} 

execute AFFICHAGE_SOLUTION {
writeln("AFFICHAGE DES REPRESENTANTS\n")
var n1,n2,p,p2,p3;
var compt =0;

for( p2 in Pts){
	for( p3 in Pts){
		if (xVar[p2][p3]>0.5) {
			compt ++;		
			writeln("CLUSTER ",compt," POINTS:");
			for(n2 in Pts){
				if (n2>=p2 && n2<=p3) write(points[n2],",");
    		}	
    		writeln();
		}		
	}
		
}	
}		
