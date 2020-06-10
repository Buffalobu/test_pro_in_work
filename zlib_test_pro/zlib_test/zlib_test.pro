QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cFileData.cpp \
    cPublicCCS.cpp \
    main.cpp \
    mainwindow.cpp \
    msb/CoreFunctions/ErrorCode.cpp \
    msb/CoreFunctions/FileFunctions.cpp \
    msb/CoreFunctions/LogFunctions.cpp \
    msb/CoreFunctions/MemoryFunctions.cpp \
    msb/CoreFunctions/ProcessFunctions.cpp \
    msb/CoreFunctions/StringFunctions.cpp \
    msb/CoreFunctions/TimeFunctions.cpp \
    msb/CoreFunctions/TypeFunctions.cpp \
    msb/CoreToolkits/Base64.cpp \
    msb/CoreToolkits/Buffer.cpp \
    msb/CoreToolkits/CommonParameterManager.cpp \
    msb/CoreToolkits/ConversionTool.cpp \
    msb/CoreToolkits/DataAccessor.cpp \
    msb/CoreToolkits/DataPoints.cpp \
    msb/CoreToolkits/DisplayProgress.cpp \
    msb/CoreToolkits/FileAccessor.cpp \
    msb/CoreToolkits/Heap.cpp \
    msb/CoreToolkits/IniFile.cpp \
    msb/CoreToolkits/ManualSelector.cpp \
    msb/CoreToolkits/Matrix.cpp \
    msb/CoreToolkits/MemoryAccessor.cpp \
    msb/CoreToolkits/MsppManager.cpp \
    msb/CoreToolkits/NumberRestriction.cpp \
    msb/CoreToolkits/Point.cpp \
    msb/CoreToolkits/PointArray.cpp \
    msb/CoreToolkits/Progress.cpp \
    msb/CoreToolkits/Properties.cpp \
    msb/CoreToolkits/RangeList.cpp \
    msb/CoreToolkits/RangeListSelector.cpp \
    msb/CoreToolkits/Rect.cpp \
#    msb/CoreToolkits/ResourceBundle.cpp \
    msb/CoreToolkits/SearchTool.cpp \
    msb/CoreToolkits/Selector.cpp \
    msb/CoreToolkits/Sha1.cpp \
    msb/CoreToolkits/Timer.cpp \
    msb/CoreToolkits/TreeNode.cpp \
    msb/CoreToolkits/Vector.cpp \
    msb/CoreToolkits/XYData.cpp \
    msb/DataObjects/ActiveObjectsManager.cpp \
    msb/DataObjects/AveragedSpectrum.cpp \
    msb/DataObjects/Chromatogram.cpp \
    msb/DataObjects/DataGroupNode.cpp \
    msb/DataObjects/DataManager.cpp \
    msb/DataObjects/DataMapInfo.cpp \
    msb/DataObjects/DataMapManager.cpp \
    msb/DataObjects/DataSet.cpp \
    msb/DataObjects/DefaultDataManager.cpp \
    msb/DataObjects/MsDataVariant.cpp \
    msb/DataObjects/OverlappingChromatogram.cpp \
    msb/DataObjects/OverlappingSpectrum.cpp \
    msb/DataObjects/Parameters.cpp \
    msb/DataObjects/Peak2DElement.cpp \
    msb/DataObjects/PeakElement.cpp \
    msb/DataObjects/Peaks.cpp \
    msb/DataObjects/Peaks2D.cpp \
    msb/DataObjects/Peaks2DArray.cpp \
    msb/DataObjects/PeaksCluster2D.cpp \
    msb/DataObjects/PeaksManager.cpp \
    msb/DataObjects/PointsManager.cpp \
    msb/DataObjects/Sample.cpp \
    msb/DataObjects/SampleReader.cpp \
    msb/DataObjects/SampleSet.cpp \
    msb/DataObjects/Script.cpp \
    msb/DataObjects/SettingParameterValues.cpp \
    msb/DataObjects/SpectraChromatogram.cpp \
    msb/DataObjects/Spectrum.cpp \
    msb/DataObjects/StatusManager.cpp \
    msb/DataObjects/Variant.cpp \
    msb/DataObjects/XYDataOperation.cpp \
    msb/DbTools/Database.cpp \
    msb/DbTools/DbManager.cpp \
    msb/DbTools/ResultSet.cpp \
    msb/DbTools/Statement.cpp \
    msb/DbTools/Table.cpp \
    msb/DbTools/TableColumn.cpp \
    msb/DbTools/TableIndex.cpp \
    msb/EventManager/KeyEvent.cpp \
    msb/EventManager/MouseEvent.cpp \
    msb/EventManager/MoveEvent.cpp \
    msb/EventManager/SizeEvent.cpp \
    msb/MsbChromatogram.cpp \
    msb/MsbIO0202.cpp \
    msb/MsbIOPluginFunctions.cpp \
    msb/MsbManager.cpp \
    msb/MsbSample.cpp \
    msb/MsbSampleSet.cpp \
    msb/MsbSpectrum.cpp \
    msb/NumericalTools/Differentiation.cpp \
    msb/NumericalTools/DynamicPrograming.cpp \
    msb/NumericalTools/FDistribution.cpp \
    msb/NumericalTools/Integration.cpp \
    msb/NumericalTools/Interpolation.cpp \
    msb/NumericalTools/LeastSquares.cpp \
    msb/NumericalTools/Math.cpp \
    msb/NumericalTools/MatrixEquationSolution.cpp \
    msb/NumericalTools/MatrixTool.cpp \
    msb/NumericalTools/MinimaxSolution.cpp \
    msb/NumericalTools/MovingAverage.cpp \
    msb/NumericalTools/NormalDistribution.cpp \
    msb/NumericalTools/SnCalculator.cpp \
    msb/NumericalTools/Statistics.cpp \
    msb/NumericalTools/TDistribution.cpp \
    msb/NumericalTools/Transformation3D.cpp \
    msb/PluginTools/BatchInfo.cpp \
    msb/PluginTools/BatchService.cpp \
    msb/PluginTools/CommandManager.cpp \
    msb/PluginTools/FileFactory.cpp \
    msb/PluginTools/ParameterSettings.cpp \
    msb/PluginTools/PluginCall.cpp \
    msb/PluginTools/PluginCallTool.cpp \
    msb/PluginTools/PluginComponent.cpp \
    msb/PluginTools/PluginFunctionItem.cpp \
    msb/PluginTools/PluginHandler.cpp \
    msb/PluginTools/PluginHelp.cpp \
    msb/PluginTools/PluginIcon.cpp \
    msb/PluginTools/PluginInfo.cpp \
    msb/PluginTools/PluginManager.cpp \
    msb/PluginTools/PluginMenu.cpp \
    msb/PluginTools/SettingsChapter.cpp \
    msb/PluginTools/SettingsForm.cpp \
    msb/PluginTools/SettingsGroup.cpp \
    msb/PluginTools/SettingsHandler.cpp \
    msb/PluginTools/SettingsPage.cpp \
    msb/PluginTools/SettingsParam.cpp \
    msb/PluginTools/SettingsValue.cpp \
    msb/PluginTools/StatusBarInfo.cpp \
    msb/SpectrumPart.cpp \
    msb/SpectrumPartArray.cpp \

HEADERS += \
    cFileData.h \
    cPublicCCS.h \
    cconfigoms.h \
    mainwindow.h \
    msb/CoreFunctions/CoreFunctions.h \
    msb/CoreFunctions/CoreMacros.h \
    msb/CoreFunctions/ErrorCode.h \
    msb/CoreFunctions/FileFunctions.h \
    msb/CoreFunctions/LogFunctions.h \
    msb/CoreFunctions/MemoryFunctions.h \
    msb/CoreFunctions/ProcessFunctions.h \
    msb/CoreFunctions/StringFunctions.h \
    msb/CoreFunctions/TimeFunctions.h \
    msb/CoreFunctions/TypeFunctions.h \
    msb/CoreFunctions/stdafx.h \
    msb/CoreToolkits/Base64.h \
    msb/CoreToolkits/Buffer.h \
    msb/CoreToolkits/CommonParameterManager.h \
    msb/CoreToolkits/CommonTypes.h \
    msb/CoreToolkits/ConversionTool.h \
    msb/CoreToolkits/CoreToolkits.h \
    msb/CoreToolkits/DataAccessor.h \
    msb/CoreToolkits/DataPoints.h \
    msb/CoreToolkits/DisplayProgress.h \
    msb/CoreToolkits/FileAccessor.h \
    msb/CoreToolkits/Heap.h \
    msb/CoreToolkits/IniFile.h \
    msb/CoreToolkits/ManualSelector.h \
    msb/CoreToolkits/Matrix.h \
    msb/CoreToolkits/MemoryAccessor.h \
    msb/CoreToolkits/MsppManager.h \
    msb/CoreToolkits/NumberRestriction.h \
    msb/CoreToolkits/Point.h \
    msb/CoreToolkits/PointArray.h \
    msb/CoreToolkits/Progress.h \
    msb/CoreToolkits/Properties.h \
    msb/CoreToolkits/RangeList.h \
    msb/CoreToolkits/RangeListSelector.h \
    msb/CoreToolkits/Rect.h \
#    msb/CoreToolkits/ResourceBundle.h \
    msb/CoreToolkits/SearchTool.h \
    msb/CoreToolkits/Selector.h \
    msb/CoreToolkits/Sha1.h \
    msb/CoreToolkits/Timer.h \
    msb/CoreToolkits/TreeNode.h \
    msb/CoreToolkits/Vector.h \
    msb/CoreToolkits/XYData.h \
    msb/CoreToolkits/stdafx.h \
    msb/DataObjects/ActiveObjectsManager.h \
    msb/DataObjects/AveragedSpectrum.h \
    msb/DataObjects/Chromatogram.h \
    msb/DataObjects/DataGroupNode.h \
    msb/DataObjects/DataManager.h \
    msb/DataObjects/DataMapInfo.h \
    msb/DataObjects/DataMapManager.h \
    msb/DataObjects/DataObjects.h \
    msb/DataObjects/DataObjectsCommon.h \
    msb/DataObjects/DataSet.h \
    msb/DataObjects/DefaultDataManager.h \
    msb/DataObjects/MsDataVariant.h \
    msb/DataObjects/OverlappingChromatogram.h \
    msb/DataObjects/OverlappingSpectrum.h \
    msb/DataObjects/Parameters.h \
    msb/DataObjects/Peak2DElement.h \
    msb/DataObjects/PeakElement.h \
    msb/DataObjects/Peaks.h \
    msb/DataObjects/Peaks2D.h \
    msb/DataObjects/Peaks2DArray.h \
    msb/DataObjects/PeaksCluster2D.h \
    msb/DataObjects/PeaksManager.h \
    msb/DataObjects/PointsManager.h \
    msb/DataObjects/Sample.h \
    msb/DataObjects/SampleReader.h \
    msb/DataObjects/SampleSet.h \
    msb/DataObjects/Script.h \
    msb/DataObjects/SettingParameterValues.h \
    msb/DataObjects/SpectraChromatogram.h \
    msb/DataObjects/Spectrum.h \
    msb/DataObjects/StatusManager.h \
    msb/DataObjects/Variant.h \
    msb/DataObjects/XYDataOperation.h \
    msb/DataObjects/stdafx.h \
    msb/DbTools/Database.h \
    msb/DbTools/DbManager.h \
    msb/DbTools/DbTools.h \
    msb/DbTools/ResultSet.h \
    msb/DbTools/Statement.h \
    msb/DbTools/Table.h \
    msb/DbTools/TableColumn.h \
    msb/DbTools/TableIndex.h \
    msb/DbTools/stdafx.h \
    msb/EventManager/EventManager.h \
    msb/EventManager/KeyEvent.h \
    msb/EventManager/MouseEvent.h \
    msb/EventManager/MoveEvent.h \
    msb/EventManager/SizeEvent.h \
    msb/EventManager/stdafx.h \
    msb/MsbChromatogram.h \
    msb/MsbIO0202.h \
    msb/MsbIOPluginFunctions.h \
    msb/MsbManager.h \
    msb/MsbSample.h \
    msb/MsbSampleSet.h \
    msb/MsbSpectrum.h \
    msb/NumericalTools/Differentiation.h \
    msb/NumericalTools/DynamicPrograming.h \
    msb/NumericalTools/FDistribution.h \
    msb/NumericalTools/Integration.h \
    msb/NumericalTools/Interpolation.h \
    msb/NumericalTools/LeastSquares.h \
    msb/NumericalTools/Math.h \
    msb/NumericalTools/MatrixEquationSolution.h \
    msb/NumericalTools/MatrixTool.h \
    msb/NumericalTools/MinimaxSolution.h \
    msb/NumericalTools/MovingAverage.h \
    msb/NumericalTools/NormalDistribution.h \
    msb/NumericalTools/NumericalTools.h \
    msb/NumericalTools/SnCalculator.h \
    msb/NumericalTools/Statistics.h \
    msb/NumericalTools/TDistribution.h \
    msb/NumericalTools/Transformation3D.h \
    msb/NumericalTools/stdafx.h \
    msb/PluginTools/BatchInfo.h \
    msb/PluginTools/BatchService.h \
    msb/PluginTools/CommandManager.h \
    msb/PluginTools/FileFactory.h \
    msb/PluginTools/ParameterSettings.h \
    msb/PluginTools/PluginCall.h \
    msb/PluginTools/PluginCallTool.h \
    msb/PluginTools/PluginComponent.h \
    msb/PluginTools/PluginFunctionItem.h \
    msb/PluginTools/PluginHandler.h \
    msb/PluginTools/PluginHelp.h \
    msb/PluginTools/PluginIcon.h \
    msb/PluginTools/PluginInfo.h \
    msb/PluginTools/PluginManager.h \
    msb/PluginTools/PluginMenu.h \
    msb/PluginTools/PluginTools.h \
    msb/PluginTools/SettingsChapter.h \
    msb/PluginTools/SettingsForm.h \
    msb/PluginTools/SettingsGroup.h \
    msb/PluginTools/SettingsHandler.h \
    msb/PluginTools/SettingsPage.h \
    msb/PluginTools/SettingsParam.h \
    msb/PluginTools/SettingsValue.h \
    msb/PluginTools/StatusBarInfo.h \
    msb/PluginTools/stdafx.h \
    msb/SpectrumPart.h \
    msb/SpectrumPartArray.h \
    msb/stdafx.h \


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    msb/CoreFunctions/CoreFunctions.def \
    msb/CoreFunctions/Makefile.in \
    msb/CoreToolkits/Makefile.in \
    msb/DataObjects/Makefile.in \
    msb/DbTools/Makefile.in \
    msb/EventManager/Makefile.in \
    msb/ImageManager/Makefile.in \
    msb/NumericalTools/Makefile.in \ \
    msb/PluginTools/Makefile.in \
    msb/PluginTools/batch.xsd \
    msb/PluginTools/plugin.xsd \
    msb/PluginTools/settings.xsd \
    msb/XMLTools/Makefile.in

LIBS += \
    -LC:\Qt\Qt5.12.5\5.12.5\mingw73_32\lib/  \
    -llibboost_filesystem-mgw73-mt-d-x32-1_66 \
    -llibboost_system-mgw73-mt-d-x32-1_66 \
    -llibboost_regex-mgw73-mt-d-x32-1_66

win32: LIBS += -L$$PWD/msb/zlib/lib/ -lzdll

INCLUDEPATH += $$PWD/msb/zlib/include
DEPENDPATH += $$PWD/msb/zlib/include
