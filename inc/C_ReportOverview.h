#ifndef C_REPORTOVERVIEW_H
#define C_REPORTOVERVIEW_H

#include "C_DbHandle.h"
#include "C_Report.h"

class C_ReportOverview : public C_DbHandle, public C_Report
{

    public:

        struct sGebInfo
        {
            int Id;
            std::string Nr;
            std::string Bez;
            bool Act;
            int WEinh;
            std::string WEinh_Date;
        };

        struct sAktion
        {
            int Id;
            int GebId;
            std::string Name;
            std::string Ausgabe;
            std::string Zurueck;
            std::string Kommentar;
        };

    public:
        C_ReportOverview(const ApplicationData *ad, const C_Settings *s);
        virtual ~C_ReportOverview();

        //Public Methods
        void rollout(void);

    protected:

    private:

        //Data container
        std::vector<sGebInfo> Gebiete;
        std::vector<sAktion> Aktionen;

        //Private Methods
        void query_Gebiete(void);
        void query_Aktionen(void);
        void query_Aktionen_of_Gebiet(int GebId);

        void create_process_data(void);

        void start_process(void);
        void cleanup(void);
        void open_result(void);
};



#endif // C_REPORTOVERVIEW_H
