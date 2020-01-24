
#include <iostream>
#include <fstream>

#include "generators.hpp"

int main()
{
	/* ------------------------------------------------------------------------------- */
	/* parametres */
	
	const unsigned int numNs = 6; //numero de tests sobre n diferents
	const unsigned int ns[numNs] = {5, 10, 50, 100, 500, 1000}; //definim les n dels diferents tests
	
	// Model RBG, p = a/n
	const float aini = 0; //c inicial
	const float afin = 20; //c final
	const float aaug = 0.2; //augment de la c en cada pas
	
	// Model RGG, r = b/n
	const float bini = 0; //c inicial
	const float bfin = 80; //c final
	const float baug = 0.8; //augment de la c en cada pas
	
	// Models RBG i RGG
	const unsigned int iter = 500; //iteracions sobre cada valor del paràmetre

	//Enable
	const bool rbg = true;
	const bool rgg = true;


	std::string str = "params.R";
	std::fstream fileParams(str, std::ios_base::out | std::ios_base::trunc);

	fileParams << "numNs <- " << numNs << std::endl;
	fileParams << "ns <- c(";
	for(unsigned int i = 0; i < numNs; i++)
	{
		if(i == 0) fileParams << ns[i];
		else fileParams << "," << ns[i];
	}
	fileParams << ')' << std::endl;

	fileParams << "aini <- " << aini << std::endl;
	fileParams << "afin <- " << afin << std::endl;

	fileParams << "bini <- " << bini << std::endl;
	fileParams << "bfin <- " << bfin << std::endl;

	fileParams << "iter <- " <<iter << std::endl;

	fileParams.close();

	/* ------------------------------------------------------------------------------- */
	/* loop per model RGB */
	
	if(rbg)
	{
		for(unsigned int n = 0; n < numNs; n++) //per cada n diferent
		{
			std::cout << "Per a n = " << ns[n] << std::endl;
			std::string str = "outputRBG" + std::to_string(ns[n]) + ".txt";
			std::fstream fileRBG(str, std::ios_base::out | std::ios_base::trunc);
			
			int dlim = 0;
			
			for(double a = aini; a <= afin; a += aaug) //per cada paràmetre
			{
				std::cout << " - a = " << a << std::endl;

				double nc = 0.0, slcc = 0.0, d = 0.0;
				for(unsigned int i = 0; i < iter; i++) //per cada iteració
				{
					Graph graph;
					generate_RBG(graph, ns[n], a/ns[n]);
					unsigned int cc, tslcc;
					property_connectedComponents(graph, cc, tslcc);
					if(cc == 1) nc += 1.0;
					slcc += tslcc;
					unsigned int td;
					if((dlim < 3) and i < (iter / 10))
					{
						property_diameter(graph, td);
						d += td;
					}
				}
				nc /= iter;
				slcc /= iter;
				
				if(dlim < 3) 
				{
					d /= (iter / 10);
					if(d == 2) dlim++;
				}
				else d = 2;
				
				fileRBG << a << '\t' << nc << '\t' << slcc << '\t' << d << std::endl;
			}
			
			fileRBG.close();
		}
	}
	
	/* ------------------------------------------------------------------------------- */
	/* loop per model RGG */
	
	if(rgg)
	{
		for(unsigned int n = 0; n < numNs; n++)
		{
			std::cout << "Per a n = " << ns[n] << std::endl;
			std::string str = "outputRGG" + std::to_string(ns[n]) + ".txt";
			std::fstream fileRBG(str, std::ios_base::out | std::ios_base::trunc);
			
			int dlim = 0;
			
			for(double b = bini; b <= bfin; b += baug) //per cada paràmetre
			{
				std::cout << " - b = " << b<< std::endl;

				double nc = 0.0, slcc = 0.0, d = 0.0;
				for(unsigned int i = 0; i < iter; i++) //per cada iteració
				{
					Graph graph;
					generate_RGG(graph, ns[n], b/ns[n]);
					unsigned int cc, tslcc;
					property_connectedComponents(graph, cc, tslcc);
					if(cc == 1) nc += 1.0;
					slcc += tslcc;
					unsigned int td;
					if((dlim < 3) and i < (iter / 10))
					{
						property_diameter(graph, td);
						d += td;
					}
				}
				nc /= iter;
				slcc /= iter;
				
				if(dlim < 3) 
				{
					d /= (iter / 10);
					if(d == 2) dlim++;
				}
				else d = 2;
				
				fileRBG << b << '\t' << nc << '\t' << slcc << '\t' << d << std::endl;
			}
			
			fileRBG.close();
		}
	}
	
}