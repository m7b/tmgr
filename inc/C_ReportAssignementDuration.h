#ifndef C_REPORTASSIGNEMENTDURATION_H
#define C_REPORTASSIGNEMENTDURATION_H

#include "C_DbHandle.h"
#include "C_Report.h"

class C_ReportAssignementDuration : public C_DbHandle, public C_Report
{

    public:

        struct sDataSet
        {
            int Id;
            std::string Nr;
            std::string Bez;
            std::string Name;
            std::string Ausgabe_Date;
            std::string Zurueck_Date;
        };

        struct sDurationData
        {
            int Id;
            std::string Nr;
            std::string Bez;
            std::string Name;
            std::string Anfang_Date;
            bool operator<(const sDurationData& a) const
            {
                return Anfang_Date < a.Anfang_Date;
            }
        };

    public:
        C_ReportAssignementDuration(const ApplicationData *ad, const C_Settings *s);
        virtual ~C_ReportAssignementDuration();

        //Public Methods
        void rollout(void);
        std::tuple<int, int, int> get_stat(void);

    protected:

    private:

        //Data container
        std::vector<sDataSet>      DataSet;
        std::vector<sDurationData> DurationData;

        //Private Methods
        void query_Data(void);
        void filter_Data(void);
        bool is_family(const std::string *a, const std::string *b);

        void create_process_data(void);

        void start_process(void);
        void cleanup(void);
        void open_result(void);
};

#endif // C_REPORTASSIGNEMENTDURATION_H