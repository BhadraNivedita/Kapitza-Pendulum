						void pendulum::gnuplot(void)

						{

						FILE *gp; 
		
						gp = popen("gnuplot -persist","w"); /* ’gp’ is the pipe descriptor */

						if (gp==NULL)

						{cout<<"Error opening pipe to GNU plot. Check if you have it!"<<"\n";exit(1);}
						
						fprintf(gp, "unset key\n");
	
						fprintf(gp, "set terminal png\n");
						
						fprintf(gp, "set output 'pq.png'\n");
						
						fprintf(gp, "set xlabel ' q'\n");

						fprintf(gp, "set ylabel ' p'\n");

						fprintf(gp, "plot 'Variables.dat' u 2:3 w d \n");
	
					       // fprintf(gp, "plot  'Boukobza.dat'  u 2:3 w d \n");


						fprintf(gp, "set output 'thetatime.png'\n");

						fprintf(gp, "set xlabel ' t'\n");

						fprintf(gp, "set ylabel ' theta'\n");

						fprintf(gp, "plot 'Variables.dat' u 1:2 w d \n");

						//fprintf(gp, "plot  'Boukobza.dat'   u 1:2 w d \n");


						fprintf(gp, "set output 'Sztime.png'\n");

						fprintf(gp, "set xlabel ' t'\n");

						fprintf(gp, "set ylabel ' Sz'\n");

						fprintf(gp, "plot 'Variables.dat' u 1:3 w d \n");
					
						//fprintf(gp, "plot  'Boukobza.dat'   u 1:3 w d \n");

	
						//fprintf(gp, "plot  'Boukobza.dat'  u 2:3 w d \n");

						 fprintf(gp, "set output 'LiyapunovExponent1.png'\n");
 							 
                                                 fprintf(gp, "set xlabel ' t'\n");
  
                                                 fprintf(gp, "set ylabel ' L1'\n");
 
                                                 fprintf(gp, "plot 'Lyapunov.dat' u 1 w d \n");

						 fprintf(gp, "set output 'LiyapunovExponent2.png'\n");
     
                                                 fprintf(gp, "set xlabel ' t'\n");
     
                                                 fprintf(gp, "set ylabel ' L2'\n");
    
                                                 fprintf(gp, "plot 'Lyapunov.dat' u 2 w d \n");

						fclose(gp);

						}
