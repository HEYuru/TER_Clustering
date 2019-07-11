def fon_alea(a,b,N):
 fo = open("dataAlea_a_b_α_N_ex1.txt", "w")
 
 fo.write("Nb_piont= ")
 fo.write(str(N))
 fo.write("\n")

#un premier point  
 B = str(b)
 fo.write("0      ") 
 fo.write("1000")
 fo.write("\n")
 
 
# a ∈]0, A], b ∈]0, B]sont tirés aléatoirement
 j = random.uniform(0,a)
 z = random.uniform(0,b)
 print (j,z)


# N point
 ai = 0
 bi = 1000
 i = 1
 while (i < N):  
     ai = ai+j
     fo.write(str(ai))
     fo.write("     ")
     bi = bi-z
     fo.write(str(bi))
     fo.write("\n")
     i += 1
 
 fo.close()

import random
fon_alea(1,100,10);
