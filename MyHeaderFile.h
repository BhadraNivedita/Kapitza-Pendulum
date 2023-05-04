////////////////////////////Simulating Kapitza equation////////////////////////////////////////////////////

	//Compile :g++ <filename>.cpp

	//Run::./a.out


	#include <stdio.h>

	#include <iostream>

	#include <math.h>

	#include <fstream>
	
	#include<stdlib.h>
	
	using namespace std;	

	////////////////////////Defining class for pendulum//////////////////////////////////////////

	class pendulum 

	{

	private:
	
	static const int nm=8;

	static const int nn=2;

	static const unsigned int ITERATION = 1000000;
	
	double pi,tf,delta_t,t;


	public:

	void derivatives(double,double*,double*);//This member function holds the equations to be integrated

        pendulum() { pi= 4.0*atan(1.0);}  //no argument constructor
 
	void rk4_step(double,double*,double*,double); 

	void test(void); 

	void gnuplot(void);
	};
///////	//Function that contains the equation to be integrated///////////////////////////////

	void pendulum::derivatives(double t, double* yy, double* dy)


	{

	double j[nn][nn],e[nn][nn],elm[nn][nn],jem[nn][nn],jlm[nn][nn],llm[nn][nn],tmp;

	double a,g,l,omega,beta; //Parameters for the system
	
	g=9.8;		

	l=1.0;		
	
	pi=4*atan(1);		

	omega=15;		

	a=0.4;
	
	beta=16.0;	
	//cout<<pi<<"\n";
	///////////////////////////Equations to be integrated///////////////////////////

	dy[0]  = yy[1];                                            

	dy[1]  = (-g*sin(yy[0])-((a)*(omega*omega))*sin(yy[0])*cos(omega*t));
 
	j[0][0] = 0.0;

	j[0][1] = 1.0;
	
	j[1][0] = (-g*cos(yy[0])-((a)*(omega*omega))*cos(yy[0])*cos(omega*t));;

	j[1][1] = 0.0;


	int k=nn;

        for(int l=0;l<nn;l++){

           for(int m=0;m<nn;m++){

              e[m][l] = yy[k];    

              k=k+1;

           			}
        			}

	for( int l=0;l<nn;l++){

        	   for(int m=0;m<nn;m++){

		              elm[l][m]=0.0;

		              jem[l][m]=0.0;
              
				for( int k=0;k<nn;k++){

			                 elm[l][m] = elm[l][m] + e[k][l]*e[k][m];

			                 jem[l][m] = jem[l][m] + j[k][l]*e[k][m];
              
							}
           				}

        			}
	
	for( int l=0;l<nn;l++){

   	     for (int m=0;m<nn;m++){

              jlm[l][m]=0.0;

        	      for( int k=0;k<nn;k++){

                	 jlm[l][m] = jlm[l][m] + e[k][l]*jem[k][m]; 

 				}

                 		}
        		   }


        for( int l=0;l<nn;l++){

           for(int  m=0;m<nn;m++){

              llm[l][m] = jlm[l][m] + jlm[m][l] + 2.0*beta*elm[l][m];

           			}

              llm[l][l] = jlm[l][l] + beta*(elm[l][l]-1.0);

        			}

 	int i=nn;

        for( int m=0;m<nn;m++){

           for(int  k=0;k<nn;k++){

              tmp=0.0;

              for( int l=0;l<m;l++){

                 tmp = tmp + e[k][l]*llm[m][l];    

             			    }

           			   dy[i] = jem[k][m] - tmp;
	              i=i+1;
           			}

        		}

////////////////////////////////Lyapunov exponents equations ////////////////////////////////////

	dy[6] = jlm[0][0];

        dy[7] = jlm[1][1];

	//cout<<jlm[2][2]<<"\n";	

	}

/////////////////////////////////////RK4 algorithm///////////////////////////////////////////////



	void pendulum::rk4_step(double t, double *yin,double *yout,double delta_t)

	{	
		

	double k1[nm],k2[nm],k3[nm],k4[nm],y_k[nm];

	derivatives(t,yin,yout);

	for (int s=0;s<nm;s++){

	k1[s]=yout[s]*delta_t;

	//cout<<yout[0]<<"\n"
;
	y_k[s]=yin[s]+k1[s]*0.5;
	
			}

	derivatives(t+delta_t*0.5,y_k,yout);

	for (int s=0;s<nm;s++){

	k2[s]=yout[s]*delta_t;
	
	y_k[s]=yin[s]+k2[s]*0.5;

				}
	
	derivatives(t+delta_t*0.5,y_k,yout);

	for(int s=0;s<nm;s++){

	k3[s]=yout[s]*delta_t;
	
	y_k[s]=yin[s]+k3[0];
			
				}

	derivatives(t+delta_t,y_k,yout);

	for(int s=0;s<nm;s++){

	k4[s]=yout[s]*delta_t;
	
	yout[s]=yin[s]+(1.0/6.0)*(k1[s]+2*k2[s]+2*k3[s]+k4[s]);

				}

	}

