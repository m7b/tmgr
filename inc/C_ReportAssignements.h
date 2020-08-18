#ifndef C_REPORTASSIGNEMENTS_H
#define C_REPORTASSIGNEMENTS_H

#include "C_DbHandle.h"
#include "C_Report.h"
#include "C_Settings.h"
#include "appl_data.h"

class C_ReportAssignements : public C_DbHandle, public C_Report
{

    public:

        struct sAssignements
        {
            std::string Name;
            std::string GebNr;
            std::string GebBez;
            std::string AusgDat;
        };

    public:
        C_ReportAssignements(const ApplicationData *ad, const C_Settings *s);
        virtual ~C_ReportAssignements();

        //Public Methods
        std::vector<std::pair<int, std::string>> *get_sort_choices(void);
        void set_sort_choice(int Sortierung);
        void rollout(void);

    protected:

    private:

        //Choices
        std::vector<std::pair<int, std::string>> Choices;

        //Data container
        std::vector<sAssignements> Zuteilungen;
        std::pair<int, std::string> Sortierung;

        //Private Methods
        void init_Choices(void);
        void query_Zuteilungen(void);

        void create_process_data(void);

        void start_process(void);
        void cleanup(void);
        void open_result(void);
};

#endif // C_REPORTASSIGNEMENTS_H
