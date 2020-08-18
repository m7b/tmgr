#ifndef C_OSMDOWNLOADER_H
#define C_OSMDOWNLOADER_H

#include "C_Report.h"
#include "C_Settings.h"
#include "helpers.h"
#include "appl_data.h"

class C_OsmDownloader : public C_Report
{

    public:
        C_OsmDownloader(const ApplicationData *ad, const C_Settings *s);
        virtual ~C_OsmDownloader();

        //Public Methods
        void start(std::string *new_osm_file);
};

#endif // C_OSMDOWNLOADER_H
