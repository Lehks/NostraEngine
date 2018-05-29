#include "nostraengine/material_system/PreProcessor.hpp"

namespace NOT
{
    PreProcessor::PreProcessor(const NOU::NOU_FILE_MNGT::File &f, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &args)
    {
        initializeStaticMembers();
    }

    void PreProcessor::start()
    {

    }

    void PreProcessor::initializeStaticMembers()
    {
        if(s_errors.size() != 0)
        {
            s_errors.map(1, "Test");
        }

        if(s_warnings.size() != 0)
        {
            s_warnings.map(1, "Test");
        }
    }
}