/**
 * @file NumericalTools.h
 * @brief header file to use NumericalTools library
 *
 * @author S.Tanaka
 * @date 2006.07.14
 * 
 * Copyright(C) 2006-2013 Eisai Co., Ltd. All rights reserved.
 */


#ifndef __KOME_NUMERICAL_TOOLS_H__
#define __KOME_NUMERICAL_TOOLS_H__


//
// macros
// 

#ifdef _MSC_VER
	#define NUMERICAL_TOOLS_CLASS __declspec(dllimport)
#else
	#define NUMERICAL_TOOLS_CLASS
#endif	// _MSC_VER


//
// includes
//

#include "Math.h"
#include "MatrixTool.h"
#include "MatrixEquationSolution.h"
#include "MovingAverage.h"
#include "Transformation3D.h"
#include "Statistics.h"
#include "Interpolation.h"
#include "Differentiation.h"
#include "Integration.h"
#include "LeastSquares.h"
#include "DynamicPrograming.h"
#include "MinimaxSolution.h"
#include "TDistribution.h"
#include "FDistribution.h"
#include "NormalDistribution.h"
#include "SnCalculator.h"


#endif	// __KOME_NUMERICAL_TOOLS_H__
