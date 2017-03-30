#include "jpg.h"
#include "mnist.h"
#include<limits.h>

	float dist_sq (float* v1 ,float *v2){
	//sum_i (v1[i]-v2[i])^2
	float d=0;
	for(int i=0; i<784 ; i++){
		d+=(v1[i]-v2[i])*(v1[i]-v2[i]);
	}
	return d;
}

	float linear_classifier(float* w , float* x){
	float d=0;
	for(int i=0;i<784;i++) {
	d+=w[i]*x[i];
	} 
	if(d>0) return 1;
	else return 0;
	}



	int main(int argc, char** argv) {

			//les 60000 images d'apprentissage
	float** images=read_mnist("train-images.idx3-ubyte");
		//les 60000 labels qui vont avec 
	float* labels = read_labels("train-labels.idx1-ubyte");
      //les 10000 images dont il faut deviner le label
 	float** test_images=read_mnist("t10k-images.idx3-ubyte");
	float* test_labels=read_labels("t10k-labels.idx1-ubyte");
	float*w=new float[784];
	for(int i=0;i<784;i++){
		w[i]=(float)rand()*2/INT_MAX-1;
	}

	float E=0;

	for(int i=0;i<10000;i++) {
		printf("%u\n ",i);

	float mind = -1;
	int  inference=linear_classifier(w, test_images[i]);
		
	//interference contient maintenant le label associe a l'image 	connuue
	save_jpg(test_images[i],28 ,28, "%u/%u.jpg",inference,i);
	//if(inference!= test_labels[i]) E++;
	//printf(" erreur = %0.2f \n ", (E*100)/i);
	//}
}
return 0;
}


   
