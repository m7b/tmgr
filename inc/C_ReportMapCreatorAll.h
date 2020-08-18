#ifndef C_REPORTMAPCREATORALL_H
#define C_REPORTMAPCREATORALL_H

#include "C_ReportMapCreator.h"

class C_ReportMapCreatorAll : public C_ReportMapCreator
{
    public:
        C_ReportMapCreatorAll(const ApplicationData *ad, const C_Settings *s);
        virtual ~C_ReportMapCreatorAll();

        void rollout_all(void);
        void printout_all(void);

    protected:

    private:
        std::vector<sMaperitive> vec_Maperitive;
        std::vector<sGebInfo> vec_Gebiet;

        void query_Maperitive(void);
        void query_Gebiete(void);

        void create_process_data(void);
        void create_process_data_im(void);
        void start_process(void);
        //void cleanup(void);
        //void open_result(void);

        void create_process_data_printout(void);
        void start_process_printout(void);
        void cleanup_printout(void);
        void open_result_printout(void);

        std::string get_GebNr_from_GebId(int GebId);
        void get_GebData_by_Id(int Id, std::string *Nr, std::string *Bez, std::string *ErzStand);
};

#endif // C_REPORTMAPCREATORALL_H
