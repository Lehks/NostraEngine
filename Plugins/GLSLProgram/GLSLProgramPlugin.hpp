#ifndef PLUGIN_GLSL_PROGRAM_PLUGIN_HPP
#define PLUGIN_GLSL_PROGRAM_PLUGIN_HPP

#include "nostraengine/NostraEngine.hpp"

#include "src/material_system/GLSLProgram.hpp"

namespace GLSLProgramPlugin
{
    class GLSLProgramPlugin final : public NOE::NOE_CORE::Plugin
    {
	private:
        //TODO
		//NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_MEM_MNGT::UniquePtr<GLSLProgram>> m_programPtr;

    public:
        /**
         * Initializes the plugin.
         */
		NOE_PLUGIN_FUNC virtual NOE::NOE_CORE::Plugin::InitResult initialize(NOE::NOE_CORE::NostraEngine &engineInstance) override;

        /**
         * Terminates the plugin.
         */
		NOE_PLUGIN_FUNC virtual NOE::NOE_CORE::Plugin::InitResult terminate(NOE::NOE_CORE::NostraEngine &engineInstance) override;

        /**
         * Receives messages from other plugins or the engine itself.
         */
		NOE_PLUGIN_FUNC virtual void receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags) override;
	};
}
#endif