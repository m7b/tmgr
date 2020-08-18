#ifndef C_REPORTMAPINLET_H
#define C_REPORTMAPINLET_H

#include "C_DbHandle.h"
#include "C_Report.h"
#include "C_Settings.h"
#include "appl_data.h"

class C_ReportMapInlet : public C_DbHandle, public C_Report
{

    public:

        struct sMapInfo
        {
            int Id;
            std::string Nr;
            std::string Bez;
            int Act;
            int WEinh;
            std::string WEinhStand;
            std::string Name;
            std::string Ausgabe;
            std::string Zurueck;
            std::string Kommentar;
        };

        struct sNoVisits
        {
            int Id;
            std::string Adresse;
            std::string Name;
            std::string Datum;
            std::string Kommentar;
        };

    public:
        C_ReportMapInlet(const ApplicationData *ad, const C_Settings *s, int GebId);
        virtual ~C_ReportMapInlet();

        //Public Methods
        void rollout(void);

    protected:

    private:

        //Data container
        int GebId;
        sMapInfo MapInfo;
        std::vector<sNoVisits> NoVisits;
        std::vector<std::string> Streets;
        
        bool m_DSGVO;

        //Private Methods
        void init_Choices(void);
        void query_MapInfo(void);
        void query_NoVisits(void);
        void query_Streets(void);

        void create_process_data(void);

        void start_process(void);
        void cleanup(void);
        void open_result(void);
};

#endif // C_REPORTMAPINLET_H
