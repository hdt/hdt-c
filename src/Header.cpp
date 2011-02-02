/* Header.cpp
 * Copyright (C) 2010, Javier D. Fernandez & Miguel A, Martinez-Prieto
 * all rights reserved.
 *
 * Implementation of the Header component
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 * Contacting the authors:
 *   Javier D. Fernandez:       jfergar@infor.uva.es
 *   Miguel A Martinez-Prieto:  migumar2@infor.uva.es
 */

#include "Header.h"
#include <iostream>
#include <fstream>

#define BINARY_HEADER 0

Header::Header()
{
}

Header::Header(int pars, int mapp, int sep, int enc, int nsub, int npred, int nobj, int nsh, int ntrip, int nlit, int nent)
{
	parsing = pars;
	mapping = mapp;
	d_separator = sep;
	t_encoding = enc;
	nsubjects = nsub;
	npredicates = npred;
	nobjects = nobj;
	ssubobj = nsh;
	ntriples = ntrip;
	nliterals = nlit;
	nentries = nent;
}


void 
Header::write(string path)
{
	string output = path;
	
#if BINARY_HEADER
	FILE *header = fopen((output.append(".hdt.header")).c_str(), "w+");
	
	// Graph parsing
	fwrite(&parsing,INT32,1,header);
	// Dictionary mapping
	fwrite(&mapping,INT32,1,header);
	// Dictionary separator
	fwrite(&d_separator,INT32,1,header);
	// Triples encoding
	fwrite(&t_encoding,INT32,1,header);
	
	// Statistics from the Dictionary
	fwrite(&nsubjects,INT32,1,header);
	fwrite(&npredicates,INT32,1,header);
	fwrite(&nobjects,INT32,1,header);
	fwrite(&ssubobj,INT32,1,header);
	
	// Triples in the dataset
	fwrite(&ntriples,INT32,1,header);
	
	fclose(header);
#else
	ofstream headerfile( (output.append(".hdt.header")).c_str());
	
	headerfile
	<< "Parsing: " << parsing << endl
	<< "Mapping: " << mapping << endl
	<< "Separator: " << d_separator << endl
	<< "Encoding: " << t_encoding << endl
	<< "NSubjects: " << nsubjects << endl
	<< "NPredicates: " << npredicates << endl
	<< "NObjects: " << nobjects << endl
	<< "NShared: " << ssubobj << endl
	<< "Triples: " << ntriples << endl
	<< "NLiterals: " << nliterals << endl
	<< "Nentries: " << nentries << endl;
	
	headerfile.close();
#endif
}

void 
Header::read(string path)
{
	string output = path;
	
#if BINARY_HEADER
	FILE *header = fopen((output.append(".hdt.header")).c_str(), "r");
	
	if (header==NULL) {
      cout << "Exception while reading Header in "<<output<<".\n";
      exit(1);
	}
	size_t t = 0;

	// Graph parsing
	t += fread(&parsing,INT32,1,header);
	// Dictionary mapping
	t += fread(&mapping,INT32,1,header);
	// Dictionary separator
	t += fread(&d_separator,INT32,1,header);
	// Triples encoding
	t += fread(&t_encoding,INT32,1,header);
	
	// Dictionary stats
	t += fread(&nsubjects,INT32,1,header);
	// Dictionary mapping
	t += fread(&npredicates,INT32,1,header);
	// Dictionary separator
	t += fread(&nobjects,INT32,1,header);
	// Triples encoding
	t += fread(&ssubobj,INT32,1,header);
	
	 // Triples in the dataset
	t += fread(&ntriples,INT32,1,header);
	
	if (t != 9)
	{
		cout << "   <ERROR> Errors in Header" << endl;
		exit(1);
	}
	
	fclose(header);
#else
	try
	{
		ifstream headerfile( (output.append(".hdt.header")).c_str());
		
		if(headerfile.good()) {
			string line;
			
			getline(headerfile, line, ' ');
			headerfile >> parsing;
			
			getline(headerfile, line, ' ');
			headerfile >> mapping;
			
			getline(headerfile, line, ' ');
			headerfile >> d_separator;
			
			getline(headerfile, line, ' ');
			headerfile >> t_encoding;
			
			getline(headerfile, line, ' ');
			headerfile >> nsubjects;
			
			getline(headerfile, line, ' ');
			headerfile >> npredicates;
			
			getline(headerfile, line, ' ');
			headerfile >> nobjects;
			
			getline(headerfile, line, ' ');
			headerfile >> ssubobj;
			
			getline(headerfile, line, ' ');
			headerfile >> ntriples;
			
			getline(headerfile, line, ' ');
			headerfile >> nliterals;
			
			getline(headerfile, line, ' ');
			headerfile >> nentries;
		}
		
		headerfile.close();
	}
	catch(const ios::failure &problem)
	{
		// Something really went wrong here
		cout << "Error reading header " << problem.what();
	}
#endif
}

int 
Header::getParsing()
{
	return parsing;
}

int
Header::getMapping()
{
	return mapping;
}

int
Header::getD_separator()
{
	return d_separator;
}

int
Header::getT_encoding()
{
	return t_encoding;
}

int
Header::getNsubjects()
{
	return nsubjects;
}

int
Header::getNpredicates()
{
	return npredicates;
}

int
Header::getNobjects()
{
	return nobjects;
}

int 
Header::getSsubobj()
{
	return ssubobj;
}

int
Header::getNtriples()
{
        return ntriples;
}

int
Header::getNliterals() 
{
	return nliterals;
}

int
Header::getNentries()
{
	return nentries;
}

Header::~Header()
{
}
