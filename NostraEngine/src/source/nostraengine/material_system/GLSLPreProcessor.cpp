#include "nostraengine/material_system/GLSLPreProcessor.hpp"
#include "nostrautils/NostraUtils.hpp"

namespace NOE::NOE_MATSYS
{
    GLSLPreProcessor::GLSLPreProcessor(NOU::NOU_FILE_MNGT::File *src, NOU::NOU_FILE_MNGT::File *trg):
        PreProcessor(src, trg){ }

    void GLSLPreProcessor::start(NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>)
    {
        
    }
}