
def fon_convex(a,b,c,N):
 fo = open("dataConvex_a_b_α_N_ex1.txt", "w")
 fo.write("Nb_piont= ")
 fo.write(str(N))
 fo.write("\n")
 i = 0
 while (i < N):
     j = random.uniform(a,b)
     y = 1/(j**c)
     fo.write(str(j))
     fo.write("           ")
     fo.write(str(y))
     fo.write("\n")
     i += 1
 
 fo.close()

import random
fon_convex(1,19,2,2);
