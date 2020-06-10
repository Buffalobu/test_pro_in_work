#ifndef CII_GCMS_NISTSCH_H
#define CII_GCMS_NISTSCH_H
#include <string>
#include <vector>
namespace CII{
    namespace GCMS{
        namespace NISTSCH{
            namespace NistSearch{
                class NistPathHelper{
                public:
                    static std::string FULL_PATH_TO_SALTS_LIBRARY;
                    static std::string FULL_PATH_TO_MSMS_LIBRARY;
                    static std::string FULL_PATH_TO_WORK_DIR;
                    static std::string Base_Path;
                    static bool IsUseMainLib;
                    static bool IsUseRepLib;
                    static bool IsUseUserLib1;
                    static bool IsUseUserLib2;
                    static std::string FULL_PATH_TO_MAIN_LIBRARY;
                    static std::string FULL_PATH_TO_REPLICATE_LIBRARY;
                    static std::string FULL_PATH_TO_USER_LIBRARY;
                    static std::string FULL_PATH_TO_USER_LIBRARY2;

                    NistPathHelper();

                    static void ModMsSearchAutoimp(std::string filePath);
                    static void Save();
                    static void SaveFilespec();
                };

                class LibMSData{
                public:
                    std::vector<unsigned int> MassNums;
                    std::vector<unsigned int> MassEnergies;
//                    unsigned int* MassNums;
//                    unsigned int* MassEnergies;
                protected:
                    std::string name;
                    std::string formula;

                public:
                    LibMSData();
                    LibMSData(LibMSData const &data);

                    //get set
                    std::string Name() {
                        return name;
                    }
                    std::string Formula() {
                        return formula;
                    }
                    float CalcMaxEnergy();
                protected:
                    void Copy(LibMSData data);
                };

                class NistMSData : LibMSData{
                public:
                    NistMSData();
//                    NistMSData(uint[] mass, uint[] abund);
                    NistMSData(std::vector<unsigned int> mass, std::vector<unsigned int> abund);
                    int LOC ();
                    unsigned int MW();
                    int Match ();
                    int R_Match ();
                    int Prob ();
                    int CAS ();
                    int EPA ();
                    std::string DB ();
                    unsigned int PeakNum ();
//                    global::NISTMSCL2.STDATA StData ();
                    std::string GetChineseNameByCas();
                };


            }
        }
    }
}
#endif // CII_GCMS_NISTSCH_H
