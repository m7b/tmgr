#ifndef C_REPORT_H
#define C_REPORT_H

#include <string>
#include <fstream>
#include <vector>

// workaround for a boost bug..
#ifndef __kernel_entry
#define __kernel_entry
#endif

#include <boost/process.hpp>
#include <boost/process/windows.hpp>

#include "appl_data.h"
#include "C_Settings.h"

#include "helpers.h"

class C_Report
{
    public:
        enum exec_mode
        {
            BLOCKING = 0,
            DETACHED
        };

    public:
        C_Report(const ApplicationData *ad, const C_Settings *s);
        virtual ~C_Report();

        void create_file(std::string &file, std::string &content);
        void exec_cmd(std::vector<std::string> *args);
        void exec_cmd(std::vector<std::string> *args, exec_mode em);
        void cleanup_processing_files(std::vector<std::string> *files_to_delete);
        std::string deform_execution(std::vector<std::string> *args);

        std::function<void(std::string)> callback;

    protected:
        //Settings (application, saveable)
        const ApplicationData *ad;
        const C_Settings *settings;

        //Process data
        std::string process_data;

        //files
        std::string process_data_file;
        std::string process_file;
        std::string output_file;
        std::string report_file;

        void create_process_data_file(std::string pdf);
        void rename_output_file_to_report_file(void);

    private:
        void write_to_console(std::string line);
};

#endif // REPORT_H
