/* * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * *
 * gausianers.cpp: Gausian Filtering of  ERS (BIL) image                  *
 * Version: 1.0.0 Final                                                   *
 * Last revised: 01/04/2009                                               *
 *                                                                        *
 *									  *
 * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * *
 * Implementation by Angelos Tzotsos (tzotsos@gmail.com)	  	  *
 * Remote Sensing Lab NTUA - GCpp                         April 2009      *
 *									  *
 *   Copyright (C) April 2009 Angelos Tzotsos <tzotsos@gmail.com>	  *
 *									  *
 * This program is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.					  *
 *									  *
 * This program is distributed in the hope that it will be useful,	  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 	  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	  *
 * GNU General Public License for more details.				  *
 *									  *
 * You should have received a copy of the GNU General Public License	  *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *									  *
 * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>
#include <stdlib.h>
#include "cvERS.h"
/*extern "C" {
#include "aml.h"
}*/

using namespace std;

int main(int argc, char *argv[])
{

    if(argc != 4 && argc != 5)   //TODO: Add to Error Handling
    {
        cout << "Error in arguments:" << endl << endl
        << "Usage : ALMcmd <input.ers> <output.ers> <scale> [s]"
        << endl;
        exit(1);
    }

    int i, j;
    int scales = atoi(argv[3]);
    string argv1(argv[1]);
    string argv2(argv[2]);
    double s = 1.0;
    if(argc == 5) s = atof(argv[4]);

    ERSImage ers(argv1);

    cvHyperImage hyper(ers);

    IplImage* dbl1 = cvCreateImage(cvGetSize(hyper.cube[0]), IPL_DEPTH_32F, 1);
    IplImage* dbl2 = cvCreateImage(cvGetSize(hyper.cube[0]), IPL_DEPTH_32F, 1);

    for(i=0;i<hyper.Bands;i++)
    {
        cvConvert(hyper.cube[i], dbl1);
        for(j=0;j<scales;j++)
        {
            cvSmooth(dbl1, dbl2, CV_GAUSSIAN, 5, 5, s, 0.0);
            cvCopy(dbl2, dbl1, NULL);
        }
        cvConvert(dbl2, hyper.cube[i]);
    }

    ERSImage out(hyper);
    out.SaveAs(argv2);

    return 0;
}



