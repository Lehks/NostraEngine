#include "nostraengine/material_system/PreProcessor.hpp"


/**
\file material_system/ShaderCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that implements the preprocessor for GLSL.
*/
namespace NOE::NOE_MATSYS
{
    class NOU_CLASS GLSLPreProcessor : public PreProcessor
    {
    private:

    public:
        GLSLPreProcessor(NOU::NOU_FILE_MNGT::File *src = nullptr, NOU::NOU_FILE_MNGT::File *trg = nullptr);
        virtual void start(NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> args) override;
    };
}
/**
\brief This is an interface. Every other PreProcessor implementation has to inherit from this interface.
       This preprocessor has to fulfill any duty and to adjust the sourcecode fitting for the compiler.
*/