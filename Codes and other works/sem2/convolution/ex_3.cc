#include <iostream>
#include<stdlib.h>
#include<math.h>
#include <iomanip> 
#include <string>
#include <fstream>  //to read from files
#include <string>
 
using namespace std;
double pi = M_PI;	
double a = -pi , b = pi , w = 2;

// list of functions
double v(double x);
double f2(double x);


int main()
{	
	//---------------------------------
	//to read and create log correction 
	ifstream MyReadFile("log_cor_val/k23.txt");  //read constants from file
	int	n_of_coff = 23;
	double C[n_of_coff] , log_corr=0; //to store constants
	int i=0;
	string myText;

	while (getline (MyReadFile, myText) ) 
	{
  	// Output the text from the file
		C[i++] = stod(myText);
	}

	//for (i =0 ; i<n_of_coff;i++)
	//cout<<setprecision(15)<<C[i]<<endl; //to verify constants

	MyReadFile.close();
	// Close the file--------------------
	//-----------------------------------



	int N[] = {200,280};  //number of quadrature points
	double M[] = { -pi ,  0 ,  pi}; //points at which to check 
	double ex_val[] = {-2.735276379598384,-2.735276379614597,-2.735276379598384};
	// double M[] = { -pi , -pi/2 , 0 , pi/2 , pi}; //points at which to check 
	// double ex_val[] = {-2.735276379598384,9.616562370705873,-2.735276379614597,-20.25592915009226,-2.735276379598384};

	//for(int f = 0 ; f<( sizeof(M)/sizeof(M[0]) );f++)
	//	cout<<M[f]<<" ";


	int n , q;
	double h; 
	double val =0 , t_p;
	for (i =0 ; i < sizeof(N)/sizeof(N[0]) ; i++)
	{
		n = N[i];
		h = (b-a)/n;
		cout<<"\n -----------------------------------"<<endl;
		cout<<"for n:"<<n<<endl;

		//-----------------------------------
		//-----------------------------------
		//constructing log correction--------
		log_corr = (log(w*h*h) + C[0])*v(0);
		for(int r=1 ; r<n_of_coff ; r++)
			log_corr = log_corr + C[r]*( v(-r*h) + v(r*h) );
		log_corr = h*log_corr;
		//------------------------------------
		//------------------------------------

		for (int j = 0 ; j < sizeof(M)/sizeof(M[0]) ; j++)
		{
			val =0;
			for(int p =1 ; p <n ; p++)
			{
				t_p = a + p*h;
				val = val + f2(M[j] - t_p)*v(t_p);
			}
			val = val + 0.5*(    f2(M[j] - a)*v(a) + f2(M[j] - b)*v(b)    );
			val = val*h + log_corr;

			cout<<" t :";
			cout<<setfill(' ')<<setw(20)<<setprecision(10)<< M[j];
			cout<<setprecision(20)<<" || value :"<<val<< " || error :"<<abs(val - ex_val[j])<<endl;
		} 
	}


	return 0;
}

//--------------------------------------------------------------
//--------------------------------------------------------------


double f2(double x)
{
	double k = log(w*(1 - cos(x) ));
	if (isinf(k))
	{
		k =0;
	}
	return k ;
}


double v(double x)
{
	return exp(2*cos(8*x) +sin(9*x));
}