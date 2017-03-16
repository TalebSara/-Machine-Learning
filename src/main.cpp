
#include "jpg.h"
#include "mnist.h"

float dist_sq (float* v1 ,float *v2){
	//sum_i (v1[i]-v2[i])^2
	float d=0;
	for(int i=0; i<784 ; i++){
		d+=(v1[i]-v2[i])*(v1[i]-v2[i]);
	}
	return d;
}


int main(int argc, char** argv) {
			//les 60000 images d'apprentissage
	float** images=read_mnist("train-images.idx3-ubyte");
		//les 60000 labels qui vont avec 
	float* labels = read_labels("train-labels.idx1-ubyte");
      //les 10000 images dont il faut deviner le label
 	float** test_images=read_mnist("t10k-images.idx3-ubyte");
	for(int i=0;i<10000;i++) {
		printf("%u\n ",i);
		float mind = -1;
		int NN; // le pus proche voisin(nearst neighbor)
		for(int j=0;j<60000;j++){
			float d = dist_sq(test_images[i],images[j]);
			if(d<mind|| mind==-1){
				mind =d;
				NN=j;
			}
		}
	//a ce stade :NN contient le numero de plus proche voisin.
	// mais attention, nous n'avons pas encore son label
	int inference = labels[NN];
	//interference contient maintenat le label associe a l'image 	connuue
	save_jpg(test_images[i],28 ,28, "%u/%u.jpg",inference,i);
}
return 0;
}


   
