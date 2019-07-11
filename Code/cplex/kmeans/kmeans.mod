/*********************************************
 * OPL 12.7.1.0 Model
 * Author: yhe2
 * Creation Date: Apr 10, 2019 at 3:01:25 PM
 *********************************************/
using CP;
 //int dimension = ...;
 //int nbPoints = ...;
 //int nbCluster = ...;
 int dimension = 2;
 int nbPoints = 5;
 int nbCluster = 2;
  
 range Dim = 1..dimension;
 range Pts = 1..nbPoints;
 
 float points[Pts][Dim] = [
 [1,2],
 [2,3],
 [6,6],
 [6,7],
 [6,7]
 ];
 //float points[Pts][Dim] =...;
 
 //float dist[p1 in Pts][p2 in Pts] = ftoi(round(sqrt( sum(d in Dim) 
 //pow(points[p1][d] - points[p2][d], 2) ) ) );
 
 range Clu = 1..nbCluster;
 dvar boolean zVar [Pts][Clu];
 dvar float+ invCard[Clu];

 dexpr float cardCluster[k in Clu] = sum(p in Pts) zVar[p][k];

 dexpr float c[k in Clu ][d in Dim]= //(1 / sum(p in Pts) zVar[p][k] )*
  invCard[k] *(sum(p in Pts) zVar[p][k] * points[p][d]);/// cardCluster[k];
 
 dexpr float dist1[p in Pts][k in Clu] = sqrt( sum(d in Dim)  pow(points[p][d] - c[k][d], 2) );
 
 minimize sum (p in Pts,k in Clu) c[k][1];//zVar[p][k] * dist1[p][k] ;



// Les contraintes
subject to {

forall (k in Clu) {
         invCard[k] * sum(p in Pts) zVar[p][k] == 1;        
}

forall (p in Pts) {
        sum_rep: sum(k in Clu) zVar[p][k] == 1;        
}
 
}

/*execute AFFICHAGE_SOLUTION {
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
    
}*/