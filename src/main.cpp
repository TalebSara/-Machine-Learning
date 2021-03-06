#include "jpg.h"
#include "mnist.h"
#include<limits.h>

 /** perceptron */
	float linear_classifier(float* w , float* x){
	float d=0;
	for(int i=0;i<784;i++) {
		d+=w[i]*x[i];
		} 
		if(d>=0) return 1;
		else return -1;
	}

	float dist_sq(float* a , float* b){
	float d=0;
	for(int i=0;i<784;i++) {
		d+=(a[i]-b[i])*(a[i]-b[i]);
		}
	return d;
	}

float A[100][784];
float B[100][784];
const int K=10;



	int main()
 {
	//les 60000 images d'apprentissage
	float** images=read_mnist("train-images.idx3-ubyte");
	//les 60000 labels qui vont avec 
	float* labels = read_labels("train-labels.idx1-ubyte");
    //les 10000 images dont il faut deviner le label
 	float** test_images=read_mnist("t10k-images.idx3-ubyte");
	float* test_labels=read_labels("t10k-labels.idx1-ubyte");



//partie k-means

int n[K];


for(int i=0;i<K;i++) {
	n[i]=0;
	for(int j=0;j<784;j++) {
		A[i][j]=images[i][j];
		B[i][j]=0;
	 }
}


for(int t=0;t<10;t++) {
	printf("%u\n",t);
	for(int i=0;i<K;i++) {
		n[i]=0;
		for(int j=0;j<784;j++) { 
			B[i][j]=0; 
		}
	}

	for(int i=0; i<60000; i++) {
		printf("t= %u , i=%u\n",t,i);
		float mind=-1; int gagnant=0;	
		for(int k=0; k<K; k++) {
			float d=dist_sq(A[k], images[i]);
			if(d<=mind || mind==-1){
				mind = d ;
				gagnant = k;
			}
		}

		for(int j=0; j<784; j++) B[gagnant][j]+= images[i][j];
		n[gagnant]++;
	}

	for(int k=0;k <K; k++){
		for(int j=0; j<784; j++) {
			A[k][j] = B[k][j]/n[k];
		}
			save_jpg(A[k],28 ,28, "%u/%u.jpg",k,t);
	}
}


//partie perceptron
float*w=new float[784];

//STEP 1: INITIALISATION 

	for(int i=0;i<784;i++){
		w[i]=(float)rand()*2/INT_MAX-1;
	}
	float gamma = 0.01;


//STEP 2 : LEARNING(que les donnes de train)

	for(int i=0;i<60000;i++){
		printf("%u\n",i);

		//calcul de gradient (g=y*x si erreur , 0 sinon )
		int prediction = linear_classifier(w,images[i]);
		int verite = (labels[i] == 1) ? 1 : -1 ;
		if(verite!=prediction){
			printf("erreur\n");
			// (w(t+1)=w(t)-gamma*y*x )
				for(int j=0; j<784 ; j++) {
					w[j] = w[j] + gamma*verite*images[i][j];
				}
		}
	}
	

//STEP 3 : TEST(que les donnes de test)

	float E=0;

	for(int i=0;i<10000;i++) {
		printf("%u\n ",i);
		float mind = -1;
		int  inference=linear_classifier(w, test_images[i]);
		//interference contient maintenant le label associe a l'image 	connuue
		save_jpg(test_images[i],28 ,28, "%u/%u.jpg",inference,i);
		if((inference==1 && test_labels[i]!=1)||(inference==-1 && test_labels[i]==1)){ E++;}
		printf(" erreur = %0.2f \n ", (E*100)/i);

	}
	return 0;
}


   
