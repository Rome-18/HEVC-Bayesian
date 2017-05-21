/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2014, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/

#include <time.h>
#include <iostream>
#include "TAppEncTop.h"
#include "TAppCommon/program_options_lite.h"

//! \ingroup TAppEncoder
//! \{

#include "../Lib/TLibCommon/Debug.h"
#include <fstream>
#include <stdio.h>

#define SPLIT 2
#define QPNUM 20
#define TUDEPTHNUM 3
#define ABOVENUM 5
#define LEFTNUM 5
#define COLNUM 5

double p_f_w[SPLIT][QPNUM][TUDEPTHNUM][ABOVENUM][LEFTNUM][COLNUM];
double C_s_n_p_Wn_[QPNUM][TUDEPTHNUM];//do split
double C_n_s_p_Ws_[QPNUM][TUDEPTHNUM];//do unsplit


void initData(char* argv[]){
	memset(p_f_w,0,sizeof(p_f_w));
	memset(C_s_n_p_Wn_,0,sizeof(C_s_n_p_Wn_));
	memset(C_n_s_p_Ws_,0,sizeof(C_n_s_p_Ws_));	
	string seqName="";
	int l=strlen(argv[4]);
	int pos=l-1;
	while(argv[4][pos]!='/'&&pos>=0)--pos;
	++pos;
	while(argv[4][pos]!='.'){
		seqName+=argv[4][pos++];
	}
	if(seqName=="ParkScene") seqName="Park";
	else if(seqName=="BasketballPass") seqName="BasketPass";
	else if(seqName=="FourPeople") seqName="Four";
	else if(seqName=="PeopleOnStreet") seqName="People";
	else if(seqName=="SteamLocomotiveTrain_10bit") seqName="Steam";
	else if(seqName=="BasketballDrill") seqName="BasketDrill";
	else if(seqName=="PartyScene") seqName="Party";
	else if(seqName=="RaceHorsesC") seqName="Race832";
	else if(seqName=="BlowingBubbles") seqName="Blow";
	else if(seqName=="RaceHorses") seqName="Race416";
	else if(seqName=="KristenAndSara") seqName="Kristen";
	seqName+=".txt";
	const char *filename=seqName.data();
	ifstream in;
	in.open(filename,ios::in);
  	for(int i1=0;i1<QPNUM;i1++)
		for(int i2=0;i2<TUDEPTHNUM;i2++)
			in>>C_s_n_p_Wn_[i1][i2];
  	for(int i1=0;i1<QPNUM;i1++)
		for(int i2=0;i2<TUDEPTHNUM;i2++)
			in>>C_n_s_p_Ws_[i1][i2];			
	for(int i0=0;i0<SPLIT;i0++)	
	  	for(int i1=0;i1<QPNUM;i1++)
	  		for(int i2=0;i2<TUDEPTHNUM;i2++)
				for(int i3=0;i3<ABOVENUM;i3++)
					for(int i4=0;i4<LEFTNUM;i4++)
						for(int i5=0;i5<COLNUM;i5++)
							in>>p_f_w[i0][i1][i2][i3][i4][i5];
	in.close();
}

// ====================================================================================================================
// Main function
// ====================================================================================================================

int main(int argc, char* argv[])
{
  initData(argv);
  TAppEncTop  cTAppEncTop;

  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "HM software: Encoder Version [%s] (including RExt)", NV_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
  fprintf( stdout, "\n\n" );

  // create application encoder class
  cTAppEncTop.create();

  // parse configuration
  try
  {
    if(!cTAppEncTop.parseCfg( argc, argv ))
    {
      cTAppEncTop.destroy();
#if RExt__ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
      EnvVar::printEnvVar();
#endif
      return 1;
    }
  }
  catch (df::program_options_lite::ParseFailure &e)
  {
    std::cerr << "Error parsing option \""<< e.arg <<"\" with argument \""<< e.val <<"\"." << std::endl;
    return 1;
  }

#if RExt__PRINT_MACRO_VALUES
  printRExtMacroSettings();
#endif

#if RExt__ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
  EnvVar::printEnvVarInUse();
#endif

  // starting time
  Double dResult;
  clock_t lBefore = clock();

  // call encoding function
  cTAppEncTop.encode();

  // ending time
  dResult = (Double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);
  // destroy application encoder class
  cTAppEncTop.destroy();
  return 0;
}

//! \}
