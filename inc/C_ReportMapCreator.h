#ifndef C_REPORTMAPCREATOR_H
#define C_REPORTMAPCREATOR_H

#include <boost/algorithm/string.hpp>

#include "C_DbHandle.h"
#include "C_Report.h"
#include "C_Settings.h"
#include "appl_data.h"

class C_ReportMapCreator : public C_DbHandle, public C_Report
{

    public:

        struct sMaperitive
        {
            int Id;
            int GebietId;
            std::string mrule;
            std::string height;
            std::string width;
            std::string orientation;
            std::string center;
            std::string scale;
            std::string border_file;
        };

        struct sGebInfo
        {
            int Id;
            std::string Nr;
            std::string Bez;
            bool Act;
            int WEinh;
            std::string WEinh_Date;
            std::string ErzStand;
        };

        struct sNoVisits
        {
            std::string Adresse;
            std::string Name;
            std::string Datum;
            std::string Kommentar;
        };

        struct sHints
        {
            std::string Strasse;
        };

        enum mode
        {
            EXPORT = 0,
            EDIT
        };

    public:
        C_ReportMapCreator(const ApplicationData *ad, const C_Settings *s, int GebId);
        virtual ~C_ReportMapCreator();

        //Public Methods
        void rollout(void);
        void rollout_description(void);
        void rollout_booklet(void);
        void open_with_app(void);

        //map dimension for printing description page
        void set_description_image_size(double width_mm, double height_mm);
        double m_width_mm;
        double m_height_mm;

        std::function<void(std::string)> push_card;

    protected:

    private:

        //Data container
        int GebId;
        sMaperitive Maperitive;
        sGebInfo Gebiet;
        std::vector<sNoVisits> Nichtbesuche;
        std::vector<sHints> Hinweise;
        
        bool m_DSGVO;

        //Private Methods
        void create_mapimg(void);
        void join_mapimg_with_border(void);

        void query_Maperitive(void);
        void query_Gebiete(void);
        void query_Nichtbesuche(void);
        void query_Hinweise(void);

        void create_process_data_map(mode m);
        void start_process_map(mode m);
        void cleanup_map(void);

        void create_process_data_im(void);
        void start_process_im(void);
        void cleanup_im(void);

        void create_process_data_descr(void);
        bool start_process_descr(void);
        void cleanup_descr(void);
        void open_result_descr(std::string result_file);

        void create_process_data_booklet(void);
        bool start_process_booklet(void);
        void cleanup_booklet(void);
        void open_result_booklet(void);

        std::string transform_xy_coordinates(std::string xy_to_cut);
        void file_rename(std::string old_name, std::string new_name);

        void push_card_viewer(void);
};

#endif // C_MAPCREATOR_H
