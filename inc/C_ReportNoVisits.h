#ifndef C_REPORTNOVISITS_H
#define C_REPORTNOVISITS_H

#include "C_DbHandle.h"
#include "C_Report.h"
#include "C_Settings.h"
#include "appl_data.h"

class C_ReportNoVisits : public C_DbHandle, public C_Report
{

    public:

        struct sNoVisits
        {
            int Id;
            std::string GebNr;
            std::string GebBez;
            std::string Adresse;
            std::string Name;
            std::string Datum;
            std::string Kommentar;
        };

    public:
        C_ReportNoVisits(const ApplicationData *ad, const C_Settings *s);
        virtual ~C_ReportNoVisits();

        //Public Methods
        std::vector<std::pair<int, std::string>> *get_sort_choices(void);
        void set_sort_choice(int Sortierung);
        void rollout(void);

    protected:

    private:

        //Choices
        std::vector<std::pair<int, std::string>> Choices;

        //Data container
        std::vector<sNoVisits> Nichtbesuche;
        std::pair<int, std::string> Sortierung;
        
        bool m_DSGVO;

        //Private Methods
        void init_Choices(void);
        void query_Nichtbesuche(void);

        void create_process_data(void);

        void start_process(void);
        void cleanup(void);
        void open_result(void);
};

#endif // C_REPORTNOVISITS_H
