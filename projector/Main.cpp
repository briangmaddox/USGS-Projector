/***************************************************************************
                          Main.cpp  -  Command line reprojection utility
                             -------------------
    begin                : Thu Oct 12 2000
    copyright            : (C) 2000 by Chris Bilderback
    email                : cbilderback@usgs.gov
 ***************************************************************************/


#ifdef _WIN32
//#define __GNU_LIBRARY__
//#pragma warning( disable : 4291 ) // Disable VC warning messages for
                                                                  // new(nothrow)
#endif


#include <iostream>
#include <fstream>
#include <time.h>
#include <getopt.h>
#include "MiscUtils/SpinnerThingy.h"
#include "Projector.h"
#include "CLineProgress.h"

using namespace ProjLib;

//function to output the status
void Status(long int linenumber, long int totallines);


//program main entry point
int main(int argc, char **argv)
{
  Projector projector;
  Projection * outproj = NULL; //output projection
  CLineProgress progress; //output progress
  MathLib::Point newscale;
  int pmeshname, pmeshsize;
  int myopt;
  clock_t start = 0, finish = 0;
  std::string logname, filename(std::string(" ")), 
    parameterfile(std::string(" "));
  std::string outfile;
  bool timefile = false;
  bool samescale = false;
  std::ofstream out;

  try
  {
    pmeshname = 0;
    pmeshsize = 4;
    newscale.x = 0;
    newscale.y = 0;
    //parse the arguments
    while (( myopt = getopt(argc, argv, "Ss:l:n:p:?")) != -1)
      switch(myopt)
      {
      case 'S':
        {
          samescale = true;
        }
        break;
      case 's':
        {
          if (optarg)
          {
            newscale.x = atof(optarg);
            newscale.y = newscale.x;
          }
          
        }
        break;
      case 'l':
        {
          if (optarg)
          {
            timefile = true;
            logname = optarg;
          }
        }
		break;
      case 'n':
        {
          if (optarg)
          {
            pmeshsize = atoi(optarg);
                  
          }
		  
        }
        break;
      case 'p':
        {
          if (optarg)
          {
            pmeshname = atoi(optarg);
                  
          }
          break;
        }
      case '?':
      default: // help
        {
          std::cout << "Usage: " << argv[0] << " [options] "
                    << "InputFile InputProjectionFile [outputfile]"
                    << std::endl;
          std::cout << "where options are: " << std::endl;
          std::cout << "   -p pmesh number 6=LeastSqrs 8=Bilinear "
                    << "9=bicubic" << std::endl;
          std::cout << "   -n pmeshsize" << std::endl;
          std::cout << "   -l logfile for timings " << std::endl;
          std::cout << "   -s number where number is the output scale" 
                    << std::endl;
          std::cout << "   -S forces output scale same length as input scale"
                    << std::endl;
          std::cout << "   -? this help screen" << std::endl;
          return 0;
        }
      }
    
    if (optind > argc-2 || argv[optind+1] == NULL)
    {
      std::cout << "You must specify a input file and a input projection file"
                << std::endl
                << "See -h for help" << std::endl;
      return 0;
    }
    else
    {
      filename = std::string(argv[optind++]);
   	  parameterfile = std::string(argv[optind++]);
    }
  
    if (parameterfile == std::string(" ") || filename == std::string(" "))
    {
      std::cout << "You must specify a input file and parameter file " 
                << "use -help for options" << std::endl;
      return 0;
    }
    
    outproj = SetProjection(parameterfile);
    
    if (!outproj)
    {
      std::cout << "Could not create the output projection!"
                << std::endl;
      return 0;
    }
    
    //check for the time file
    if (timefile)
    {
      out.open(logname.c_str()); //open the ouput file
      start = time(NULL);        //get the start
      out << start << std::endl; //output the start
    }
    
    if (optind == argc-1)
    {
      projector.setOutputFileName(std::string(argv[optind]));
    }

    projector.setOutputProjection(outproj);
    projector.setPmeshName(pmeshname);
    projector.setPmeshSize(pmeshsize);
    
    if (!samescale)
      projector.setOutputScale(newscale);
    else
      projector.setSameScale(true);
    
    projector.setInputFile(filename);
 
    projector.project(&progress);
   
    if (timefile)
    {
      finish = time(NULL);
      out << finish << std::endl;
      out << (finish - start);
      out.close();
    }
    return 0;
  }
  catch(ProjectorException & temp)
  {
    std::cout << temp.getExceptionMessage() << std::endl;
    return 0;
  }
  catch(...)
  {
    std::cout << "An unkown exception has been thrown" << std::endl;
    return 0;
  }
}
