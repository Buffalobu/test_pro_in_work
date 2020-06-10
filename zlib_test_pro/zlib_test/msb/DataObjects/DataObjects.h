/**
 * @file DataObjects.h
 * @brief header file to use DataObjects library
 *
 * @author S.Tanaka
 * @date 2006.07.20
 * 
 * Copyright(C) 2006-2014 Eisai Co., Ltd. All rights reserved.
 */


#ifndef __KOME_OBJECTS_DATA_OBJECTS_H__
#define __KOME_OBJECTS_DATA_OBJECTS_H__


//
// macros
//

#ifdef _MSC_VER
	#define DATA_OBJECTS_CLASS __declspec(dllimport)
#else
	#define DATA_OBJECTS_CLASS
#endif	// _MSC_VER


//
// includes
//

#include "DataObjectsCommon.h"
#include "Variant.h"
#include "MsDataVariant.h"
#include "Parameters.h"
#include "SettingParameterValues.h"
#include "SampleSet.h"
#include "Sample.h"
#include "Spectrum.h"
#include "DataSet.h"
#include "DataGroupNode.h"
#include "Peaks.h"
#include "PeakElement.h"
#include "Chromatogram.h"
#include "DataManager.h"
#include "DefaultDataManager.h"
#include "ActiveObjectsManager.h"
#include "PeaksManager.h"
#include "PointsManager.h"
#include "StatusManager.h"
#include "AveragedSpectrum.h"
#include "SpectraChromatogram.h"
#include "OverlappingSpectrum.h"
#include "OverlappingChromatogram.h"
#include "XYDataOperation.h"
#include "DataMapInfo.h"
#include "Peak2DElement.h"
#include "Peaks2DArray.h"
#include "Peaks2D.h"
#include "PeaksCluster2D.h"
#include "DataMapManager.h"
#include "SampleReader.h"	// 2012/07/19 <Add> OKADA
#include "Script.h"			// @Date:2013/07/24	<Add>	A.Ozaki

#endif	//	__KOME_OBJECTS_DATA_OBJECTS_H__
