	#include <stdio.h>

	#include <iostream>

	#include "MyHeaderFile.h" 

	#include "Gnuplot.h"

	void pendulum::test(void)

	{

	int n1,n2,nsam;

	double yy[nm], dy[nm];

	t  = 0.0;
	
	delta_t=.00001;

	nsam=1;

	tf=delta_t*nsam;

	n1=nn+nn*nn+1;

        n2=2*nn+nn*nn;

	//////////////////////Initialization of the variables//////////////////////////
	
	double 	y_h[nm] = {pi,0.1,1.0,0.0,0.0,1.0,0.0,0.0};
		 	

	ofstream first("Variables.dat");//Files to write the data for variables 
	
	if(!first) {

	cerr << "Could not open output file " << endl;

	exit(1);

			}

	first.setf(ios::scientific);//Files to write the lyapunov exponents

	first.precision(4);

	ofstream second("Lyapunov.dat");

	if(!second) {
    
	cerr << "Could not open output file " << endl;
    	
	exit(1);

			}

	second.setf(ios::scientific);

	second.precision(4);

	
	for(int iter=1; iter<=ITERATION;iter++){

	rk4_step(t,y_h,yy,delta_t);//calling rk4
	
	if(isnan(yy[6]) || isnan(yy[7])){ 

	cout<<"Program is terminated at theiteration"<<"\t\t"<<iter<<"\n";

       exit(1);	
					}				

	first<<iter*delta_t<<"\t\t"<<yy[0]<<"\t\t"<<yy[1]<<"\n";////Write to file variables

	double parameter=1.0/(delta_t*iter);

	cout<<parameter<<"\n";

	second<<yy[6]*parameter<<"\t\t"<<yy[7]*parameter<<"\n";//Write to file the lyapunov exponents

	/////Updating the variables//////

	t+=delta_t;
	
		for( int jj=0;jj<nm;jj++){

	//		y_h[0]=yy[0];y_h[1]=yy[1];y_h[2]=yy[2];y_h[3]=yy[3];y_h[4]=yy[4];y_h[5]=yy[5];y_h[6]=yy[6];y_h[7]=yy[7];
	
				y_h[jj]=yy[jj];	  

           			}


						}

	first.close();///Close first file

	second.close();///Close second file

	}

//////////////////////////////////////main Function////////////////////////////////////////

		 int main()
	
		{

		pendulum Kapitza ;

		Kapitza.test();

		Kapitza.gnuplot();

		return 0;
        	}



      
	
	


	
