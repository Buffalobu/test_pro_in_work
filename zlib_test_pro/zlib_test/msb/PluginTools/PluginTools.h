/**
 * @file PluginTools.h
 * @brief header file to use PluginTools library
 *
 * @author S.Tanaka
 * @date 2006.07.03
 * 
 * Copyright(C) 2006-2014 Eisai Co., Ltd. All rights reserved.
 */


#ifndef __KOME_PLUGIN_TOOLS_H__
#define __KOME_PLUGIN_TOOLS_H__


//
// macros
// 

#ifdef _MSC_VER
	#define PLUGIN_TOOLS_CLASS __declspec(dllimport)
#else
	#define PLUGIN_TOOLS_CLASS
#endif	// _MSC_VER


//
// includes
//

#include "PluginInfo.h"
#include "PluginManager.h"
#include "PluginMenu.h"
#include "PluginCall.h"
#include "PluginFunctionItem.h"
#include "PluginCallTool.h"
#include "PluginIcon.h"
#include "PluginHelp.h"
#include "ParameterSettings.h"
#include "SettingsValue.h"
#include "SettingsParam.h"
#include "SettingsGroup.h"
#include "SettingsPage.h"
#include "SettingsForm.h"
#include "SettingsChapter.h"
#include "CommandManager.h"
#include "FileFactory.h"
#include "BatchInfo.h"
#include "BatchService.h"
#include "PluginComponent.h"	// @Date:2013/07/29	<Add>	A.Ozaki

#endif	// __KOME_PLUGIN_TOOLS_H__
