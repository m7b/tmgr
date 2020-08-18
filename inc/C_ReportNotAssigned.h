#ifndef C_REPORTNOTASSIGNED_H
#define C_REPORTNOTASSIGNED_H

#include "C_DbHandle.h"
#include "C_Report.h"
#include "C_Settings.h"
#include "appl_data.h"

class C_ReportNotAssigned : public C_DbHandle, public C_Report
{

    public:

        struct sNotAssigned
        {
            std::string GebNr;
            std::string GebBez;
            int WEinh;
            std::string Name;
            std::string AusgDat;
            std::string ZurueckDat;
            std::string Kommentar;
        };

    public:
        C_ReportNotAssigned(const ApplicationData *ad, const C_Settings *s);
        virtual ~C_ReportNotAssigned();

        //Public Methods
        std::vector<std::pair<int, std::string>> *get_sort_choices(void);
        void set_sort_choice(int Sortierung);
        void rollout(void);

    protected:

    private:

        //Choices
        std::vector<std::pair<int, std::string>> Choices;

        //Data container
        std::vector<sNotAssigned> Nichtzuteilungen;
        std::pair<int, std::string> Sortierung;

        //Private Methods
        void init_Choices(void);
        void query_Nichtzuteilungen(void);

        void create_process_data(void);

        void start_process(void);
        void cleanup(void);
        void open_result(void);
};

#endif // C_REPORTNOTASSIGNED_H
